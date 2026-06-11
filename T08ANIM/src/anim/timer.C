/* FILE NAME: timer.c
 * PURPOSE: 3D math implementation module.
 * PROGRAMMER: MI6
 * DATE: 09.06.2026
 */
#include <windows.h>
#include <time.h>

typedef unsigned long long UINT64;

DOUBLE GlobalTime, GlobalDeltaTime, /* Global time and interframe interval */
  MI6_Time, MI6_DeltaTime,             /* Time with pause and interframe interval */
  MI6_FPS;                         /* Frames per second value */
BOOL
  MI6_IsPause;                     /* Pause flag */

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
  MI6_IsPause = FALSE;
  MI6_Time = MI6_DeltaTime = 0;
  MI6_FPS = 30;
} 

VOID MI6_TimerResponse( VOID )
{
  LARGE_INTEGER t;
 
  QueryPerformanceCounter(&t);
 
  /* Global time */
  GlobalTime = (DOUBLE)(t.QuadPart - StartTime) / TimePerSec;
  GlobalDeltaTime = (DOUBLE)(t.QuadPart - OldTime) / TimePerSec;

  /* Time with pause */
  if (!MI6_IsPause)
  {
    MI6_Time = (DOUBLE)(t.QuadPart - PauseTime - StartTime) / TimePerSec;
    MI6_DeltaTime = GlobalDeltaTime;
  }
  else
  {
    MI6_DeltaTime = 0;
    PauseTime += t.QuadPart - OldTime;
  }
 
  /* FPS */
  FrameCounter++;
  if (t.QuadPart - OldTimeFPS > 0.1 * TimePerSec)
  {
    MI6_FPS = FrameCounter * TimePerSec / (DOUBLE)(t.QuadPart - OldTimeFPS);
    OldTimeFPS = t.QuadPart;
    FrameCounter = 0;
  }
  OldTime = t.QuadPart;
}