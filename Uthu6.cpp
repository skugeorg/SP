#include "rbt.h"

#define WND_CLASS_NAME "Красно-черное дерево"

LRESULT CALLBACK MyWindowFunc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

rbtree Tr;

INT WINAPI WinMain(_In_ HINSTANCE hInstance,
                   _In_opt_ HINSTANCE hPrevInstance,
                   _In_ LPSTR CmdLine,
                   _In_ INT ShowCmd)
{
  WNDCLASS wc;
  HWND hWnd, hConWnd;
  MSG msg;
  CONSOLE_FONT_INFOEX cfi = {0};

  /* Create console */
  AllocConsole();

  cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
  GetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
  cfi.dwFontSize.Y = 18;
  cfi.FontWeight = FW_BOLD;
  SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

  freopen("CONOUT$", "w", stdout);
  freopen("CONIN$", "r", stdin);
  system("@chcp 1251 > nul");
  fflush(stdout);

  hConWnd = GetConsoleWindow();
  SetWindowPos(hConWnd, HWND_TOP, 1920 / 2, 0, 1920 / 2, 1000, 0);

  /* Insert random elements */
  for (int i = 0; i < 255; i++)
  {
    int rndval = rand() % 255; 
    std::cout << "add " << rndval << std::endl;
    Tr.Acces(rndval);
  }

  std::cout << std::endl;
  Tr.Draw();
  std::cout << std::endl;
  
  /* Test deletion (stub) */
  Tr.Delete(225);
  Tr.Draw();

  /* Register window class */
  wc.style = CS_VREDRAW | CS_HREDRAW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor = LoadCursor(NULL, IDC_CROSS);
  wc.hIcon = LoadIcon(NULL, IDI_ASTERISK);
  wc.lpszMenuName = NULL;
  wc.hInstance = hInstance;
  wc.lpfnWndProc = MyWindowFunc;
  wc.lpszClassName = WND_CLASS_NAME;

  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error register window class", "ERROR", MB_OK);
    return 0;
  }

  /* Create main window */
  hWnd = CreateWindow(WND_CLASS_NAME, "Red-Black Tree Visualization", WS_OVERLAPPEDWINDOW, 
                      CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, NULL);
  ShowWindow(hWnd, SW_SHOWNORMAL);
  UpdateWindow(hWnd);

  /* Message loop */
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return (INT)msg.wParam;
}

LRESULT CALLBACK MyWindowFunc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  HDC hDc;
  PAINTSTRUCT pt;
  static INT W, H, is_flag = 0, OldX, OldY, OrgX, OrgY;
  static HDC hMemDC;
  static BITMAP bm;
  static HBITMAP hBm;
  static HFONT hFnt;

  switch (Msg)
  {
  case WM_CLOSE:
    if (MessageBox(hWnd, "Are you sure?", "EXIT", MB_YESNO) == IDNO)
      return 0;
    break;

  case WM_ERASEBKGND:
    return 0;

  case WM_PAINT:
    hDc = BeginPaint(hWnd, &pt);
    BitBlt(hDc, 0, 0, W, H, hMemDC, 0, 0, SRCCOPY);
    EndPaint(hWnd, &pt);
    return 0;

  case WM_MOUSEMOVE:
    if (wParam & MK_LBUTTON)
    {
      INT X = (SHORT)LOWORD(lParam);
      INT Y = (SHORT)HIWORD(lParam);
      OrgX += OldX - X;
      OrgY += OldY - Y;
      OldX = X;
      OldY = Y;
    }
    return 0;

  case WM_LBUTTONDOWN:
    SetCapture(hWnd);
    OldX = (SHORT)LOWORD(lParam);
    OldY = (SHORT)HIWORD(lParam);
    break;

  case WM_LBUTTONUP:
    ReleaseCapture();
    break;

  case WM_SIZE:
    W = LOWORD(lParam);
    H = HIWORD(lParam);

    if (hBm != NULL)
      DeleteObject(hBm);
    hDc = GetDC(hWnd);
    hBm = CreateCompatibleBitmap(hDc, W, H);
    ReleaseDC(hWnd, hDc);
    return 0;

  case WM_CREATE:
    hDc = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDc);
    OrgX = OrgY = 0;
    ReleaseDC(hWnd, hDc);
    SetTimer(hWnd, 3, 30, NULL); /* 30ms timer for smooth redraw */
    return 0;

  case WM_TIMER:
    SelectObject(hMemDC, hBm);
    SetWindowOrgEx(hMemDC, 0, 0, nullptr);

    /* Clear background */
    SelectObject(hMemDC, GetStockObject(BLACK_BRUSH));
    Rectangle(hMemDC, 0, 0, W, H); 

    /* Apply panning offset */
    SetWindowOrgEx(hMemDC, OrgX, OrgY, nullptr);

    SelectObject(hMemDC, GetStockObject(WHITE_BRUSH));
    SelectObject(hMemDC, GetStockObject(WHITE_PEN));
    
    /* Calculate coordinates and draw the tree */
    Tr.SetXY(W, H);
    Tr.Display(hMemDC);

    SetWindowOrgEx(hMemDC, 0, 0, nullptr);
    InvalidateRect(hWnd, NULL, FALSE);
    return 0;

  case WM_DESTROY:
    PostQuitMessage(0);
    DeleteObject(hBm);
    DeleteDC(hMemDC);
    KillTimer(hWnd, 3);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}
