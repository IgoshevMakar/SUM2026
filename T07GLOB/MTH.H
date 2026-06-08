 /* FILE NAME: mth.h
 * PURPOSE: 3D math implementation module.
 * PROGRAMMER: MI6
 * DATE: 08.06.2026
 */
 
#ifndef __mth_h_
#define __mth_h_
 
#include <math.h>
 
#include <windows.h>
 
/* Pi math constant */
#define PI 3.14159265358979323846
 
/* Degrees to radians conversion */
#define D2R(A) ((A) * (PI / 180.0))
#define Degree2Radian(a) D2R(a)
#define UnitMatrix 
{                  
  {                
    {1, 0, 0, 0},  
    {0, 1, 0, 0},  
    {0, 0, 1, 0},  
    {0, 0, 0, 1}   
  }                
}
 
/* Base float point types */
typedef double DBL;
typedef float FLT;
 
/* Space vector/point representation type */
typedef struct tagVEC
{
  DBL X, Y, Z; /* Vector coordinates */
} VEC;
 
/* Transformation matrix representation type */
typedef struct tagMATR
{
  DBL A[4][4]; /* Matrix elements */
} MATR;
 
/* Add two vectors function.
 * ARGUMENTS:
 *   - vectors to be add:
 *       VEC V1, V2;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecAddVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X + V2.X, V1.Y + V2.Y, V1.Z + V2.Z);
} /* End of 'VecAddVec' function */

VEC VecSubVec( VEC V1, VEC V2 );  V1 Ц V2
VEC VecMulNum( VEC V1, DBL N );   V1 * N
VEC VecDivNum( VEC V1, DBL N );   V1 / N
 
VEC VecNeg( VEC V )
 {
  return VecSet(-V.X, -V.Y, -V.Z);
}
 
/* скал€рное произведение векторов */
DBL VecDotVec( VEC V1, VEC V2 )
{
  return V1.X * V2.X + V1.Y * V2.Y + V1.Z * V2.Z;
}
 
/* векторное произведение векторов */
VEC VecCrossVec( VEC V1, VEC V2 )
{
  return VecSet(V1.Y * V2.Z - V1.Z * V2.Y, V1.X * V2.Z - V1.Z * V2.X, V1.X * V2.Y - V1.X * V2.Y);
}
 
DBL VecLen2( VEC V );  |V|2
 
DBL VecLen( VEC V )   |V|
{
  DBL len = VecDotVec(V, V);
 
  if (len == 1 || len == 0)
    return len;
  return sqrt(len);
}

VEC VecNormalize( VEC V )   V/|V|
{
  DBL len = VecDotVec(V, V);
 
  if (len == 1 || len == 0)
    return V;
  return VecDivNum(V, sqrt(len));
}

__inline VEC PointTransform( VEC V, MATR M)
{
  return VecSet(V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0],
         V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1],
         V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2]);
}

MATR MatrIdentity( VOID )
{
  MATR I = 0055nitMatrix;
 
  return I;
}
 
MATR MatrSet( DBL A00, DBL A01, DBL A02, DBL A03,
              DBL A10, DBL A11, DBL A12, DBL A13,
              DBL A20, DBL A21, DBL A22, DBL A23,
              DBL A30, DBL A31, DBL A32, DBL A33 )
{
  MATR m =
  {
    {
      {A00, A01, A02, A03},
      {A10, A11, A12, A13},
      {A20, A21, A22, A23},
      {A30, A31, A32, A33},
    }
  };
 
  return m;
}
 
MATR MatrTranslate( VEC T )
{
  MATR m = UnitMatrix;
 
  m.A[3][0] = T.X;
  m.A[3][1] = T.Y;
  m.A[3][2] = T.Z;
  return m;
}
 
MATR MatrTranslate( VEC T )
{
  MATR m =
  {
    {
      {1, 0, 0, 0},
      {0, 1, 0, 0},
      {0, 0, 1, 0},
      {T.X, T.Y, T.Z, 1}
    }
  };
 
  return m;
}
 
MATR MatrTranslate( VEC T )
{
  return MatrSet(1, 0, 0, 0,
                 0, 1, 0, 0,
                 0, 0, 1, 0,
                 T.X, T.Y, T.Z, 1);
}
 
MATR MatrScale( VEC S )
{
  MatrSet( S.X,0, 0, 0,
              0, S.Y, 0, 0,
              0, 0, S.Z, 0,
              0, 0, 0, 1 )
}
MATR MatrRotateX( DBL AngleInDegree )
{
  MatrSet( 1,0, 0, 0,
    0, cos(AngleInDegree), sin(AngleInDegree), 0,    
    0, sin(AngleInDegree), cos(AngleInDegree), 0,
   0, 0, 0, 1 );

}
MATR MatrRotateY( DBL AngleInDegree 
{
  MatrSet( 1,0, 0, 0,
    0, cos(AngleInDegree), sin(AngleInDegree), 0,
    0, -sin(AngleInDegree), cos(AngleInDegree), 0,
    0, 0, 0, 1 );
}
MATR MatrRotateZ( DBL AngleInDegree )
{
  MatrSet( 1,0, 0, 0,
    0, cos(AngleInDegree), sin(AngleInDegree), 0,
    0, -sin(AngleInDegree), cos(AngleInDegree), 0,
    0, 0, 0, 1 );
}

MATR MatrTranspose( MATR M );

MATR MatrRotate( DBL AngleInDegree, VEC V ) 
{
  DBL c, s;

  V = VecMormalize(V);
  c = cos(AngleInDegree);
  s = sin(AngleInDegree);
  ax = V.X;
  ay = V.Y;
  az = V.Z;

  return (MatrSet(c + ax * ax * (1 - c), ax * ay * (1 - c), ax * az * (1 - c) - ay * s,
    ay * ax * (1 - c) - az * s, c + ay * ay * (1 - c), ay * az * (1 - c) + ax * s,
    az * ax * (1 - c) + ay * s, az * ay * (1 - c) - ax * s, c + ax * ax * (1 - c));



}
 
MATR MatrMulMatr( MATR M1, MATR M2 )
{
  MATR r = {{{0}}};
 
  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      for (k = 0; k < 4; k++)
        r.M[i][j] += M1.A[i][k] * M2.A[k][j];
  return r;
}
 
MATR MatrTranspose( MATR M )
{
  return MatrSet(M.A[0][0], M.A[1][0], M.A[2][0], M.A[3][0], 
                 M.A[0][1], M.A[1][1], M.A[2][1], M.A[3][1], 
                 M.A[0][2], M.A[1][2], M.A[2][2], M.A[3][2],
                 M.A[0][3], M.A[1][3], M.A[2][3], M.A[3][3], );
}
 
 
DBL MatrDeterm3x3( DBL A11, DBL A12, DBL A13,
                   DBL A21, DBL A22, DBL A23,
                   DBL A31, DBL A32, DBL A33 )
 {
  return A11 * A22 * A33 + A12 * A23 * A31 + A13 * A21 A32 Ц
         A11 * A23 * A32 Ц A12 * A21 * A33 Ц A13 * A22 * A31;
}

DBL MatrDeterm( MATR M )
{
  return
    M.A[0][0] * MatrDeterm3x3(M.A[1][1], M.A[1][2], M.A[1][3],
                              M.A[2][1], M.A[2][2], M.A[2][3],
                              M.A[3][1], M.A[3][2], M.A[3][3]) +
    -M.A[0][1] * MatrDeterm3x3(M.A[1][0], M.A[1][2], M.A[1][3],
                               M.A[2][0], M.A[2][2], M.A[2][3],
                               M.A[3][0], M.A[3][2], M.A[3][3]) +
    M.A[0][2] * MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][3],
                              M.A[2][0], M.A[2][1], M.A[2][3],
                              M.A[3][0], M.A[3][1], M.A[3][3]) +
    -M.A[0][2] * MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][2],
                               M.A[2][0], M.A[2][1], M.A[2][2],
                               M.A[3][0], M.A[3][1], M.A[3][2]);
}
 
MATR MatrInverse( MATR M )
{
  DBL det = MatrDeterm(M);
  MATR r;
 
  if (det == 0)
    return MatrIdentity();
 
 
  /* Build adjoint matrix */
  r.A[0][0] =
    MatrDeterm3x3(M.A[1][1], M.A[1][2], M.A[1][3],
                  M.A[2][1], M.A[2][2], M.A[2][3],
                  M.A[3][1], M.A[3][2], M.A[3][3]) / det;
  r.A[1][0] =
    -MatrDeterm3x3(M.A[1][0], M.A[1][2], M.A[1][3],
                   M.A[2][0], M.A[2][2], M.A[2][3],
                   M.A[3][0], M.A[3][2], M.A[3][3]) / det;
  r.A[2][0] =
    MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][3],
                  M.A[2][0], M.A[2][1], M.A[2][3],
                  M.A[3][0], M.A[3][1], M.A[3][3]) / det;
  r.A[3][0] =
    -MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][2],
                   M.A[2][0], M.A[2][1], M.A[2][2],
                   M.A[3][0], M.A[3][1], M.A[3][2]) / det;
 
  r.A[0][1] =
    -MatrDeterm3x3(M.A[0][1], M.A[0][2], M.A[0][3],
                   M.A[2][1], M.A[2][2], M.A[2][3],
                   M.A[3][1], M.A[3][2], M.A[3][3]) / det;
  r.A[1][1] =
    MatrDeterm3x3(M.A[0][0], M.A[0][2], M.A[0][3],
                  M.A[2][0], M.A[2][2], M.A[2][3],
                  M.A[3][0], M.A[3][2], M.A[3][3]) / det;
  r.A[2][1] =
    -MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][3],
                   M.A[2][0], M.A[2][1], M.A[2][3],
                   M.A[3][0], M.A[3][1], M.A[3][3]) / det;
  r.A[3][1] =
    MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][2],
                  M.A[2][0], M.A[2][1], M.A[2][2],
                  M.A[3][0], M.A[3][1], M.A[3][2]) / det;
 
  r.A[0][2] =
    MatrDeterm3x3(M.A[0][1], M.A[0][2], M.A[0][3],
                  M.A[1][1], M.A[1][2], M.A[1][3],
                  M.A[3][1], M.A[3][2], M.A[3][3]) / det;
  r.A[1][2] =
    -MatrDeterm3x3(M.A[0][0], M.A[0][2], M.A[0][3],
                   M.A[1][0], M.A[1][2], M.A[1][3],
                   M.A[3][0], M.A[3][2], M.A[3][3]) / det;
  r.A[2][2] =
    MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][3],
                  M.A[1][0], M.A[1][1], M.A[1][3],
                  M.A[3][0], M.A[3][1], M.A[3][3]) / det;
  r.A[3][2] =
    -MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][2],
                   M.A[1][0], M.A[1][1], M.A[1][2],
                   M.A[3][0], M.A[3][1], M.A[3][2]) / det;
 
  r.A[0][3] =
    -MatrDeterm3x3(M.A[0][1], M.A[0][2], M.A[0][3],
                   M.A[1][1], M.A[1][2], M.A[1][3],
                   M.A[2][1], M.A[2][2], M.A[2][3]) / det;
  r.A[1][3] =
    MatrDeterm3x3(M.A[0][0], M.A[0][2], M.A[0][3],
                  M.A[1][0], M.A[1][2], M.A[1][3],
                  M.A[2][0], M.A[2][2], M.A[2][3]) / det;
  r.A[2][3] =
    -MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][3],
                   M.A[1][0], M.A[1][1], M.A[1][3],
                   M.A[2][0], M.A[2][1], M.A[2][3]) / det;
  r.A[3][3] =
    MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][2],
                  M.A[1][0], M.A[1][1], M.A[1][2],
                  M.A[2][0], M.A[2][1], M.A[2][2]) / det;
 
  return r;
}

/* Vector by matrix multiplication (with homogenious devide) function.
 * ARGUMENTS:
 *   - source vector:
 *       VEC V;
 *   - multiplied matrix:
 *       MATR M;
 * RETURNS:
 *   (VEC) result vector.
 */

__inline VEC VecMulMatr( VEC V, MATR M )
{
  DBL w = V.X * M.A[0][3] + V.Y * M.A[1][3] + V.Z * M.A[2][3] + M.A[3][3];
 
  return VecSet((V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0] + M.A[3][0]) / w,
                (V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1] + M.A[3][1]) / w,
                (V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2] + M.A[3][2]) / w);
} /* End of 'VecMulMatr' function */
 
#endif /* __mth_h_ */
/* END OF 'mth.h' FILE */
