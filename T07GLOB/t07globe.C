#include <windows.h>
#include <math.h>
#include <time.h>
#include "globe.h"

#define WND_CLASS_NAME "something"

LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );

INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT ShowCmd )
{
  WNDCLASS wc;
  MSG msg;

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
    //t = clock();
    //FrameCount = 0;
    SetTimer(hWnd, 30, 1, NULL);
    hDC = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDC);
    ReleaseDC(hWnd, hDC);
    hBm = NULL;
    
    GLB_Init(0.3);
    return 0;
  case WM_ERASEBKGND:
    return 1;
  case WM_SIZE:
    W = LOWORD(lParam);
    H = HIWORD(lParam);
    GLB_Resize(W, H);
    
    if (hBm != NULL)
      DeleteObject(hBm);
    hDC = GetDC(hWnd);
    hBm = CreateCompatibleBitmap(hDC, W, H);
    ReleaseDC(hWnd, hDC);
    SelectObject(hMemDC, hBm);
    
    SendMessage(hWnd, WM_TIMER, 0, 0);  

    return 0;
  case WM_TIMER:
   /* FrameCount++;
    t = clock();
    if (t - StartTime > CLOCKS_PER_SED)
    {
      FPS = FrameCount / t;

    }
    */

    Rectangle(hMemDC, 0, 0, W, H);
    GLB_Draw(hMemDC);
    hDC = GetDC(hWnd);
    BitBlt(hDC, 0, 0, W, H, hMemDC, 0, 0, SRCCOPY);
    ReleaseDC(hWnd, hDC);
    return 0;

  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    BitBlt(hDC, 0, 0, W, H, hMemDC, 0, 0, SRCCOPY);
    EndPaint(hWnd, &ps);
    return 0;

  case WM_DESTROY:
    if (hBm != NULL)
      DeleteObject(hBm);
    DeleteDC(hMemDC);
    KillTimer(hWnd, 30);
    PostMessage(NULL, WM_QUIT, 0, 0);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}