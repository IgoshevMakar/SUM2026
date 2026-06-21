#include "units/units.h"

typedef struct tagmi6UINT_COW
{
  MI6_UNIT_BASE_FIELDS;
  mi6PRIM Cow;
} mi6UNIT_COW;

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       mi6UNIT_COW *Uni;
 *   - animation context:
 *       MI6ANIM *Ani;
 * RETURNS: None.
 */
static VOID MI6_UnitInit( mi6UNIT_COW *Uni, MI6ANIM *Ani )
{
  MI6_RndPrimLoad(&Uni->Cow, "bin/models/cow.obj");


} /* End of 'MI6_UnitInit' function */
 
/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       mi6UNIT_COW *Uni;
 *   - animation context:
 *       MI6ANIM *Ani;
 * RETURNS: None.
 */
static VOID MI6_UnitClose( mi6UNIT_COW *Uni, MI6ANIM *Ani )
{
  MI6_RndPrimFree(&Uni->Cow);
} /* End of 'MI6_UnitClose' function */
 
/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       mi6UNIT_COW *Uni;
 *   - animation context:
 *       MI6ANIM *Ani;
 * RETURNS: None.
 */
static VOID MI6_UnitResponse( mi6UNIT_COW *Uni, MI6ANIM *Ani )
{
} /* End of 'MI6_UnitResponse' function */
 
/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       mi6UNIT_COW *Uni;
 *   - animation context:
 *       MI6ANIM *Ani;
 * RETURNS: None.
 */
static VOID MI6_UnitRender( mi6UNIT_COW *Uni, MI6ANIM *Ani )
{
  INT s = 4, i, j, k;

  for (i = -s; i <= s; i++)
    for (j = -s; j <= s; j++)
      for (k = -s; k <= s; k++)
      MI6_RndPrimDraw(&Uni->Cow,
        MatrMulMatr5(MatrScale(VecSet1(2)),
          MatrRotateY(sin(Ani->Time) * 30),
          MatrRotateX(sin(Ani->Time) * 30),
          MatrRotateZ(sin(Ani->Time) * 30),
          MatrTranslate(VecSet(i, j, k))));
} /* End of 'MI6_UnitRender' function */
 
/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (mi6UNIT *) pointer to created unit.
 */
mi6UNIT * MI6_UnitCreateCow( VOID )
{
  mi6UNIT *Uni;
 
  /* Memory allocation */
  if ((Uni = MI6_AnimUnitCreate(sizeof(mi6UNIT_COW))) == NULL)
    return NULL;
 
  /* Setup unit methods */
  Uni->Init = (VOID *)MI6_UnitInit;
  Uni->Close = (VOID *)MI6_UnitClose;
  Uni->Render = (VOID *)MI6_UnitRender;
 
  return Uni;
} /* End of 'MI6_AnimUnitCreate' function */