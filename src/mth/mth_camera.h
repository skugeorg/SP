/*************************************************************
 * Copyright (C) 2026
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : mth_camera.h
 * PURPOSE     : Raytracing project.
 *               Mathematics library.
 *               Camera handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2026.
 *               GS6.
 * LAST UPDATE : 30.07.2026.
 * NOTE        : Module namespace 'mth'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __mth_camera_h_
#define __mth_camera_h_

#include "mth_def.h"

/* Math library namespace */
namespace mth
{
  /* Space camera handle class */
  template<typename type>
    class camera
    {
    public:
      vec3<type>
        Loc,            // camera location
        Dir, Up, Right, // basis camera directions
        At;             // camera pivot point
      type
        ProjDist,       // near project plane distance
        FarClip,        // far project plane distance
        Size,           // inner project plane rectangle size
        Wp, Hp;         // project plane size
 
      INT FrameW, FrameH; // Camera frame size in pixels
 
      matr<type>
        View,           // view matrix
        Proj,           // projection matrix
        VP;             // View and Proj matrix production
 
      /* Class default constructor.
       * ARGUMENTS: None.
       */
      camera( VOID ) :
        Loc(0, 0, 5), Dir(0, 0, -1), Up(0, 1, 0), Right(1, 0, 0), At(0, 0, 0),
        ProjDist(0.1), FarClip(500), Size(0.1), FrameW(30), FrameH(30)
      {
        UpdateProj();
      }
 
      /* Set camera projection parameters function.
       * ARGUMENTS:
       *   - new inner project plane size:
       *       type NewSize;
       *   - new near project plane distance:
       *       type NewProjDist;
       *   - new far clip plane distance:
       *       type NewFarClip;
       * RETURNS:
       *   (camera &) self-reference.
       */
      camera & SetProj( type NewSize, type NewProjDist, type NewFarClip )
      {
        ProjDist = NewProjDist;
        Size = NewSize;
        FarClip = NewFarClip;
 
        UpdateProj();
        return *this;
      }
 
      /* Resize camera frame size function.
       * ARGUMENTS:
       *   - new frame width in pixels:
       *       INT NewFrameW;
       *   - new frame height in pixels:
       *       INT NewFrameH;
       * RETURNS:
       *   (camera &) self-reference.
       */
      camera & Resize( INT NewFrameW, INT NewFrameH )
      {
        FrameW = NewFrameW;
        FrameH = NewFrameH;
 
        UpdateProj();
        return *this;
      }

 
      /* Set camera orientation and location function.
       * ARGUMENTS:
       *   - new camera location:
       *       const vec3<type> &L;
       *   - new camera pivot point:
       *       const vec3<type> A;
       *   - target up-vector direction:
       *       const vec3<type> U;
       * RETURNS:
       *   (camera &) self-reference.
       */
      camera & SetLocAtUp( const vec3<type> &L, const vec3<type> A, const vec3<type> U = vec3<type>(0, 1, 0) )
      {
        Loc = L;
        At = A;
        Up = U;
 
        Dir = (At - Loc).Normalizing();
        Right = (Dir % Up).Normalizing();
        Up = Right % Dir;
 
        UpdateProj();
        return *this;
      }
 
      /* Build primary ray from screen coordinates function.
       * ARGUMENTS:
       *   - screen coordinate X (0..FrameW):
       *       type Xs;
       *   - screen coordinate Y (0..FrameH):
       *       type Ys;
       * RETURNS:
       *   (ray<type>) built ray.
       */
      ray<type> FrameRay( type Xs, type Ys )
      {
        type A = Xs / (type)FrameW - 0.5;
        type B = 0.5 - Ys / (type)FrameH;

        vec3<type> Direction = Dir * ProjDist + Right * A * Wp + Up * B * Hp;

        return ray<type>(Loc, Direction.Normalizing());
      } /* End of 'FrameRay' function */
 
    private:
      /* Update camera projection and full matrices internal function.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      VOID UpdateProj( VOID )
      {
        type rx = Size / 2, ry = Size / 2;
 
        if (FrameW > FrameH)
          rx *= (type)FrameW / FrameH;
        else
          ry *= (type)FrameH / FrameW;
        Wp = rx * 2;
        Hp = ry * 2;

        Proj = matr<type>::Frustum(-rx, rx, -ry, ry, ProjDist, FarClip);
        View = matr<type>::View(Loc, At, Up);
        VP = View * Proj;
      }
    };
} /* end of 'mth' namespace */

#endif /* __mth_camera_h_ */
