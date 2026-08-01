/*************************************************************
 * Copyright (C) 2026
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : test_matr.c
 * PURPOSE     : Ray-Tracing project.
 *               Test system module.
 * PROGRAMMER  : CGSG-SummerCamp'2026.
 *               Maksim Eremeev.  
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
 
/* Test 1 operator type * method function */
TEST( MathTest, OperatorTypeMatr1 )
{
  INT nm[4][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
  INT nmo[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  mth::matr<INT> M(nm);

  for (INT i = 0; i < 16; i++)
  {
    EXPECT_EQ_OPER_PNT_MATR(*(M + i), nmo[i]);
  }
} /* End of 'MathTest.OperatorTypeMatr1' test */

/* Test 2 const operator type * method function */
TEST( MathTest, OperatorTypeMatr2 )
{
  INT nm[4][4] = {{1, 2, 3, 40}, {5, 6, 7, 81}, {9, 10, 11, 12}, {13, 47, 15, 16}};
  INT nmo[16] = {1, 2, 3, 40, 5, 6, 7, 81, 9, 10, 11, 12, 13, 47, 15, 16};
  const mth::matr<INT> M(nm);

  for (INT i = 0; i < 16; i++)
  {
    EXPECT_EQ_OPER_PNT_MATR(*(M + i), nmo[i]);
  }
} /* End of 'MathTest.OperatorTypeMatr2' test */


/* Test 3 operator type * method function */
TEST( MathTest, OperatorTypeMatr3 )
{
  INT nm[4][4];
  for (INT i = 0; i < 4; i++)
    for (INT j = 0; j < 4; j++)
      nm[i][j] = rand();
  mth::matr<INT> M(nm);

  for (INT i = 0; i < 4; i++)
    for (INT j = 0; j < 4; j++)
    {
      INT k = j + 4 * i;

      EXPECT_EQ_OPER_PNT_MATR(*(M + k), nm[i][j]);
    }
} /* End of 'MathTest.OperatorTypeMatr3' test */
