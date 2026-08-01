/*************************************************************
 * Copyright (C) 2026
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : test_matrscale.cpp
 * PURPOSE     : Ray-Tracing project.
 *               Test system module - matrixes of scaling.
 * PROGRAMMER  : CGSG-SummerCamp'2026.
 *               DT3.
 * LAST UPDATE : 28.07.2026.
 * NOTE        : Module namespace 'tst'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "gert.h"
#include "mth/mth.h"
#include "test_system.h"

TEST(MathMatrTest, MatrScaleFromVecDBL)
{
  EXPECT_MATR_EQ(mth::matr<DBL>::Scale(mth::vec3<DBL>(102.255, 3.47, 4.18)), mth::matr<DBL>(102.255, 0, 0, 0, 0, 3.47, 0, 0, 0, 0, 4.18, 0, 0, 0, 0, 1));
}
TEST(MathMatrTest, MatrScaleFromVecFLT)
{
  EXPECT_MATR_EQ(mth::matr<FLT>::Scale(mth::vec3<FLT>(102.255, 3.47, 4.18)), mth::matr<FLT>(102.255, 0, 0, 0, 0, 3.47, 0, 0, 0, 0, 4.18, 0, 0, 0, 0, 1));
}
TEST(MathMatrTest, MatrScaleFromComponentsDBL)
{
  EXPECT_MATR_EQ(mth::matr<DBL>::Scale(102.255, 3.47, 4.18), mth::matr<DBL>(102.255, 0, 0, 0, 0, 3.47, 0, 0, 0, 0, 4.18, 0, 0, 0, 0, 1));
}

TEST(MathMatrTest, MatrScaleFromComponentsFLT)
{
  EXPECT_MATR_EQ(mth::matr<FLT>::Scale(102.255, 3.47, 4.18), mth::matr<FLT>(102.255, 0, 0, 0, 0, 3.47, 0, 0, 0, 0, 4.18, 0, 0, 0, 0, 1));
}

/* END OF 'test_matr_scale.h' FILE */
