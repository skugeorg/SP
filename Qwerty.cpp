namespace virt {
namespace lights {

/* Базовый класс источника света */
class light
{
public:
  DBL Cc, Cl, Cq; // Коэффициенты затухания (constant, linear, quadratic)
  vec3 Color;     // Цвет источника

  // 1. Обязательно виртуальный деструктор!
  virtual ~light() = default; 

  // 2. Чисто виртуальная функция (= 0), чтобы заставить наследников её реализовать
  virtual DBL Shadow(const vec3 &P, light_info *L) = 0; 
};

/* Точечный источник света (Point Light) */
class point : public light
{
  vec3 Pos; // Позиция источника
public:
  point(const vec3 &P, const vec3 &C, DBL c0 = 1.0, DBL c1 = 0.0, DBL c2 = 0.0)
  {
    Pos = P;
    Color = C;
    Cc = c0; Cl = c1; Cq = c2;
  }

  // 3. Ключевое слово override говорит компилятору: "Я переопределяю виртуальную функцию"
  DBL Shadow(const vec3 &P, light_info *L) override
  {
    L->L = Pos - P;                // Вектор от точки к источнику
    L->Dist = L->L.Length();       // Расстояние до источника
    L->L = L->L / L->Dist;         // Нормируем направление
    L->Color = Color;
    return 1.0; // 1.0 означает, что источник "виден" (саму проверку пересечения лучом делает scene::Shade)
  }
};

/* Направленный источник света (Directional Light, например, Солнце) */
class dir : public light
{
  vec3 Dir; // Направление, КУДА светит свет (лучи идут параллельно)
public:
  // D - направление света (например, vec3(0, -1, 0) - свет сверху вниз)
  dir(const vec3 &D, const vec3 &C)
  {
    Dir = -D.Normalized(); // Инвертируем, чтобы вектор указывал НА источник (как требует формула освещения)
    Color = C;
    // Для направленного света затухания нет, расстояние бесконечно
    Cc = 1.0; Cl = 0.0; Cq = 0.0; 
  }

  DBL Shadow(const vec3 &P, light_info *L) override
  {
    L->L = Dir;
    L->Dist = Infinity; // Бесконечное расстояние
    L->Color = Color;
    return 1.0;
  }
};

} // namespace lights
} // namespace virt
