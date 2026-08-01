/*************************************************************
 * Copyright (C) 2026
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : sphere.h
 * PURPOSE     : Ray Tracing project.
 *               Shapes library.
 *               Sphere class declaration module.
 * PROGRAMMER  : CGSG-SummerCamp'2026.
 *               GS6.
 * LAST UPDATE : 31.07.2026.
 * NOTE        : Module namespace 'gert'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
 
#ifndef __sphere_h_
#define __sphere_h_
 
#include "../rt_def.h"
 
/* Project namespace */
namespace gert
{
  /* Sphere class */
  class sphere : public shape
  {
  private:
    vec3 C; // center point
    DBL R;  // raduis

  public:
    /* Class default constructor */
      sphere( const vec3 Ctr, DBL Rad ) : C(Ctr), R(Rad)
      {
      } /* End of 'sphere' function */

    /* Get ray sphere intersection function.
     * ARGUMENTS:
     *   - ray to intersect with:
     *       const ray &R;
     *   - result intersection store pointer:
     *       intr *I;
     * RETURNS:
     *   (BOOL) TRUE if sphere interseced by ray.
     */
    BOOL Intersect( const ray &Ray, intr *I ) override
    {
      vec3 oc = Ray.Org - C;
      DBL b = oc & Ray.Dir;
      DBL c = (oc & oc) - R * R;
      DBL h = b * b - c;

      /* Check for no intersection condition */
      if (h < 0)
        return FALSE;

      h = sqrt(h);
      DBL t = -b - h;

      /* Tryclosest intersection point */
      if (t < Threshold)
      {
        /* Try second if first is behind the ray origin */
        t = -b + h;
        if (t < Threshold)
          return FALSE;
      }

      /* Store primary intersection data */
      I->T = t;
      I->Shp = this;
      I->P = Ray.Org + Ray.Dir * t;
      I->IsP = TRUE;
      I->IsN = FALSE;


      return TRUE;
    } /* End of 'Intersect' function */

     /* Get sphere normal function.
     * ARGUMENTS:
     *   - intersection store pointer:
     *       intr *I;
     * RETURNS: None.
     */
    VOID GetNormal( intr *I ) override
    {
      if (I->IsN)
        return;

      I->N = (I->P - C) / R;
      I->IsN = TRUE;
    } /* End of 'GetNormal' function */

  }; /* End of 'sphere' class */
} /* end of 'gert' namespace */
 
#endif /* __sphere_h_ */
 
/* END OF 'sphere.h' FILE */