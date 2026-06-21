/* FILE NAME  : rndmtl.c
 * PROGRAMMER : MI6
 * UPDATE: 18.06.2026
 */

#include "anim/rnd/rnd.h"

mi6MATERIAL MI6_RndMaterials[MI6_MAX_MATERIALS]; 
INT MI6_RndMaterialSize;


mi6MATERIAL MI6_RndMtlGetDef( VOID )
{
  mi6MATERIAL def_mtl =
  {
    "Default",
    {0.1, 0.1, 0.1},
    {0.90, 0.90, 0.90},
    {0.30, 0.30, 0.30},
    30, 1,
    {-1, -1, -1, -1, -1, -1, -1, -1},
    0
  };

  return def_mtl;
}

INT MI6_RndMtlAdd( mi6MATERIAL *Mtl );

VOID MI6_RndMtlInit( VOID )
{
  mi6MATERIAL def = MI6_RndMtlGetDef();
  MI6_RndMaterialSize = 0;
  MI6_RndMtlAdd(&def);
}

VOID MI6_RndMtlClose( VOID )
{
}

INT MI6_RndMtlAdd( mi6MATERIAL *Mtl )
{
  if (MI6_RndMaterialSize >= MI6_MAX_MATERIALS)
    return 0;

  MI6_RndMaterials[MI6_RndMaterialSize] = *Mtl;
  return MI6_RndMaterialSize++;
}

UINT MI6_RndMtlApply( INT MtlNo )
{
  UINT prg;
  mi6MATERIAL *mtl;
  INT loc, i;
 
  if (MtlNo < 0 || MtlNo >= MI6_RndMaterialSize)
    MtlNo = 0;
  mtl = &MI6_RndMaterials[MtlNo];
 
  prg = mtl->ShdNo;
  if (prg < 0 || (INT)prg >= MI6_RndShadersSize)
    prg = MI6_RndShaders[0].ProgId;
  else
    prg = MI6_RndShaders[prg].ProgId;
 
  glUseProgram(prg);

  if ((loc = glGetUniformLocation(prg, "Ka")) != -1)
    glUniform3fv(loc, 1, &mtl->Ka.X);
  if ((loc = glGetUniformLocation(prg, "Kd")) != -1)
    glUniform3fv(loc, 1, &mtl->Kd.X);
  if ((loc = glGetUniformLocation(prg, "Ks")) != -1)
    glUniform3fv(loc, 1, &mtl->Ks.X);
  if ((loc = glGetUniformLocation(prg, "Ph")) != -1)
    glUniform1f(loc, mtl->Ph);
  if ((loc = glGetUniformLocation(prg, "Trans")) != -1)
    glUniform1f(loc, mtl->Trans);

  for (i = 0; i < 8; i++)
  {
    CHAR tname[] = "IsTexture0";
    CHAR tnamew[] = "IsTexture0W";
    CHAR tnameh[] = "IsTexture0H";
    BOOL IsTex = FALSE;

    tname[9] = '0' + i;
    tnamew[7] = '0' + i;
    tnameh[7] = '0' + i;

    if (mtl->Tex[i] != -1)
    {
      glActiveTexture(GL_TEXTURE0 + i);
      glBindTexture(GL_TEXTURE_2D, MI6_RndTextures[mtl->Tex[i]].TexId);
    }
    if ((loc = glGetUniformLocation(prg, tname)) != -1)
      glUniform1i(loc, mtl->Tex[i] != -1);
    if ((loc = glGetUniformLocation(prg, tnamew)) != -1)
      glUniform1i(loc, MI6_RndTextures[mtl->Tex[i]].W != -1);
    if ((loc = glGetUniformLocation(prg, tnameh)) != -1)
      glUniform1i(loc, MI6_RndTextures[mtl->Tex[i]].H != -1);
  }
  return prg;
}

mi6MATERIAL * MI6_RndMtlGet( INT MtlNo)
{
  if (MtlNo < 0 || MtlNo >= MI6_RndMaterialSize)
    MtlNo = 0;

  return &MI6_RndMaterials[MtlNo];
}