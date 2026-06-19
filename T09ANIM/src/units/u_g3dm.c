#include "units.h"

typedef struct tagmi6UNIT_G3DM
{
  MI6_UNIT_BASE_FIELDS;
  mi6PRIMS Model;
} mi6UNIT_G3DM;

static VOID MI6_UnitInit( mi6UNIT_G3DM *Uni, mi6ANIM *Ani)
{
  MI6_RndPrimsLoad(&Uni->Model, "bin/models/btr.g3dm");
}

static VOID MI6_UnitClose( mi6UNIT_G3DM *Uni, mi6PRIM *Ani)
{
  MI6_RndPrimsFree(&Uni->Model);
}

static VOID MI6_UnitResponse( mi6UNIT_G3DM *Uni, mi6ANIM *Ani)
{
}

static VOID MI6_UnitRender( mi6UNIT_G3DM *Uni, mi6PRIM *Ani )
{
  MI6_RndPrimDraw(&Uni->Model, MatrIdenity());
}


