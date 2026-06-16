/* FILE NAME: timer.c
 * PURPOSE: 3D math implementation module.
 * PROGRAMMER: MI6
 * DATE: 09.06.2026
 */
#include "anim/anim.h"


static UINT64
  StartTime,    /* Start program time */
  OldTime,      /* Previous frame time */
  OldTimeFPS,   /* Old time FPS measurement */
  PauseTime,    /* Time during pause period */
  TimePerSec,   /* Timer resolution */
  FrameCounter; /* Frames counter */

VOID MI6_TimerInit( VOID )
{
  LARGE_INTEGER cnt;
  LARGE_INTEGER freq;

  QueryPerformanceFrequency(&freq);
  TimePerSec = freq.QuadPart;

  QueryPerformanceCounter(&cnt);
  StartTime = OldTime = OldTimeFPS = cnt.QuadPart;

  PauseTime = 0;
  FrameCounter = 0;
  MI6_Anim.IsPause = FALSE;
  MI6_Anim.Time = MI6_Anim.DeltaTime = 0;
  MI6_Anim.FPS = 30;
} 

VOID MI6_TimerResponse( VOID )
{
  LARGE_INTEGER t;
 
  QueryPerformanceCounter(&t);
 
  /* Global time */
  MI6_Anim.GlobalTime = (DOUBLE)(t.QuadPart - StartTime) / TimePerSec;
  MI6_Anim.GlobalDeltaTime = (DOUBLE)(t.QuadPart - OldTime) / TimePerSec;

  /* Time with pause */
  if (!MI6_Anim.IsPause)
  {
    MI6_Anim.Time = (DOUBLE)(t.QuadPart - PauseTime - StartTime) / TimePerSec;
    MI6_Anim.DeltaTime = MI6_Anim.GlobalDeltaTime;
  }
  else
  {
    MI6_Anim.DeltaTime = 0;
    PauseTime += t.QuadPart - OldTime;
  }
 
  /* FPS */
  FrameCounter++;
  if (t.QuadPart - OldTimeFPS > 0.1 * TimePerSec)
  {
    MI6_Anim.FPS = FrameCounter * TimePerSec / (DOUBLE)(t.QuadPart - OldTimeFPS);
    OldTimeFPS = t.QuadPart;
    FrameCounter = 0;
  }                            
  OldTime = t.QuadPart;
}