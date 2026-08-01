/*************************************************************
 * Copyright (C) 2026
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : point.h
 * PURPOSE     : Ray Tracing project.
 *               Lights library.
 *               Point light class module.
 * PROGRAMMER  : CGSG-SummerCamp'2026.
 *               GS6.
 * LAST UPDATE : 01.08.2026.
 * NOTE        : Module namespace 'lights'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
 
#ifndef __point_h_
#define __point_h_

#include "light_def.h"

/* lights namespace */
namespace gert
{
  namespace lights
  {
    /* Point light source handle class */
    class point : public light
    {
    private:
      vec3 Pos; // Point light source position
 
    public:
      /* Class constructor.
        * ARGUMENTS:
        *   - çoint light source position:
        *       const vec3 &P;
        */
      point( const vec3 &P ) : Pos(P)
      {
      } /* End of 'point' function */
    
      /* Light source shadow evalution function.
        * ARGUMENTS:
        *   - point of lighting to:
        *       const vec3 &P;
        *   - light source information data pointer (to be fill):
        *       light_info *L;
        * RETURNS:
        *   (DBL) common shading factor.
        */
      virtual DBL Shadow( const vec3 &P, light_info *L )
      {
        L->Color = Color;
        L->L = Pos - P;
        L->Dist = L->L.Length();
        L->L /= L->Dist;
        return 1;
      } /* End of 'Shadow' function */
    }; /* End of 'Point' class */
  } /* end of 'lights' namespace */
} /* end of 'gert' namespace */

#endif /* __point_h_ */ 
/* END OF 'point.h' FILE */
