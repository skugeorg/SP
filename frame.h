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

#pragma pack(push, 1)
#include <tgahead.h>
#pragma pack(pop)
 
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
 
    /* Store frame buffer image to TGA file function.
     * ARGUMENTS:
     *   - file name:
     *       const std::string &FileName;
     *   - addition comments:
     *       const std::string &Comments;
     *   - render/job time (hours, minutes, seconds):
     *       const std::tuple<INT, INT, INT> &JobTime;
     * RETURNS:
     *   (BOOL) TRUE if success, FALSE otherwise.
     */
    BOOL SaveTGA( const std::string &FileName,
                  const std::string &Comments = "",
                  const std::tuple<INT, INT, INT> &JobTime = {0, 0, 0} )
    {
      // Lock access
      const std::lock_guard<std::recursive_mutex> lock(frame_mutex);
      
      std::filesystem::path PathName(FileName);
      if (!PathName.has_extension())
        PathName += ".tga";
 
      //auto pp = PathName.relative_path();
      //auto pp1 = PathName.stem();
      //auto pp2 = PathName.root_directory();
      //std::filesystem::create_directories(PathName.relative_path());
 
      std::fstream f(PathName, std::fstream::out | std::fstream::binary);
      if (!f.is_open())
        return FALSE;
 
      // Fill file header
      tgaFILEHEADER head {};  
      INT len = static_cast<INT>(Comments.length());
      if (len > 254)
        len = 255;
      else
        if (len != 0)
          len++;
      head.IDLength = len;
      head.ColorMapType = 0;
      head.ImageType = 2;
      head.BitsPerPixel = 32;
      head.Width = W;
      head.Height = H;
      head.ImageDescr = 1 << 5; // image start - left-top corner
 
      // Store header and comments
      f.write(reinterpret_cast<CHAR *>(&head), sizeof(head));
      if (len != 0)
        f.write(Comments.c_str(), len - 1), f.put(0);
 
      // Store image
      f.write(reinterpret_cast<CHAR *>(Pixels), W * H * 4);
 
      tgaEXTHEADER ext {};
      strcpy(ext.AuthorName, "VG4");
      strcpy(ext.SoftwareID, "CGSG RayTracing'2026-summer");
      strcpy(ext.AuthorComment, "CGSG forever!!!");
      ext.VersionNumber = 100;
      ext.GammaDenominator = 1;
      ext.GammaNumerator = 1;
      ext.PixelDenominator = 1;
      ext.PixelNumerator = 1;
      strcpy(ext.JobName, "CGSG Raytracing");
 
      ext.JobHour = std::get<0>(JobTime);
      ext.JobMinute = std::get<1>(JobTime);
      ext.JobSecond = std::get<2>(JobTime);
 
      f.write((CHAR *)&ext, sizeof(ext));
 
      tgaFILEFOOTER foot {};
      foot.ExtensionOffset = sizeof(head) + head.IDLength + 4 * W * H;
      strncpy(foot.Signature, TGA_EXT_SIGNATURE, 18);
      f.write((CHAR *)&foot, sizeof(foot));
 
      f.close();
      return TRUE;
    } /* End of 'SaveTGA' function */
 
    /* Auto naming store frame buffer image to TGA file function.
     * ARGUMENTS:
     *   - addition comments:
     *       const std::string &Comments;
     *   - render/job time (hours, minutes, seconds):
     *       const std::tuple<INT, INT, INT> &JobTime;
     * RETURNS:
     *   (BOOL) TRUE if success, FALSE otherwise.
     */
    BOOL AutoSaveTGA( const std::string &Comments = "",
                      const std::tuple<INT, INT, INT> &JobTime = {0, 0, 0} )
    {
      SYSTEMTIME st;
 
      GetLocalTime(&st);
      CHAR Buf[300];
      wsprintf(Buf, "%04d%02d%02d_%02d%02d%02d_%03d_%02d",
        st.wYear, st.wMonth, st.wDay, st.wHour,
        st.wMinute, st.wSecond, st.wMilliseconds,
        rand() % 90);
 
      std::string path("bin/images/AutoSave");
      std::filesystem::create_directories(path);
 
      return SaveTGA(path + "/" + Buf + ".tga", Comments, JobTime);
    } /* End of 'AutoSaveTGA' function */
  }; /* End of 'frame' class */
} /* end of 'gert' namespace */
 
#endif /* __frame_h_ */
 
/* END OF 'frame.h' FILE */