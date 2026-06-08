#include <windows.h>
#include "globe.h"
#include <time.h>

#define pi 3.14159265358979323846
#define GLB_MIN(A, B) ((A) < (B) ? (A) : (B))
#define GLB_MAX(A, B) ((A) > (B) ? (A) : (B))

static VEC GLB_Geom[GLB_GRID_H][GLB_GRID_W];
static INT GLB_Ws, GLB_Hs;
static DBL GLB_ProjSize = 1, GLB_Wp, GLB_Hp, GLB_ProjDist = 1;

VEC RotateZ( VEC P, DBL Angle );
VEC RotateX( VEC P, DBL Angle );
VEC RotateY( VEC P, DBL Angle );
VOID GLB_Init ( DBL R );

COLORREF ColorTo255( VEC Color )
{
  INT R = (INT)(Color.X * 255), G = (INT)(Color.Y * 255), B = (INT)(Color.Z * 255);

  R = 255;
  G = 0;
  B = 255;
  return RGB(R, G, B);
}

VOID GLB_Draw( HDC hDC )
{
  DBL xp, yp, len, t;
  INT i, j, s = 2;
  static POINT pnts[GLB_GRID_H][GLB_GRID_W];
  POINT pts[4];
  VEC P;
  VEC L;

  for (i = 0; i < GLB_GRID_H; i++)
    for (j = 0; j < GLB_GRID_W; j++)
    {
      P = GLB_Geom[i][j];
      P.Z -= 1;
      xp = P.X * GLB_ProjDist / (-P.Z);
      yp = P.Y * GLB_ProjDist / (-P.Z);
      pnts[i][j].x = (INT)(xp * GLB_Ws / GLB_Wp + GLB_Ws / 2); 
      pnts[i][j].y = (INT)(-yp * GLB_Hs / GLB_Hp + GLB_Hs / 2); 
    }

  SetDCPenColor(hDC, RGB(0, 255, 0));
  SelectObject(hDC, GetStockObject(DC_PEN));
  for (i = 0; i < GLB_GRID_H; i++)
  {
    MoveToEx(hDC, pnts[i][0].x, pnts[i][0].y, NULL);
    for (j = 0; j < GLB_GRID_W; j++)
    {
      LineTo(hDC, pnts[i][j].x, pnts[i][j].y);
    }
  }
  for (j = 0; j < GLB_GRID_W; j++)  
  {  
    MoveToEx(hDC, pnts[0][j].x, pnts[0][j].y, NULL);
    for (i = 0; i < GLB_GRID_H; i++)
      {
         LineTo(hDC, pnts[i][j].x, pnts[i][j].y);
      }
  }
  
  L.X = 1;
  L.Y = 1;
  L.Z = 1;
  len = sqrt(L.X * L.X + L.Y * L.Y + L.Z * L.Z);
  L.X /= len;
  L.Y /= len;
  L.Z /= len;

  for (i = 0; i < GLB_GRID_H - 1; i++)
  {
    for (j = 0; j < GLB_GRID_W - 1; j++)
    {
      VEC N = GLB_Geom[i][j];
      DBL nl;
      VEC C = {0.47, 0.8, 0.30};
      t = clock() / (DBL)CLOCKS_PER_SEC;
      N = RotateZ( N, 10 * t);
      N = RotateX( N, 20 * t);
      N = RotateY( N, 10 * t);
      nl = N.X * L.X + N.Y * L.Y + N.Z * L.Z;
      C.X *= nl;
      C.Y *= nl;
      C.Z *= nl;

      SetDCPenColor(hDC, RGB(255, 255, 255));
      SetDCBrushColor(hDC, RGB(20, 255, 40));
      SelectObject(hDC, GetStockObject(DC_PEN));
      SelectObject(hDC, GetStockObject(DC_BRUSH));
  
      pts[0] = pnts[i][j];
      pts[1] = pnts[i][j + 1];
      pts[2] = pnts[i + 1][j + 1];
      pts[3] = pnts[i + 1][j];
      
      SetDCBrushColor(hDC, ColorTo255(C));
      SelectObject(hDC, GetStockObject(DC_BRUSH));
      Polygon(hDC, pts, 4);
  
      SetDCBrushColor(hDC, RGB(0, 0, 0));
      SelectObject(hDC, GetStockObject(DC_BRUSH));
    }
  }
}

VOID GLB_Resize( INT Ws, INT Hs )
{
  DBL Wp, Hp;
  GLB_Ws = Ws;
  GLB_Hs = Hs;
  if (GLB_Ws >= GLB_Hs)
  {  
    GLB_Wp = GLB_ProjSize * GLB_Ws / GLB_Hs;
    GLB_Hp = GLB_ProjSize;
  }
  else
  {
    Wp = GLB_ProjSize;
    Hp = GLB_ProjSize * Hs / Ws;
  }
}

/* Rotate vector around Z axis function.
 * ARGUMENTS:
 *   - vector coordinates:
 *       VEC P;
 *   - rotation angle in degrees:
 *       DBL Angle;
 * RETURNS:
 *   (VEC) rotated vector.
 */
VEC RotateZ( VEC P, DBL Angle )
{
  VEC NewP;
  DBL a = Angle * pi / 180, si = sin(a), co = cos(a);
 
  NewP.X = P.X * co - P.Y * si;
  NewP.Y = P.X * si + P.Y * co;
  NewP.Z = P.Z;
  return NewP;
}

/* Rotate vector around X axis function.
 * ARGUMENTS:
 *   - vector coordinates:
 *       VEC P;
 *   - rotation angle in degrees:
 *       DBL Angle;
 * RETURNS:
 *   (VEC) rotated vector.
 */
VEC RotateX( VEC P, DBL Angle )
{
  VEC NewP;
  DBL a = Angle * pi / 180, si = sin(a), co = cos(a);
 
  NewP.X = P.X;
  NewP.Y = P.Y * co - P.Z * si;
  NewP.Z = P.Y * si + P.Z * co;
  return NewP;
} /* End of 'RotateX' function */
 
/* Rotate vector around Y axis function.
 * ARGUMENTS:
 *   - vector coordinates:
 *       VEC P;
 *   - rotation angle in degrees:
 *       DBL Angle;
 * RETURNS:
 *   (VEC) rotated vector.
 */
VEC RotateY( VEC P, DBL Angle )
{
  VEC NewP;
  DBL a = Angle * pi / 180, si = sin(a), co = cos(a);
 
  NewP.X = P.Z * si + P.X * co;
  NewP.Y = P.Y;
  NewP.Z = P.Z * co - P.X * si;
  return NewP;
} /* End of 'RotateY' function */

VOID GLB_Init ( DBL R )
{
  DBL t;
  INT i, j;

  for (i = 0; i < GLB_GRID_H; i++)  
  {
    DBL theta = i * pi / (GLB_GRID_H - 1);
    for (j = 0; j < GLB_GRID_W; j++)
    {
      DBL phi = j * 2 * pi / (GLB_GRID_W - 1);
      t = clock() / (DBL)CLOCKS_PER_SEC;
      GLB_GeomN[i][j].X = sin(theta) * sin(phi);
      GLB_GeomN[i][j].Y = cos(theta);
      GLB_GeomN[i][j].Z = sin(theta) * cos(phi);
      
      GLB_Geom[i][j].X = R * sin(theta) * sin(phi);
      GLB_Geom[i][j].Y = R * cos(theta);
      GLB_Geom[i][j].Z = R * sin(theta) * cos(phi);
      
      GLB_Geom[i][j] = RotateZ( GLB_Geom[i][j], 10 * t);
      GLB_Geom[i][j] = RotateX( GLB_Geom[i][j], 20 * t);
      GLB_Geom[i][j] = RotateY( GLB_Geom[i][j], 10 * t);
    }
  }
}