/*************************************************************
 * Copyright (C) 2026
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : mth_def.h
 * PURPOSE     : Animation project.
 *               Mathematics library.
 *               main declaration module.
 * PROGRAMMER  : CGSG-SummerCamp'2026.
 *               Skulyabin Georgy.
 * LAST UPDATE : 27.07.2026.
 * NOTE        : Module namespace 'mth'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __mth_def_h_
#define __mth_def_h_

#include "def.h"

typedef DOUBLE DBL;
typedef long double LDBL;
typedef FLOAT FLT;

/* Math library namespace */
namespace mth
{
  /* Angle transform constants */
  const LDBL PI = 3.14159265358979323846L;

  /* Multiplier for degree to radian conversions */
  const LDBL MultiplierDegree2Radian = 0.01745329251994329576L;

  /* Random value 0..1 range obtain function.
   * ARGUMENTS: None.
   * RETURNS:
   *   (DBL) result value.
   */
  inline DBL Rnd0( VOID )
  {
    return (DBL)rand() / RAND_MAX;
  } /* End of 'Rnd0' function */

  /* Random value -1..1 range obtain function.
   * ARGUMENTS: None.
   * RETURNS:
   *   (DBL) result value.
   */
  inline DBL Rnd1( VOID )
  {
    return 2.0 * rand() / RAND_MAX - 1;
  } /* End of 'Rnd1' function */


  /* Convertion from degrees to radians function.
   * ARGUMENTS:
   *   - angle value in degrees:
   *       type AngleInDegree;
   * RETURNS:
   *   (type) converted value in radians.
   */
  template<typename type>
    type D2R( type AngleInDegrees )
    {
      return AngleInDegrees * PI / 180.0;
    } /* End of 'D2R' function */

  // Forward declaration
  template<typename type> class vec2;
  template<typename type> class vec3;
  template<typename type> class vec4;
  template<typename type> class matr;
  template<typename type> class ray;
  template<typename type> class camera;
} /* end of 'mth' namespace */

#endif /* __mth_def_h_ */
