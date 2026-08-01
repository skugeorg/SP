/*************************************************************
 * Copyright (C) 2026
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : rt_def.h
 * PURPOSE     : Ray Tracing project.
 *               Shape class declaration module.
 * PROGRAMMER  : CGSG-SummerCamp'2026.
 *               GS6.
 * LAST UPDATE : 01.08.2026.
 * NOTE        : Module namespace 'gert'.
 */

#ifndef __rt_def_h_
#define __rt_def_h_

#include "def.h"
#include "lights/light.h"
#include <vector>
#include <thread>
#include <atomic>

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
    DBL T = -1;    // Ray distance (Исправлен варнинг C26495)
    vec3 N;        // Normal at intersection point
    BOOL IsN {};   // Normal evaluation flag
    vec3 P;        // Ray point
    BOOL IsP {};   // Ray point evaluation flag
    shape *Shp {}; // Intersected shape pointer
  }; /* End of 'intr' structure */

  class surface
  {
  public:
    vec3 Ka, Kd, Ks; // ambient, diffuse, specular
    DBL Ph;          // Bui Tong Phong coefficient
    vec3 Kr, Kt;     // reflected, transmitted
  };
 
  class envi
  {
  public:
    DBL RefractionCoef;  // Refraction coefficient
    DBL Decay;           // Environment media decay coefficient
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
    /* Class destructor */
    virtual ~shape( VOID )
    {
    } /* End of '~shape' function */
 
    /* Get ray shape intersection function. */
    virtual BOOL Intersect( const ray &R, intr *I )
    {
      return FALSE;
    } /* End of 'Intersect' function */
 
    /* Get shape normal function. */
    virtual VOID GetNormal( intr *I )
    {
    } /* End of 'GetNormal' function */
  }; /* End of 'shape' class */

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

    stock<shape *> Shapes; // shape data struct
    stock<lights::light *> Lights; // light data struct

    /* default class dctor */
    ~scene( VOID )
    {
      for (auto shp : Shapes)
        delete shp;
      for (auto lig : Lights)
        delete lig;
    } /* End of '~scene' function */

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

    /* Check intersection with any scene shape function. */
    BOOL Intersect( const ray &R, intr *Intr = nullptr )
    {
      intr ClosestI;
      DBL MinT = Infinity;
      BOOL IsIntersected = FALSE;

      /* Find closest intersection among all shapes */
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

      /* Copy closest intersection data to output store if needed */
      if (IsIntersected && Intr != nullptr)
        *Intr = ClosestI;

      return IsIntersected;
    } /* End of 'Intersect' function */

    /* Shade pixel location via material lightning function. */
    vec3 Shade( const ray &R, intr *I )
    {
      const vec3 Ka = vec3(0.1);
      const vec3 Kd = vec3(0.7);
      const vec3 Ks = vec3(0.3);
      constexpr DBL Ph = 30.0;
 
      vec3 N = I->N;
      DBL vn = N & R.Dir;
      if (vn > 0)
        N = -N, vn = -vn;
 
      vec3 color(0);
      
      // 1. Ambient component
      color += Ka;
 
      // 2. Accounting light sources
      for (auto lig : Lights)
      {
        lights::light_info light;
        
        DBL Atten = lig->Shadow(I->P, &light);
        if (Atten < Threshold)
          continue;

        ray LightRay(I->P + light.L * Threshold, light.L);
        
        intr ShadowIntr;
        if (Intersect(LightRay, &ShadowIntr))
        {
          if (ShadowIntr.T > Threshold && ShadowIntr.T < light.Dist)
            continue;
        }

        if (DBL nl = N & light.L; nl > Threshold)
          color += Kd * light.Color * nl * Atten;
 
        vec3 Refl = R.Dir - N * (2 * vn);
        if (DBL rl = Refl & light.L; rl > Threshold)
          color += Ks * light.Color * pow(rl, Ph) * Atten;
      }
      
      return color;
    } /* End of 'Shade' function */

    /* Trace single ray path function. */
    vec3 Trace( const ray &R )
    {
      intr Intr;
      if (IsToBeStop)
        return vec3(0);
      if (Intersect(R, &Intr))
      {
        if (!Intr.IsP)
        {
          Intr.P = R.Org + R.Dir * Intr.T;
          Intr.IsP = TRUE;
        }
        if (!Intr.IsN)
          Intr.Shp->GetNormal(&Intr);
        return Shade(R, &Intr);
      }
      else
        return vec3(0.3, 0.4, 0.5);
    } /* End of 'Trace' function */

    /* Render camera frame buffer function. */
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
          });
      for (INT i = 0; i < n; i++)
        Ths[i].join();
    } /* End of 'Render' function */
  }; /* End of 'scene' class */
} /* end of 'gert' namespace */

#endif /* __rt_def_h_ */
