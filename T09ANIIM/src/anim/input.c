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

VOID MI6_AnimInputInit( VOID )
{
  KeyBoardInit();
}

VOID MI6_AnimInputResponse( VOID )
{
  KeyboardResponse();
} 