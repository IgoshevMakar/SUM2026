#include <time.h>
typedef unsigned long long UINT64;

extern DOUBLE GlobalTime, GlobalDeltaTime, Time, DeltaTime, FPS;
extern BOOL
  IsPause;

VOID Timer( VOID );

VOID GLB_TimerInit( VOID );

VOID GLB_TimerResponse( VOID );