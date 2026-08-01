/*************************************************************
 * Copyright (C) 2026
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : mth_vec3.h
 * PURPOSE     : Raytracing project.
 *               Mathematics library.
 *               Ray handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2026.
 *               GS6.
 * LAST UPDATE : 30.07.2026.
 * NOTE        : Module namespace 'mth'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __mth_ray_h_
#define __mth_ray_h_

#include "mth_def.h"

namespace mth
{
template<typename type>
  class ray
  {
  public:
    vec3<type> Org, Dir;
 
    ray( void );
    ray( const vec3<type> &NewOrg, const vec3<type> &NewDir ) :
      Org(NewOrg), Dir(NewDir.Normalizing())
    {
    }
 
    vec3<type> operator()( type T ) const
    {
      return Org + Dir * T;
    }
  };

} /* End of 'mth' namespace */

#endif /* __mth_ray_h_ */

/* END OF 'mth_ray.h' FUNCTION */