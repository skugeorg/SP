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
namespace gert::lights
{
  /* Point light source class */
  class Point : public light
  {
  private:
    vec3 Pos; // Light position
  public:
    /* Constructor */
    Point( const vec3 &LP = vec3(0), DBL C = 0.3, DBL L = 0.4, DBL Q = 0.5, vec3 Col = vec3(1) ) 
      : light(C, L, Q, Col), Pos(LP)
    {
    }
    
    /* Evaluate light properties and Attuation */
    DBL Shadow( const vec3 &P, light_info *L ) override
    {
      if (L == nullptr)
        return 0;

      vec3 Dir = Pos - P;
      L->Dist = Dir.Length();

      if (L->Dist > 0.0001)
        L->L = Dir / L->Dist;
      else
        L->L = vec3(0, 1, 0);

      L->Color = this->Color; 

      DBL Att = 1.0 / (Cc + Cl * L->Dist + Cq * L->Dist * L->Dist);
      
      if (Att > 1.0)
        Att = 1.0;
      if (Att < 0.0)
        Att = 0.0;

      return Att;
    } /* End of 'Shadow' function */
  }; /* End of 'Point' class */

} /* end of 'lights' namespace */

#endif /* __point_h_ */ 
/* END OF 'point.h' FILE */
