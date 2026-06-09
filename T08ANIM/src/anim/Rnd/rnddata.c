#include <windows.h>
#include "def.h"

DOUBLE
  MI6_RndProjSize = 0.1,     /* Project plane fit square */
  MI6_RndProjDist = 0.1,     /* Distance to project plane from viewer (near) */
  MI6_RndProjFarClip = 300;  /* Distance to project far clip plane (far) */
 
MATR
  MI6_RndMatrView, /* View coordinate system matrix */
  MI6_RndMatrProj, /* Projection coordinate system matrix */
  MI6_RndMatrVP;   /* Stored (View * Proj) matrix */
 
void MI6_RndProjSet( void )
{
  DOUBLE rx, ry;
 
  rx = ry = MI6_RndProjSize;
  /* Correct aspect ratio */
  if (MI6_RndFrameW > MI6_RndFrameH)
    rx *= (DOUBLE)MI6_RndFrameW / MI6_RndFrameH;
  else
    ry *= (DOUBLE)MI6_RndFrameH / MI6_RndFrameW;
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
 
VOID MI6_RndCamSet(VecSet1(5), VecSet1(0), VecSet(0, 1, 0));
 
VOID MI6_RndPrimDraw( MI6PRIM *Pr, MATR World )
{
  MATR wvp = MatrMulMatr(World, MI6_RndMatrVP);

    VEC p = VecMulMatr(Prim->V[i], wvp);
 
    pnts[i].x = (INT)((P.X + 1) * MI6_RndFrameW / 2);
    pnts[i].y = (INT)((-P.Y + 1) * MI6_RndFrameH / 2);

}