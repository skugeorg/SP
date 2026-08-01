/*************************************************************
 * Copyright (C) 2026
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : test_system.h
 * PURPOSE     : Ray-Tracing project.
 *               Test system module.
 * PROGRAMMER  : CGSG-SummerCamp'2026.
 * LAST UPDATE : 28.07.2026.
 * NOTE        : Module namespace 'tst'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __test_system_h_
#define __test_system_h_

/* Generate passed result macro */
#define TEST_PASSED(Str) \
  std::cout << tst::SetColor(0x00FF00) << "PASSED: " << tst::SetColor(0xFFFFFF) << Str << std::endl

#define TEST_FAILED(Str) \
  do                                                                                                   \
  {                                                                                                    \
    std::cout << tst::SetColor(0xFF5000) << "FAILED: " << tst::SetColor(0xFFFFFF) << Str << std::endl; \
    throw std::logic_error("");                                                                        \
  } while (FALSE)

/* Check equivalence macro function */
#define EXPECT_EQ(a, b) \
  do                                                                     \
  {                                                                      \
    if ((a) != (b))                                                      \
      TEST_FAILED(std::format("{} != {} ({} vs {})", #a, #b, (a), (b))); \
    else                                                                 \
      TEST_PASSED(std::format("{} == {}", #a, #b));                      \
  } while (FALSE)

/* Check mostly equivalence macro function */
#define EXPECT_NEAR(a, b, epsilon) \
  do                                                                                      \
  {                                                                                       \
    if (std::abs((a) - (b)) > epsilon)                                                    \
      TEST_FAILED(std::format("{} != {} within {} ({} vs {})", #a, #b, epsilon, (a), (b); \
    else                                                                                  \
      TEST_PASSED(std::format("{} ~= {} (epsilon {})", #a, #b, epsilon);                  \
  } while (FALSE)

/* Check equivalence for float type macro function */
#define EXPECT_FLT_EQ(a, b) \
    EXPECT_NEAR((a), (b), 1e-5F)

/* Check equivalence for double type macro function */
#define EXPECT_DBL_EQ(a, b) \
    EXPECT_NEAR((a), (b), 1e-12F)

/* Check for conditional TRUE value macro function */
#define EXPECT_TRUE(condition) \
  do                                       \
  {                                        \
    if (!(condition))                      \
      TEST_FAILED(#condition " is false"); \
    else                                   \
      TEST_PASSED(#condition " is true");  \
  } while (FALSE)

/* Check for conditional FALSE value macro function */
#define EXPECT_FALSE(condition) \
  do                                       \
  {                                        \
    if (!(condition))                      \
      TEST_PASSED(#condition " is false"); \
    else                                   \
      TEST_FAILED(#condition " is true");  \
  } while (FALSE)

/* Check equivalence macro function with normal out for operator type * */
#define EXPECT_EQ_OPER_PNT_MATR(a, b) \
  do                                                                     \
  {                                                                      \
    if ((a) != (b))                                                      \
      TEST_FAILED(std::format("{} != {} ({} vs {})", #a, #b, (a), (b))); \
    else                                                                 \
      TEST_PASSED(std::format("{}:{} == {}:{}", #a, (a), #b, (b)));                      \
  } while (FALSE)

/* Check matrix equivalence macro function */
#define EXPECT_MATR_EQ(m1, m2) \
  do                                                                                                                  \
  {                                                                                                                   \
    if (*(m1) != *(m2) || *(m1 + 1) != *(m2 + 1) || *(m1 + 2) != *(m2 + 2) || *(m1 + 3) != *(m2 + 3) ||               \
        *(m1 + 4) != *(m2 + 4) || *(m1 + 5) != *(m2 + 5) || *(m1 + 6) != *(m2 + 6) || *(m1 + 7) != *(m2 + 7) ||       \
        *(m1 + 8) != *(m2 + 8) || *(m1 + 9) != *(m2 + 9) || *(m1 + 10) != *(m2 + 10) || *(m1 + 11) != *(m2 + 11) ||   \
        *(m1 + 12) != *(m2 + 12) || *(m1 + 13) != *(m2 + 13) || *(m1 + 14) != *(m2 + 14) || *(m1 + 15) != *(m2 + 15)) \
      TEST_FAILED(std::format("{} != {}\nYour Matrix:\n{}, {}, {}, {}\n"                                              \
                              "{}, {}, {}, {}\n"                                                                      \
                              "{}, {}, {}, {}\n"                                                                      \
                              "{}, {}, {}, {}\n"                                                                      \
                              "Right Matrix:\n"                                                                       \
                              "{}, {}, {}, {}\n"                                                                      \
                              "{}, {}, {}, {}\n"                                                                      \
                              "{}, {}, {}, {}\n"                                                                      \
                              "{}, {}, {}, {}\n",                                                                     \
                              #m1, #m2, *(m1), *(m1 + 1), *(m1 + 2), *(m1 + 3),                                       \
                              *(m1 + 4), *(m1 + 5), *(m1 + 6), *(m1 + 7),                                             \
                              *(m1 + 8), *(m1 + 9), *(m1 + 10), *(m1 + 11),                                           \
                              *(m1 + 12), *(m1 + 13), *(m1 + 14), *(m1 + 15),                                         \
                              *(m2), *(m2 + 1), *(m2 + 2), *(m2 + 3),                                                 \
                              *(m2 + 4), *(m2 + 5), *(m2 + 6), *(m2 + 7),                                             \
                              *(m2 + 8), *(m2 + 9), *(m2 + 10), *(m2 + 11),                                           \
                              *(m2 + 12), *(m2 + 13), *(m2 + 14), *(m2 + 15)));                                       \
    else                                                                                                              \
      TEST_PASSED(std::format("{} == {}", #m1, #m2));                                                                 \
  } while (FALSE)

/* Check matrix mostly equivalence macro function */
#define EXPECT_MATR_NEAR(m1, m2, epsilon) \
  do                                                                                                                                                                                              \
  {                                                                                                                                                                                               \
    if (std::abs(*(m1) - *(m2)) > epsilon || std::abs(*(m1 + 1) - *(m2 + 1)) > epsilon || std::abs(*(m1 + 2) - *(m2 + 2)) > epsilon || std::abs(*(m1 + 3) - *(m2 + 3)) > epsilon ||               \
        std::abs(*(m1 + 4) - *(m2 + 4)) > epsilon || std::abs(*(m1 + 5) - *(m2 + 5)) > epsilon || std::abs(*(m1 + 6) - *(m2 + 6)) > epsilon || std::abs(*(m1 + 7) - *(m2 + 7)) > epsilon ||       \
        std::abs(*(m1 + 8) - *(m2 + 8)) > epsilon || std::abs(*(m1 + 9) - *(m2 + 9)) > epsilon || std::abs(*(m1 + 10) - *(m2 + 10)) > epsilon || std::abs(*(m1 + 11) - *(m2 + 11)) > epsilon ||   \
        std::abs(*(m1 + 12) - *(m2 + 12)) > epsilon || std::abs(*(m1 + 13) - *(m2 + 13)) > epsilon || std::abs(*(m1 + 14) - *(m2 + 14)) > epsilon || std::abs(*(m1 + 15) - *(m2 + 15)) > epsilon) \
      TEST_FAILED(std::format("{} != {}\nYour Matrix:\n{}, {}, {}, {}\n"                                                                                                                          \
                              "{}, {}, {}, {}\n"                                                                                                                                                  \
                              "{}, {}, {}, {}\n"                                                                                                                                                  \
                              "{}, {}, {}, {}\n"                                                                                                                                                  \
                              "Right Matrix:\n"                                                                                                                                                   \
                              "{}, {}, {}, {}\n"                                                                                                                                                  \
                              "{}, {}, {}, {}\n"                                                                                                                                                  \
                              "{}, {}, {}, {}\n"                                                                                                                                                  \
                              "{}, {}, {}, {}\n",                                                                                                                                                 \
                              #m1, #m2, *(m1), *(m1 + 1), *(m1 + 2), *(m1 + 3),                                                                                                                   \
                              *(m1 + 4), *(m1 + 5), *(m1 + 6), *(m1 + 7),                                                                                                                         \
                              *(m1 + 8), *(m1 + 9), *(m1 + 10), *(m1 + 11),                                                                                                                       \
                              *(m1 + 12), *(m1 + 13), *(m1 + 14), *(m1 + 15),                                                                                                                     \
                              *(m2), *(m2 + 1), *(m2 + 2), *(m2 + 3),                                                                                                                             \
                              *(m2 + 4), *(m2 + 5), *(m2 + 6), *(m2 + 7),                                                                                                                         \
                              *(m2 + 8), *(m2 + 9), *(m2 + 10), *(m2 + 11),                                                                                                                       \
                              *(m2 + 12), *(m2 + 13), *(m2 + 14), *(m2 + 15)));                                                                                                                   \
    else                                                                                                                                                                                          \
      TEST_PASSED(std::format("{} == {}", #m1, #m2));                                                                                                                                             \
  } while (FALSE)

/* Check matrix equivalence macro function */
#define EXPECT_MATR_EQ2(m1, m2) \
  do                                                                                   \
  {                                                                                    \
    for (INT i = 0; i < 16; i++)                                                       \
      if (*(m1 + i) != *(m2 + i))                                                      \
      {                                                                                \
        TEST_FAILED(std::format("{} != {}\nYour Matrix:\n{}, {}, {}, {}\n"             \
                                "{}, {}, {}, {}\n"                                     \
                                "{}, {}, {}, {}\n"                                     \
                                "{}, {}, {}, {}\n"                                     \
                                "Right Matrix:\n"                                      \
                                "{}, {}, {}, {}\n"                                     \
                                "{}, {}, {}, {}\n"                                     \
                                "{}, {}, {}, {}\n"                                     \
                                "{}, {}, {}, {}\n",                                    \
                                #m1, #m2, *(m1), *(m1 + 1), *(m1 + 2), *(m1 + 3),      \
                                *(m1 + 4), *(m1 + 5), *(m1 + 6), *(m1 + 7),            \
                                *(m1 + 8), *(m1 + 9), *(m1 + 10), *(m1 + 11),          \
                                *(m1 + 12), *(m1 + 13), *(m1 + 14), *(m1 + 15),        \
                                *(m2), *(m2 + 1), *(m2 + 2), *(m2 + 3),                \
                                *(m2 + 4), *(m2 + 5), *(m2 + 6), *(m2 + 7),            \
                                *(m2 + 8), *(m2 + 9), *(m2 + 10), *(m2 + 11),          \
                                *(m2 + 12), *(m2 + 13), *(m2 + 14), *(m2 + 15)));      \
        return;                                                                        \
      }                                                                                \
    TEST_PASSED(std::format("{} == {}", #m1, #m2));                                    \
  } while (FALSE)

/* Check matrix mostly equivalence macro function */
#define EXPECT_MATR_NEAR2(m1, m2, epsilon) \
  do                                                                                   \
  {                                                                                    \
    for (INT i = 0; i < 16; i++)                                                       \
      if (std::abs(*(m1 + i) - *(m2 + i)) > epsilon)                                   \
      {                                                                                \
        TEST_FAILED(std::format("{} != {}\nYour Matrix:\n{}, {}, {}, {}\n"             \
                                "{}, {}, {}, {}\n"                                     \
                                "{}, {}, {}, {}\n"                                     \
                                "{}, {}, {}, {}\n"                                     \
                                "Right Matrix:\n"                                      \
                                "{}, {}, {}, {}\n"                                     \
                                "{}, {}, {}, {}\n"                                     \
                                "{}, {}, {}, {}\n"                                     \
                                "{}, {}, {}, {}\n",                                    \
                                #m1, #m2, *(m1), *(m1 + 1), *(m1 + 2), *(m1 + 3),      \
                                *(m1 + 4), *(m1 + 5), *(m1 + 6), *(m1 + 7),            \
                                *(m1 + 8), *(m1 + 9), *(m1 + 10), *(m1 + 11),          \
                                *(m1 + 12), *(m1 + 13), *(m1 + 14), *(m1 + 15),        \
                                *(m2), *(m2 + 1), *(m2 + 2), *(m2 + 3),                \
                                *(m2 + 4), *(m2 + 5), *(m2 + 6), *(m2 + 7),            \
                                *(m2 + 8), *(m2 + 9), *(m2 + 10), *(m2 + 11),          \
                                *(m2 + 12), *(m2 + 13), *(m2 + 14), *(m2 + 15)));      \
        return;                                                                        \
      }                                                                                \
    TEST_PASSED(std::format("{} == {}", #m1, #m2));                                    \
  } while (FALSE)

/* Check vec2 equivalence macro function */
#define EXPECT_VEC2_EQ(v1, v2) \
  do                                                                                                         \
  {                                                                                                          \
    if ((v1).X != (v2).X || (v1).Y != (v2).Y)                                                                \
      TEST_FAILED(std::format("{} != {} (({}, {}) vs ({}, {}))", #v1, #v2, (v1).X, (v1).Y, (v2).X, (v2).Y)); \
    else                                                                                                     \
      TEST_PASSED(std::format("{} == {}", #v1, #v2));                                                        \
  } while (FALSE)
/* Check mostly equivalence macro function */
#define EXPECT_VEC2_NEAR(v1, v2, epsilon) \
  do                                                                                                            \
  {                                                                                                             \
    if (std::abs((v1).X - (v2).X) > (epsilon) || std::abs((v1).Y - (v2).Y) > epsilon)                           \
      TEST_FAILED(std::format("({}, {}) != ({}, {}) within {}", (v1).X, (v1).Y, (v2).X, (v2).Y, (epsilon)));    \
    else                                                                                                        \
      TEST_PASSED(std::format("({}, {}) ~= ({}, {}) (epsilon {})", (v1).X, (v1).Y, (v2).X, (v2).Y, (epsilon))); \
  } while (FALSE)

/* Check vec3 equivalence macro function */
#define EXPECT_VEC3_EQ(v1, v2) \
  do                                                                                                                                 \
  {                                                                                                                                  \
    if ((v1).X != (v2).X || (v1).Y != (v2).Y || (v1).Z != (v2).Z)                                                                    \
      TEST_FAILED(std::format("{} != {} (({}, {}, {}) vs ({}, {}, {}))", #v1, #v2, (v1).X, (v1).Y, (v1).Z, (v2).X, (v2).Y, (v2).Z)); \
    else                                                                                                                             \
      TEST_PASSED(std::format("{} == {}", #v1, #v2));                                                                                \
  } while (FALSE)

/* Check mostly equivalence macro function */
#define EXPECT_VEC3_NEAR(v1, v2, epsilon) \
  do                                                                                                                                    \
  {                                                                                                                                     \
    if (std::abs((v1).X - (v2).X) > (epsilon) || std::abs((v1).Y - (v2).Y) > epsilon || std::abs((v1).Z - (v2).Z) > (epsilon))          \
      TEST_FAILED(std::format("({}, {}, {}) != ({}, {}, {}) within {}", (v1).X, (v1).Y, (v1).Z, (v2).X, (v2).Y, (v2).Z, (epsilon)));    \
    else                                                                                                                                \
      TEST_PASSED(std::format("({}, {}, {}) ~= ({}, {}, {}) (epsilon {})", (v1).X, (v1).Y, (v1).Z, (v2).X, (v2).Y, (v2).Z, (epsilon))); \
  } while (FALSE)

/* Check vec4 equivalence macro function */
#define EXPECT_VEC4_EQ(v1, v2) \
  do                                                                                                                                                         \
  {                                                                                                                                                          \
    if ((v1).X != (v2).X || (v1).Y != (v2).Y || (v1).Z != (v2).Z || (v1).W != (v2).W)                                                                        \
      TEST_FAILED(std::format("{} != {} (({}, {}, {}, {}) vs ({}, {}, {}, {}))", #v1, #v2, (v1).X, (v1).Y, (v1).Z, (v1).W, (v2).X, (v2).Y, (v2).Z, (v2).W)); \
    else                                                                                                                                                     \
      TEST_PASSED(std::format("{} == {}", #v1, #v2));                                                                                                        \
  } while (FALSE)

/* Check mostly equivalence macro function */
#define EXPECT_VEC4_NEAR(v1, v2, epsilon) \
  do                                                                                                                                                                    \
  {                                                                                                                                                                     \
    if (std::abs((v1).X - (v2).X) > (epsilon) || std::abs((v1).Y - (v2).Y) > epsilon || std::abs((v1).Z - (v2).Z) > (epsilon) || std::abs((v1).W - (v2).W) > (epsilon)) \
      TEST_FAILED(std::format("({}, {}, {}, {}) != ({}, {}, {}, {}) within {}", (v1).X, (v1).Y, (v1).Z, (v1).W, (v2).X, (v2).Y, (v2).Z, (v2).W, (epsilon)));            \
    else                                                                                                                                                                \
      TEST_PASSED(std::format("({}, {}, {}, {}) ~= ({}, {}, {}, {}) (epsilon {})", (v1).X, (v1).Y, (v1).Z, (v1).W, (v2).X, (v2).Y, (v2).Z, (v2).W, (epsilon)));         \
  } while (FALSE)

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

/* Test declaration macro code */
#define TEST(TestSuiteName, TestName) \
  VOID TestSuiteName ## TestName( VOID );                                 \
  struct TestSuiteName ## TestName ## _Register                           \
  {                                                                       \
    TestSuiteName ## TestName ## _Register( VOID )                        \
    {                                                                     \
      tst::RegisterTest(#TestSuiteName, #TestName, TestSuiteName ## TestName); \
    }                                                                     \
  } TestSuiteName ## TestName ## _Instance;                               \
  VOID TestSuiteName ## TestName( VOID )

/* Test support namespace */
namespace tst
{
  // Function type
  using test_func_type = VOID(*)( VOID );

  /* Store test function type */
  struct test_case
  {
    std::string Suite;   // Suite name
    std::string Name;    // Subtask name
    test_func_type Func; // Test function
  }; /* End of 'test_case' structure */

  /* Get all test single ton vector function.
   * ARGUMENTS: None.
   * RETURNS:
   *   (std::vector<test_case> &) result test subtasks vector.
   */
  inline std::vector<test_case> & GetTests( VOID )
  {
    static std::vector<test_case> Tests;
    return Tests;
  } /* End of 'GetTests' function */

  /* Register test function.
   * ARGUMENTS:
   *   - test suite name:
   *       const std::string &Suite;
   *   - test name:
   *       const std::string &Name;
   *   - test function:
   *       test_func_type Func
   * RETURNS: None.
   */
  inline VOID RegisterTest( const std::string &Suite, const std::string &Name, test_func_type Func )
  {
    GetTests().push_back({Suite, Name, Func});
  } /* End of 'RegisterTest' function */


  /* Run all registered tests function.
   * ARGUMENTS: None.
   * RETURNS:
   *   (BOOL) TRUE if all tests are passed.
   */
  inline BOOL RunAllTests( VOID )
  {
    INT passed = 0, failed = 0;

    for (const auto &test : GetTests())
    {
      std::cout << "[ RUN      ] " << test.Suite << "." << test.Name << std::endl;
      try
      {
        test.Func();
        std::cout << "[       OK ] " << test.Suite << "." << test.Name << std::endl;
        passed++;
      }
      catch (...)
      {
        std::cerr << "[  FAILED  ] " << test.Suite << "." << test.Name << std::endl;
        failed++;
      }
    }
    std::cout << "TESTS PASSED: " << passed << ", FAILED: " << failed << std::endl;
    return failed == 0;
  } /* End of 'RunAllTests' function */

  /* Change output color function.
   * ARGUMENTS:
   *   - foreground and background colors (RGB in DWORD pack):
   *       DWORD ForeColor, BackColor;
   * RETURNS: None.
   */
  inline std::string SetColor( DWORD ForeColor, DWORD BackColor = 0 )
  {
    return std::format("\x1b[38;2;{};{};{}m\x1b[48;2;{};{};{}m",
      COM_LONGBYTE2(ForeColor), COM_LONGBYTE1(ForeColor), COM_LONGBYTE0(ForeColor),
      COM_LONGBYTE2(BackColor), COM_LONGBYTE1(BackColor), COM_LONGBYTE0(BackColor));
  } /* End of 'SetColor' function */
} /* end of 'tst' namespace */


#endif /* __test_system_h_ */

/* END OF 'test_system.h' FILE */
