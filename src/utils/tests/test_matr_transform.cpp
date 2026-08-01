/*************************************************************
 * Copyright (C) 2026
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : test_system.h
 * PURPOSE     : Ray-Tracing project.
 *               Test system module.
 * PROGRAMMER  : Mikhail Aleksandrov.
 * LAST UPDATE : 28.07.2026.
 * NOTE        : Module namespace 'tst'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "gert.h"
#include "mth/mth.h"
#include "test_system.h"

INT AddNums( INT A, INT B )
{
  return A + B;
} /* End of 'AddNums' function */
 
/***
 * Test functions block
 ***/


/***
 * Test TransformPoint
 ***/

/* Test 1 transform point */
TEST(MathTestTransformPoint1, AddPositive)
{
  mth::matr<FLT> M(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

  mth::vec3<FLT> L = M.TransformPoint(mth::vec3<FLT>(10, 3, 1));
  mth::vec3<FLT> L1 = mth::vec3<FLT>(47, 62, 77);

  EXPECT_VEC3_EQ(L, L1);
} /* End of 'MathTest.AddPositive' test */

/* Test 2 transform point */
TEST(MathTestTransformPoint1, AddNegative)
{
  mth::matr<FLT> M(-1, -2, -3, -4, -5, -6, -7, -8, -9, -10, -11, -12, -13, -14, -15, -16);
  
  mth::vec3<FLT> L = M.TransformPoint(mth::vec3<FLT>(-162, 13, -122));
  mth::vec3<FLT> L1 = mth::vec3<FLT>(1182, 1452, 1722);

  EXPECT_VEC3_EQ(L, L1);
} /* End of 'MathTest.AddNegative' test */

/* Test 3 transform point */
TEST(MathTestTransformPoint2, AddPositive)
{
  mth::matr<FLT> M(3, 22, 23, 14, 5, 0, 7, 8, 0, 10, 15, 12, 13, 4, 1, 16);

  mth::vec3<FLT> L = M.TransformPoint(mth::vec3<FLT>(310, 34, -23));
  mth::vec3<FLT> L1 = mth::vec3<FLT>(1113, 6594, 7024);

  EXPECT_VEC3_EQ(L, L1);
} /* End of 'MathTest.AddPositive' test */

/* Test 4 transform point */
TEST(MathTestTransformPoint2, AddNegative)
{
  mth::matr<FLT> M(-10, -2, -32, -4, 3, -6, 0, -8, -9, -10, -11, -1, -13, -10, -15, -35);
  
  mth::vec3<FLT> L = M.TransformPoint(mth::vec3<FLT>(-21, 2, 20));
  mth::vec3<FLT> L1 = mth::vec3<FLT>(23, -180, 437);

  EXPECT_VEC3_EQ(L, L1);
} /* End of 'MathTest.AddNegative' test */

/* Test 5 transform point */
TEST(MathTestTransformPoint3, AddPositive)
{
  mth::matr<FLT> M(11, 2, 21, 70, 5, 14, 7, 8, 0, 102, 11, 2, 13, -10, 125, 6);

  mth::vec3<FLT> L = M.TransformPoint(mth::vec3<FLT>(-28, -4, 72));
  mth::vec3<FLT> L1 = mth::vec3<FLT>(-315, 7222, 301);

  EXPECT_VEC3_EQ(L, L1);
} /* End of 'MathTest.AddPositive' test */
 
/* Test 6 transform point */
TEST(MathTestTransformPoint3, AddNegative)
{
  mth::matr<FLT> M(-81, 2, 31, -70, 5, 14, 7, -8, 0, -102, 11, 202, 13, -10, 15, 6);
  
  mth::vec3<FLT> L = M.TransformPoint(mth::vec3<FLT>(-1, 27, 32));
  mth::vec3<FLT> L1 = mth::vec3<FLT>(229, -2898, 525);

  EXPECT_VEC3_EQ(L, L1);
} /* End of 'MathTest.AddNegative' test */



/********
 * Test TransformVector
 ********/



/* Test 1 transform vector */
TEST(MathTestTransformVector1, AddPositive)
{
  mth::matr<FLT> M(-149, -79, 44, -127, -68, -41, -73, 145, -54, 130, -96, 107, -139, -147, 38, -4);

  mth::vec3<FLT> L = M.TransformVector(mth::vec3<FLT>(-20, 12, 43));
  mth::vec3<FLT> L1 = mth::vec3<FLT>(-158, 6678, -5884);

  EXPECT_VEC3_EQ(L, L1);
} /* End of 'MathTest.AddPositive' test */
 
/* Test 2 transform vector */
TEST(MathTestTransformVector1, AddNegative)
{
  mth::matr<FLT> M(-42, 32, -3, 24, -0, -6, 45, -4, 29, -13, 52, -12, 37, 14, -85, 12);
  
  mth::vec3<FLT> L = M.TransformVector(mth::vec3<FLT>(0, 13, 31));
  mth::vec3<FLT> L1 = mth::vec3<FLT>(899, -481, 2197);

  EXPECT_VEC3_EQ(L, L1);
} /* End of 'MathTest.AddNegative' test */

/* Test 3 transform vector */
TEST(MathTestTransformVector2, AddPositive)
{
  mth::matr<FLT> M(0, 12, 33, -12, 54, 16, -27, 83, -95, 10, -1, 52, -63, 11, -15, 94);

  mth::vec3<FLT> L = M.TransformVector(mth::vec3<FLT>(112, -23, 11));
  mth::vec3<FLT> L1 = mth::vec3<FLT>(-2287, 1086, 4306);

  EXPECT_VEC3_EQ(L, L1);
} /* End of 'MathTestTransformVector2.AddPositive' test */
 
/* Test 4 transform vector */
TEST(MathTestTransformVector2, AddNegative)
{
  mth::matr<FLT> M(-1, -2, -3, -4, -5, -6, -7, -8, -9, -10, -11, -12, -13, -14, -15, -16);
  
  mth::vec3<FLT> L = M.TransformVector(mth::vec3<FLT>(10, 3, 1));
  mth::vec3<FLT> L1 = mth::vec3<FLT>(-34, -48, -62);

  EXPECT_VEC3_EQ(L, L1);
} /* End of 'MathTestTransformVector2.AddNegative' test */

/* Test 5 transform vector */
TEST(MathTestTransformVector3, AddPositive)
{
  mth::matr<FLT> M(-17, 22, 3, -44, 75, -26, 78, 8, 95, -160, 11, 12, 134, -142, 25, 10);

  mth::vec3<FLT> L = M.TransformVector(mth::vec3<FLT>(-12, 23, 10));
  mth::vec3<FLT> L1 = mth::vec3<FLT>(2879, -2462, 1868);

  EXPECT_VEC3_EQ(L, L1);
} /* End of 'MathTestTransformVector3.AddPositive' test */
 
/* Test 6 transform vector */
TEST(MathTestTransformVector3, AddNegative)
{
  mth::matr<FLT> M(-123, 212, -3.43, 234.1, 54, -6, 72.12, -8, 9, 10, 1.213, -12.223, -13, -134.43, -145.1, -26.233);
  
  mth::vec3<FLT> L = M.TransformVector(mth::vec3<FLT>(10.212, 23, 234));
  mth::vec3<FLT> L1 = mth::vec3<FLT>(2091.924, 4366.9443, 1907.575);

  EXPECT_VEC3_EQ(L, L1);
} /* End of 'MathTestTransformVector3.AddNegative' test */



/***
 * Test TransformNormal
 ***/



/* Test 1 transform normal */
TEST(MathTestTransformNormal1, AddPositive)
{
  mth::matr<FLT> M(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

  mth::vec3<FLT> L = M.TransformNormal(mth::vec3<FLT>(10, 3, 1));
  mth::vec3<FLT> L1 = mth::vec3<FLT>(10, 3, 1);

  EXPECT_VEC3_EQ(L, L1);
} /* End of 'MathTestTransformNormal1.AddPositive' test */

/* Test 2 transform normal */
TEST(MathTestTransformNormal1, AddNegative)
{
  mth::matr<FLT> M(-1, 2, -3, -4, 10, 6, -7, 8, -9, -100, -11, -12, -13, 140, -15, -16);

  mth::vec3<FLT> L = M.TransformNormal(mth::vec3<FLT>(10, 3, 1));
  mth::vec3<FLT> L1 = mth::vec3<FLT>(4.321123, 0.012027491, 0.89917386);

  EXPECT_VEC3_EQ(L, L1);
} /* End of 'MathTestTransformNormal1.AddNegative' test */

/* Test 3 transform normal */
TEST(MathTestTransformNormal2, AddPositive)
{
  mth::matr<FLT> M(11, -22, 2, -64, 3, 6, 0, -8, 9, 110, -11, 12, 23, -44, 95, 26);

  mth::vec3<FLT> L = M.TransformNormal(mth::vec3<FLT>(0.1, 23, -1.1));
  mth::vec3<FLT> L1 = mth::vec3<FLT>(47.91301, -6.7703185, -17.476568);

  EXPECT_VEC3_EQ(L, L1);
} /* End of 'MathTestTransformNormal2.AddPositive' test */
 
/* Test 4 transform normal */
TEST(MathTestTransformNormal2, AddNegative)
{
  mth::matr<FLT> M(-1, 2, -3, -40, 0, 6, -7, 8, -9, -10, 11, -12, -10, 14, -15, 16);

  mth::vec3<FLT> L = M.TransformNormal(mth::vec3<FLT>(10, 3, 1));
  mth::vec3<FLT> L1 = mth::vec3<FLT>(-0.17857143, -7.2881494, -6.7905846);

  EXPECT_VEC3_EQ(L, L1);
} /* End of 'MathTestTransformNormal2.AddNegative' test */

/* Test 5 transform normal */
TEST(MathTestTransformNormal3, AddPositive)
{
  mth::matr<FLT> M(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

  mth::vec3<FLT> L = M.TransformNormal(mth::vec3<FLT>(0, 0, 0));
  mth::vec3<FLT> L1 = mth::vec3<FLT>(0, 0, 0);

  EXPECT_VEC3_EQ(L, L1);
} /* End of 'MathTestTransformNormal3.AddPositive' test */
 
/* Test 6 transform normal */
TEST(MathTestTransformNormal3, AddNegative)
{
  mth::matr<FLT> M(1, 20, -3, 14, 10, 2, -7, 8.2, 9, 100, -11, -12, -13, 140, -15, 6);

  mth::vec3<FLT> L = M.TransformNormal(mth::vec3<FLT>(10, 3, 1));
  mth::vec3<FLT> L1 = mth::vec3<FLT>(0.7033372, 0.19097996, 1.4540404);

  EXPECT_VEC3_EQ(L, L1);
} /* End of 'MathTestTransformNormal3.AddNegative' test */

/* END OF 'test_matr_transform.cpp' FILE */