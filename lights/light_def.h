/*************************************************************
 * Copyright (C) 2026
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : light_def.h
 * PURPOSE     : Ray Tracing project.
 *               Lights library.
 *               Light class definition module.
 * PROGRAMMER  : CGSG-SummerCamp'2026.
 *               GS6.
 * LAST UPDATE : 01.08.2026.
 * NOTE        : Module namespace 'lights'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
 
#ifndef __light_def_h_
#define __light_def_h_

#include "def.h"

/* lights namespace */
namespace gert::lights
{
  /* light params decl class */
  struct light_info
  {
    vec3 L;     // Light source direction
    vec3 Color; // Light source color
    DBL Dist;   // Distance to light source
  }; /* End of 'light_info' class */

  /* light source class */
  class light
  {
  protected:
    DBL Cc, Cl, Cq; // Attenuation coefficients
    vec3 Color;     // Light source color
  public:
    light( DBL C = 0.3, DBL L = 0.4, DBL Q = 0.5, vec3 Col = vec3(1, 0, 0) ) : Cc(C), Cl(L), Cq(Q), Color(Col)
    {
    }
    virtual DBL Shadow( const vec3 &P, light_info *L );
  }; /* End of 'light' class */

} /* end of 'lights' namespace */

#endif /* __light_def_h_ */ 
/* END OF 'light_def.h' FILE */
