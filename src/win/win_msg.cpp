#include "gert.h"
#include "win.h"

/* WM_CREATE window message handle function.
 * ARGUMENTS:
 *   - structure with creation data:
 *       CREATESTRUCT *CS;
 * RETURNS:
 *   (BOOL) TRUE to continue creation window, FALSE to terminate.
 */
BOOL gert::win::OnCreate( CREATESTRUCT *CS )
{
  return TRUE;
} /* End of 'gert::win::OnCreate' function */

/* WM_DESTROY window message handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID gert::win::OnDestroy( VOID )
{
} /* End of 'gert::win::OnDestroy' function */

/* WM_SIZE window message handle function.
 * ARGUMENTS:
 *   - sizing flag (see SIZE_***, like SIZE_MAXIMIZED)
 *       UINT State;
 *   - new width and height of client area:
 *       INT W, H;
 * RETURNS: None.
 */
VOID gert::win::OnSize( UINT State, INT W, INT H )
{
} /* End of 'gert::win::OnSize' function */

/* WM_ERASEBKGND window message handle function.
 * ARGUMENTS:
 *   - device context of client area:
 *       HDC hDC;
 * RETURNS:
 *   (BOOL) TRUE if background is erased, FALSE otherwise.
 */
BOOL gert::win::OnEraseBackground( HDC hDC )
{
  return TRUE;
} /* End of 'gert::win::OnEraseBkgnd' function */

/* WM_PAINT window message handle function.
 * ARGUMENTS:
 *   - window device context:
 *       HDC hDC;
 *   - paint message structure pointer:
 *       PAINTSTRUCT *PS;
 * RETURNS: None.
 */
VOID gert::win::OnPaint( HDC hDC, PAINTSTRUCT *PS )
{
} /* End of 'gert::win::OnPaint' function */ 

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
VOID gert::win::OnKey( UINT Key, BOOL IsPress, INT RepeatCount, UINT ShiftKeysFlags )
{
}  /* End of 'OnKey' function */ 

/* WM_ACTIVATE window message handle function.
 * ARGUMENTS:
 *   - reason (WA_CLICKACTIVE, WA_ACTIVE or WA_INACTIVE):
 *       UINT Reason;
 *   - handle of active window:
 *       HWND hWndActDeact;
 *   - minimized flag:
 *       BOOL IsMinimized;
 * RETURNS: None.
 */
VOID gert::win::OnActivate( UINT Reason, HWND hWndActDeact, BOOL IsMinimized )
{
  // IsActive = Reason == WA_CLICKACTIVE || Reason == WA_ACTIVE;
} /* End of 'gert::win::OnActivate' function */

/* WM_TIMER window message handle function.
 * ARGUMENTS:
 *   - specified the timer identifier.
 *       INT Id;
 * RETURNS: None.
 */
VOID gert::win::OnTimer( INT Id ) 
{
} /* End of 'gert::win::OnTimer' function */

/* WM_MOUSEWHEEL window message handle function.
 * ARGUMENTS:
 *   - mouse window position:
 *       INT X, Y;
 *   - mouse wheel relative delta value:
 *       INT Z;
 *   - mouse keys bits (see MK_*** bits constants):
 *       UINT Keys;
 * RETURNS: None.
 */
VOID gert::win::OnMouseWheel( INT X, INT Y, INT Z, UINT Keys )
{
  MouseWheel += Z;
} /* End of 'gert::win::OnMouseWheel' function */


/* WM_NOTIFY window message handle function.
 * ARGUMENTS:
 *   - control identifier:
 *       INT Id;
 *   - notification header depended to control type:
 *       NMHDR *NoteHead;
 * RETURNS:
 *   (LRESULT) return value depended to notification.
 */
LRESULT gert::win::OnNotify( INT Id, NMHDR* NoteHead )
{
  return 0;
} /* End of 'gert::win::OnNotify' function */


/* WM_COMMAND window message handle function.
 * ARGUMENTS:
 *   - item (menu or accelerator) or control window identifier:
 *       INT Id;
 *   - control window handle:
 *       HWND hWndCtl;
 *   - notification: 0 - menu, 1 - accelerator, otherwise -
 *     depended to control (like BM_CLICKED):
 *       UINT CodeNotify;
 * RETURNS: None.
 */
VOID gert::win::OnCommand( INT Id, HWND hWndCtl, UINT CodeNotify )
{
} /* End of 'gert::win::OnCommand' function */



/* WM_DROPFILES window message handle function.
 * ARGUMENTS:
 *   - handle to an internal structure describing the dropped files:
 *       HDROP hDrop;
 * RETURNS: None.
 */
VOID gert::win::OnDropFiles( HDROP hDrop )
{
  /*
  static CHAR Buf[_MAX_PATH];

  INT n = DragQueryFile(hDrop, 0xFFFFFFFF, NULL, 0);
  if (n > 0)
  {
    POINT pt;
    DragQueryPoint(hDrop, &pt);
    ClientToScreen(hWnd, &pt);
    HWND hWndItem = WindowFromPoint(pt);
    if (hWndItem == / Check window / )
    {
      / for single file: DragQueryFile(hDrop, 0, Buf, sizeof(Buf)); /
      // Handle every file
      for (INT i = 0; i < n; i++)
      {
        DragQueryFile(hDrop, i, Buf, sizeof(Buf));
        /// Handle filename from 'Buf'
        // Can split:
        static CHAR
          Drive[_MAX_DRIVE], Dir[_MAX_DIR],
          FileName[_MAX_FNAME], FileExt[_MAX_EXT];

        _splitpath(Buf, Drive, Dir, FileName, FileExt);
        // . . .
      }
    }
  }
  */
} /* End of 'gert::win::OnDropFiles' function */


/* WM_DRAWITEM window message handle function.
 * ARGUMENTS:
 *   - control identifier (for menu - 0):
 *       INT Id;
 *   - draw item information structure pointer:
 *       DRAWITEMSTRUCT *DrawItem;
 * RETURNS: None.
 *   (LRESULT) return value depended to notification.
 */
VOID gert::win::OnDrawItem( INT Id, DRAWITEMSTRUCT* DrawItem )
{
  /*if (DrawItem->CtlID == ...) // sample for check box draw as button
  {
    UINT Flags = DFCS_BUTTONPUSH;

    if (DrawItem->itemState & ODS_DISABLED)
      Flags |= DFCS_INACTIVE;
    if (DrawItem->itemState & ODS_SELECTED)
      Flags |= DFCS_PUSHED;

    DrawFrameControl(DrawItem->hDC, &DrawItem->rcItem, DFC_BUTTON, Flags);
    InflateRect(&DrawItem->rcItem, -2, -2);
    Flags &= ~DFCS_PUSHED;
    Flags &= ~DFCS_BUTTONPUSH;
    Flags |= DFCS_BUTTONCHECK | DFCS_FLAT;
    if (DrawItem->CtlID == ...)
      Flags |= DFCS_CHECKED;
    DrawFrameControl(DrawItem->hDC, &DrawItem->rcItem, DFC_BUTTON, Flags);
  }
  */
} /* End of 'gert::win::OnDrawItem' function */

/* WM_HSCROLL message handle function.
 * ARGUMENTS:
 *   - handle of scroll window or nullptr for window scroll bars:
 *       HWND hWndCtl;
 *   - scrool bar request code (see SB_***):
 *       UINT Code;
 *   - scroll position for 'Code' is SB_THUMBPOSITION or SB_THUMBTRACK:
 *       INT Pos;
 * RETURNS: None.
 */
VOID gert::win::OnHScroll( HWND hWndCtl, UINT Code, INT Pos )
{
} /* End of 'gert::win::OnHScroll' function */

/* WM_VSCROLL message handle function.
 * ARGUMENTS:
 *   - handle of scroll window or nullptr for window scroll bars:
 *       HWND hWndCtl;
 *   - scrool bar request code (see SB_***):
 *       UINT Code;
 *   - scroll position for 'Code' is SB_THUMBPOSITION or SB_THUMBTRACK:
 *       INT Pos;
 * RETURNS: None.
 */
VOID gert::win::OnVScroll( HWND hWndCtl, UINT Code, INT Pos )
{
} /* End of 'gert::win::OnVScroll' function */

/* WM_MENUSELECT window message handle function.
 * ARGUMENTS:
 *   - handle of menu:
 *       HMENU hMenu;
 *   - submenu item ID or submenu index
 *       INT Item;
 *   - handle of popup menu if selected popup submenu:
 *       HMENU hMenuPopup;
 *   - menu item flags (see MF_***):
 *       UINT Flags;
 * RETURNS: None.
 */
VOID gert::win::OnMenuSelect( HMENU hMenu, INT Item, HMENU hMenuPopup, UINT Flags )
{
} /* End of 'gert::win::OnMenuSelect' function */

/* WM_INITMENUPOPUP window message handle function.
 * ARGUMENTS:
 *   - handle of popup menu:
 *       HMENU hMenu;
 *   - submenu item position:
 *       UINT Item;
 *   - window system menu flag:
 *       BOOL IsSystemMenu;
 * RETURNS: None.
 */
VOID gert::win::OnInitMenuPopup( HMENU hMenu, UINT Item, BOOL IsSystemMenu )
{
} /* End of 'gert::win::OnInitMenuPopup' function */


/* WM_EXITSIZEMOVE window message handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID gert::win::OnExitSizeMove( VOID )
{
} /* End of 'gert::win::OnExitSizeMove' function */

/* WM_ENTERSIZEMOVE window message handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID gert::win::OnEnterSizeMove( VOID )
{
} /* End of 'gert::win::OnEnterSizeMove' function */

/* Window message universal handle function.
 * Should be returned 'DefWindowProc' call result.
 * ARGUMENTS:
 *   - message type (see WM_***):
 *      UINT Msg;
 *   - message 'word' parameter:
 *      WPARAM wParam;
 *   - message 'long' parameter:
 *      LPARAM lParam;
 * RETURNS:
 *   (LRESULT) message depende return value.
 */
LRESULT gert::win::OnMessage( UINT Msg, WPARAM wParam, LPARAM lParam )
{
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'gert::win::OnMessage' function */

/* WM_BUTTONDOWN window message handle function.
 * ARGUMENTS:
 *   - is double click:
 *      BOOL IsDoubleClick;
 *   - mouse pos:
 *      INT X, Y;
 *   - key type:
 *      UINT Keys;
 * RETURNS: None.
 */
VOID gert::win::OnButtonDown( BOOL IsDoubleClick, INT X, INT Y, UINT Keys )
{
} /* End of 'gert::win::OnButtonDown' function */

/* WM_BUTTONUP window message handle function.
 * ARGUMENTS:
 *   - mouse pos:
 *      INT X, Y;
 *   - key type:
 *      UINT Keys;
 * RETURNS: None.
 */
VOID gert::win::OnButtonUp( INT X, INT Y, UINT Keys )
{
} /* End of 'gert::win::OnButtonUp' function */

/* WM_MOUSEMOVE window message handle function.
 * ARGUMENTS:
 *   - mouse pos:
 *      INT X, Y;
 *   - key type:
 *      UINT Keys;
 * RETURNS: None.
 */
VOID gert::win::OnMouseMove( INT X, INT Y, UINT Keys )
{
} /* End of 'gert::win::OnMouseMove' function */