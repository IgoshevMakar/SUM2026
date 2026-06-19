/* FILE NAME: main.C
 * PURPOSE: 3D math implementation module.
 * PROGRAMMER: MI6
 * DATE: 12.06.2026
 */

#include <units/units.h>
#include <stdio.h>

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
  INT i;
  CONSOLE_FONT_INFOEX cfi = {0};
  HWND hConWnd;

  SetDbgMemHooks();
  /* Create console */
  AllocConsole();
 
  cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
  GetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
  cfi.dwFontSize.Y = 18;
  cfi.FontWeight = FW_BOLD;
  SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
 
  freopen("CONOUT$", "w", stdout);
  system("@chcp 1251 > nul");
  printf("\x1b[38;2;%d;%d;%dm \x1b[48;2;%d;%d;%dm", 255, 255, 0, 0, 102, 102);

  printf("Группа компьютерной графики ФМЛ № 30\n");
  printf("\x1b[38;2;%d;%d;%dm\x1b[48;2;%d;%d;%dm", 0, 255, 0, 90, 90, 90);
  printf("Computer Graphics Support Group\n");
  printf("\x1b[38;2;%d;%d;%dm\x1b[48;2;%d;%d;%dm", 255, 255, 255, 0, 0, 0);
  fflush(stdout);
 
  hConWnd = GetConsoleWindow();
  /* MoveWindow(hConWnd, 2560 + 1920 / 2, 0, 1920 / 2, 1080, FALSE); */
  SetWindowPos(hConWnd, HWND_TOP, 256 + 192 / 2, 0, 192 / 2, 100, 0);

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
  srand(30);
  for (i = 0; i < 5; i++)
    MI6_AnimUnitAdd(MI6_UnitCreateBounceBall());
  MI6_AnimUnitAdd(MI6_UnitCreateCow());
  MI6_AnimUnitAdd(MI6_UnitCreateLandscape());
  MI6_AnimUnitAdd(MI6_UnitCreateControl());
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
    MI6_AnimCopyFrame();
    EndPaint(hWnd, &ps);
    return 0;

  case WM_ACTIVATE:
    MI6_Anim.IsActive = HIWORD(wParam) != WA_INACTIVE;
    return 0;

  case WM_ENTERSIZEMOVE:
    MI6_Anim.IsActive = FALSE;
    return 0;

  case WM_EXITSIZEMOVE:
    MI6_Anim.IsActive = TRUE;
    ReleaseCapture();
    SetFocus(hWnd);
    return 0;

  case WM_TIMER:
    MI6_AnimRender();
    MI6_AnimCopyFrame();
    return 0;

  case WM_LBUTTONDOWN:
    SetCapture(hWnd);
    return 0;

  case WM_LBUTTONUP:
    ReleaseCapture();
    return 0;

  case WM_MOUSEWHEEL:
    MI6_MouseWheel += (SHORT)HIWORD(wParam);
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