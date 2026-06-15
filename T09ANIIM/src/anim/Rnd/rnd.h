/* FILE NAME: rnd.h
 * PURPOSE: 3D math implementation module.
 * PROGRAMMER: MI6
 * DATE: 09.06.2026
 */
#define GLEW_STATIC
#include <glew.h>
#include "def.h"
#include "res/rndres.h"

extern HWND MI6_hRndWnd;        /* Work window handle */
extern HDC MI6_hRndDC;     /* Work window memory device context  */
extern INT MI6_RndFrameW, MI6_RndFrameH; /* Work window size */

extern DBL
  MI6_RndProjSize,     /* Project plane fit square */
  MI6_RndProjDist,     /* Distance to project plane from viewer (near) */
  MI6_RndProjFarClip;  /* Distance to project far clip plane (far) */
 
extern MATR
  MI6_RndMatrView, /* View coordinate system matrix */
  MI6_RndMatrProj, /* Projection coordinate system matrix */
  MI6_RndMatrVP; /* Stored (View * Proj) matrix */

typedef struct tagMI6VERTEX
{
  VEC P;  /* Vertex position */
  VEC2 T;  /* Vertex texture coordinate */
  VEC N;  /* Vertex normal */
  VEC4 C;  /* Vertex color */
} MI6VERTEX;

typedef struct tagmi6PRIM
{
  mi6PRIM_TYPE Type;

  INT 
    VA,
    VBuf,
    IBUF;

  INT NumOfElements;

  VEC MinBB, MaxBB;
} mi6PRIM;
 
VOID APIENTRY glDebugOutput( UINT Source, UINT Type, UINT Id, UINT Severity,
                             INT Length, const CHAR *Message,
                             const VOID *UserParam );
BOOL MI6_RndPrimCreate( mi6PRIM *Pr, INT NoofV, INT NoofI );
VOID MI6_RndPrimFree( mi6PRIM *Pr );
VOID MI6_RndPrimDraw( mi6PRIM *Pr, MATR World );
BOOL MI6_RndPrimCreateSphere( mi6PRIM *Pr, DBL R, INT W, INT H );
BOOL MI6_RndPrimLoad( mi6PRIM *Pr, CHAR *FileName );
VOID MI6_RndPrimTriMeshAutoNormals( MI6VERTEX *V, INT NumOfV, INT *Ind, INT NumOfI );
VOID MI6_RndInit( HWND hWnd );
VOID MI6_RndClose( VOID );
VOID MI6_RndResize( INT W, INT H );
VOID MI6_RndCopyFrame( VOID );
VOID MI6_RndStart( VOID );
VOID MI6_RndEnd( VOID );
VOID MI6_RndProjSet( VOID );
VOID MI6_RndCamSet( VEC Loc, VEC At, VEC Up );


#ifndef __rnd_h_
#define __rnd_h_

#include "def.h"

#endif /* __rnd_h_ */