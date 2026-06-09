#ifndef __TIMER_H_
#define __TIMER_H_

#include <windows.h>

typedef unsigned long long UINT64;

extern DOUBLE GlobalTime, GlobalDeltaTime, GLB_Time, GLB_DeltaTime, GLB_FPS;
extern BOOL GLB_IsPause;

VOID Timer( VOID );

VOID GLB_TimerInit( VOID );

VOID GLB_TimerResponse( VOID );

#endif