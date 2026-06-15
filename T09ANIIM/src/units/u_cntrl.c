#include "units.h"
#include <stdio.h>

typedef struct tagmi6UINT_CONTROL
{
  MI6_UNIT_BASE_FIELDS;
  VEC CamLoc, CamAt;
  DBL Speed;
} mi6UNIT_CONTROL;

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       mi6UNIT_CONTROL *Uni;
 *   - animation context:
 *       MI6ANIM *Ani;
 * RETURNS: None.
 */
  static VOID MI6_UnitInit( mi6UNIT_CONTROL *Uni, MI6ANIM *Ani )
{
  Uni->CamLoc = VecSet(8, 8, 8);
  Uni->CamAt = VecSet(0, 0, 0);
  Uni->Speed = 1;
} /* End of 'MI6_UnitInit' function */
 
/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       mi6UNIT_CONTROL *Uni;
 *   - animation context:
 *       MI6ANIM *Ani;
 * RETURNS: None.
 */
static VOID MI6_UnitClose( mi6UNIT_CONTROL *Uni, MI6ANIM *Ani )
{
} /* End of 'MI6_UnitClose' function */
 
/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       mi6UNIT_CONTROL *Uni;
 *   - animation context:
 *       MI6ANIM *Ani;
 * RETURNS: None.
 */
 static VOID MI6_UnitResponse( mi6UNIT_CONTROL *Uni, MI6ANIM *Ani )
{
  VEC d;
  INT modes[2];
 
  if (Ani->KeysClick['P'])
    Ani->IsPause = !Ani->IsPause;

  if (Ani->Keys[VK_SHIFT] && Ani->KeysClick['W'])
  {
    glGetIntegerv(GL_POLYGON_MODE, modes);

    if (modes[0] == GL_FILL)
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
  }

  if (Ani->KeysClick[VK_ESCAPE])
    MI6_AnimDoExit();

  d = VecNormalize(VecSubVec(Uni->CamAt, Uni->CamLoc));;

  Uni->CamLoc = 
    VecAddVec(Uni->CamLoc,
      VecMulNum(d, Ani->GlobalDeltaTime * 0.1 * (Ani->Mdz)));

  Uni->CamLoc =
    PointTransform(Uni->CamLoc,
      MatrRotateY(Ani->Keys[VK_LBUTTON] * 
        Ani->Mdx));

  MI6_RndCamSet(Uni->CamLoc, Uni->CamAt, VecSet(0, 1, 0));
} /* End of 'MI6_UnitResponse' function */
 
/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       mi6UNIT_CONTROL *Uni;
 *   - animation context:
 *       MI6ANIM *Ani;
 * RETURNS: None.
 */
static VOID MI6_UnitRender( mi6UNIT_CONTROL *Uni, MI6ANIM *Ani )
{
  CHAR Buf[102];
  static DBL OldTime;
  
  if (Ani->GlobalTime - OldTime < 2)
  {
    sprintf(Buf, "FPS: %.3f", Ani->FPS);
    SetWindowText(Ani->hWnd, Buf);
    OldTime = Ani->GlobalTime;
  }
} /* End of 'MI6_UnitRender' function */
 
/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (mi6UNIT *) pointer to created unit.
 */
 mi6UNIT * MI6_UnitCreateControl( VOID )
{
  mi6UNIT_CONTROL *Uni;

  if (( Uni = (mi6UNIT_CONTROL *)MI6_AnimUnitCreate(sizeof(mi6UNIT_CONTROL))) == NULL)
    return NULL;
  Uni->Init = (VOID *)MI6_UnitInit;                      
  Uni->Response = (VOID *)MI6_UnitResponse;
  Uni->Render = (VOID *)MI6_UnitRender;
  return (mi6UNIT *)Uni;
} /* End of 'MI6_AnimUnitCreate' function */  