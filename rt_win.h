/*************************************************************
 * Copyright (C) 2026
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : rt_win.h
 * PURPOSE     : Raytracing project.
 *               Raytracing library.
 *               Raytracing handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2026.
 *               GS6.
 * LAST UPDATE : 31.07.2026.
 * NOTE        : Module namespace 'gert'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __rt_win_h_
#define __rt_win_h_

#include "win/win.h"
#include "frame.h"
#include "rt_def.h"

/* Project namespace */
namespace gert
{
  /* Ray tracing window handle class */
  class rt_win : public win
  {
  public:
    frame Frm;  // window frame
    camera Cam; // scene camera
    scene Sc;   // rt scene

    /* Render scene function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Render( VOID )
    {
      Sc.Render(Cam, Frm);
    } /* End of 'Render' function */

  private:
    /* Window creation handle function.
     * ARGUMENTS:
     *   - creation structure pointer:
     *       CREATESTRUCT *CS;
     * RETURNS:
     *   (BOOL) TRUE if success, FALSE otherwise.
     */
    BOOL OnCreate( CREATESTRUCT *CS ) override
    {
      Frm.Resize(600, 500);
      Cam.Resize(600, 500);
      Cam.SetLocAtUp(vec3(0, 0, 5), vec3(0));
      return TRUE;
    } /* End of 'OnCreate' function */

    /* Window painting handle function.
     * ARGUMENTS:
     *   - device context handle:
     *       HDC hDC;
     *   - paint structure pointer:
     *       PAINTSTRUCT *Ps;
     * RETURNS: None.
     */
    VOID OnPaint( HDC hDC, PAINTSTRUCT *Ps )
    {
      SelectObject(hDC, GetStockObject(DC_BRUSH));
      SelectObject(hDC, GetStockObject(WHITE_PEN));
      SetDCBrushColor(hDC, RGB(255, 0, 0));
      if (Frm.W != 0 && Frm.H != 0)
      {
        INT
          X = (W - Frm.W) / 2,
          Y = (H - Frm.H) / 2;
 
        // Draw top rectangle
        if (Y > 0)
          Rectangle(hDC, 0, 0, W + 1, Y);
 
        // Draw left rectangle
        if (X > 0)
          Rectangle(hDC, 0, Y, X, Y + Frm.H + 1);
 
        // Draw right rectangle
        if (X + Frm.W < W)
          Rectangle(hDC, X + Frm.W, Y, W + 1, Y + Frm.H + 1);
 
        // Draw bottom rectangle
        if (Y + Frm.H < H)
          Rectangle(hDC, 0, Y + Frm.H, W + 1, H + 1);
 
        // Draw frame at window center
        Frm.Draw(hDC, X, Y, Frm.W, Frm.H);
      }
      else
        Rectangle(hDC, 0, 0, W + 1, H + 1);

      InvalidateRect(hWnd, nullptr, FALSE); 
    } /* End of 'OnPaint' function */

    /* Window resizing handle function.
     * ARGUMENTS:
     *   - window state flag:
     *       UINT State;
     *   - new width and height:
     *       INT W, H;
     * RETURNS: None.
     */
    VOID OnSize( UINT State, INT W, INT H ) override
    {
    } /* End of 'OnSize' function */

    /* Window destruction handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID OnDestroy( VOID )
    {
      PostQuitMessage(30);
    } /* End of 'OnDestroy' function */

    /* WM_KEYDOWN/WM_KEYUP window message handle function.
     * ARGUMENTS:
     *   - virtual key number (see VK_***, 'A', ..., '0', ...):
     *       UINT Key;
     *   - press flag:
     *       BOOL IsPress;
     *   - autorepeat counter:
     *       INT RepeatCount;
     *   - shift/control etc key states bits (see MK_***):
     *       UINT ShiftKeysFlags;
     * RETURNS: None.
     */
    VOID OnKey( UINT Key, BOOL IsPress, INT RepeatCount, UINT ShiftKeysFlags ) override
    {
      if (Key == VK_ESCAPE)
        if (Sc.IsRenderActive)
          Sc.IsToBeStop = TRUE;
        else
          DestroyWindow(hWnd);
      else if (Key == 'C')
        Frm.Fill(0x00303030);
      else if (Key == 'R')
      {
        if (Sc.IsRenderActive)
          return;
 
        Sc.IsRenderActive = TRUE;
        Sc.IsToBeStop = FALSE;
        Sc.IsReadyToFinish = FALSE;
 
        std::cout << std::endl << "Start render scene at ";
        std::time_t t_c =
          std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::cout << std::put_time(std::localtime(&t_c), "%H:%M:%S %d.%m.%Y\n");
 
        std::thread Th;
        Th = std::thread(
          [this]( VOID )
          {
            auto start_time = std::chrono::high_resolution_clock::now();
 
            Sc.Render(Cam, Frm);
 
            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration = end_time - start_time;
            auto hours = std::chrono::duration_cast<std::chrono::hours>(duration);
            duration -= hours;
            auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
            duration -= minutes;
            auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
            duration -= seconds;
            auto milliseconds =
              std::chrono::duration_cast<std::chrono::milliseconds>(duration);
            duration -= milliseconds;
            std::cout << std::format("Frame render time in [{}:{}:{}.{}]\n",
              hours.count(), minutes.count(), seconds.count(), milliseconds.count());
 
            std::cout << "End render scene at ";
            std::time_t t_c =
              std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            std::cout << std::put_time(std::localtime(&t_c), "%H:%M:%S %d.%m.%Y\n");
 
            InvalidateRect(hWnd, NULL, FALSE);
            UpdateWindow(hWnd);
 
            // Save to TGA
            //std::tuple<INT, INT, INT> Dur
            //{
            //  hours.count(), minutes.count(), seconds.count()
            //};
            //Frm.AutosaveTGA("CGSG forever!!!", Dur);
 
            Sc.IsToBeStop = FALSE;
            Sc.IsReadyToFinish = TRUE;
            Sc.IsRenderActive = FALSE;
          });
        Th.detach();
      }
    } /* End of 'OnKey' function */

  public:
    using win::win;
  }; /* end of 'rt_win' class */
} /* End of 'gert' namespace */

#endif /* __rt_win_h_ */
