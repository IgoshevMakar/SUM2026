/* Igoshev Makar, 10-6, 01.06.2026 */
#include <windows.h>
#include <math.h>

#define WND_CLASS_NAME "!!!"

LRESULT CALLBACK MyWindowFunc( HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam);

void DrawArrow( HWND hWnd, HDC hdc, INT xc, INT yc, INT L, INT W)
{
  POINT pnts[] =
{
  {L, 0}, {-W, -W}, {0, 0}, {-W, W}
};
  POINT pt;
  POINT pnts_res[4];
  int X, Y, i;
  double len, cos, sin;

  GetCursorPos(&pt);
  ScreenToClient(hWnd, &pt);

  len = sqrt((pt.x - xc) * (pt.x - xc) + (pt.y - yc) * (pt.y - yc));
  X = (pt.x - xc) * L/len + xc;
  Y = (pt.y - yc) * L/len + yc;

  cos = (pt.x - xc) / len;
  sin = (pt.y - yc) / len;

  for (i = 0; i < 4; i++) 
  {
    pnts_res[i].x = xc + pnts[i].x * cos + pnts[i].y * sin;
    pnts_res[i].y = yc - pnts[i].y * cos + pnts[i].x * sin;
  }
  Polygon(hdc, pnts_res, sizeof(pnts_res) / sizeof(pnts_res[0]));
  MoveToEx(hdc, xc, yc, NULL);
  LineTo(hdc, X, Y);

}

INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT ShowCmd )
{
  WNDCLASS wc;
  MSG msg;
  HWND hwnd;
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
  hwnd = CreateWindow(WND_CLASS_NAME, "SummerPractice2026", WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW | WS_VISIBLE,
    100, 100, 500, 300, NULL, NULL, hInstance, NULL);

  CreateWindow("BUTTON1", "Static", WS_CHILD | WS_VISIBLE,
    10, 10, 100, 30, hwnd, (HMENU)123, hInstance, NULL);
  CreateWindow("BUTTON2", "Random", WS_CHILD | WS_VISIBLE,
    10, 47, 100, 30, hwnd, (HMENU)124, hInstance, NULL);


  while(GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return msg.wParam;
}  


  LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  HDC hDC;
  INT i, j, mode = 0;
  PAINTSTRUCT ps;
  POINT pt;
  static BOOL is_select = FALSE;
  static INT W, H;

  switch ( Msg )
  {
  case WM_SIZE:
    W = LOWORD(lParam);
    H = HIWORD(lParam);
    break;
  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;  
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);

    for (i = 0; i < H; i += 150)
      for (j = 0; j < W; j += 145)
        DrawArrow( hWnd, hDC, j, i, 30, 30);
    ReleaseDC(hWnd, hDC);
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
