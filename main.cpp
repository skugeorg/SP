#include "rbt.h"

#define WND_CLASS_NAME "ÆÎÐÆ ÄÅÑÅÒÜ-ØÅÑÒÜ"

LRESULT CALLBACK MyWindowFunc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

rbtree Tr;

INT WINAPI WinMain(_In_ HINSTANCE hInstance,
HINSTANCE hPrevInstance, CHAR* CmdLine, INT ShowCmd)
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
  /* MoveWindow(hConWnd, 1920 / 2, 0, 1920 / 2, 1080, FALSE); */
  SetWindowPos(hConWnd, HWND_TOP, 1920 / 2, 0, 1920 / 2, 1000, 0);

  for (int i = 0; i < 255; i++)
  {
    int rndval = rand() % 125;

    std::cout << "add" << rndval << std::endl;
    Tr.Acces(rndval);
  }

  //Tr.Put();
  std::cout << std::endl;

  std::cout << std::endl;
  //Tr.Draw();
  Tr.Delete(225);
  Tr.Draw();
  //Tr.SetXY();
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

  hWnd = CreateWindow(WND_CLASS_NAME, "Title", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
  ShowWindow(hWnd, SW_SHOWNORMAL);
  UpdateWindow(hWnd);

  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return msg.wParam;
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

    INT X, Y;

    if (wParam & MK_LBUTTON)
    {
      X = (SHORT)LOWORD(lParam);
      Y = (SHORT)HIWORD(lParam);
      OrgX += OldX - X;
      OrgY += OldY - Y;
      OldX = X;
      OldY = Y;
    }
    //InvalidateRect(hWnd, NULL, TRUE);
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
    SetTimer(hWnd, 3, 8, NULL);
    return 0;

  case WM_TIMER:
    SelectObject(hMemDC, hBm);

    SetWindowOrgEx(hMemDC, 0, 0, nullptr);

    SelectObject(hMemDC, GetStockObject(BLACK_BRUSH));
    Rectangle(hMemDC, W, H, 0, 0);

    SetWindowOrgEx(hMemDC, OrgX, OrgY, nullptr);

    SelectObject(hMemDC, GetStockObject(WHITE_BRUSH));
    SelectObject(hMemDC, GetStockObject(WHITE_PEN));
    Tr.SetXY(W);
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