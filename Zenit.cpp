/***********************************************************************
* Copyright (C) 2026
* Computer Graphics Support Group of 30 Phys-Math Lyceum
***********************************************************************/
/* FILE NAME : rt_def.h
* PURPOSE : Ray Tracing project.
* Shape class declaration module.
* PROGRAMMER : CGSG-SummerCamp'2026.
* GS6.
* LAST UPDATE : 02.08.2026.
* NOTE : Module namespace 'gert'.
*
* No part of this file may be changed without agreement of
* Computer Graphics Support Group of 30 Phys-Math Lyceum
*/

#ifndef __rt_def_h_
#define __rt_def_h_

#include "def.h"
#include "frame.h"
#include "lights/light.h"

/* Project namespace */
namespace gert
{

/* Geometry calculation threshold value */
inline const DBL Threshold = 1e-6;
inline const DBL Infinity = 1e12;

class shape;

/* Intersection store class */
struct intr
{
  DBL T = -1;       // Ray distance
  vec3 N;           // Normal at intersection point
  BOOL IsN = FALSE; // Normal evaluation flag
  vec3 P;           // Ray point
  BOOL IsP = FALSE; // Ray point evaluation flag
  shape *Shp = nullptr; // Intersected shape pointer
};

/* Coefficient class with usage flag */
class coef
{
public:
  vec3 K;
  BOOL IsUsage;

  coef( VOID ) : IsUsage(FALSE) { }
  
  coef( DBL C ) : K(C, C, C), IsUsage(C > Threshold) { }
  
  coef( DBL X, DBL Y, DBL Z ) :
    K(X, Y, Z),
    IsUsage(X > Threshold || Y > Threshold || Z > Threshold) { }
  
  coef( const vec3 &C ) : coef(C.X, C.Y, C.Z) { }

  coef & operator=( const vec3 &C )
  {
    K = C;
    IsUsage = C.X > Threshold || C.Y > Threshold || C.Z > Threshold;
    return *this;
  }

  operator vec3( VOID ) const { return K; }
};

/* Surface material properties */
class surface
{
public:
  coef Ka, Kd, Ks; // ambient, diffuse, specular
  DBL Ph;          // Phong coefficient
  coef Kr, Kt;     // reflected, transmitted
};

/* Environment media properties */
class envi
{
public:
  DBL RefractionCoef; // Refraction coefficient
  DBL Decay;          // Environment media decay coefficient
};

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

/* Geometry shape handle class */
class shape
{
public:
  surface Surf;
  envi Env;

  virtual ~shape( VOID ) { }

  virtual BOOL Intersect( const ray &R, intr *I )
  {
    return FALSE;
  }

  virtual VOID GetNormal( intr *I ) { }

  virtual VOID GetShadeInfo( shade_info *Sh, intr *I )
  {
    Sh->Shp = this;
    Sh->P = I->P;
    Sh->N = I->N;
    Sh->Surf = this->Surf;
    Sh->Env = this->Env;
    Sh->MapP = I->P;
    Sh->Du = vec3(1, 0, 0);
    Sh->Dv = vec3(0, 0, -1);
    // Здесь можно добавить модификаторы для конкретных наследников
  }
};

/* Scene handle class */
class scene
{
public:
  // Sync flags
  std::atomic_bool IsRenderActive = FALSE;
  std::atomic_bool IsToBeStop = FALSE;
  std::atomic_bool IsReadyToFinish = TRUE;
  std::atomic_int StartRow = 0;

  stock<shape *> Shapes;
  stock<lights::light *> Lights;

  // Scene environment settings
  vec3 AmbientColor = vec3(0.1);
  vec3 BackgroundColor = vec3(0.3, 0.4, 0.5);
  vec3 FogColor = vec3(0.5, 0.5, 0.5);
  DBL FogStart = Infinity;
  DBL FogEnd = Infinity;
  INT MaxRecLevel = 5;
  envi Air{1.0, 0.0}; // RefractionCoef = 1.0, Decay = 0.0

  ~scene( VOID )
  {
    for (auto shp : Shapes) delete shp;
    for (auto lig : Lights) delete lig;
  }

  scene & operator<<( shape *Shp )
  {
    Shapes << Shp;
    return *this;
  }

  scene & operator<<( lights::light *Lig )
  {
    Lights << Lig;
    return *this;
  }

  BOOL Intersect( const ray &R, intr *Intr = nullptr )
  {
    intr ClosestI;
    DBL MinT = Infinity;
    BOOL IsIntersected = FALSE;

    for (INT i = 0; i < Shapes.size(); i++)
    {
      intr CurrentI;
      if (Shapes[i]->Intersect(R, &CurrentI))
      {
        if (CurrentI.T < MinT && CurrentI.T > Threshold)
        {
          MinT = CurrentI.T;
          ClosestI = CurrentI;
          IsIntersected = TRUE;
        }
      }
    }

    if (IsIntersected && Intr != nullptr)
      *Intr = ClosestI;

    return IsIntersected;
  }

  vec3 Trace( const ray &R, const envi &Media, DBL Weight, INT RecLevel )
  {
    vec3 color = BackgroundColor;
    if (IsToBeStop)
      return color;

    if (RecLevel < MaxRecLevel)
    {
      intr closest_intersection;
      if (Intersect(R, &closest_intersection))
      {
        if (!closest_intersection.IsP)
        {
          closest_intersection.P = R.Org + R.Dir * closest_intersection.T;
          closest_intersection.IsP = TRUE;
        }
        if (!closest_intersection.IsN)
          closest_intersection.Shp->GetNormal(&closest_intersection);

        shade_info sh;
        closest_intersection.Shp->GetShadeInfo(&sh, &closest_intersection);
        
        color = Shade(R.Dir, Media, &sh, Weight, RecLevel);
        
        // Учёт затухания в среде (например, туман или объёмный материал)
        color *= exp(-closest_intersection.T * Media.Decay);
        
        // >>> Если будет туман, логику можно добавить здесь
      }
    }
    return color;
  }

  vec3 Shade( const vec3 &V, const envi &Env, shade_info *Sh, DBL Weight, INT RecLevel )
  {
    vec3 res_color(0);
    DBL vn = V & Sh->N;
    
    // Check: enter or leave
    BOOL IsEnter = TRUE;
    if (vn > 0)
    {
      vn = -vn;
      Sh->N = -Sh->N;
      IsEnter = FALSE;
    }
    
    // Reflected ray evaluation
    vec3 R = V - Sh->N * (2 * vn);
    
    // Accounting ambient reflection
    if (Sh->Surf.Ka.IsUsage)
      res_color += Sh->Surf.Ka.K * AmbientColor;
    
    // Accounting light sources
    for (auto lig : Lights)
    {
      lights::light_info light;
      DBL s = lig->Shadow(Sh->P, &light);
      s *= mth::Min(1.0, 1.0 / (lig->Cc + lig->Cl * light.Dist + lig->Cq * light.Dist * light.Dist));
      
      if (s < Threshold)
        continue;
      
      // Shadow cast
      ray LightRay(Sh->P + light.L * Threshold, light.L);
      intr ShadowIntr;
      if (Intersect(LightRay, &ShadowIntr))
      {
        if (ShadowIntr.T > Threshold && ShadowIntr.T < light.Dist)
          continue; // Simple shadows
      }
      
      if (s > Threshold)
      {
        // Accounting diffuse reflection
        if (DBL nl = Sh->N & light.L; nl > Threshold)
        {
          res_color += Sh->Surf.Kd.K * light.Color * nl * s;
          
          // Accounting specular reflection
          if (DBL rl = R & light.L; rl > Threshold)
            res_color += Sh->Surf.Ks.K * light.Color * pow(rl, Sh->Surf.Ph) * s;
        }
      }
    }
    
    // Reflected ray accounting
    if (Sh->Surf.Kr.IsUsage && coef(Sh->Surf.Kr.K * Weight).IsUsage)
    {
      res_color += Trace(ray(Sh->P + R * Threshold, R), Env, Weight * Sh->Surf.Kr.K.MaxC(), RecLevel + 1) * Sh->Surf.Kr.K * Weight;
    }
    
    // Refracted ray accounting
    if (Sh->Surf.Kt.IsUsage && coef(Sh->Surf.Kt.K * Weight).IsUsage)
    {
      DBL eta = IsEnter ? Sh->Env.RefractionCoef / Env.RefractionCoef : Air.RefractionCoef / Env.RefractionCoef;
      
      // Проверка на полное внутреннее отражение (TIR)
      // Формула исправлена на корректную: 1.0 - sin^2(theta_t)
      DBL factor = 1.0 - (1.0 - vn * vn) * eta * eta;
      
      if (factor > Threshold)
      {
        vec3 T = V * eta + Sh->N * (-vn * eta - sqrt(factor));
        res_color += Trace(ray(Sh->P + T * Threshold, T), IsEnter ? Sh->Env : Air, Weight * Sh->Surf.Kt.K.MaxC(), RecLevel + 1) * Sh->Surf.Kt.K * Weight;
      }
    }
    
    return res_color;
  }

  VOID Render( camera &Cam, frame &Frm )
  {
    if (Frm.W <= 0 || Frm.H <= 0)
      return;
    
    Cam.Resize(Frm.W, Frm.H);
    INT n = std::thread::hardware_concurrency() - 1;
    if (n < 1) n = 1;
    
#ifndef NDEBUG
    n = 1;
#endif /* NDEBUG */
    
    std::vector<std::thread> Ths;
    Ths.resize(n);
    StartRow = 0;
    
    for (INT i = 0; i < n; i++)
    {
      Ths[i] = std::thread(
        [&]()
        {
          INT y = StartRow++;
          while (y < Frm.H)
          {
            for (INT x = 0; x < Frm.W; x++)
            {
              ray r = Cam.FrameRay(x + 0.5, y + 0.5);
              // Начальный вызов трассировки с воздухом, весом 1.0 и уровнем рекурсии 0
              vec3 c = Trace(r, Air, 1.0, 0);
              Frm.PutPixel(x, y, frame::ToRGB(c.X, c.Y, c.Z));
            }
            y = StartRow++;
          }
        });
    }
    
    for (INT i = 0; i < n; i++)
      Ths[i].join();
  }
};

/* Default materials library */
inline std::map<std::string, surface> MtlLib = {
  {"Black Plastic", {{0.0, 0.0, 0.0}, {0.01, 0.01, 0.01}, {0.5, 0.5, 0.5}, 32.0, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}},
  {"Glass", {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 1.0, 1.0}, 100.0, {0.9, 0.9, 0.9}, {0.9, 0.9, 0.9}}},
  // ... остальные материалы можно инициализировать аналогично, добавляя значения для Kr и Kt
};

} /* end of 'gert' namespace */

#endif /* __rt_def_h_ */
gert::sphere *sph = new gert::sphere(vec3(0, 0, -5), 2.0);
sph->Surf = MtlLib["Glass"];       // Назначаем материал
sph->Env.RefractionCoef = 1.5;     // Коэффициент преломления стекла
sph->Env.Decay = 0.0;              // Затухание внутри объекта
RT.Scene << sph;                   // Добавляем в сцену
