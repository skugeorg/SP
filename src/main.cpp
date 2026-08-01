/*************************************************************
 * Copyright (C) 2026
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : main.cpp
 * PURPOSE     : Raytracing project.
 *               Main module.
 *               Definitions handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2026.
 *               GS6.
 * LAST UPDATE : 31.07.2026.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "gert.h"

#include "rt/rt.h"
#include "rt/rt_win.h"

/* The main program function.
 * ARGUMENTS:
 *   - handle of application instance:
 *       HINSTANCE hInstance;
 *   - dummy handle of previous application instance (not used):
 *       HINSTANCE hPrevInstance;
 *   - command line string:
 *       CHAR *CmdLine;
 *   - show window command parameter (see SW_***):
 *       INT CmdShow;
 *   - error code to return:
 * RETURNS:
 *   (INT) Error level for operation system (0 for success).
 */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    CHAR *CmdLine, INT ShowCmd )
{
  gert::rt_win myw(hInstance);
                                                                    
  myw.Create();

  myw.Sc <<
    new gert::sphere(mth::vec3<DBL>(0, 0, 0), 1.0) <<
    new gert::sphere(mth::vec3<DBL>(2, 1, 2), 0.5);
  myw.Sc <<
    new gert::lights::point(mth::vec3<DBL>(3, 3, 3));

  myw.Run();

  if (myw.Sc.IsRenderActive)
  {
    myw.Sc.IsToBeStop = TRUE;
    std::cout << "\nWait rendering threads are finished\n";
    while (!myw.Sc.IsReadyToFinish)
      ;
    std::cout << "\nWaiting is finished\n";
  }
  std::cout << "\nFinish...\n";
  return 0;
} /* End of 'WinMain' function */
