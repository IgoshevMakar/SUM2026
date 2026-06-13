/* FILE NAME  : anim.c
 * PROGRAMMER : MI6
 * LAST UPDATE: 11.06.2026
 */

#include "anim.h"

MI6ANIM MI6_Anim;

VOID MI6_AnimInit( HWND hWnd )
{
  memset(&MI6_Anim, 0, sizeof(MI6ANIM));
  MI6_Anim.hWnd = hWnd;
  MI6_RndInit(hWnd);
  MI6_Anim.hDC = MI6_hRndDC;
  MI6_Anim.W = MI6_RndFrameW;
  MI6_Anim.H = MI6_RndFrameH;

  MI6_TimerInit();

  MI6_AnimInputInit();
}

VOID MI6_AnimClose( VOID )
{
  INT i;

  for (i = 0; i < MI6_Anim.NumOfUnits; i++)
  {
    MI6_Anim.Units[i]->Close(MI6_Anim.Units[i], &MI6_Anim);
    free(MI6_Anim.Units[i]);
  }
  MI6_Anim.NumOfUnits = 0;
  MI6_RndClose();
}

VOID MI6_AnimResize( INT W, INT H )
{
  MI6_RndResize(W, H);
  MI6_Anim.W = W;
  MI6_Anim.H = H;
}
VOID MI6_AnimCopyFrame( VOID )
{
  MI6_RndCopyFrame();
}
VOID MI6_AnimRender( VOID )
{
  INT i;

  MI6_TimerResponse();

  MI6_AnimInputResponse();


  for (i = 0; i < MI6_Anim.NumOfUnits; i++)
    MI6_Anim.Units[i]->Response(MI6_Anim.Units[i], &MI6_Anim);

  MI6_RndStart();

  for (i = 0; i < MI6_Anim.NumOfUnits; i++)
    MI6_Anim.Units[i]->Render(MI6_Anim.Units[i], &MI6_Anim);
  
  MI6_RndEnd();
}

VOID MI6_AnimFlipFullScreen( VOID )
{
}
VOID MI6_AnimDoExit( VOID )
{
  static BOOL IsFinalizeStart = FALSE;

  if (IsFinalizeStart)
    return;
  IsFinalizeStart = TRUE;
  if (MessageBox(MI6_Anim.hWnd, "Are you shure close the window?",
    "Exit", MB_OKCANCEL | MB_ICONQUESTION | MB_DEFBUTTON1) != IDOK)
  {
    IsFinalizeStart = FALSE;
    return;
  }
  PostMessage(MI6_Anim.hWnd, WM_CLOSE, 0, 0);
}

VOID MI6_AnimUnitAdd( mi6UNIT *Uni )
{
  if (MI6_Anim.NumOfUnits < MI6_MAX_UNITS)
    MI6_Anim.Units[MI6_Anim.NumOfUnits++] = Uni, Uni->Init(Uni, &MI6_Anim);
}