/* FILE NAME  : u_tex.c
 * PROGRAMMER : MI6
 * UPDATE: 18.06.2026
 */

#include "units.h"

typedef struct tagMI6UNIT_TEX
{
  MI6_UNIT_BASE_FIELDS;
  mi6PRIM Pr;
  INT MtlNo, TexId;
} mi6UNIT_TEX;

static VOID MI6_UnitInit( mi6UNIT_TEX *Uni, mi6ANIM *Ani )
{
  mi6VERTEX V[] =
  {
    {{0, 0, 0}, {0, 0}, {0, 0, 1}, {1, 1, 1, 1}},
    {{1, 0, 0}, {1, 0}, {0, 0, 1}, {1, 1, 1, 1}},
    {{0, 1, 0}, {0, 1}, {0, 0, 1}, {1, 1, 1, 1}},
    {{1, 1, 0}, {1, 1}, {0, 0, 1}, {1, 1, 1, 1}},
  };
  FLT t[2][2] =
  {
    {0.8, 1},
    {1, 0.3}
  };

  mi6MATERIAL mtl = MI6_RndMtlGetDef();
  strncpy(mtl.Name, "Texture sample", MI6_STR_MAX - 1);
  mtl.ShdNo = MI6_RndShdAdd("tex");
  Uni->MtlNo = MI6_RndMtlAdd(&mtl);

  glGenTextures(1, &Uni->TexId);
  glBindTexture(GL_TEXTURE_2D, Uni->TexId);
  glTexImage2D(GL_TEXTURE_2D, 0, 1, 2, 2, 0, GL_LUMINANCE, GL_FLOAT, t);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  MI6_RndPrimCreate(&Uni->Pr, MI6_RND_PRIM_TRISTRIP, V, 4, NULL, 0);
}

static VOID MI6_UnitClose( mi6UNIT_TEX *Uni, mi6ANIM *Ani )
{
  glDeleteTextures(1, &Uni->TexId);
  MI6_RndPrimFree(&Uni->Pr); 
}

static VOID MI6_UnitResponse( mi6UNIT_TEX *Uni, mi6ANIM *Ani )
{
} 

static VOID MI6_UnitRender( mi6UNIT_TEX *Uni, mi6ANIM *Ani )
{
  glActiveTexture(GL_TEXTURE0 + 5);
  glBindTexture(GL_TEXTURE_2D, Uni->TexId);
  MI6_RndPrimDraw(&Uni->Pr, MatrIdentity());
}

mi6UNIT * MI6_AnimUnitCreateTexture( VOID )
{
  MI6UNIT_TEX *Uni;
 
  if ((Uni = (mi6UNIT_TEX *)MI6_AnimUnitCreate(sizeof(mi6UNIT_TEX))) == NULL)
    return NULL;

  Uni->Init = (VOID *)MI6_UnitInit;
  Uni->Close = (VOID *)MI6_UnitClose;
  Uni->Response = (VOID *)MI6_UnitResponse;
  Uni->Render = (VOID *)MI6_UnitRender;
  return (mi6UNIT *)Uni;
}