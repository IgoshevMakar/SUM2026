/* FILE NAME: rndbase.C
 * PURPOSE: 3D math implementation module.
 * PROGRAMMER: MI6
 * DATE: 09.06.2026
 */

#include "rnd.h"

VOID MI6_RndInit( HWND hWnd )
{
  HDC hDC;

  MI6_hRndWnd = hWnd;
  hDC = GetDC(hWnd);
  MI6_hRndDCFrame = CreateCompatibleDC(hDC);
  ReleaseDC(hWnd, hDC);
    
  MI6_hRndBmFrame = NULL;

  MI6_RndResize(47, 47);
  MI6_RndCamSet(VecSet1(8), VecSet1(0), VecSet(0, 1, 0));
}

VOID MI6_RndClose( VOID )
{
  DeleteObject(MI6_hRndBmFrame);
  DeleteDC(MI6_hRndDCFrame);
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


VOID MI6_RndStart( VOID )
{
  SelectObject(MI6_hRndDCFrame, GetStockObject(DC_BRUSH));
  SetDCBrushColor(MI6_hRndDCFrame, RGB(0, 0, 0));
  Rectangle(MI6_hRndDCFrame, 0, 0, MI6_RndFrameW, MI6_RndFrameH);
}

VOID MI6_RndEnd( VOID )
{

}

VOID MI6_RndProjSet( VOID )
{
  DBL rx, ry;
 
  rx = ry = MI6_RndProjSize;
  /* Correct aspect ratio */
  if (MI6_RndFrameW > MI6_RndFrameH)
    rx *= (DBL)MI6_RndFrameW / MI6_RndFrameH;
  else
    ry *= (DBL)MI6_RndFrameH / MI6_RndFrameW;
  MI6_RndMatrProj =
    MatrFrustum(-rx / 2, rx / 2, -ry / 2, ry / 2,
      MI6_RndProjDist, MI6_RndProjFarClip);
  MI6_RndMatrVP = MatrMulMatr(MI6_RndMatrView, MI6_RndMatrProj);
}
  
VOID MI6_RndCamSet( VEC Loc, VEC At, VEC Up )
{
  MI6_RndMatrView = MatrView(Loc, At, Up);
  MI6_RndMatrVP = MatrMulMatr(MI6_RndMatrView, MI6_RndMatrProj);
}