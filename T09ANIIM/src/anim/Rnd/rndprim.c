/* FILE NAME: rndprim.C
 * PURPOSE: 3D math implementation module.
 * PROGRAMMER: MI6
 * DATE: 09.06.2026
 */
#include "rnd.h"
#include <stdio.h>

BOOL MI6_RndPrimLoad( mi6PRIM *Pr, CHAR *FileName );
VOID MI6_RndPrimFree( mi6PRIM *Pr )
{
  free(Pr->V);
  memset(Pr, 0, sizeof(MI6VERTEX));
}
 
BOOL MI6_RndPrimCreate( mi6PRIM *Pr, INT NoofV, INT NoofI )
{
  INT size;
 
  memset(Pr, 0, sizeof(mi6PRIM));
  Pr->Trans = MatrIdenity();
  Pr->Type = Type;

  glGenVertexArrays(1, &Pr->VA);

  /* Vertex data */
  if (V != NULL && NoofV != 0)
  {
    glBindVertexArray(Pr->VA);
    glGenBuffers(1, &Pr->VBuf);
    
    glBindBuffer(GL_ARRAY_BUFFER, Pr->VBuf);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vg4VERTEX) * NoofV, V, GL_STATIC_DRAW);
 
    glVertexAttribPointer(0, 3, GL_FLOAT, FALSE, sizeof(vg4VERTEX),
                          (VOID *)0); /* position */
    glVertexAttribPointer(1, 2, GL_FLOAT, FALSE, sizeof(vg4VERTEX),
                          (VOID *)sizeof(VEC)); /* texture coordinates */
    glVertexAttribPointer(2, 3, GL_FLOAT, FALSE, sizeof(vg4VERTEX),
                          (VOID *)(sizeof(VEC) + sizeof(VEC2))); /* normal */
    glVertexAttribPointer(3, 4, GL_FLOAT, FALSE, sizeof(vg4VERTEX),
                          (VOID *)(sizeof(VEC) * 2 + sizeof(VEC2))); /* color */
 
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
 
    glBindVertexArray(0);
  }

  if (Ind != NULL && NoofI != 0)
  {
    glGenBuffers(1, &Pr->IBuf);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INT) * NoofI, Ind, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
 
    Pr->NumOfElements = NoofI;
  }
  else
    Pr->NumOfElements = NoofV;
    if (NoofV > 0)
    {
      INT i;
 
      Pr->MinBB = Pr->MaxBB = V[0].P;
      for (i = 1; i < NoofV; i++)
      {
        Pr->MinBB = VecMinVec(Pr->MinBB, V[i].P);
        Pr->MaxBB = VecMaxVec(Pr->MaxBB, V[i].P);
      }
    }
  }
  return TRUE;
}

VOID MI6_RndPrimTriMeshAutoNormals( MI6VERTEX *V, INT NumOfV, INT *Ind, INT NumOfI )
{
  INT i;

  for(i = 0; i < NumOfV; i++)
    V[i].N = VecSet(0, 0, 0);

  for (i = 0; i < NumOfI; i += 3)
  {
    VEC
      p0 = V[Ind[i]].P,
      p1 = V[Ind[i + 1]].P,
      p2 = V[Ind[i + 2]].P,
      N = VecNormalize(VecCrossVec(VecSubVec(p1, p0), VecSubVec(p2, p0)));

    V[Ind[i]].N = VecAddVec(V[Ind[i]].N, N);
    V[Ind[i + 1]].N = VecAddVec(V[Ind[i + 1]].N, N);
    V[Ind[i + 2]].N = VecAddVec(V[Ind[i + 2]].N, N);
  }
  for(i = 0; i < NumOfV; i++)
    V[i].N = VecNormalize(V[i].N);
}
VOID MI6_RndPrimDraw( mi6PRIM *Pr, MATR World )
{
  INT i;
  MATR wvp = MatrMulMatr3(Pr->Trans, World, MI6_RndMatrVP);
 
  glLoadMatrixf(wvp.A[0]);
 
  /* Draw triangles by edges */
  glBegin(GL_TRIANGLES);
  for (i = 0; i < Pr->NumOfI; i++)
  {
    glColor4fv(&Pr->V[Pr->I[i]].C.X);
    glVertex3fv(&Pr->V[Pr->I[i]].P.X);
  }
  glEnd();
}
BOOL MI6_RndPrimCreateSphere( mi6PRIM *Pr, DBL R, INT W, INT H )
{
  INT i, j, k;
  DBL theta, phi;
  DBL nl;
  VEC L = VecNormalize(VecSet(1, 1, 1));
  VEC4 color = Vec4Set(Rnd0(), Rnd0(),Rnd0(), Rnd0());
 
  INT size;
 
  memset(Pr, 0, sizeof(mi6PRIM));
  size = sizeof(MI6VERTEX) * NoofV + sizeof(INT) * NoofI;
 
  if ((Pr->V = malloc(size)) == NULL)
    return FALSE;
  Pr->I = (INT *)(Pr->V + NoofV);

  if (!MI6_RndPrimCreate(Pr, W * H, (H - 1) * (W - 1) * 2 * 3))
    return FALSE;

  /* Fill vertex array */
  for (k = 0, i = 0, theta = 0; i < H; i++, theta += PI / (H - 1))
    for (j = 0, phi = 0; j < W; j++, phi += 2 * PI / (W - 1))
      {
        Pr->V[k].N = VecSet(sin(theta) * sin(phi),
                      cos(theta),
                      sin(theta) * cos(phi));
        nl = VecDotVec(Pr->V[i].N, L);
        if (nl < 0.1)
          nl = 0.1;
        Pr->V[k].C = Vec4MulNum(color, nl);
        Pr->V[k++].P = VecSet(R * sin(theta) * sin(phi),
                              R * cos(theta),
                              R  * sin(theta) * cos(phi));
    }
   
  /* Fill vertex array */
  for (k = 0, i = 0; i < H - 1; i++)
    for (j = 0; j < W - 1; j++)
    {
      /* bottom-left */
      Pr->I[k++] = i * W + j;
      Pr->I[k++] = i * W + j + 1;
      Pr->I[k++] = (i + 1) * W + j;
      /* top-right */
      Pr->I[k++] = (i + 1) * W + j;
      Pr->I[k++] = i * W + j + 1;
      Pr->I[k++] = (i + 1) * W + j + 1;
    }
  return TRUE;
} /* End of 'MI6_RndPrimCreateSphere' function */
 /* Primitive free function.
 * ARGUMENTS:
 *   - primitive to be load:
 *       mi6PRIM *Pr;
 *   - primitve filename (.OBJ):
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FLASE otherwise.
 */
BOOL MI6_RndPrimLoad( mi6PRIM *Pr, CHAR *FileName )
{
  INT i;
  FILE *F;
  INT nv = 0, nf = 0;
  VEC L = VecNormalize(VecSet(1, 1, 1));
  static CHAR Buf[3000];
 
  memset(Pr, 0, sizeof(mi6PRIM));
  size = sizeof(MI6VERTEX) * NoofV + sizeof(INT) * NoofI;
 
  if ((Pr->V = malloc(size)) == NULL)
    return FALSE;
  Pr->I = (INT *)(Pr->V + NoofV);

  memset(Pr, 0, sizeof(mi6PRIM));
 
  if ((F = fopen(FileName, "r")) == NULL)
    return FALSE;

  /* Count vertices and indices */
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
  {
    if (Buf[0] == 'v' && Buf[1] == ' ')
      nv++;
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT n = 0;
      CHAR *ptr = Buf + 2, oldc = ' ';
 
      while (*ptr != 0)
      {
        if (*ptr != ' ' && oldc == ' ')
          n++;
        oldc = *ptr++;
      }
 
      nf += n - 2;
    }
  }
 
  if (!MI6_RndPrimCreate(Pr, nv, nf * 3))
  {
    fclose(F);
    return FALSE;
  }
 
  /* Load model */
  rewind(F);
  nv = 0;
  nf = 0;
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
  {
    if (Buf[0] == 'v' && Buf[1] == ' ')
    {
      DBL x, y, z;
 
      sscanf(Buf + 2, "%lf%lf%lf", &x, &y, &z);
      Pr->V[nv++].P = VecSet(x / 50, y / 50, z / 50);
    }
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT n, n1, n2, n3;
      INT fvn = 0;
      CHAR *ptr = Buf + 2, oldc = ' ';
 
      while (*ptr != 0)
      {
        if (*ptr != ' ' && oldc == ' ')
        {
          sscanf(ptr, "%d", &n);
          if (n > 0)
            n--;
          else
            if (n < 0)
              n = nv + n;
 
          if (fvn == 0)
            n1 = n;
          else if (fvn == 1)
            n2 = n;
          else
          {
            n3 = n;
 
            Pr->I[nf++] = n1;
            Pr->I[nf++] = n2;
            Pr->I[nf++] = n3;
 
            n2 = n3;
          }
          fvn++;
        }
        oldc = *ptr++;
      }
    }
  }
  fclose(F);
  MI6_RndPrimTriMeshAutoNormals(Pr->V, Pr->NumOfV, Pr->I, Pr->NumOfI);

  for (i = 0; i < Pr->NumOfV; i++) 
  {
    FLT nl = VecDotVec(Pr->V[i].N, L);

    if (nl < 0.1)
      nl = 0.1;
    Pr->V[i].C = Vec4Set(0.9 * nl, 0 * nl, 0.9 * nl, 1);
  }
  return TRUE;
} /* End of 'MI6_RndPrimLoad' function */