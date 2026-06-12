/* FILE NAME  : anim.h
 * PROGRAMMER : MI6
 * LAST UPDATE: 11.06.2026
 */

#ifndef __anim_h_
#define __anim_h_

#include "def.h"
#include "rnd/rnd.h"

#define MI6_MAX_UNITS 3000
 
typedef struct tagmi6UNIT mi6UNIT;
typedef struct tagMI6ANIM MI6ANIM;


#define MI6_UNIT_BASE_FIELDS \
  VOID (*Init)( mi6UNIT *Uni, MI6ANIM *Ani );      \
  VOID (*Close)( mi6UNIT *Uni, MI6ANIM *Ani );     \
  VOID (*Response)( mi6UNIT *Uni, MI6ANIM *Ani );  \
  VOID (*Render)( mi6UNIT *Uni, MI6ANIM *Ani )

typedef struct tagmi6UNIT
{
  MI6_UNIT_BASE_FIELDS;
};

struct tagMI6ANIM
{                                              
  HWND hWnd;                      
  HDC hDC;                        
  INT W, H; 
  BOOL IsActive;
  BYTE Keys[256];     
  BYTE KeysClick[256];
  BYTE KeysOld[256];  
 
 
  mi6UNIT * Units[MI6_MAX_UNITS]; 
  INT NumOfUnits;            
 
  DBL
    GlobalTime, GlobalDeltaTime, 
    Time, DeltaTime,         
    FPS;                      
  BOOL
    IsPause;
};  

extern MI6ANIM MI6_Anim;

VOID MI6_AnimInit( HWND hWnd );
VOID MI6_AnimClose( VOID );
VOID MI6_AnimResize( INT W, INT H );
VOID MI6_AnimCopyFrame( VOID );
VOID MI6_AnimRender( VOID );
VOID MI6_AnimFlipFullScreen( VOID );
VOID MI6_AnimDoExit( VOID );
VOID MI6_AnimUnitAdd( mi6UNIT *Uni );
mi6UNIT * MI6_AnimUnitCreate( INT size );

VOID MI6_TimerInit( VOID );
VOID MI6_TimerResponse( VOID );

#endif