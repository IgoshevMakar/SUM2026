/* FILE NAME: rnddata.C
 * PURPOSE: 3D math implementation module.
 * PROGRAMMER: MI6
 * DATE: 09.06.2026
 */

#include <windows.h>
#include "def.h"

#include "rnd.h"
HWND MI6_hRndWnd;        /* Work window handle */
HDC MI6_hRndDC;     /* Work window memory device context  */
HBITMAP MI6_hRndBmFrame; /* Work window background bitmap handle */
INT MI6_RndFrameW, MI6_RndFrameH; /* Work window size */
HGLRC MI6_hRndGLRC;

DBL
  MI6_RndProjSize = 0.1,     /* Project plane fit square */
  MI6_RndProjDist = 0.1,     /* Distance to project plane from viewer (near) */
  MI6_RndProjFarClip = 300;  /* Distance to project far clip plane (far) */
 
MATR
  MI6_RndMatrView, /* View coordinate system matrix */
  MI6_RndMatrProj, /* Projection coordinate system matrix */
  MI6_RndMatrVP;   /* Stored (View * Proj) matrix */

VEC MI6_RndCamLoc, MI6_RndCamDir, MI6_RndCamAt, MI6_RndCamRight;

INT MI6_RndShdAddonI[8];
FLT MI6_RndShdAddonF[8];
VEC MI6_RndShdAddonV[8];