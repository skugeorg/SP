/*************************************************************
 * Copyright (C) 2026
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : frame.h
 * PURPOSE     : Ray Tracing project.
 *               Frame buffer class declaration module.
 * PROGRAMMER  : CGSG-SummerCamp'2026.
 *               GS6.
 * LAST UPDATE : 30.07.2026.
 * NOTE        : Module namespace 'gert'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
 
#ifndef __frame_h_
#define __frame_h_

#include "def.h"
 
/* Project namespace */
namespace gert
{
  /* Frame buffer handle class */
  class frame
  {
  private:
    DWORD *Pixels = nullptr; // Frame buffer pixels
 
    // Frame access mutex
    recursive_mutex frame_mutex;
 
  public:
    // Frame size
    INT W = 0, H = 0;
 
    /* Resize frame buffer function.
     * ARGUMENTS:
     *   - new frame size:
     *       INT NewW, NewH;
     * RETURNS: None.
     */
    VOID Resize( INT NewW, INT NewH )
    {
      // Lock access
      const lock_guard<recursive_mutex> lock(frame_mutex);
 
      delete[] Pixels;
      Pixels = nullptr;
      W = H = 0;
      if (NewW != 0 && NewH != 0)
      {
        Pixels = new DWORD[NewW * NewH];
        ZeroMemory(Pixels, NewW * NewH * 4);
        W = NewW;
        H = NewH;
      }
    } /* End of Resize' function */
 
    /* Put pixel with specified color function.
     * ARGUMENTS:
     *   - pixel coordinates:
     *       INT X, Y;
     *   - pixel color:
     *       DWORD Color;
     * RETURNS: None.
     */
    VOID PutPixel( INT X, INT Y, DWORD Color )
    {
      // Lock access
      const lock_guard<recursive_mutex> lock(frame_mutex);
 
      // Clipping
      if (X < 0 || Y < 0 || X >= W || Y >= H)
        return;
 
      Pixels[Y * W + X] = (Color & 0x00FFFFFF);
    } /* End of 'PutPixel' function */
 
    /* Get pixel color function.
     * ARGUMENTS:
     *   - pixel coordinates:
     *       INT X, Y;
     * RETURNS:
     *   (DWORD) pixel color.
     */
    DWORD GetPixel( INT X, INT Y )
    {
      // Lock access
      const lock_guard<recursive_mutex> lock(frame_mutex);
 
      // Clipping
      if (X < 0 || Y < 0 || X >= W || Y >= H)
        return 0;
 
      // Set pixel color
      return Pixels[Y * W + X];
    } /* End of 'PutPixel' function */
 
    /* Fill frame with specified color function.
     * ARGUMENTS:
     *   - pixels color:
     *       DWORD Color;
     * RETURNS: None.
     */
    VOID Fill( DWORD Color )
    {
      // Lock access
      const lock_guard<recursive_mutex> lock(frame_mutex);    
 
      // Set pixel color
      INT n = W * H;
      DWORD *ptr = Pixels;
      while (n-- > 0)
        *ptr++ = Color;
    } /* End of 'Fill' function */
 
    /* Blit frame to device context function.
     * ARGUMENTS:
     *   - device context:
     *       HDC hDC;
     *   - window coordinates:
     *       INT X, Y;
     *   - window rectangle size:
     *       INT DrawW, DrawH;
     *   - image draw offset:
     *       INT OffX, OffY;
     * RETURNS: None.
     */
    VOID Draw( HDC hDC, INT X, INT Y, INT DrawW, INT DrawH,
               INT OffX = 0, INT OffY = 0 )
    {
      // Lock access
      const lock_guard<recursive_mutex> lock(frame_mutex);
 
      // Draw buffer through DIB
      BITMAPINFOHEADER bih
      {
        .biSize = sizeof(BITMAPINFOHEADER),
        .biWidth = W,
        .biHeight = -H,
        .biPlanes = 1,
        .biBitCount = 32,
        .biCompression = BI_RGB,
        .biSizeImage = static_cast<DWORD>(W * H * 4),
        .biXPelsPerMeter = 30,
        .biYPelsPerMeter = 30,
        .biClrUsed = 0,
        .biClrImportant = 0,
      };
      SetStretchBltMode(hDC, COLORONCOLOR);
      StretchDIBits(hDC, X, Y, DrawW, DrawH, OffX, OffY, W, H, Pixels,
        (BITMAPINFO *)&bih, DIB_RGB_COLORS, SRCCOPY);
    } /* End of 'Draw' function */
 
    /* Convert float point 0..1 range color to DWORD function.
     * ARGUMENTS:
     *   - color RGB values:
     *       DBL R, G, B;
     * RETURNS:
     *   (DWORD) result packed color.
     */
    static DWORD ToRGB( DBL R, DBL G, DBL B )
    {
      auto clamp =
        []( FLT Value ) -> BYTE
        {
          if (Value < 0)
            return 0;
          if (Value > 1)
            return 255;
          return Value * 255;
        };
      return (clamp(R) << 16) | (clamp(G) << 8) | clamp(B);
    } /* End of 'ToRGB' function */
 
    /* Class destructor */
    ~frame( VOID )
    {
      Resize(0, 0);
    } /* End of '~frame' function */ 

  }; /* End of 'frame' class */
} /* end of 'gert' namespace */
 
#endif /* __frame_h_ */
 
/* END OF 'frame.h' FILE */