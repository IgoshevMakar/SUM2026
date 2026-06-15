#include "anim/anim.h"

static BYTE OldKeys[256];

static VOID KeyBoardInit( VOID )
{
  INT i;

  GetKeyboardState(MI6_Anim.Keys);
  for (i = 0; i < 256; i++)
    MI6_Anim.Keys[i] >>= 7;
  memcpy(OldKeys, MI6_Anim.Keys, 256);
}

static VOID KeyboardResponse( VOID )
{
  INT i;

  GetKeyboardState(MI6_Anim.Keys);
  for (i = 0; i < 256; i++)
  {
    MI6_Anim.Keys[i] >>= 7;
    MI6_Anim.KeysClick[i] = MI6_Anim.Keys[i] && !OldKeys[i];
  }
  memcpy(OldKeys, MI6_Anim.Keys, 256);
}

INT MI6_MouseWheel;

static VOID MouseInit( VOID )
{
  POINT pt;

  GetCursorPos(&pt);
  ScreenToClient(MI6_Anim.hWnd, &pt);

  MI6_Anim.Mdx = 0;
  MI6_Anim.Mdy = 0;

  MI6_Anim.Mx = pt.x;
  MI6_Anim.My = pt.y;

  MI6_Anim.Mdz = MI6_MouseWheel;
  MI6_Anim.Mz += MI6_MouseWheel;
  
  MI6_MouseWheel = MI6_Anim.Mdz = MI6_Anim.Mz = 0;
}

static VOID MouseResponse( VOID )
{
  POINT pt;

  GetCursorPos(&pt);
  ScreenToClient(MI6_Anim.hWnd, &pt);

  MI6_Anim.Mdx = pt.x - MI6_Anim.Mx;
  MI6_Anim.Mdy = pt.y - MI6_Anim.My;

  MI6_Anim.Mx = pt.x;
  MI6_Anim.My = pt.y;

  MI6_Anim.Mdz = MI6_MouseWheel;
  MI6_Anim.Mz += MI6_MouseWheel;
  MI6_MouseWheel = 0;
}

VOID MI6_AnimInputInit( VOID )
{
  KeyBoardInit();
  MouseInit();
}

VOID MI6_AnimInputResponse( VOID )
{
  KeyboardResponse();
  MouseResponse();
} 