/*       #include "units.h"


typedef struct tagMI6UINT_CONTROL
{
  MI6_UNIT_BASE_FIELDS;
  mi6PRIM CONTROL;
  VEC Pos;
  DBL Shift, Scale;
} mi6UNIT_CONTROL;

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       mi6UNIT_CONTROL *Uni;
 *   - animation context:
 *       MI6ANIM *Ani;
 * RETURNS: None.
 */
/* static VOID MI6_UnitInit( mi6UNIT_CONTROL *Uni, MI6ANIM *Ani )
{
  Uni->CamLoc = VecSet(8, 8, 8);
} /* End of 'MI6_UnitInit' function */
 
/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       mi6UNIT_CONTROL *Uni;
 *   - animation context:
 *       MI6ANIM *Ani;
 * RETURNS: None.
 */
/* static VOID MI6_UnitClose( mi6UNIT_CONTROL *Uni, MI6ANIM *Ani )
{
  MI6_RndPrimFree(&Uni->CONTROL);
} /* End of 'MI6_UnitClose' function */
 
/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       mi6UNIT_CONTROL *Uni;
 *   - animation context:
 *       MI6ANIM *Ani;
 * RETURNS: None.
 */
/* static VOID MI6_UnitResponse( mi6UNIT_CONTROL *Uni, MI6ANIM *Ani )
{
} /* End of 'MI6_UnitResponse' function */
 
/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       mi6UNIT_CONTROL *Uni;
 *   - animation context:
 *       MI6ANIM *Ani;
 * RETURNS: None.
 */
/* static VOID MI6_UnitRender( mi6UNIT_CONTROL *Uni, MI6ANIM *Ani )
{
  MI6_RndPrimDraw(&Uni->CONTROL, MatrTranslate(VecAddVec(Uni->Pos, VecSet(0, fabs(sin(5 * Ani->Time)), 0))));
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
  mi6UNIT *Uni;
 
  /* Memory allocation */
  if ((Uni = MI6_AnimUnitCreate(sizeof(mi6UNIT_CONTROL))) == NULL)
    return NULL;
 
  /* Setup unit methods */
  Uni->Init = (VOID *)MI6_UnitInit;
  Uni->Close = (VOID *)MI6_UnitClose;
  Uni->Response = (VOID *)MI6_UnitResponse;
  Uni->Render = (VOID *)MI6_UnitRender;
 
  return Uni;
} /* End of 'MI6_AnimUnitCreate' function */ */