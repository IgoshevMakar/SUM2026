/* FILE NAME: rndbase.C
 * PURPOSE: 3D math implementation module.
 * PROGRAMMER: MI6
 * DATE: 10.06.2026
 */
#include <windows.h>
#include "def.h"

HWND MI6_hRndWnd;        /* Work window handle */
HDC MI6_hRndDCFrame;     /* Work window memory device context  */
HBITMAP MI6_hRndBmFrame; /* Work window background bitmap handle */
INT MI6_RndFrameW, MI6_RndFrameH; /* Work window size */

VOID MI6_RndInit( HWND hWnd )
{

}
VOID MI6_RndClose( VOID )
{

}

VOID MI6_RndResize( INT W, INT H )
{
  HDC hDC = GetDC(MI6_hRndWnd);
 
  if (MI6_hRndBmFrame != NULL)
    DeleteObject(MI6_hRndBmFrame);
  MI6_hRndBmFrame = CreateCompatibleBitmap(hDC, W, H);
  ReleaseDC(MI6_hRndWnd, hDC);		
 
  SelectObject(MI6_hRndDCFrame, MI6_hRndBmFrame);
 
  MI6_RndFrameW = W;
  MI6_RndFrameH = H;
 
 
  MI6_RndProjSet();
}
 
 
VOID MI6_RndCopyFrame( HDC hDC )
{
  BitBlt(hDC, 0, 0, MI6_RndFrameW, MI6_RndFrameH,
    MI6_hRndDCFrame, 0, 0, SRCCOPY);
}

VOID MI6_RndStart( VOID );
VOID MI6_RndEnd( VOID );