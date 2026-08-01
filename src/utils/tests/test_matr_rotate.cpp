/*************************************************************
 * Copyright (C) 2026
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : test_matr_scale_translate.cpp
 * PURPOSE     : Ray-Tracing project.
 *               Test system module.
 * PROGRAMMER  : CGSG-SummerCamp'2026.
 *               Gavriil Leontev (GL3).
 * LAST UPDATE : 28.07.2026.
 * NOTE        : Module namespace 'tst'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "gert.h"
#include "mth/mth.h"
#include "test_system.h"


/* Test by matrix rotate by x */
TEST(MatrTest, RotateX)
{
  mth::matr<DBL> M1,
                 M2(1.0, 0.0, 0.0, 0.0,
                    0.0, -0.84804827, -0.52991903, 0.0,
                    0.0, 0.52991903, -0.84804827, 0.0,
                    0.0, 0.0, 0.0, 1.0);
  
  M1 = M1.RotateX(572);
  EXPECT_MATR_NEAR(M1, M2, 0.00001);
} /* End of 'RotateX' test */

TEST(MatrTest, RotateX1)
{
  mth::matr<FLT> M1,
                 M2(1.0, 0.0, 0.0, 0.0,
                    0.0, 0.0, 1.0, 0.0,
                    0.0, -1.0, 0.0, 0.0,
                    0.0, 0.0, 0.0, 1.0);
  
  M1 = M1.RotateX(90.0);
  EXPECT_MATR_NEAR(M1, M2, 0.00001);
} /* End of 'RotateX1' test */


/* Test by matrix rotate by y */
TEST(MatrTest, RotateY)
{
  mth::matr<DBL> M1,
                 M2(0.0, 0.0, -1.0, 0.0,
                    0.0, 1.0, 0.0, 0.0,
                    1.0, 0.0, 0.0, 0.0,
                    0.0, 0.0, 0.0, 1.0);
  
  M1 = M1.RotateY(90.0);
  EXPECT_MATR_NEAR(M1, M2, 0.00001);
} /* End of 'RotateY' test */

/* Test by matrix rotate by y */
TEST(MatrTest, RotateY1)
{
  mth::matr<FLT> M1,
                 M2(0.64278489, 0.0, -0.76604670, 0.0,
                    0.0, 1.0, 0.0, 0.0,
                    0.76604670, 0.0, 0.64278489, 0.0,
                    0.0, 0.0, 0.0, 1.0);
  
  M1 = M1.RotateY(4730);
  EXPECT_MATR_NEAR(M1, M2, 0.00001);
} /* End of 'RotateY1' test */


/* Test by matrix rotate by z */
TEST(MatrTest, RotateZ)
{
  mth::matr<DBL> M1,
                 M2(0.0, 1.0, 0.0, 0.0,
                    -1.0, 0.0, 0.0, 0.0,
                    0.0, 0.0, 1.0, 0.0,
                    0.0, 0.0, 0.0, 1.0);
  
  M1 = M1.RotateZ(90.0);
  EXPECT_MATR_NEAR(M1, M2, 0.0000001);
} /* End of 'RotateZ' test */

/* Test by matrix rotate by z */
TEST(MatrTest, RotateZ1)
{
  mth::matr<FLT> M1,
                 M2(-0.17364788, 0.98480779, 0.0, 0.0,
                    -0.98480779, -0.17364788, 0.0, 0.0,
                    0.0, 0.0, 1.0, 0.0,
                    0.0, 0.0, 0.0, 1.0);
  
  M1 = M1.RotateZ(1180);
  EXPECT_MATR_NEAR(M1, M2, 0.00001);
} /* End of 'RotateZ1' test */

/* Test by matrix rotate by any vector */
TEST(MatrTest, Rotate)
{
  mth::matr<DBL> M1,
                 M2(0.0, 0.0, -1.0, 0.0,
                    0.0, 1.0, 0.0, 0.0,
                    1.0, 0.0, 0.0, 0.0,
                    0.0, 0.0, 0.0, 1.0);
  mth::vec3<DBL> a(0.0, 1.0, 0.0);
  
  M1 = M1.Rotate(90.0, a);
  EXPECT_MATR_NEAR(M1, M2, 0.00001);
} /* End of 'Rotate' test */

/* Test by matrix rotate by any vector */
TEST(MatrTest, Rotate1)
{
  mth::matr<FLT> M1,
                 M2(0.766044497, 0.0, -0.642787516, 0.0,
                    0.0, 1.0, 0.0, 0.0,
                    0.642787516, 0.0, 0.766044497, 0.0,
                    0.0, 0.0, 0.0, 1.0);
  mth::vec3<FLT> a(0.0, 1.0, 0.0);
  
  M1 = M1.Rotate(1120.0, a);
  EXPECT_MATR_NEAR(M1, M2, 0.00001);
} /* End of 'Rotate1' test */


/* END OF 'test_matr_scale_translate' FILE */