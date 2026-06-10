/* FILE NAME: timer.c
 * PURPOSE: 3D math implementation module.
 * PROGRAMMER: MI6
 * DATE: 09.06.2026
 */
#include <windows.h>
#include "timer.h"

typedef unsigned long long UINT64;

DOUBLE GlobalTime, GlobalDeltaTime, /* Global time and interframe interval */
  GLB_Time, GLB_DeltaTime,             /* Time with pause and interframe interval */
  GLB_FPS;                         /* Frames per second value */
BOOL
  GLB_IsPause;                     /* Pause flag */

static UINT64
  StartTime,    /* Start program time */
  OldTime,      /* Previous frame time */
  OldTimeFPS,   /* Old time FPS measurement */
  PauseTime,    /* Time during pause period */
  TimePerSec,   /* Timer resolution */
  FrameCounter; /* Frames counter */

VOID GLB_TimerInit( VOID )
{
  LARGE_INTEGER cnt;
  LARGE_INTEGER freq;

  QueryPerformanceFrequency(&freq);
  TimePerSec = freq.QuadPart;

  
  QueryPerformanceCounter(&cnt);
  StartTime = OldTime = OldTimeFPS = cnt.QuadPart;

  PauseTime = 0;
  FrameCounter = 0;
  GLB_IsPause = FALSE;
  GLB_Time = GLB_DeltaTime = 0;
  GLB_FPS = 30;
} 

VOID GLB_TimerResponse( VOID )
{
  LARGE_INTEGER t;
 
  QueryPerformanceCounter(&t);
 
  /* Global time */
  GlobalTime = (DOUBLE)(t.QuadPart - StartTime) / TimePerSec;
  GlobalDeltaTime = (DOUBLE)(t.QuadPart - OldTime) / TimePerSec;

  /* Time with pause */
  if (!GLB_IsPause)
  {
    GLB_Time = (DOUBLE)(t.QuadPart - PauseTime - StartTime) / TimePerSec;
    GLB_DeltaTime = GlobalDeltaTime;
  }
  else
  {
    GLB_DeltaTime = 0;
    PauseTime += t.QuadPart - OldTime;
  }
 
  /* FPS */
  FrameCounter++;
  if (t.QuadPart - OldTimeFPS > 0.1 * TimePerSec)
  {
    GLB_FPS = FrameCounter * TimePerSec / (DOUBLE)(t.QuadPart - OldTimeFPS);
    OldTimeFPS = t.QuadPart;
    FrameCounter = 0;
  }
  OldTime = t.QuadPart;
}