/* FILE NAME: main.C
 * PURPOSE: 3D math implementation module.
 * PROGRAMMER: MI6
 * DATE: 10.06.2026
 */
#include <windows.h>
#include <math.h>
#include <time.h>
#include "def.h"

#define WND_CLASS_NAME "something"

LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );

INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT ShowCmd )
{
  WNDCLASS wc;
  MSG msg;
  HWND hWnd;

  SetDbgMemHooks();

    /* window class register */
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
    MessageBox(NULL, "Error", "ERROR", MB_ICONERROR);
    return 0;
  }
  /* create window */ 
  CreateWindowA(WND_CLASS_NAME, "text", WS_CLIPCHILDREN|WS_OVERLAPPEDWINDOW|WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL); 
  /* main program loop  */
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return 30;
}

LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  static HBITMAP hBm;
  static HDC hMemDC;
  static BITMAP bm;
  PAINTSTRUCT ps;
  HDC hDC;
  static INT W, H, StartTime, Framecount;
  //static DBL t;

  switch (Msg)
  {
  case WM_CREATE:
    MI6_RndInit();
    SetTimer(hWnd, 30, 1, NULL);
    hDC = GetDC(hWnd);
    ReleaseDC(hWnd, hDC);
    return 0;

  case WM_ERASEBKGND:
    return 1;

  case WM_SIZE:
    SendMessage(hWnd, WM_TIMER, 0, 0);
    return 0;

  case WM_TIMER:
    return 0;

  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    EndPaint(hWnd, &ps);
    return 0;

  case WM_DESTROY:
    MI6_RndClose();
    KillTimer(hWnd, 30);
    PostMessage(NULL, WM_QUIT, 0, 0);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}