/*************************************************************
 * Copyright (C) 2026
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : test_matr_multiplication.cpp
 * PURPOSE     : Ray-Tracing project.
 *               Test system module.
 *               Matrix multiplication test.
 * PROGRAMMER  : CGSG-SummerCamp'2026.
 * LAST UPDATE : 28.07.2026.
 * NOTE        : Module namespace 'tst'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "gert.h"
#include "mth/mth.h"
#include "test_system.h"
#include <chrono>

/* Matrix multiplication test
 * ARGUMENTS: None.
 * RETURNS: None.
 */
template<typename Type>
  VOID MatrixesMultiplication( VOID )
  {
    srand(std::chrono::system_clock::now().time_since_epoch().count());

    mth::matr<Type> a(mth::Rnd1() * rand(), mth::Rnd1() * rand(), mth::Rnd1() * rand(), mth::Rnd1() * rand(),
                     mth::Rnd1() * rand(), mth::Rnd1() * rand(), mth::Rnd1() * rand(), mth::Rnd1() * rand(),
                     mth::Rnd1() * rand(), mth::Rnd1() * rand(), mth::Rnd1() * rand(), mth::Rnd1() * rand(),
                     mth::Rnd1() * rand(), mth::Rnd1() * rand(), mth::Rnd1() * rand(), mth::Rnd1() * rand());
    mth::matr<Type> b(mth::Rnd1() * rand(), mth::Rnd1() * rand(), mth::Rnd1() * rand(), mth::Rnd1() * rand(),
                     mth::Rnd1() * rand(), mth::Rnd1() * rand(), mth::Rnd1() * rand(), mth::Rnd1() * rand(),
                     mth::Rnd1() * rand(), mth::Rnd1() * rand(), mth::Rnd1() * rand(), mth::Rnd1() * rand(),
                     mth::Rnd1() * rand(), mth::Rnd1() * rand(), mth::Rnd1() * rand(), mth::Rnd1() * rand());
    mth::matr<Type> c(a * b);
    mth::matr<Type> d {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    for (INT i = 0; i < 4; i++)
      for (INT j = 0; j < 4; j++)
        for (INT k = 0; k < 4; k++)
          *(d + (j + i * 4)) += *(a + (k + i * 4)) * *(b + (j + k * 4));

    EXPECT_MATR_EQ2(c, d);
  } /* End of 'MatrixesMultiplication' function */

/* Matrix itself multiplication test
 * ARGUMENTS: None.
 * RETURNS: None.
 */
template<typename Type>
  VOID MatrixesItselfMultiplication( VOID )
  {
    srand(std::chrono::system_clock::now().time_since_epoch().count());

    mth::matr<FLT> a(mth::Rnd1() * rand(), mth::Rnd1() * rand(), mth::Rnd1() * rand(), mth::Rnd1() * rand(),
                     mth::Rnd1() * rand(), mth::Rnd1() * rand(), mth::Rnd1() * rand(), mth::Rnd1() * rand(),
                     mth::Rnd1() * rand(), mth::Rnd1() * rand(), mth::Rnd1() * rand(), mth::Rnd1() * rand(),
                     mth::Rnd1() * rand(), mth::Rnd1() * rand(), mth::Rnd1() * rand(), mth::Rnd1() * rand());
    mth::matr<FLT> b(mth::Rnd1() * rand(), mth::Rnd1() * rand(), mth::Rnd1() * rand(), mth::Rnd1() * rand(),
                     mth::Rnd1() * rand(), mth::Rnd1() * rand(), mth::Rnd1() * rand(), mth::Rnd1() * rand(),
                     mth::Rnd1() * rand(), mth::Rnd1() * rand(), mth::Rnd1() * rand(), mth::Rnd1() * rand(),
                     mth::Rnd1() * rand(), mth::Rnd1() * rand(), mth::Rnd1() * rand(), mth::Rnd1() * rand());
    mth::matr<FLT> d {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    for (INT i = 0; i < 4; i++)
      for (INT j = 0; j < 4; j++)
        for (INT k = 0; k < 4; k++)
          *(d + (j + i * 4)) += *(a + (k + i * 4)) * *(b + (j + k * 4));

    a *= b;

    EXPECT_MATR_EQ2(a, d);
  
} /* End of 'MatrixesItselfMultiplication' function */

/* Test 1 multiplication of matrixes */
TEST(MatrixesTest, Multiplication1)
{
  srand(std::chrono::system_clock::now().time_since_epoch().count());

  mth::matr<INT> a(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
  mth::matr<INT> b(mth::matr<INT>::Identity());
  mth::matr<INT> c(a * b);
  mth::matr<INT> d {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  for (INT i = 0; i < 4; i++)
    for (INT j = 0; j < 4; j++)
      for (INT k = 0; k < 4; k++)
        *(d + (j + i * 4)) += *(a + (k + i * 4)) * *(b + (j + k * 4));

  EXPECT_MATR_EQ2(c, d);
}

/* Test multiplication of float matrixes */
TEST(MatrixesTest, MultiplicationFLT)
{
  MatrixesMultiplication<FLT>();
}

/* Test multiplication of double matrixes */
TEST(MatrixesTest, MultiplicationDBL)
{
  MatrixesMultiplication<DBL>();
}

/* Test multiplication of int matrixes */
TEST(MatrixesTest, MultiplicationINT)
{
  MatrixesMultiplication<INT>();
}

/* Test multiplication itself on float matrix */
TEST(MatrixesTest, MultiplicationOnItselfFLT)
{
  MatrixesItselfMultiplication<FLT>();
}

/* Test multiplication itself on double matrix */
TEST(MatrixesTest, MultiplicationOnItselfDBL)
{
  MatrixesItselfMultiplication<DBL>();
}

/* Test multiplication itself on int matrix */
TEST(MatrixesTest, MultiplicationOnItselfINT)
{
  MatrixesItselfMultiplication<INT>();
}

/* END OF 'test_matr_multiplication.cpp' FILE */
