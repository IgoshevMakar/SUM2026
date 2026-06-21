#include <stdio.h>

#include "units.h"
#include "anim/rnd/rnd.h"

typedef struct tagmi6UNIT_G3DM
  {
  MI6_UNIT_BASE_FIELDS;
  mi6PRIMS Model;
} mi6UNIT_G3DM;

static VOID MI6_UnitInit( mi6UNIT_G3DM *Uni, MI6ANIM *Ani)
{
  VEC B;
  MATR m;

  MI6_RndPrimsLoad(&Uni->Model, "bin/models/city_1.g3dm");
  //B = VecSubVec(Uni->Model.MaxBB, Uni->Model.MinBB);
  //m = MatrMulMatr(MatrTranslate(VecAddVec(VecNeg(Uni->Model.MinBB), VecSet(-B.X / 2, 0, -B.Z / 2))), MatrScale(VecSet1(1 / B.Y)));
  //Uni->Model.Trans = m;
}

static VOID MI6_UnitClose( mi6UNIT_G3DM *Uni, mi6PRIM *Ani)
{
  MI6_RndPrimsFree(&Uni->Model);
}

static VOID MI6_UnitResponse( mi6UNIT_G3DM *Uni, MI6ANIM *Ani)
{
}

static VOID MI6_UnitRender( mi6UNIT_G3DM *Uni, MI6ANIM *Ani)
{
  MI6_RndPrimsDraw(&Uni->Model, MatrIdenity());
}

mi6UNIT * MI6_UnitCreateG3DM( VOID )
{
  mi6UNIT_G3DM *Uni;
  if ((Uni = (mi6UNIT_G3DM *)MI6_AnimUnitCreate(sizeof(mi6UNIT_G3DM))) == NULL)
    return NULL;
  Uni->Init = (VOID *)MI6_UnitInit;
  Uni->Response = (VOID *)MI6_UnitResponse;
  Uni->Render = (VOID *)MI6_UnitRender;
  return (mi6UNIT *)Uni;
}

