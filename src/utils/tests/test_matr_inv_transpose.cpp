/*************************************************************
 * Copyright (C) 2026
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : test_matr_inv_transpose.cpp
 * PURPOSE     : Ray-Tracing project.
 *               Test inverse & transpose matrix system module.
 * PROGRAMMER  : CGSG-SummerCamp'2026.
 *               Atyukov Alexander (AA3).
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
 * Test functions block
 ***/

/* Transpose matrix test #01 */
TEST(MatrTest, Transpose01)
{
  mth::matr<DBL> M1(8.7, 23.4, 35.442, 81.72, 
                    9.4, 5.5, 3.7, 1, 
                    22.11, 3.3, 0, 856.45,
                    33.23, 346.2, 879.9, 723.423);
  M1 = M1.Transpose();
  mth::matr<DBL> M2(8.7, 23.4, 35.442, 81.72, 
                    9.4, 5.5, 3.7, 1, 
                    22.11, 3.3, 0, 856.45,
                    33.23, 346.2, 879.9, 723.423);
  M2 = M2.Transpose();
  EXPECT_MATR_EQ(M1, M2);
} /* End of 'MatrTest.Transpose01' test */

/* Transpose matrix test #02 */
TEST(MatrTest, Transpose02)
{
  mth::matr<DBL> M1(1, 1, 1, 1, 
                    0, 0, 0, 0, 
                    0, 0, 0, 0,
                    0, 0, 0, 0);
  mth::matr<DBL> M2(M1);
  M1 = M1.Transpose();
  M1 = M1.Transpose();
  EXPECT_MATR_EQ(M1, M2);
} /* End of 'MatrTest.Transpose02' test */

/* Transpose matrix test #03 */
TEST(MatrTest, Transpose03)
{
  mth::matr<DBL> M1(1, 1, 1, 1,
                    0, 0, 0, 0,
                    0, 0, 0, 0,
                    0, 0, 0, 0);
  mth::matr<DBL> M2(M1);
  for (int i = 0; i < 30; i++)
    M1 = M1.Transpose();
  EXPECT_MATR_EQ(M1, M2);
} /* End of 'MatrTest.Transpose03' test */

/* Transpose matrix test #04 */
TEST(MatrTest, Transpose04)
{
  mth::matr<FLT> M1(1, 1, 1, 1,
                    0, 0, 0, 0,
                    0, 0, 0, 0,
                    0, 0, 0, 0);
  mth::matr<FLT> M2(M1);
  for (int i = 0; i < 31; i++)
    M1 = M1.Transpose();
  M2 = M2.Transpose();
  EXPECT_MATR_EQ(M1, M2);
} /* End of 'MatrTest.Transpose04' test */

/* Transpose matrix test #05 */
TEST(MatrTest, Transpose05)
{
  mth::matr<FLT> M1(1, 2, 3, 4,
                    5, 6, 7, 8,
                    9, 10, 11, 12,
                    13, 14, 15, 16);
  mth::matr<FLT> M2(1, 5, 9, 13,
                    2, 6, 10, 14,
                    3, 7, 11, 15,
                    4, 8, 12, 16);
  for (int i = 0; i < 11; i++)
    M1 = M1.Transpose();
  EXPECT_MATR_EQ(M1, M2);
} /* End of 'MatrTest.Transpose05' test */

/* Inverse matrix test #01 */
TEST(MatrTest, Inverse01)
{
  mth::matr<FLT> M1(5, 1, 2, 1,
                    1, 6, 1, 2,
                    2, 1, 7, 1,
                    1, 2, 1, 8);
  mth::matr<FLT> M2;
  mth::matr<FLT> M3;
  mth::matr<FLT> M4;
  M4 = M4.Identity();
  M2 = M1.Inverse();
  M3 = M1 * M2;
  EXPECT_MATR_NEAR(M3, M4, 0.000001);
} /* End of 'MatrTest.Inverse01' test */

/* Inverse matrix test #02 */
TEST(MatrTest, Inverse02)
{
  mth::matr<FLT> M1(1, 0, 0, 0,
                    0, 1, 0, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1);
  mth::matr<FLT> M2;
  M2 = M1.Inverse();
  EXPECT_MATR_EQ(M1, M2);
} /* End of 'MatrTest.Inverse02' test */

/* Inverse matrix test #03 */
TEST(MatrTest, Inverse03)
{
  mth::matr<DBL> M1(1, 1, 0, 0,
                    0, 1, 1, 0,
                    0, 0, 1, 1,
                    0, 0, 0, 1);
  M1 = M1.Inverse();
  mth::matr<DBL> M2(1, 0, 0, 0,
                    -1, 1, 0, 0,
                     1, -1, 1, 0,
                     -1, 1, -1, 1);
  EXPECT_MATR_EQ(M1, M2);
} /* End of 'MatrTest.Inverse03' test */

/* Inverse matrix test #04 */
TEST(MatrTest, Inverse04)
{
  mth::matr<FLT> M1(1, 2, 3, 4,
                    2, 1, 0, 3,
                    3, 0, 1, 2,
                    4, 3, 2, 1);
  mth::matr<FLT> M2;
  mth::matr<FLT> M3;
  mth::matr<FLT> M4;
  M4 = M4.Identity();
  M2 = M1.Inverse();
  M3 = M1 * M2;
  EXPECT_MATR_NEAR(M3, M4, 0.000001);
} /* End of 'MatrTest.Inverse04' test */

/* Inverse matrix test #05 */
TEST(MatrTest, Inverse05)
{
  mth::matr<DBL> M1(1, 1, 1, 1,
                    0, 1, 1, 1,
                    0, 0, 1, 1,
                    0, 0, 0, 1);
  M1 = M1.Inverse();
  mth::matr<DBL> M2(1, 0, 0, 0,
                    -1, 1, 0, 0,
                     0, -1, 1, 0,
                     0, 0, -1, 1);
  EXPECT_MATR_EQ(M1, M2);
} /* End of 'MatrTest.Inverse05' test */

/* END OF 'test_matr_inv_transpose.cpp' FILE */