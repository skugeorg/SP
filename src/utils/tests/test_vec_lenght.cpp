/*************************************************************
 * Copyright (C) 2026
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : test_vec_lenght.cpp.
 * PURPOSE     : Ray-Tracing project.
 *               Vector lenght test module.
 * PROGRAMMER  : CGSG-SummerCamp'2026.
 * LAST UPDATE : 28.07.2026.
 * NOTE        : Module namespace 'tst'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "gert.h"
#include "test_system.h"
#include "../../mth/mth.h"

/* Check vectors(2, 3, 4) lenght equivalence macro function */
#define EXPECT_VEC_LENGHT_NEAR(l1, l2, epsilon) \
  do                                                                            \
  {                                                                             \
    if (std::abs(l1 - l2) > (epsilon))                                          \
      TEST_FAILED(std::format("({}) != ({}) within {}", l1, l2, (epsilon)));    \
    else                                                                        \
      TEST_PASSED(std::format("({}) ~= ({}) (epsilon {})", l1, l2, (epsilon))); \
  } while (FALSE)

/* Check vectors(2, 3, 4) lenght equivalence macro function */
#define EXPECT_INT_VEC_LENGHT_EQ(l1, l2) \
  do                                                     \
  {                                                      \
    if (l1 != l2)                                        \
      TEST_FAILED(std::format("({}) != ({})", l1, l2));  \
    else                                                 \
      TEST_PASSED(std::format("({}) == ({})", l1, l2));  \
  } while (FALSE)

TEST(MathVec2Test, Lenght)
{
  /* Lenght, ! */
  EXPECT_VEC_LENGHT_NEAR(mth::vec2<DBL>(1.0).Length(), sqrt(2.0), 0.000001);
  EXPECT_VEC_LENGHT_NEAR(mth::vec2<DBL>(1.0, 2.0).Length(), sqrt(5.0), 0.000001);

  EXPECT_VEC_LENGHT_NEAR(mth::vec2<FLT>(6.0).Length(), sqrt(72.0), 0.000001);
  EXPECT_VEC_LENGHT_NEAR(mth::vec2<FLT>(5.0, 2.0).Length(), sqrt(29.0), 0.000001);

  EXPECT_INT_VEC_LENGHT_EQ(mth::vec2<INT>(1).Length(), (INT)sqrt(2));
  EXPECT_INT_VEC_LENGHT_EQ(mth::vec2<INT>(1, 7).Length(), (INT)sqrt(50));

  EXPECT_VEC_LENGHT_NEAR(!mth::vec2<DBL>(0.0), sqrt(0.0), 0.000001);
  EXPECT_VEC_LENGHT_NEAR(!mth::vec2<DBL>(9.0, 2.0), sqrt(85.0), 0.000001);

  EXPECT_VEC_LENGHT_NEAR(!mth::vec2<FLT>(21.0), sqrt(441.0 * 2), 0.000001);
  EXPECT_VEC_LENGHT_NEAR(!mth::vec2<FLT>(5.0, 7.0), sqrt(74.0), 0.000001);

  EXPECT_INT_VEC_LENGHT_EQ(!mth::vec2<INT>(5), (INT)sqrt(50));
  EXPECT_INT_VEC_LENGHT_EQ(!mth::vec2<INT>(13, 7), (INT)sqrt(218));

  /* Lenght2 */
  EXPECT_VEC_LENGHT_NEAR(mth::vec2<DBL>(1.0).Length2(), 2.0, 0.000001);
  EXPECT_VEC_LENGHT_NEAR(mth::vec2<DBL>(1.0, 2.0).Length2(), 5.0, 0.000001);

  EXPECT_VEC_LENGHT_NEAR(mth::vec2<FLT>(6.0).Length2(), 72.0, 0.000001);
  EXPECT_VEC_LENGHT_NEAR(mth::vec2<FLT>(5.0, 2.0).Length2(), 29.0, 0.000001);

  EXPECT_INT_VEC_LENGHT_EQ(mth::vec2<INT>(1).Length2(), 2);
  EXPECT_INT_VEC_LENGHT_EQ(mth::vec2<INT>(1, 7).Length2(), 50);
}

TEST(MathVec3Test, Lenght)
{
  EXPECT_VEC_LENGHT_NEAR(mth::vec3<DBL>(1.0).Length(), sqrt(3.0), 0.000001);
  EXPECT_VEC_LENGHT_NEAR(mth::vec3<DBL>(1.0, 2.0, 3.0).Length(), sqrt(14.0), 0.000001);
  EXPECT_VEC_LENGHT_NEAR(mth::vec3<DBL>(mth::vec2<DBL>(2.0, 3.0), 5.0).Length(), sqrt(38.0), 0.000001);
  EXPECT_VEC_LENGHT_NEAR(mth::vec3<DBL>(mth::vec3<DBL>(2.0, 3.0, 5.0)).Length(), sqrt(38.0), 0.000001);

  EXPECT_VEC_LENGHT_NEAR(mth::vec3<FLT>(1.0).Length(), sqrt(3.0), 0.000001);
  EXPECT_VEC_LENGHT_NEAR(mth::vec3<FLT>(1.0, 2.0, 3.0).Length(), sqrt(14.0), 0.000001);
  EXPECT_VEC_LENGHT_NEAR(mth::vec3<FLT>(mth::vec2<FLT>(1.0f, 4.0f), 5.0f).Length(), sqrt(42.0), 0.000001);
  EXPECT_VEC_LENGHT_NEAR(mth::vec3<FLT>(mth::vec3<FLT>(2.0f, 3.0f, 5.0f)).Length(), sqrt(38.0), 0.000001);

  EXPECT_INT_VEC_LENGHT_EQ(mth::vec3<INT>(1).Length(), (INT)sqrt(3.0));
  EXPECT_INT_VEC_LENGHT_EQ(mth::vec3<INT>(1, 2, 3).Length(), (INT)sqrt(14.0));
  EXPECT_INT_VEC_LENGHT_EQ(mth::vec3<INT>(mth::vec2<INT>(1, 4), 5).Length(), (INT)sqrt(42));
  EXPECT_INT_VEC_LENGHT_EQ(mth::vec3<INT>(mth::vec3<INT>(2, 3, 5)).Length(), (INT)sqrt(38));

  EXPECT_VEC_LENGHT_NEAR(mth::vec3<DBL>(1.0).Length2(), 3.0, 0.000001);
  EXPECT_VEC_LENGHT_NEAR(mth::vec3<DBL>(1.0, 2.0, 3.0).Length2(), 14.0, 0.000001);
  EXPECT_VEC_LENGHT_NEAR(mth::vec3<DBL>(mth::vec2<DBL>(2.0, 3.0), 5.0).Length2(), 38.0, 0.000001);
  EXPECT_VEC_LENGHT_NEAR(mth::vec3<DBL>(mth::vec3<DBL>(2.0, 3.0, 5.0)).Length2(), 38.0, 0.000001);

  EXPECT_VEC_LENGHT_NEAR(mth::vec3<FLT>(1.0).Length2(), 3.0, 0.000001);
  EXPECT_VEC_LENGHT_NEAR(mth::vec3<FLT>(1.0, 2.0, 3.0).Length2(), 14.0, 0.000001);
  EXPECT_VEC_LENGHT_NEAR(mth::vec3<FLT>(mth::vec2<FLT>(1.0f, 4.0f), 5.0f).Length2(), 42.0, 0.000001);
  EXPECT_VEC_LENGHT_NEAR(mth::vec3<FLT>(mth::vec3<FLT>(2.0f, 3.0f, 5.0f)).Length2(), 38.0, 0.000001);

  EXPECT_INT_VEC_LENGHT_EQ(mth::vec3<INT>(1).Length2(), 3);
  EXPECT_INT_VEC_LENGHT_EQ(mth::vec3<INT>(1, 2, 3).Length2(), 14);
  EXPECT_INT_VEC_LENGHT_EQ(mth::vec3<INT>(mth::vec2<INT>(1, 4), 5).Length2(), 42);
  EXPECT_INT_VEC_LENGHT_EQ(mth::vec3<INT>(mth::vec3<INT>(2, 3, 5)).Length2(), 38);
}

TEST(MathVec4Test, Lenght)
{
  EXPECT_VEC_LENGHT_NEAR(mth::vec4<DBL>(1.0).Length(), sqrt(4.0), 0.000001);
  EXPECT_VEC_LENGHT_NEAR(mth::vec4<DBL>(1.0, 2.0, 3.0, 4.0).Length(), sqrt(30.0), 0.000001);
  EXPECT_VEC_LENGHT_NEAR(mth::vec4<DBL>(mth::vec3<DBL>(2.0, 3.0, 1.0), 5.0).Length(), sqrt(39.0), 0.000001);
  EXPECT_VEC_LENGHT_NEAR(mth::vec4<DBL>(mth::vec4<DBL>(2.0, 3.0, 5.0, 7.0)).Length(), sqrt(87.0), 0.000001);

  EXPECT_VEC_LENGHT_NEAR(mth::vec4<FLT>(5.0).Length(), sqrt(100), 0.000001);
  EXPECT_VEC_LENGHT_NEAR(mth::vec4<FLT>(1.0, 2.0, 3.0, 0.0).Length(), sqrt(14.0), 0.000001);
  EXPECT_VEC_LENGHT_NEAR(mth::vec4<FLT>(mth::vec3<FLT>(1.0f, 4.0f, -10.0f), 5.0f).Length(), sqrt(142.0), 0.000001);
  EXPECT_VEC_LENGHT_NEAR(mth::vec4<FLT>(mth::vec4<FLT>(6.0f, 2.0f, 3.0f, 5.0f)).Length(), sqrt(74.0), 0.000001);

  EXPECT_INT_VEC_LENGHT_EQ(mth::vec4<INT>(1).Length(), (INT)sqrt(4.0));
  EXPECT_INT_VEC_LENGHT_EQ(mth::vec4<INT>(1, 2, 3, 2).Length(), (INT)sqrt(18.0));
  EXPECT_INT_VEC_LENGHT_EQ(mth::vec4<INT>(mth::vec3<INT>(1, 4, 20), 5).Length(), (INT)sqrt(442));
  EXPECT_INT_VEC_LENGHT_EQ(mth::vec4<INT>(mth::vec4<INT>(2, 3, 5, -14)).Length(), (INT)sqrt(234));

  EXPECT_VEC_LENGHT_NEAR(mth::vec4<DBL>(0.0).Length2(), 0.0, 0.000001);
  EXPECT_VEC_LENGHT_NEAR(mth::vec4<DBL>(-15.0, 1.0, 2.0, 3.0).Length2(), (239.0), 0.000001);
  EXPECT_VEC_LENGHT_NEAR(mth::vec4<DBL>(mth::vec3<DBL>(5.0, 3.0, 0.0), 5.0).Length2(), 59.0, 0.000001);
  EXPECT_VEC_LENGHT_NEAR(mth::vec4<DBL>(mth::vec4<DBL>(1.0, 1.0, 1.0, 8.0)).Length2(), 67.0, 0.000001);

  EXPECT_VEC_LENGHT_NEAR(mth::vec4<FLT>(1.0).Length2(), 4.0, 0.000001);
  EXPECT_VEC_LENGHT_NEAR(mth::vec4<FLT>(13.0, 8.0, 2.0, 3.0).Length2(), 246.0, 0.000001);
  EXPECT_VEC_LENGHT_NEAR(mth::vec4<FLT>(mth::vec3<FLT>(1.0f, 4.0f, -1.0f), 5.0f).Length2(), 43.0, 0.000001);
  EXPECT_VEC_LENGHT_NEAR(mth::vec4<FLT>(mth::vec4<FLT>(2.0f, 17.0f, 3.0f, 5.0f)).Length2(), 327.0, 0.000001);

  EXPECT_INT_VEC_LENGHT_EQ(mth::vec4<INT>(1).Length2(), 4);
  EXPECT_INT_VEC_LENGHT_EQ(mth::vec4<INT>(1, 2, 3, 9).Length2(), 95);
  EXPECT_INT_VEC_LENGHT_EQ(mth::vec4<INT>(mth::vec3<INT>(-0, 1, 4), 5).Length2(), 42);
  EXPECT_INT_VEC_LENGHT_EQ(mth::vec4<INT>(mth::vec4<INT>(2, 3, 5, -95)).Length2(), 9063);
}
    