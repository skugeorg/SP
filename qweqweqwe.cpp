
	2
 
 
 

OPS
CGSG
forever
1
СБ
АВГ
Log as:	Скулябин Георгий	 :: User:	cgsg264@ad.pml30.ru	 :: 	
Computer Graphics Support Group
Current working. August 2026. | CGSG Camp # 76 is done (Вырица, Агробиостанция, октябрь-ноябрь, 2025) | CGSG Camp # 77 is done (Вырица, Агробиостанция, январь, 2026)
CGSG Camp # 78 is done (Вырица, Агробиостанция, январь, 2026) | [CGSG'Ad TCA | CGSG'Sr TAM | CGSG'Jr TTV]

Главная
Информация о программистских лагерях CGSG
Фотос
Материалы
Проекты CGSG
CGSG Source File Browser
File: RT_RayTracingConcurrencyIllumination.cpp

Ray Tracing Concurrency
 
namespace virt
{
  /* Scene handle class */
  class scene
  {
  public:
    // Sync flags
    std::atomic_bool IsRenderActive = FALSE;
    std::atomic_bool IsToBeStop = FALSE;
    std::atomic_bool IsReadyToFinish = TRUE;
 
    // Store rendering line
    std::atomic_int StartRow = 0;
    . . .
 
    vec3 Trace( const ray &V )
    {
      . . .
      if (IsToBeStop)
        return vec3(0);
      . . .
    } /* End of 'Trace' function*/
 
    VOID Render( camera &Cam, frame &Frm )
    {
      Cam.Resize(Frm.W, Frm.H);
      INT n = std::thread::hardware_concurrency() - 1;
#ifndef NDEBUG
      n = 1;
#endif /* NDEBUG */
      std::vector<std::thread> Ths;
      Ths.resize(n);
      StartRow = 0;
      for (INT i = 0; i < n; i++)
        Ths[i] = std::thread(
          [&]( VOID )
          {
            INT y = StartRow++;
            while (y < Frm.H)
            {
              for (INT x = 0; x < Frm.W; x++)
              {
                ray r = Cam.FrameRay(x + 0.5, y + 0.5);
                vec3 c = Trace(r);
                Frm.PutPixel(x, y, frame::ToRGB(c.X, c.Y, c.Z));
              }
              y = StartRow++;
            }
          }
      for (INT i = 0; i < n; i++)
        Ths[i].join();
      . . .
    } /* End of 'Render' function*/
  };
}
 
namespace virt
{
  /* Window handle class */
  class rt_win : public win
  {
    . . .
  };
}
 
/* WM_KEYDOWN/WM_KEYUP window message handle function.
 * ARGUMENTS:
 *   - virtual key number (see VK_***, 'A', ..., '0', ...):
 *       UINT Key;
 *   - press flag:
 *       BOOL IsPress;
 *   - autorepeat counter:
 *       INT RepeatCount;
 *   - shift/control etc key states bits (see MK_***):
 *       UINT ShiftKeysFlags;
 * RETURNS: None.
 */
VOID virt::rt_win::OnKey( UINT Key, BOOL IsPress, INT RepeatCount,
                          UINT ShiftKeysFlags )
{
  if (Key == VK_ESCAPE)
    if (Scene.IsRenderActive)
      Scene.IsToBeStop = TRUE;
    else
      DestroyWindow(hWnd);
  else if (Key == 'C')
    Frm.Fill(0x00303030);
  else if (Key == 'R')
  {
    if (Scene.IsRenderActive)
      return;
 
    Scene.IsRenderActive = TRUE;
    Scene.IsToBeStop = FALSE;
    Scene.IsReadyToFinish = FALSE;
 
    std::cout << std::endl << "Start render scene at ";
    std::time_t t_c =
      std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cout << std::put_time(std::localtime(&t_c), "%H:%M:%S %d.%m.%Y\n");
 
    std::thread Th;
    Th = std::thread(
      [this]( VOID )
      {
        auto start_time = std::chrono::high_resolution_clock::now();
 
        Scene.Render(Cam, Frm);
 
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = end_time - start_time;
        auto hours = std::chrono::duration_cast<std::chrono::hours>(duration);
        duration -= hours;
        auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
        duration -= minutes;
        auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
        duration -= seconds;
        auto milliseconds =
          std::chrono::duration_cast<std::chrono::milliseconds>(duration);
        duration -= milliseconds;
        std::cout << std::format("Frame render time in [{}:{}:{}.{}]\n",
          hours.count(), minutes.count(), seconds.count(), milliseconds.count());
 
        std::cout << "End render scene at ";
        std::time_t t_c =
          std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::cout << std::put_time(std::localtime(&t_c), "%H:%M:%S %d.%m.%Y\n");
 
        InvalidateRect(hWnd, NULL, FALSE);
        UpdateWindow(hWnd);
 
        // Save to TGA
        //std::tuple<INT, INT, INT> Dur
        //{
        //  hours.count(), minutes.count(), seconds.count()
        //};
        //Frm.AutosaveTGA("CGSG forever!!!", Dur);
 
        Scene.IsToBeStop = FALSE;
        Scene.IsReadyToFinish = TRUE;
        Scene.IsRenderActive = FALSE;
      });
    Th.detach();
  }
} /* End of 'virt::rt_win::OnKey' function */
 
Концовка в WinMain:
  if (RT.Scene.IsRenderActive)
  {
    RT.Scene.IsToBeStop = TRUE;
    std::cout << "\nWait rendering threads are finished\n";
    while (!RT.Scene.IsReadyToFinish)
      ;
    std::cout << "\nWaiting is finished\n";
  }
  std::cout << "\nFinish...\n";
 
 
Illumination & Shading:
 
class surface
{
  vec3 Ka, Kd, Ks; // ambient, diffuse, specular
  DBL Ph;          // Bui Tong Phong coefficient
  vec3 Kr, Kt;     // reflected, transmitted
};
 
среда прохождения:
 
class envi
{
  DBL
    RefractionCoef,  // Refraction coefficient
    Decay;           // Environment media decay coefficient
};
 
источники света:
 
class light
{
  DBL Cc, Cl, Cq; // Attenuation coefficients
  vec3 Color;     // Light source color
 
  virtual DBL Shadow( const vec3 &P, light_info *L );
};
 
 
информация по источнику (возврат):
class light_info
{
  vec3 L;     // Light source direction
  vec3 Color; // Light source color
  DBL Dist;   // Distance to light source
};
 
изменения в scene:
vec3 AmbientColor, BackgroundColor, FogColor(?);
DBL FogStart(?), FogEnd(?);
stock<light *> Lights;
scene & operator<<( light *Lgh );
 
про рекурсию и среду:
 
INT RecLevel, MaxRecLevel;
 
envi Air;
 
Trace:
 
vec3 Trace( const ray &R, const evni &Media, DBL Weight, INT RecLevel )
{
  vec3 color = Background;
 
  if (RecLevel < MaxRecLevel)
  {
    . . .look for closest intersection + GetNormal ...
    >>> если будет туман, то добавлять сюда
    color = Shade(R.Dir, Media, &closest_intersection, Weight, RecLevel);
    ???
    color *= exp(-closest_intersection.T * Media.Decay);
  }
  return color;
}
 
 
  /* Shading store info type */
  class shade_info
  {
  public:
    vec3 P;       // Point of shading evaluation
    vec3 N;       // Point normal
    surface Surf; // Surface material
    envi Env;     // Object media environment
 
    vec3 MapP;    // Mapping point of shading evaluation
    vec3 Du, Dv;  // Tangent vectors
    shape *Shp;   // Shape pointer
  };
 
!!! укаждого объекта добавляем виртуальную функцию:
 
shape:
 
    virtual VOID GetShadeInfo( shade_info *Sh, intr *I )
    {
      Sh->Shp = this;
      Sh->P = I->P;
      Sh->N = I->N;
      Sh->Surf = I->Shp->Surf;
      Sh->Env = I->Shp->Env;
      Sh->MapP = I->P;
      Sh->Du = vec3(1, 0, 0);
      Sh->Dv = vec3(0, 0, -1);
 
      // тут добавим модификаторы
    }
 
изменим Trace:
    color = Shade(R.Dir, Media, &closest_intersection, Weight, RecLevel);
 
--->
  shade_info sh;
  closest_intersection.Shp->GetShadeInfo(&sh, &closest_intesection);
  color = Shade(R.Dir, &sh, Weight, RecLevel);
 
заменим vec3 на coef в surface:
 
class surface
{
  vec3 Ka, Kd, Ks; // ambient, diffuse, specular
  DBL Ph;          // Bui Tong Phong coefficient
  vec3 Kr, Kt;     // reflected, transmitted
};
 
станет:
 
class surface
{
  coef Ka, Kd, Ks; // ambient, diffuse, specular
  DBL Ph;          // Bui Tong Phong coefficient
  coef Kr, Kt;     // reflected, transmitted
};
 
  class coef
  {
  public:
    // Coefficient color value
    vec3 K;
 
    // Coefficient usage flag
    BOOL IsUsage;
 
    /* Class constructor */
    coef( VOID ) : IsUsage(FALSE)
    {
    } /* End of 'coef' function */
 
 
    /* Class constructor.
     * AGUMENTS:
     *   - color all components value:
     *       DBL C;
     */
    coef( DBL C ) : K(C, C, C), IsUsage(C > Threshold)
    {
    } /* End of 'coef' function */
 
 
    /* Class constructor.
     * AGUMENTS:
     *   - color component values:
     *       DBL X, Y, Z;
     */
    coef( DBL X, DBL Y, DBL Z ) :
      K(X, Y, Z),
      IsUsage(X > Threshold || Y > Threshold || Z > Threshold)
    {
    } /* End of 'coef' function */
 
    /* Class constructor.
     * AGUMENTS:
     *   - color value:
     *       const vec3 &C;
     */
    coef( const vec3 &C ) : coef(C.X, C.Y, C.Z)
    {
    } /* End of 'coef' function */
 
 
    /* Coefficient set from vec3 function.
     * AGUMENTS:
     *   - color value:
     *       const vec3 &C;
     * RETURNS:
     *   (coef &) self reference.
     */
    coef & operator=( const vec3 &C )
    {
      K = C;
      IsUsage = C.X > Threshold ||
                C.Y > Threshold ||
                C.Z > Threshold;
      return *this;
    } /* End of 'operator=' constructor */
 
    /* Coefficient to vec3 color conversion function.
     * AGUMENTS: None.
     * RETURNS:
     *   (vec3) color value.
     */
    operator vec3( VOID ) const
    {
      return K;
    } /* End of 'operator color' function */
  };
 
vec3 Shade( const vec3 &V, const envi &Env, shade_info *Sh,
            DBL Weight, INT RecLevel )
{
  // Result color
  vec3 res_color(0);
 
  DBL vn = V & Sh->N;
  // Check: enter or leave
  BOOL IsEnter = TRUE;
  if (vn > 0)
  {
    // leave
    vn = -vn;
    Sh->N = -Sh->N;
    IsEnter = FALSE;
  }
 
  // Reflected ray evaluation
  vec3 R = V - Sh->N * (2 * vn);
 
  // Accounting ambient reflection
  if (Sh->Surf.Ka.IsUsage)
    res_color += Sh->Surf.Ka.K * Ambient;
 
 
  // Accounting light sources
  for (auto lig : Lights)
  {
    light_info light;
    DBL s = lig->Shadow(Sh->P, &light);
    s *=
      mth::Min(1.0,
        1 / (lig->Cc + lig->Cl * light.Dist + lig->Cq * light.Dist * light.Dist));
    if (s < Threshold)
      continue;
 
    // Shadow cast
    ray LightRay(Sh->P + light.L * Threshold, light.L);
 
    // SIMPLE SHADOWS
    if (Intertsect(LightRay))
      continue;
 
    // Light reflection
    if (s > Threshold)
    {
      // Accounting diffuse reflection
      if (DBL nl = Sh->N & light.L; nl > Threshold)
      {
        res_color += Sh->Surf.Kd.K * light.Color * nl * s;
 
        // Accounting specular reflection
        if (DBL rl = R & light.L;rl > Threshold)
          res_color += Sh->Surf.Ks.K * light.Color * pow(rl, Sh->Surf.Ph) * s;
      }
    }
  }
 
  // Reflected ray accounting
  if (Sh->Surf.Kr.IsUsage && coef(Sh->Surf.Kr.K * Weight).IsUsage)
    res_color += Trace(ray(Sh->P + R * Threshold, R), Env,
      Weight * Sh->Surf.Kr.K.MaxC(), RecLevel + 1) * Sh->Surf.Kr.K * Weight;
 
  // Refracted ray accounting
  if (Sh->Surf.Kt.IsUsage && coef(Sh->Surf.Kt.K * Weight).IsUsage)
  {
    DBL
      eta =
        IsEnter ?
          Sh->Env.RefractionCoef / Env.RefractionCoef :
          Air.RefractionCoef / Env.RefractionCoef,
      factor = (1 - (1 - vn * vn)) * eta * eta;
    // Check for full inner reflection
    if (factor > Threshold)
    {        
      vec3 T = V * eta + Sh->N * (-vn * eta - sqrt(factor));
 
      res_color += Trace(ray(Sh->P + T * Threshold, T), IsEnter ? Sh->Env : Air,
        Weight * Sh->Surf.Kt.K.MaxC(), RecLevel + 1) * Sh->Surf.Kt.K * Weight;
    }
  }
  return res_color;
}
 
src/rt/lights/*** point.h dir.h
namespaces:
 
virt::lights::point
 
Copyright © 1992-2026 Computer Graphics Support Group of 30 Phys-Math Lyceum ip:192.168.8.242 ::: Log as: Скулябин Георгий (cgsg264@ad.pml30.ru)
