
/* FILE NAME  : unit.c
 * PROGRAMMER : MI6
 * LAST UPDATE: 11.06.2026
 */

#include "anim.h"

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       mi6UNIT *Uni;
 *   - animation context:
 *       MI6ANIM *Ani;
 * RETURNS: None.
 */
static VOID MI6_UnitInit( mi6UNIT *Uni, MI6ANIM *Ani )
{
} /* End of 'MI6_UnitInit' function */
 
/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       mi6UNIT *Uni;
 *   - animation context:
 *       MI6ANIM *Ani;
 * RETURNS: None.
 */
static VOID MI6_UnitClose( mi6UNIT *Uni, MI6ANIM *Ani )
{
} /* End of 'MI6_UnitClose' function */
 
/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       mi6UNIT *Uni;
 *   - animation context:
 *       MI6ANIM *Ani;
 * RETURNS: None.
 */
static VOID MI6_UnitResponse( mi6UNIT *Uni, MI6ANIM *Ani )
{
} /* End of 'MI6_UnitResponse' function */
 
/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       mi6UNIT *Uni;
 *   - animation context:
 *       MI6ANIM *Ani;
 * RETURNS: None.
 */
static VOID MI6_UnitRender( mi6UNIT *Uni, MI6ANIM *Ani )
{
} /* End of 'MI6_UnitRender' function */
 
/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (mi6UNIT *) pointer to created unit.
 */
mi6UNIT * MI6_AnimUnitCreate( INT Size )
{
  mi6UNIT *Uni;
 
  /* Memory allocation */
  if (Size < sizeof(mi6UNIT) || (Uni = malloc(Size)) == NULL)
    return NULL;
  memset(Uni, 0, Size);
 
  /* Setup unit methods */
  Uni->Init = MI6_UnitInit;
  Uni->Close = MI6_UnitClose;
  Uni->Response = MI6_UnitResponse;
  Uni->Render = MI6_UnitRender;
 
  return Uni;
} /* End of 'MI6_AnimUnitCreate' function */