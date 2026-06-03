/* Igoshev Makar, 10-6, 01.06.2026 */
#include <windows.h>
#include <math.h>
#include <time.h>

#define WND_CLASS_NAME "!!!"

LRESULT CALLBACK MyWindowFunc( HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT ShowCmd )
{
  WNDCLASS wc;
  MSG msg;

  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor = LoadCursor(NULL, IDC_HAND);
  wc.hIcon = LoadIcon(NULL, IDI_SHIELD);
  wc.hInstance = hInstance;
  wc.lpszMenuName = NULL;
  wc.lpszClassName = WND_CLASS_NAME;
  wc.lpfnWndProc = MyWindowFunc;

  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error registr window class", "ERROR", MB_ICONERROR | MB_OK);
    return 0;
  }

  //CreateWindowA( "EDIT", "", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 300, NULL, NULL, hInstance, NULL);
  CreateWindow(WND_CLASS_NAME, "SummerPractice2026", WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW | WS_VISIBLE,
    100, 100, 500, 300, NULL, NULL, hInstance, NULL);

  while(GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return msg.wParam;
}  

  LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  HFONT hFnt, hOldFnt;
  HPEN hPen, hOldPen;
  HDC hDC;
  PAINTSTRUCT ps;
  POINT pt;
  INT i, y, x;
  SYSTEMTIME st;
  DOUBLE angel_sec;
  CHAR Buf[100];
  static BOOL is_select = FALSE;
  static INT W, H;
  static HDC hMemDC, hDCClock;
  static HBITMAP hBm, hBmClock;
  BITMAP bm;

  switch ( Msg )
  {
  case WM_CREATE:
    hDC = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDC);
    ReleaseDC(hWnd, hDC);
    SetTimer(hWnd, 30, 100, NULL);

    hDCClock = CreateCompatibleDC(hMemDC);
    hBmClock = CreateCompatibleBitmap(hDCClock, W, H);
    hBmClock = LoadImage(NULL, "chasiki.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    return 0;

  case WM_SIZE:
    W = LOWORD(lParam);
    H = HIWORD(lParam);
    if (hBm != NULL)
      DeleteObject(hBm);
    hDC = GetDC(hWnd);
    hBm = CreateCompatibleBitmap(hDC, W, H);
    ReleaseDC(hWnd, hDC);
    SelectObject(hMemDC, hBm);
    break;

  case WM_LBUTTONDOWN:
    InvalidateRect(hWnd, NULL, FALSE);
    return 0;

  case WM_TIMER:
    InvalidateRect(hWnd, NULL, FALSE);
    return 0;

  case WM_ERASEBKGND:
    return 0;

  case WM_DESTROY:
    DeleteObject(hBm);
    DeleteDC(hMemDC);
    KillTimer(hWnd, 30);
    PostQuitMessage(0);
    return 0;

  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);

    hFnt = CreateFont(0, 0, 0, 0, FW_HEAVY, FALSE, FALSE, FALSE, RUSSIAN_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, VARIABLE_PITCH | FF_SWISS, "");
    hOldFnt = SelectObject(hMemDC, hFnt);
 
   
    
    SetDCBrushColor(hMemDC, RGB(0, 0, 0));
    SelectObject(hMemDC, GetStockObject(DC_BRUSH));
    Rectangle(hMemDC, -8, -8, W + 8, H + 8);

    GetObject(hBmClock, sizeof(BITMAP), &bm);
    StretchBlt(hMemDC, 0, 0, W, H, hDCClock, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
    SelectObject(hDCClock, hBmClock);
    //BitBlt(hMemDC, (W - bm.bmWidth) / 2, (H - bm.bmHeight) / 2, bm.bmWidth , bm.bmHeight, hDCClock, 0, 0, SRCCOPY);
    
    hPen = CreatePen(PS_SOLID, 8, RGB(255, 0, 0));
    hOldPen = SelectObject(hMemDC, hPen);
    GetLocalTime(&st);
    angel_sec = ((st.wSecond - 15) + (st.wMilliseconds / 1000.0)) * 3.14 / 30;

    pt.x = (W / 2) + 200 * cos(angel_sec);
    pt.y = (H / 2) + 200 * sin(angel_sec);

    MoveToEx(hMemDC, W / 2, H / 2, NULL);
    LineTo(hMemDC, pt.x , pt.y );

    hPen = CreatePen(PS_SOLID, 10, RGB(0, 255, 0));
    hOldPen = SelectObject(hMemDC, hPen);

    angel_sec = ((st.wMinute - 15) + (st.wSecond - 15) / 60.0) * 3.14 / 30;

    pt.x = (W / 2) + 100 * cos(angel_sec);
    pt.y = (H / 2) + 100 * sin(angel_sec);

    MoveToEx(hMemDC, W / 2, H / 2, NULL);
    LineTo(hMemDC, pt.x , pt.y );


    hPen = CreatePen(PS_SOLID, 12, RGB(180, 0, 255));
    hOldPen = SelectObject(hMemDC, hPen);

    angel_sec = ((st.wHour - 3) + (st.wMinute - 15) / 60.0) * 3.14 / 6;

    pt.x = (W / 2) + 50 * cos(angel_sec);
    pt.y = (H / 2) + 50 * sin(angel_sec);

    MoveToEx(hMemDC, W / 2, H / 2, NULL);
    LineTo(hMemDC, pt.x , pt.y );


    

    SetBkColor(hMemDC, RGB(220, 220, 180));
    SetTextColor(hMemDC, RGB(255, 0, 0));
    GetLocalTime(&st);
    TextOut(hMemDC, W / 12, H / 12, Buf, sprintf(Buf, ">>> %d x %d ::время: %i: %i: %i <<<", W, H, st.wHour, st.wMinute, st.wSecond));
    DeleteObject(hFnt);
    DeleteObject(hOldFnt);

    BitBlt(hDC, 0, 0, W, H, hMemDC, 0, 0, SRCCOPY);
    DeleteObject(hPen);
    EndPaint(hWnd, &ps);
    return 0;

  case WM_MOUSEMOVE:
    hDC = GetDC(hWnd);
    ReleaseDC(hWnd, hDC);
    InvalidateRect(hWnd, NULL, TRUE);
    return 0;

  case WM_CLOSE:
    if (MessageBox(hWnd, "Are you sure close window?", "Exit", MB_YESNO | MB_ICONQUESTION) == IDNO)
      return 0;
    break;
  }

  return DefWindowProc(hWnd, Msg, wParam, lParam);
}
