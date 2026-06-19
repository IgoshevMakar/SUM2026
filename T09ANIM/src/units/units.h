/* FILE NAME  : units.h
 * PROGRAMMER : MI6
 * LAST UPDATE: 11.06.2026
 */

#ifndef __units_h_
#define __units_h_

#include "anim/anim.h"

/* Unit creation functions.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (mi6UNIT *) pointer to created unit.
 */
mi6UNIT * MI6_UnitCreateBounceBall( VOID );
mi6UNIT * MI6_UnitCreateControl( VOID );
mi6UNIT * MI6_UnitCreateCow( VOID );
mi6UNIT * MI6_UnitCreateLandscape( VOID );

#endif 

