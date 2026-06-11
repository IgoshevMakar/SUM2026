/* FILE NAME: main.C
 * PURPOSE: 3D math implementation module.
 * PROGRAMMER: MI6
 * DATE: 09.06.2026
 * DATE: 10.06.2026
 */

#include <units/units.h>

/* Window class name */
#define WND_CLASS_NAME "039  window class"

/* Forward declaration */
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

/* Main startup program function.
 * ARGUMENTS:
 *   - application instance handle:
 *       HINSTANCE hInstance;
 *   - previouse application instance handle
 *     (not used, alway NULL):
 *       HINSTANCE hPrevInstance;
 *   - command line string:
 *       CHAR *CmdLine;
 *   - command line window show parameter (see SW_***):
 *       INT CmdShow;
 * RETURNS:
 *   (INT) system error level value.
 */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, 
                    CHAR *CmdLine, INT ShowCmd )
{
  WNDCLASS wc;
  MSG msg;
  HWND hWnd;

  SetDbgMemHooks();

  /* Window class register */
  wc.style = CS_VREDRAW | CS_HREDRAW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor = LoadCursor(NULL, IDC_HAND);
  wc.hIcon = LoadIcon(NULL, IDI_SHIELD);
  wc.hInstance = hInstance;
  wc.lpfnWndProc = MyWindowFunc;
  wc.lpszMenuName = NULL;
  wc.lpszClassName = WND_CLASS_NAME;

  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error", "ERROR", MB_ICONERROR | MB_OK);
    return 0;
  }
  
  /* Create window */
  hWnd = CreateWindowA(WND_CLASS_NAME, "anim", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
    100, 100, 700, 700, NULL, NULL, hInstance, NULL);

  MI6_AnimUnitAdd(MI6_UnitCreateBounceBall());

  /* Message loop */
  while (TRUE)
  if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
  {
    if (msg.message == WM_QUIT)
      break;
    DispatchMessage(&msg);
  }
  else
    SendMessage(hWnd, WM_TIMER, 47, 0);
  return msg.wParam;
} /* End of 'WinMain' function */

LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  HDC hDC;
  PAINTSTRUCT ps;
  static INT W, H;
  
  switch (Msg)
  { 

  case WM_CREATE:
    SetTimer(hWnd, 3, 8, NULL);
    MI6_AnimInit(hWnd);
    return 0;

  case WM_SIZE:
    MI6_AnimResize(LOWORD(lParam), HIWORD(lParam));
    SendMessage(hWnd, WM_TIMER, 47, 0);
    return 0;

  case WM_ERASEBKGND:
    return 1;

  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    MI6_RndCopyFrame(hDC);
    EndPaint(hWnd, &ps);
    return 0;

  case WM_TIMER:
    MI6_AnimRender();

    hDC = GetDC(hWnd);
    MI6_AnimCopyFrame(hDC);
    ReleaseDC(hWnd, hDC);

    return 0;

  case WM_DESTROY:
    MI6_AnimClose();
    PostQuitMessage(30);
    KillTimer(hWnd, 47);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}/* End of 'MyWindowFunc' function */
    
/* END OF 'main.c' FILE */