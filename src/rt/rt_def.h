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

  inline map<string, surface> MtlLib
  {
    {"Black Plastic",   {{0.0, 0.0, 0.0},             {0.01, 0.01, 0.01},           {0.5, 0.5, 0.5},               32}},
    {"Brass",           {{0.329412,0.223529,0.027451}, {0.780392,0.568627,0.113725}, {0.992157,0.941176,0.807843}, 27.8974}},
    {"Bronze",          {{0.2125,0.1275,0.054},       {0.714,0.4284,0.18144},       {0.393548,0.271906,0.166721},  25.6}},
    {"Chrome",          {{0.25, 0.25, 0.25},          {0.4, 0.4, 0.4},              {0.774597, 0.774597, 0.774597}, 76.8}},
    {"Copper",          {{0.19125,0.0735,0.0225},     {0.7038,0.27048,0.0828},      {0.256777,0.137622,0.086014},  12.8}},
    {"Gold",            {{0.24725,0.1995,0.0745},     {0.75164,0.60648,0.22648},    {0.628281,0.555802,0.366065},  51.2}},
    {"Peweter",         {{0.10588,0.058824,0.113725}, {0.427451,0.470588,0.541176}, {0.3333,0.3333,0.521569},      9.84615}},
    {"Silver",          {{0.19225,0.19225,0.19225},   {0.50754,0.50754,0.50754},    {0.508273,0.508273,0.508273},  51.2}},
    {"Polished Silver", {{0.23125,0.23125,0.23125}, {0.2775,0.2775,0.2775},       {0.773911,0.773911,0.773911},  89.6}},
    {"Turquoise",       {{0.1, 0.18725, 0.1745},      {0.396, 0.74151, 0.69102},    {0.297254, 0.30829, 0.306678}, 12.8}},
    {"Ruby",            {{0.1745, 0.01175, 0.01175},  {0.61424, 0.04136, 0.04136},  {0.727811, 0.626959, 0.626959}, 76.8}},
    {"Polished Gold",   {{0.24725, 0.2245, 0.0645},   {0.34615, 0.3143, 0.0903},    {0.797357, 0.723991, 0.208006}, 83.2}},
    {"Polished Bronze", {{0.25, 0.148, 0.06475},    {0.4, 0.2368, 0.1036},        {0.774597, 0.458561, 0.200621}, 76.8}},
    {"Polished Copper", {{0.2295, 0.08825, 0.0275}, {0.5508, 0.2118, 0.066},      {0.580594, 0.223257, 0.0695701}, 51.2}},
    {"Jade",            {{0.135, 0.2225, 0.1575},     {0.135, 0.2225, 0.1575},      {0.316228, 0.316228, 0.316228}, 12.8}},
    {"Obsidian",        {{0.05375, 0.05, 0.06625},    {0.18275, 0.17, 0.22525},     {0.332741, 0.328634, 0.346435}, 38.4}},
    {"Pearl",           {{0.25, 0.20725, 0.20725},    {1.0, 0.829, 0.829},          {0.296648, 0.296648, 0.296648}, 11.264}},
    {"Emerald",         {{0.0215, 0.1745, 0.0215},    {0.07568, 0.61424, 0.07568},  {0.633, 0.727811, 0.633},       76.8}},
    {"Black Plastic",   {{0.0, 0.0, 0.0},             {0.01, 0.01, 0.01},           {0.5, 0.5, 0.5},                32.0}},
    {"Black Rubber",    {{0.02, 0.02, 0.02},          {0.01, 0.01, 0.01},           {0.4, 0.4, 0.4},                10.0}},
  };
} /* end of 'gert' namespace */

#endif /* __rt_def_h_ */
