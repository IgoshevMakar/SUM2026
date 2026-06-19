/* FILE NAME: rndprim.C
 * PURPOSE: 3D math implementation module.
 * PROGRAMMER: MI6
 * DATE: 09.06.2026
 */
#include "rnd.h"
#include <stdio.h>
#include <string.h>
#include "anim/anim.h"
 
VOID MI6_RndPrimCreate( mi6PRIM *Pr, mi6PRIM_TYPE Type, mi6VERTEX *V, INT NoofV, INT *Ind, INT NoofI )
{
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

    glBufferData(GL_ARRAY_BUFFER, sizeof(mi6VERTEX) * NoofV, V, GL_STATIC_DRAW);
 
    glVertexAttribPointer(0, 3, GL_FLOAT, FALSE, sizeof(mi6VERTEX),
                          (VOID *)0); /* position */
    glVertexAttribPointer(1, 2, GL_FLOAT, FALSE, sizeof(mi6VERTEX),
                          (VOID *)sizeof(VEC)); /* texture coordinates */
    glVertexAttribPointer(2, 3, GL_FLOAT, FALSE, sizeof(mi6VERTEX),
                          (VOID *)(sizeof(VEC) + sizeof(VEC2))); /* normal */
    glVertexAttribPointer(3, 4, GL_FLOAT, FALSE, sizeof(mi6VERTEX),
                          (VOID *)(sizeof(VEC) * 2 + sizeof(VEC2))); /* color */
 
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
 
    glBindVertexArray(0);

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
}

VOID MI6_RndPrimFree( mi6PRIM *Pr )
{
  if (Pr == NULL)
    return;
  glDeleteVertexArrays(1, &Pr->VA);
  glDeleteBuffers(1, &Pr->VBuf);
  glDeleteBuffers(1, &Pr->IBuf);
  memset(Pr, 0, sizeof(mi6PRIM));
}

VOID MI6_RndPrimTriMeshAutoNormals( mi6VERTEX *V, INT NumOfV, INT *Ind, INT NumOfI )
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
  MATR
    w = MatrMulMatr(Pr->Trans, World),
    winv = MatrTranspose(MatrInverse(w)),
    wvp = MatrMulMatr(w, MI6_RndMatrVP);
  UINT ProgId;
  INT loc,
    prim_type =
      Pr->Type == MI6_RND_PRIM_LINES ? GL_LINES :
      Pr->Type == MI6_RND_PRIM_TRIMESH ? GL_TRIANGLES :
      Pr->Type == MI6_RND_PRIM_TRISTRIP ? GL_TRIANGLE_STRIP :
      GL_POINTS;

  if ((ProgId = MI6_RndMtlApply(Pr->MtlNo)) == 0)
    return;
  glUseProgram(ProgId);

  /* Pass render uniforms */
  if ((loc = glGetUniformLocation(ProgId, "MatrWVP")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, wvp.A[0]);
  if ((loc = glGetUniformLocation(ProgId, "MatrW")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, w.A[0]);
  if ((loc = glGetUniformLocation(ProgId, "MatrWInv")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, winv.A[0]);
  if ((loc = glGetUniformLocation(ProgId, "Time")) != -1)
    glUniform1f(loc, MI6_Anim.Time);
  if ((loc = glGetUniformLocation(ProgId, "GlobalTime")) != -1)
    glUniform1f(loc, MI6_Anim.GlobalTime);

  glBindVertexArray(Pr->VA);

  if (Pr->IBuf == 0)
    glDrawArrays(prim_type, 0, Pr->NumOfElements);
  else
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
    glDrawElements(prim_type, Pr->NumOfElements, GL_UNSIGNED_INT, NULL);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }
  glBindVertexArray(0);
  glUseProgram(0); 
} /* End of 'MI6_RndPrimDraw' function */

BOOL MI6_RndPrimCreateSphere( mi6PRIM *Pr, DBL R, INT W, INT H )
{

  INT i, j, k;
  DBL theta, phi;
  DBL nl;
  VEC L = VecNormalize(VecSet(1, 1, 1));
  /* VEC4 color = Vec4Set(Rnd0(), Rnd0(),Rnd0(), Rnd0()); */
  mi6VERTEX *V;
  INT *Ind;
  INT size;

  /*glColor3f(0.8, 0, 0.8);*/

 
  memset(Pr, 0, sizeof(mi6PRIM));
  size = sizeof(mi6VERTEX) *  W * H + sizeof(INT) * (H - 1) * (W - 1) * 2 * 3;
 
  if ((V = malloc(size)) == NULL)
    return FALSE;
  Ind = (INT *)(V + W * H);

  /* Fill vertex array */
  for (k = 0, i = 0, theta = 0; i < H; i++, theta += PI / (H - 1))
    for (j = 0, phi = 0; j < W; j++, phi += 2 * PI / (W - 1))
      {
        V[k].N = VecSet(sin(theta) * sin(phi),
                      cos(theta),
                      sin(theta) * cos(phi));
        nl = VecDotVec(V[k].N, L);
        if (nl < 0.1)
          nl = 0.1;
        V[k].C = Vec4SetVec3(VecMulNum(VecSet(0.8, 0, 0.8), nl * 1.30));
        V[k++].P = VecSet(R * sin(theta) * sin(phi),
                              R * cos(theta),
                              R  * sin(theta) * cos(phi));
    }
   
  /* Fill vertex array */
  for (k = 0, i = 0; i < H - 1; i++)
    for (j = 0; j < W - 1; j++)
    {
      /* bottom-left */
      Ind[k++] = i * W + j;
      Ind[k++] = i * W + j + 1;
      Ind[k++] = (i + 1) * W + j;
      /* top-right */
      Ind[k++] = (i + 1) * W + j;
      Ind[k++] = i * W + j + 1;
      Ind[k++] = (i + 1) * W + j + 1;
    }
   MI6_RndPrimCreate(Pr, MI6_RND_PRIM_TRIMESH, V, W * H, Ind, (H - 1) * (W - 1) * 2 * 3);
   free(V);
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
  mi6VERTEX *V;
  INT *Ind;
  INT size;
  static CHAR Buf[3000];

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

  size = sizeof(mi6VERTEX) * nv + sizeof(INT) * nf * 3;
 
  if ((V = malloc(size)) == NULL)
    return FALSE;
  Ind = (INT *)(V + nv);
 
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
      V[nv++].P = VecSet(x / 50, y / 50, z / 50);
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
 
            Ind[nf++] = n1;
            Ind[nf++] = n2;
            Ind[nf++] = n3;
 
            n2 = n3;
          }
          fvn++;
        }
        oldc = *ptr++;
      }
    }
  }
  fclose(F);

  MI6_RndPrimTriMeshAutoNormals(V, nv, Ind, nf);
  
  for (i = 0; i < nv; i++) 
  {
    FLT nl = VecDotVec(V[i].N, L);

    if (nl < 0.1)
      nl = 0.1;
    V[i].C = Vec4Set(0.9 * nl, 0 * nl, 0.9 * nl, 1);
  }
  MI6_RndPrimCreate(Pr, MI6_RND_PRIM_TRIMESH, V, nv, Ind, nf);
  free(V);
  return TRUE;
} /* End of 'MI6_RndPrimLoad' function */