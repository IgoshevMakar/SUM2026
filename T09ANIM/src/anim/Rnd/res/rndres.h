#ifndef __rndres_h_
#define __rndres_h_

#include "def.h"

 

VOID MI6_RndResInit();
VOID MI6_RndResClose();

//#define MI6_MAX_SHADRERS 30
//extern mi6SHADER MI6_RndShaders[MI6_MAX_SHADRERS];
//extern INT MI6_RndShadersSize;
INT MI6_RndShdAdd( CHAR *ShaderFileNamePrefix );
VOID MI6_RndShdUpdate( VOID );

VOID MI6_RndShdInit( VOID );
VOID MI6_RndShdClose( VOID );


/* Material store type */
/* typedef struct tagmi6MATERIAL
{
  CHAR Name[MI6_STR_MAX]; /* Material name */
 
  /* Illumination coefficients */    
  /* VEC Ka, Kd, Ks;           /* Ambient, diffuse, specular coefficients */
  //FLT Ph;                   /* Phong power coefficient */
 
  //FLT Trans;                /* Transparency factor */
 
  //INT Tex[8];               /* Texture references from texture table (or -1) */
 
  //INT ShdNo;
/* } mi6MATERIAL;
#define MI6_MAX_MATERIALES 30
extern mi6MATERIAL MI6_RndMaterials[MI6_MAX_MATERIALES];
extern INT MI6_RndMaterialSize;
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
VOID MI6_RndMtlInit( VOID );
VOID MI6_RndMtlClose( VOID );


typedef struct tagmi6TEXTURE
{
  CHAR Name[MI6_STR_MAX]; /* Texture name */
  //INT W, H;               /* Texture size in pixels */
  //UINT TexId;             /* OpenGL texture Id */ 
/* } mi6TEXTURE
#define MI6_MAX_TEXTURES 3000
extern mi6TEXTURE MI6_RndTextures[MI6_MAX_TEXTURES];
extern INT MI6_RndTexturesSize;
INT MI6_RndTexAddImg( CHAR *Name, INT W, INT H, INT C, VOID *Bits );
INT VG4_RndTexAdd( CHAR *FileName );
VOID MI6_RndTexInit( VOID );
VOID MI6_RndTexClose( VOID ); */



#endif