/* FILE NAME  : rndres.h
 * PROGRAMMER : MI6
 * UPDATE: 18.06.2026
 */

#ifndef __rndres_h_
#define __rndres_h_

#include "def.h"

#define MI6_STR_MAX 3000
#define MI6_MAX_SHADERS 30

typedef struct tagmi6SHADER
{
  CHAR Name[MI6_STR_MAX];
  UINT ProgId;
} mi6SHADER;

extern mi6SHADER MI6_RndShaders[MI6_MAX_SHADERS];
extern INT MI6_RndShadersSize;

#define MI6_MAX_TEXTURES 300

typedef struct tagmi6TEXTURES
{
  CHAR Name[MI6_STR_MAX];
  INT W, H;
  UINT TexId;
} mi6TEXTURES;

extern mi6TEXTURES MI6_RndTextures[MI6_MAX_TEXTURES];
extern INT MI6_RndTexturesSize;  

typedef struct tagmi6MATERIAL
{
  CHAR Name[MI6_STR_MAX];
  VEC Ka, Kd, Ks;
  FLT Ph;
  FLT Trans;
  INT Tex[8];
  INT ShdNo;
} mi6MATERIAL;

#define MI6_MAX_MATERIALS 300

extern mi6MATERIAL MI6_RndMaterials[MI6_MAX_MATERIALS]; 
extern INT MI6_RndMaterialSize;

VOID MI6_RndResInit();
VOID MI6_RndResClose();

INT MI6_RndShdAdd( CHAR *ShaderFileNamePrefix );
VOID MI6_RndShdUpdate( VOID );
VOID MI6_RndShdInit( VOID );
VOID MI6_RndShdClose( VOID );

#endif