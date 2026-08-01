/*************************************************************
 * Copyright (C) 2026
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : test_matr_invtransform.cpp
 * PURPOSE     : Ray-tracing project.
 *               Test inverse matrices module.
 * PROGRAMMER  : CGSG-SummerCamp'2026.
 *               Dmitry Moiseev (DM3).
 * LAST UPDATE : 28.07.2026.
 * NOTE        : Module namespace 'tst'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "gert.h"
#include "mth/mth.h"
#include "test_system.h"

/***
 * INVERSE TRANSFORM VECTOR
 ***/

/* Zero vector check */
TEST(MatrTest, InverseTransformVector_ZeroVector)
{
  mth::matr<DBL> Matr = mth::matr<DBL>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  mth::vec3<DBL> VectorCheck = mth::vec3<DBL>(0, 0, 0), VectorRight = mth::vec3<DBL>(0, 0, 0);

  VectorCheck = Matr.InvTransformVector(VectorCheck);

  EXPECT_VEC3_EQ(VectorCheck, VectorRight);
} /* End of 'InverseTransformVector' function */

/* Vector check */
TEST(MatrTest, InverseTransformVector_Vector1)
{
  mth::matr<DBL> Matr = mth::matr<DBL>(2, 0, 0, 0, 0, 2, 0, 0, 0, 0, -3, -1, 0, 0, -16, 0);
  mth::vec3<DBL> VectorCheck = mth::vec3<DBL>(1, 2, 3), VectorRight = mth::vec3<DBL>(0.5, 1, 0);

  VectorCheck = Matr.InvTransformVector(VectorCheck);

  EXPECT_VEC3_EQ(VectorCheck, VectorRight);
} /* End of 'InverseTransformVector' function */

/* Vector check */
TEST(MatrTest, InverseTransformVector_Vector2)
{
  mth::matr<FLT> Matr = mth::matr<FLT>(0.25, 0, 0, 0, 0, 0.5, 0, 0, 0, 0, -0.2, 0, -0.25, -4, -3, 1);
  mth::vec3<FLT> VectorCheck = mth::vec3<FLT>(30, 47, 102), VectorRight = mth::vec3<FLT>(120, 94, -510);

  EXPECT_VEC3_EQ(Matr.InvTransformVector(VectorCheck), VectorRight);
} /* End of 'InverseTransformVector' function */

/***
 * INVERSE TRANSFORM POINT
 ***/

/* Zero vector check */
TEST(MatrTest, InverseTransformPoint_ZeroVectorDBL)
{
  mth::matr<DBL> Matr = mth::matr<DBL>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  mth::vec3<DBL> VectorCheck = mth::vec3<DBL>(0, 0, 0), VectorRight = mth::vec3<DBL>(0, 0, 0);

  VectorCheck = Matr.InvTransformPoint(VectorCheck);

  EXPECT_VEC3_EQ(VectorCheck, VectorRight);
} /* End of 'InverseTransformPoint' function */

/* Vector check */
TEST(MatrTest, InverseTransformPoint_Vector1DBL)
{
  mth::matr<DBL> Matr = mth::matr<DBL>(2, 0, 0, 0, 0, 2, 0, 0, 0, 0, -3, -1, 0, 0, -16, 0);
  mth::vec3<DBL> VectorCheck = mth::vec3<DBL>(1, 2, 3), VectorRight = mth::vec3<DBL>(0.5, 1, -0.0625);

  VectorCheck = Matr.InvTransformPoint(VectorCheck);

  EXPECT_VEC3_EQ(VectorCheck, VectorRight);
} /* End of 'InverseTransformPoint' function*/

/* Vector check */
TEST(MatrTest, InverseTransformPoint_Vector2FLT)
{
  mth::matr<FLT> Matr = mth::matr<FLT>(0.25, 0, 0, 0, 0, 0.5, 0, 0, 0, 0, -0.2, 0, -0.25, -4, -3, 1);
  mth::vec3<FLT> VectorCheck = mth::vec3<FLT>(30, 47, 102), VectorRight = mth::vec3<FLT>(120, 94, -510);

  EXPECT_VEC3_EQ(Matr.InvTransformPoint(VectorCheck), VectorRight);
} /* End of 'InverseTransformPoint' function*/

/***
 * INVERSE TRANSFORM NORMAL
 ***/

/* Zero vector check */
TEST(MatrTest, InverseTransformNormal_ZeroVectorDBL)
{
  mth::matr<DBL> Matr = mth::matr<DBL>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  mth::vec3<DBL> VectorCheck = mth::vec3<DBL>(0, 0, 0), VectorRight = mth::vec3<DBL>(0, 0, 0);

  VectorCheck = Matr.InvTransformNormal(VectorCheck);

  EXPECT_VEC3_EQ(VectorCheck, VectorRight);
} /* End of 'InverseTransformNormal' function */

/* Vector check */
TEST(MatrTest, InverseTransformNormal_Vector1DBL)
{
  mth::matr<DBL> Matr = mth::matr<DBL>(2, 0, 0, 0, 0, 2, 0, 0, 0, 0, -3, -1, 0, 0, -16, 0);
  mth::vec3<DBL> VectorCheck = mth::vec3<DBL>(1, 2, 3), VectorRight = mth::vec3<DBL>(2, 4, -9);

  VectorCheck = Matr.InvTransformNormal(VectorCheck);

  EXPECT_VEC3_EQ(VectorCheck, VectorRight);
} /* End of 'InverseTransformNormal' function */

/* Vector check */
TEST(MatrTest, InverseTransformNormal_Vector2FLT)
{
  mth::matr<FLT> Matr = mth::matr<FLT>(0.25, 0, 0, 0, 0, 0.5, 0, 0, 0, 0, -0.2, 0, -0.25, -4, -3, 1);
  mth::vec3<FLT> VectorCheck = mth::vec3<FLT>(30, 47, 102), VectorRight = mth::vec3<FLT>(7.5, 23.5, -20.4);

  EXPECT_VEC3_EQ(Matr.InvTransformNormal(VectorCheck), VectorRight);
} /* End of 'InverseTransformNormal' function */

/* END OF 'test_matr_invtransform.cpp' FILE */