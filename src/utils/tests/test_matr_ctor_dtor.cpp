/*************************************************************
 * Copyright (C) 2026
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : test_matr_ctor_dtor.cpp
 * PURPOSE     : Ray-Tracing project.
 *               Test system module.
 * PROGRAMMER  : CGSG-SummerCamp'2026.
 *               Artem Zhukov (AZ3).  
 * LAST UPDATE : 28.07.2026.
 * NOTE        : Module namespace 'tst'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "gert.h"
#include "mth/mth.h"
#include "test_system.h"

/* Test constructor method function */
TEST(Matr, CtorDtor)
{
  mth::matr m(1, 1, 1, 1, 1 ,1 ,1, 1, 1, 1, 1, 1, 1, 1, 1, 1);    
  DBL Test[4][4] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  mth::matr<FLT> f {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

  std::cout << "Test constructor from const array " << std::endl;
  EXPECT_MATR_EQ(m, f);
  std::cout << "End test constructor from const array " << std::endl;

  std::cout << "Test constructor from another matrix " << std::endl;
  mth::matr s(f);
  EXPECT_MATR_EQ(m, s);
  std::cout << "End test constructor from another matrix " << std::endl;


  std::cout << "Test constructor from DBL list(random)" << std::endl;
  for (INT i = 0; i < 1; i++)
  {
    mth::matr<DBL> k(i * 0.5, i * rand() % 4, i * 4, i * 8 * sin(i), i * 2, i + sin(i * i * i), i * 1, i * 3, i + tanf(i + 3), i * 1, i, i * 9, i, i + i * i, i * 1, i);
    mth::matr<DBL> j(k);
      EXPECT_MATR_EQ(k, j);
  }
  std::cout << "End test constructor from DBL list(random)" << std::endl;

  std::cout << "Test constructor from DBL array(random)" << std::endl;
  for (INT i = 0; i < 1; i++)
  {
    DBL G[16] = {(DBL)i * 5, (DBL)i * sin(3.0), (DBL)i * 4.3 * sin(cosf(1.0 * sin(100.0))), (DBL)i * 8.3 * sin(i), (DBL)i * 2.0 + sin(i * 0.5), (DBL)i + sin(i * i * i * 1.0), (DBL)i * 1.0, (DBL)i * 3.0 + tan(i + 3.0), i * 1.0 + tan(i + 3.0), (DBL)i * 1.0, (DBL)i * 1.0, i * 9.4, i * 1.0, (DBL)i * 0.3 + (DBL)i * 0.7, i * 1.0, (DBL)i + 4.0};
    mth::matr j {(DBL)i * 5, (DBL)i * sin(3.0), (DBL)i * 4.3 * sin(cosf(1.0 * sin(100.0))), (DBL)i * 8.3 * sin(i), (DBL)i * 2.0 + sin(i * 0.5), (DBL)i + sin(i * i * i * 1.0), (DBL)i * 1.0, (DBL)i * 3.0 + tan(i + 3.0), i * 1.0 + tan(i + 3.0), (DBL)i * 1.0, (DBL)i * 1.0, i * 9.4, i * 1.0, (DBL)i * 0.3 + (DBL)i * 0.7, i * 1.0, (DBL)i + 4.0};
    mth::matr k(j);
    EXPECT_MATR_EQ(j, k);

/*    std::cout << " ===================================================" << std::endl;
    std::cout << "Matrix J:" << std::endl;
    std::cout << *(j[0]) << " " << *(j[0] + 1) << " " << *(j[0] + 2) << " " << *(j[0] + 3) << std::endl;
    std::cout << *(j[1]) << " " << *(j[1] + 1) << " " <<  *(j[1] + 2) << " " << *(j[1] + 3) << std::endl;
    std::cout << *(j[2]) << " " << *(j[2] + 1) << " " <<  *(j[2] + 2) << " " << *(j[2] + 3) << std::endl;
    std::cout << *(j[3]) << " " << *(j[3] + 1) << " " <<  *(j[3] + 2) << " " << *(j[3] + 3) << std::endl;
    std::cout << " ===================================================" << std::endl;

    std::cout << " ===================================================" << std::endl;
    std::cout << "Matrix K:" << std::endl;
    std::cout << *(k[0]) << " " << *(k[0] + 1) << " " << *(k[0] + 2) << " " << *(k[0] + 3) << std::endl;
    std::cout << *(k[1]) << " " << *(k[1] + 1) << " " <<  *(k[1] + 2) << " " << *(k[1] + 3) << std::endl;
    std::cout << *(k[2]) << " " << *(k[2] + 1) << " " <<  *(k[2] + 2) << " " << *(k[2] + 3) << std::endl;
    std::cout << *(k[3]) << " " << *(k[3] + 1) << " " <<  *(k[3] + 2) << " " << *(k[3] + 3) << std::endl;
    std::cout << " ===================================================" << std::endl;
*/
  }

  std::cout << "Test constructor from INT array" << std::endl;
  for (INT i = -1000; i < -999; i++)
  {
    INT G[16] = {(INT)(i * 0.5), i * rand() % 4, i * 4, i * 8 * (INT)sin(i), i * 2, i + (INT)sin(i * i * i), i * 1, i * 3, i + (INT)tanf(i + 3), i * 1, i, i * 9, i, i + i * i, i * 1, i};
    mth::matr j {(INT)(i * 0.5), i * rand() % 4, i * 4, i * 8 * (INT)sin(i), i * 2, i + (INT)sin(i * i * i), i * 1, i * 3, i + (INT)tanf(i + 3), i * 1, i, i * 9, i, i + i * i, i * 1, i};
    mth::matr k {(INT)(i * 0.5), i * rand() % 4, i * 4, i * 8 * (INT)sin(i), i * 2, i + (INT)sin(i * i * i), i * 1, i * 3, i + (INT)tanf(i + 3), i * 1, i, i * 9, i, i + i * i, i * 1, i};
    EXPECT_MATR_EQ(j, k);
  }
  std::cout << "End test constructor from INT array" << std::endl;

  std::cout << "Test constructor from another matrix x3(check copy constructor)" << std::endl;

  for (INT i = -1000; i < -999; i++)
  {
    INT G[16] = {(INT)(i * 0.5), i * rand() % 4, i * 4, i * 8 * (INT)sin(i), i * 2, i + (INT)sin(i * i * i), i * 1, i * 3, i + (INT)tanf(i + 3), i * 1, i, i * 9, i, i + i * i, i * 1, i};
    mth::matr j {(INT)(i * 0.5), i * rand() % 4, i * 4, i * 8 * (INT)sin(i), i * 2, i + (INT)sin(i * i * i), i * 1, i * 3, i + (INT)tanf(i + 3), i * 1, i, i * 9, i, i + i * i, i * 1, i};
    mth::matr k {(INT)(i * 0.5), i * rand() % 4, i * 4, i * 8 * (INT)sin(i), i * 2, i + (INT)sin(i * i * i), i * 1, i * 3, i + (INT)tanf(i + 3), i * 1, i, i * 9, i, i + i * i, i * 1, i};
    mth::matr l(k);
    EXPECT_MATR_EQ(l, j);
  }
  std::cout << " End test constructor from another matrix" << std::endl;

} /* End of 'Matr.CtorDtor' function */

/* END OF 'test_matr_ctor_dtor.cpp' FILE */