/* Igoshev Makar, 10-6, 01.06.2026 */
#include <windows.h>

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

  
  CreateWindowA( "EDIT", "", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 300, NULL, NULL, hInstance, NULL);
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
  HDC hDC;
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
    
    SelectObject(hDC, GetStockObject(DC_PEN));
    SetDCPenColor(hDC, RGB(0, 0, 0));
 
    Ellipse(hDC, 0, 0, 200, 200);
    Ellipse(hDC, 200, 0, 400, 200);

    SelectObject(hDC, GetStockObject( DC_BRUSH));
    SetDCBrushColor(hDC, RGB(0, 0, 0));

    Ellipse(hDC, 0, 0, 100, 100);
    Ellipse(hDC, 200, 0, 300, 100);
    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);

    EndPaint(hWnd, &ps);
    return 0;
  case WM_MOUSEMOVE:
    InvalidateRect(hWnd, NULL, TRUE);
    return 0;
  case WM_CLOSE:
    if (MessageBox(hWnd, "Are you sure close window?", "Exit", MB_YESNO | MB_ICONQUESTION) == IDNO)
      return 0;
    break;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}
