/*************************************************************
 * Copyright (C) 2026
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : test_matr_translate.cpp
 * PURPOSE     : Ray-Tracing project.
 *               Test system module - matrixes of translation.
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

TEST(MathMatrTest, MatrTranslateFromVecDBL)
{
  EXPECT_MATR_EQ(mth::matr<DBL>::Translate(mth::vec3<DBL>(255.102, 3.47, 4.18)), mth::matr<DBL>(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 255.102, 3.47, 4.18, 1));
}

TEST(MathMatrTest, MatrTranslateFromVecFLT)
{
  EXPECT_MATR_EQ(mth::matr<FLT>::Translate(mth::vec3<FLT>(255.102, 3.47, 4.18)), mth::matr<FLT>(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 255.102, 3.47, 4.18, 1));
}

TEST(MathMatrTest, MatrTranslateFromComponentsDBL)
{
  EXPECT_MATR_EQ(mth::matr<DBL>::Translate(255.102, 3.47, 4.18), mth::matr<DBL>(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 255.102, 3.47, 4.18, 1));
}

TEST(MathMatrTest, MatrTranslateFromComponentsFLT)
{
  EXPECT_MATR_EQ(mth::matr<FLT>::Translate(255.102, 3.47, 4.18), mth::matr<FLT>(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 255.102, 3.47, 4.18, 1));
}

/* END OF 'test_matr_translate.cpp' FILE */