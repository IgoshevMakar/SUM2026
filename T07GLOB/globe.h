#include <math.h>
#include <windows.h>

#ifndef __globe_h_
#define __globe_h_

#define GLB_GRID_W 4
#define GLB_GRID_H 6

typedef DOUBLE DBL;

typedef struct
{
  DBL X, Y, Z;
} VEC;
 
VOID GLB_Draw( HDC hDC );
VOID GLB_Resize( INT Ws, INT Hs );
VOID GLB_Init( DBL R );

static VEC GLB_GeomN[GLB_GRID_H][GLB_GRID_W];

#endif /* __globe_h_ */