/*************************************************************
 * Copyright (C) 2026
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : mth_matr.h
 * PURPOSE     : Ray-tracing project.
 *               Mathematics library.
 *               Matrix handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2026.
 *               Skulyabin Georgy.
 * LAST UPDATE : 28.07.2026.
 * NOTE        : Module namespace 'mth'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __mth_matr4x4_h_
#define __mth_matr4x4_h_

/* Math library namespace */
namespace mth
{
  /* Space transformation matrix handle class */
  template<typename type>
    class matr
    {
    private:
      // Transformation matrix
      type M[4][4];

      /* Inverse mat4rix and it presence flag */
      mutable BOOL IsInverseObtain;
      mutable type InverseM[4][4];

      /* Matrix 3x3 determinant obtain function.
       * ARGUMENTS:
       *   - matrix elements:
       *       type A11, A12, A13,
       *            A21, A22, A23,
       *            A31, A32, A33;
       * RETURNS:
       *   (FLT) determinant value.
       */
      static type MatrDeterm3x3( type A11, type A12, type A13,
                                 type A21, type A22, type A23,
                                 type A31, type A32, type A33 )
      {
        return A11 * A22 * A33 + A12 * A23 * A31 + A13 * A21 * A32 -
         A11 * A23 * A32 - A12 * A21 * A33 - A13 * A22 * A31;
      }

      /* Find matrix determinator function.
       * ARGUMENTS:
       *   - input matrix:
       *       MATR M;
       * RETURNS:
       *   (FLT) Matrix determinator.
       */
      inline type MatrDeterm( VOID ) const
      {
        return
          M[0][0] * MatrDeterm3x3(M[1][1], M[1][2], M[1][3],
                                    M[2][1], M[2][2], M[2][3],
                                    M[3][1], M[3][2], M[3][3]) -
          M[0][1] * MatrDeterm3x3(M[1][0], M[1][2], M[1][3],
                                    M[2][0], M[2][2], M[2][3],
                                    M[3][0], M[3][2], M[3][3]) +
          M[0][2] * MatrDeterm3x3(M[1][0], M[1][1], M[1][3],
                                    M[2][0], M[2][1], M[2][3],
                                    M[3][0], M[3][1], M[3][3]) -
          M[0][3] * MatrDeterm3x3(M[1][0], M[1][1], M[1][2],
                                    M[2][0], M[2][1], M[2][2],
                                    M[3][0], M[3][1], M[3][2]);
      }

      /* Evaluate inverse matrix function.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      inline VOID EvaluateInverseMatrix( VOID ) const
      {
        if (IsInverseObtain)
          return;

        IsInverseObtain = TRUE;

        type det = MatrDeterm();

        if (det == 0)
        {
          InverseM[0][0] = 1;
          InverseM[0][1] = 0;
          InverseM[0][2] = 0;
          InverseM[0][3] = 0;

          InverseM[1][0] = 0;
          InverseM[1][1] = 1;
          InverseM[1][2] = 0;
          InverseM[1][3] = 0;

          InverseM[2][0] = 0;
          InverseM[2][1] = 0;
          InverseM[2][2] = 1;
          InverseM[2][3] = 0;

          InverseM[3][0] = 0;
          InverseM[3][1] = 0;
          InverseM[3][2] = 0;
          InverseM[3][3] = 1;
          return;
        }

        /* Build adjoint matrix */
        InverseM[0][0] =
          MatrDeterm3x3(M[1][1], M[1][2], M[1][3],
                        M[2][1], M[2][2], M[2][3],
                        M[3][1], M[3][2], M[3][3]) / det;
        InverseM[0][1] =
         -MatrDeterm3x3(M[1][0], M[1][2], M[1][3],
                        M[2][0], M[2][2], M[2][3],
                        M[3][0], M[3][2], M[3][3]) / det;
        InverseM[0][2] =
          MatrDeterm3x3(M[1][0], M[1][1], M[1][3],
                        M[2][0], M[2][1], M[2][3],
                        M[3][0], M[3][1], M[3][3]) / det;
        InverseM[0][3] =
         -MatrDeterm3x3(M[1][0], M[1][1], M[1][2],
                        M[2][0], M[2][1], M[2][2],
                        M[3][0], M[3][1], M[3][2]) / det;

        InverseM[1][0] =
         -MatrDeterm3x3(M[0][1], M[0][2], M[0][3],
                        M[2][1], M[2][2], M[2][3],
                        M[3][1], M[3][2], M[3][3]) / det;
        InverseM[1][1] =
          MatrDeterm3x3(M[0][0], M[0][2], M[0][3],
                        M[2][0], M[2][2], M[2][3],
                        M[3][0], M[3][2], M[3][3]) / det;
        InverseM[1][2] =
         -MatrDeterm3x3(M[0][0], M[0][1], M[0][3],
                        M[2][0], M[2][1], M[2][3],
                        M[3][0], M[3][1], M[3][3]) / det;
        InverseM[1][3] =
          MatrDeterm3x3(M[0][0], M[0][1], M[0][2],
                        M[2][0], M[2][1], M[2][2],
                        M[3][0], M[3][1], M[3][2]) / det;

        InverseM[2][0] =
          MatrDeterm3x3(M[0][1], M[0][2], M[0][3],
                        M[1][1], M[1][2], M[1][3],
                        M[3][1], M[3][2], M[3][3]) / det;
        InverseM[2][1] =
         -MatrDeterm3x3(M[0][0], M[0][2], M[0][3],
                        M[1][0], M[1][2], M[1][3],
                        M[3][0], M[3][2], M[3][3]) / det;
        InverseM[2][2] =
          MatrDeterm3x3(M[0][0], M[0][1], M[0][3],
                        M[1][0], M[1][1], M[1][3],
                        M[3][0], M[3][1], M[3][3]) / det;
        InverseM[2][3] =
         -MatrDeterm3x3(M[0][0], M[0][1], M[0][2],
                        M[1][0], M[1][1], M[1][2],
                        M[3][0], M[3][1], M[3][2]) / det;

        InverseM[3][0] =
         -MatrDeterm3x3(M[0][1], M[0][2], M[0][3],
                        M[1][1], M[1][2], M[1][3],
                        M[2][1], M[2][2], M[2][3]) / det;
        InverseM[3][1] =
          MatrDeterm3x3(M[0][0], M[0][2], M[0][3],
                        M[1][0], M[1][2], M[1][3],
                        M[2][0], M[2][2], M[2][3]) / det;
        InverseM[3][2] =
         -MatrDeterm3x3(M[0][0], M[0][1], M[0][3],
                        M[1][0], M[1][1], M[1][3],
                        M[2][0], M[2][1], M[2][3]) / det;
        InverseM[3][3] =
          MatrDeterm3x3(M[0][0], M[0][1], M[0][2],
                        M[1][0], M[1][1], M[1][2],
                        M[2][0], M[2][1], M[2][2]) / det;
      }

    public:

      /* Class default constructor */
      matr( VOID ) : IsInverseObtain(FALSE)
      {
      }


      /* Matrix constructor.
       * ARGUMENTS:
       *   - matrix 4x4 values:
       *       type
       *         A00, A01, A02, A03,
       *         A10, A11, A12, A13,
       *         A20, A21, A22, A23,
       *         A30, A31, A32, A33;
       */
      matr( type A00, type A01, type A02, type A03,
            type A10, type A11, type A12, type A13,
            type A20, type A21, type A22, type A23,
            type A30, type A31, type A32, type A33 ) : IsInverseObtain(FALSE)
      {
        M[0][0] = A00, M[0][1] = A01, M[0][2] = A02, M[0][3] = A03,
        M[1][0] = A10, M[1][1] = A11, M[1][2] = A12, M[1][3] = A13,
        M[2][0] = A20, M[2][1] = A21, M[2][2] = A22, M[2][3] = A23,
        M[3][0] = A30, M[3][1] = A31, M[3][2] = A32, M[3][3] = A33;
      }
      /* Class constructor.
       * ARGUMENTS:
       *   - matrix elements:
       *       type R[4][4];
       */
      matr( type R[4][4] ) : IsInverseObtain(FALSE)
      {
        M[0][0] = R[0][0], M[0][1] = R[0][1], M[0][2] = R[0][2], M[0][3] = R[0][3],
        M[1][0] = R[1][0], M[1][1] = R[1][1], M[1][2] = R[1][2], M[1][3] = R[1][3],
        M[2][0] = R[2][0], M[2][1] = R[2][1], M[2][2] = R[2][2], M[2][3] = R[2][3],
        M[3][0] = R[3][0], M[3][1] = R[3][1], M[3][2] = R[3][2], M[3][3] = R[3][3];
      }

      /* Obtain matrix first element pointer function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (type *) pointer to A00 element.
       */
      operator type *( VOID )
      {
        return &M[0][0];
      }/* End of 'operator const type *' function */

      /* Obtain matrix first element pointer function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (const type *) pointer to A00 element.
       */
      operator const type *( VOID ) const
      {
        return &M[0][0];
      }/* End of 'operator const type *' function */

      /* Obtain inverse matrix function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (matr) result matrix.
       */
      matr<type> Inverse( VOID ) const
      {
        if (!IsInverseObtain)
          EvaluateInverseMatrix();
        
        return matr(InverseM);
      }/* End of 'Inverse' function */

      /* Obtain transpose matrix function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (matr) result matrix.
       */
      matr<type> Transpose( VOID ) const
      {
        matr r(
          M[0][0],
          M[1][0],
          M[2][0],
          M[3][0],
               
          M[0][1],
          M[1][1],
          M[2][1],
          M[3][1],
               
          M[0][2],
          M[1][2],
          M[2][2],
          M[3][2],
               
          M[0][3],
          M[1][3],
          M[2][3],
          M[3][3]
        );

        return r;
      }/* End of 'Transpose' function */

      /* Multiplication of two matrix function.
       * ARGUMENTS:
       *   - matrix to be multiply:
       *       const matr<type> &A;
       * RETURNS:
       *   (matr) result matrix.
       */
      matr operator*( const matr<type> &A ) const
      {
        return matr(
          M[0][0] * A.M[0][0] +
          M[0][1] * A.M[1][0] +
          M[0][2] * A.M[2][0] +
          M[0][3] * A.M[3][0],
                          
          M[0][0] * A.M[0][1] +
          M[0][1] * A.M[1][1] +
          M[0][2] * A.M[2][1] +
          M[0][3] * A.M[3][1],
                          
          M[0][0] * A.M[0][2] +
          M[0][1] * A.M[1][2] +
          M[0][2] * A.M[2][2] +
          M[0][3] * A.M[3][2],
                          
          M[0][0] * A.M[0][3] +
          M[0][1] * A.M[1][3] +
          M[0][2] * A.M[2][3] +
          M[0][3] * A.M[3][3],
                          
          M[1][0] * A.M[0][0] +
          M[1][1] * A.M[1][0] +
          M[1][2] * A.M[2][0] +
          M[1][3] * A.M[3][0],
                          
          M[1][0] * A.M[0][1] +
          M[1][1] * A.M[1][1] +
          M[1][2] * A.M[2][1] +
          M[1][3] * A.M[3][1],
                     
          M[1][0] * A.M[0][2] +
          M[1][1] * A.M[1][2] +
          M[1][2] * A.M[2][2] +
          M[1][3] * A.M[3][2],
                          
          M[1][0] * A.M[0][3] +
          M[1][1] * A.M[1][3] +
          M[1][2] * A.M[2][3] +
          M[1][3] * A.M[3][3],
                          
          M[2][0] * A.M[0][0] +
          M[2][1] * A.M[1][0] +
          M[2][2] * A.M[2][0] +
          M[2][3] * A.M[3][0],
                          
          M[2][0] * A.M[0][1] +
          M[2][1] * A.M[1][1] +
          M[2][2] * A.M[2][1] +
          M[2][3] * A.M[3][1],
                          
          M[2][0] * A.M[0][2] +
          M[2][1] * A.M[1][2] +
          M[2][2] * A.M[2][2] +
          M[2][3] * A.M[3][2],
                          
          M[2][0] * A.M[0][3] +
          M[2][1] * A.M[1][3] +
          M[2][2] * A.M[2][3] +
          M[2][3] * A.M[3][3],
                          
          M[3][0] * A.M[0][0] +
          M[3][1] * A.M[1][0] +
          M[3][2] * A.M[2][0] +
          M[3][3] * A.M[3][0],
                          
          M[3][0] * A.M[0][1] +
          M[3][1] * A.M[1][1] +
          M[3][2] * A.M[2][1] +
          M[3][3] * A.M[3][1], 
                          
          M[3][0] * A.M[0][2] +
          M[3][1] * A.M[1][2] +
          M[3][2] * A.M[2][2] +
          M[3][3] * A.M[3][2],
                          
          M[3][0] * A.M[0][3] +
          M[3][1] * A.M[1][3] +
          M[3][2] * A.M[2][3] +
          M[3][3] * A.M[3][3]);
      }/* End of 'operator*' function */

      /* Multiplication with assignment of two matrix function.
       * ARGUMENTS:
       *   - matrix to be multiply:
       *       const matr<type> &A;
       * RETURNS:
       *   (matr &) self reference.
       */
      matr operator*=( const matr<type> &A )
      {
        IsInverseObtain = FALSE;

        *this = matr(
          M[0][0] * A.M[0][0] +
          M[0][1] * A.M[1][0] +
          M[0][2] * A.M[2][0] +
          M[0][3] * A.M[3][0],
                          
          M[0][0] * A.M[0][1] +
          M[0][1] * A.M[1][1] +
          M[0][2] * A.M[2][1] +
          M[0][3] * A.M[3][1],
                          
          M[0][0] * A.M[0][2] +
          M[0][1] * A.M[1][2] +
          M[0][2] * A.M[2][2] +
          M[0][3] * A.M[3][2],
                          
          M[0][0] * A.M[0][3] +
          M[0][1] * A.M[1][3] +
          M[0][2] * A.M[2][3] +
          M[0][3] * A.M[3][3],
                          
          M[1][0] * A.M[0][0] +
          M[1][1] * A.M[1][0] +
          M[1][2] * A.M[2][0] +
          M[1][3] * A.M[3][0],
                          
          M[1][0] * A.M[0][1] +
          M[1][1] * A.M[1][1] +
          M[1][2] * A.M[2][1] +
          M[1][3] * A.M[3][1],
                     
          M[1][0] * A.M[0][2] +
          M[1][1] * A.M[1][2] +
          M[1][2] * A.M[2][2] +
          M[1][3] * A.M[3][2],
                          
          M[1][0] * A.M[0][3] +
          M[1][1] * A.M[1][3] +
          M[1][2] * A.M[2][3] +
          M[1][3] * A.M[3][3],
                          
          M[2][0] * A.M[0][0] +
          M[2][1] * A.M[1][0] +
          M[2][2] * A.M[2][0] +
          M[2][3] * A.M[3][0],
                          
          M[2][0] * A.M[0][1] +
          M[2][1] * A.M[1][1] +
          M[2][2] * A.M[2][1] +
          M[2][3] * A.M[3][1],
                          
          M[2][0] * A.M[0][2] +
          M[2][1] * A.M[1][2] +
          M[2][2] * A.M[2][2] +
          M[2][3] * A.M[3][2],
                          
          M[2][0] * A.M[0][3] +
          M[2][1] * A.M[1][3] +
          M[2][2] * A.M[2][3] +
          M[2][3] * A.M[3][3],
                          
          M[3][0] * A.M[0][0] +
          M[3][1] * A.M[1][0] +
          M[3][2] * A.M[2][0] +
          M[3][3] * A.M[3][0],
                          
          M[3][0] * A.M[0][1] +
          M[3][1] * A.M[1][1] +
          M[3][2] * A.M[2][1] +
          M[3][3] * A.M[3][1], 
                          
          M[3][0] * A.M[0][2] +
          M[3][1] * A.M[1][2] +
          M[3][2] * A.M[2][2] +
          M[3][3] * A.M[3][2],
                          
          M[3][0] * A.M[0][3] +
          M[3][1] * A.M[1][3] +
          M[3][2] * A.M[2][3] +
          M[3][3] * A.M[3][3]);

        return *this;
      }/* End of 'operator*=' function */

      /* Get identity matrix function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (matr) identity matrix.
       */
      static matr Identity( VOID )
      {
        return matr(
          1, 0, 0, 0,
          0, 1, 0, 0,
          0, 0, 1, 0,
          0, 0, 0, 1
        );
      } /* End of 'Identity' function */

      //Create translate matrix
      inline static matr<type> Translate( type Dx, type Dy, type Dz )
      {
        return matr<type>(1, 0, 0, 0,
                       0, 1, 0, 0,
                       0, 0, 1, 0,
                       Dx, Dy, Dz, 1);
      } /* End of 'Translate' function */

      //Create translate matrix from vec3
      inline static matr<type> Translate( vec3<type> V )
      {
        return matr<type>(1, 0, 0, 0,
                       0, 1, 0, 0,
                       0, 0, 1, 0,
                       V.X, V.Y, V.Z, 1);
      } /* End of 'Translate' function */

      /* Scale matrix function.
       * ARGUMENTS:
       *   - input vector:
       *       vec3 S;
       * RETURNS:
       *   (matr) scale matrix.
       */
      inline static matr<type> Scale( vec3<type> S )
      {
        return matr<type>(S.X, 0, 0, 0,
                          0, S.Y, 0, 0,
                          0, 0, S.Z, 0,
                          0, 0, 0, 1);
      } /* End of 'Scale' function */

      /* Scale matrix function.
       * ARGUMENTS:
       *   - input values:
       *       type Dx, Dy, Dz;
       * RETURNS:
       *   (matr) scale matrix.
       */
      inline static matr<type> Scale( type Dx, type Dy, type Dz )
      {
        return matr<type>(Dx, 0, 0, 0,
                       0, Dy, 0, 0,
                       0, 0, Dz, 0,
                       0, 0, 0, 1);
      } /* End of 'Scale' function */

      /* Rotation by X axis matrix function.
       * ARGUMENTS:
       *   - input angle in degree:
       *       type AngleInDegree;
       * RETURNS:
       *   (matr) RotateX matrix.
       */
      inline static matr RotateX( type AngleInDegree )
      {
        type si, co;

        AngleInDegree = D2R(AngleInDegree);
        si = sin(AngleInDegree), co = cos(AngleInDegree);

        return matr(1, 0, 0, 0,
                       0, co, si, 0,
                       0, -si, co, 0,
                       0, 0, 0, 1);
      } /* End of 'RotateX' function */

      /* Rotation by Y axis matrix function.
       * ARGUMENTS:
       *   - input angle in degree:
       *       type AngleInDegree;
       * RETURNS:
       *   (matr) RotateY matrix.
       */
      inline static matr RotateY( type AngleInDegree )
      {
        type si, co;

        AngleInDegree = D2R(AngleInDegree);
        si = sin(AngleInDegree), co = cos(AngleInDegree);

        return matr(co, 0, -si, 0,
                       0, 1, 0, 0,
                       si, 0, co, 0,
                       0, 0, 0, 1);
      } /* End of 'RotateY' function */

      /* Rotation by Z axis matrix function.
       * ARGUMENTS:
       *   - input angle in degree:
       *       type AngleInDegree;
       * RETURNS:
       *   (matr) RotateZ matrix.
       */
      inline static matr RotateZ( type AngleInDegree )
      {
        FLT si, co;

        AngleInDegree = D2R(AngleInDegree);
        si = sin(AngleInDegree), co = cos(AngleInDegree);

        return matr(co, si, 0, 0,
                       -si, co, 0, 0,
                       0, 0, 1, 0,
                       0, 0, 0, 1);
      } /* End of 'RotateZ' function */

      /* Rotation by input vector matrix function.
       * ARGUMENTS:
       *   - input angle in degree:
       *       type AngleInDegree;
       *   - input vector rotation above:
       *       vec3 R;
       * RETURNS:
       *   (MATR) Rotate matrix.
       */
      inline static matr Rotate( type AngleInDegree, vec3<type> R )
      {
        type
          A = D2R(AngleInDegree),
          si = sin(A), co = cos(A);
        vec3 V = R;
        //vec3 V = R.Normalizing();
        matr M(co + V.X * V.X * (1 - co), V.X * V.Y * (1 - co) + V.Z * si, V.X * V.Z * (1 - co) - V.Y * si, 0,
               V.Y * V.X * (1 - co) - V.Z * si, co + V.Y * V.Y * (1 - co), V.Y * V.Z * (1 - co) + V.X * si, 0,
               V.Z * V.X * (1 - co) + V.Y * si, V.Z * V.Y * (1 - co) - V.X * si, co + V.Z * V.Z * (1 - co), 0,
               0,                               0,                               0,                         1);

        return M;
      } /* End of 'Rotate' function */

      /* Create viewer matrix function.
      * ARGUMENTS:
      *   - camera location:
      *       vec3 Loc;
      *   - pivot point:
      *       vec3 At;
      *   - up direction:
      *       vec3 Up;
      * RETURNS:
      *   (matr) built view matrix.
      */
      static matr View( vec3<type> Loc, vec3<type> At, vec3<type> Up )
      {
        vec3 Dir = (At - Loc).Normalizing();
        vec3 Right = (Dir % Up).Normalizing();
        Up = Right % Dir;
        return matr(
          Right.X,          Up.X,          -Dir.X,          0,
          Right.Y,          Up.Y,          -Dir.Y,          0,
          Right.Z,          Up.Z,          -Dir.Z,          0,
          -(Loc & Right),  -(Loc & Up),     (Loc & Dir),    1
        );
      } /* End of 'View' function */

      /* Orthographics projection matrix setup function.
       * ARGUMENTS:
       *   - orthographic box side facets coordinates:
       *       type Left, Right, Bottom, Top, Near, Far;
       * RETURNS:
       *   (matr) result matrix.
       */
      inline static matr Ortho( type Left, type Right, type Bottom, type Top, type Near, type Far )
      {
        matr m =
        {
          {
            {2 / (Right - Left), 0, 0, 0},
            {0, 2 / (Top - Bottom), 0, 0},
            {0, 0, -2 / (Far - Near), 0},
            {-(Right + Left) / (Right - Left), -(Top + Bottom) / (Top - Bottom), -(Far + Near) / (Far - Near), 1}
          }
        };

        return m;
      } /* End of 'Ortho' function */

      /* Create frustum projection matrix function.
       * ARGUMENTS:
       *   - frustum bounds:
       *       type l, r, b, t, n, f;
       * RETURNS:
       *   (matr) built frustum matrix.
       */
      static matr Frustum( type l, type r, type b, type t, type n, type f )
      {
        return matr(
          (2 * n) / (r - l),   0,                   0,                      0,
          0,                   (2 * n) / (t - b),   0,                      0,
          (r + l) / (r - l),   (t + b) / (t - b),   -(f + n) / (f - n),    -1,
          0,                   0,                   -(2 * n * f) / (f - n), 0
        );
      } /* End of 'Frustum' function */

      /* Point transform by matrix.
       * ARGUMENTS:
       *   - input vector:
       *       vec3 &V;
       * RETURNS:
       *   (vec3) result vector.
       */
      inline vec3<type> TransformPoint( const vec3<type> &V ) const
      {
        return vec3<type>(V.X * M[0][0] + V.Y * M[1][0] + V.Z * M[2][0] + M[3][0],
                          V.X * M[0][1] + V.Y * M[1][1] + V.Z * M[2][1] + M[3][1],
                          V.X * M[0][2] + V.Y * M[1][2] + V.Z * M[2][2] + M[3][2]);
      } /* End of 'PointTransform' function */

      /* Vector transform by matrix function.
       * ARGUMENTS:
       *   - input vector:
       *       vec3 V;
       *   - input matrix:
       *       matr M;
       * RETURNS:
       *   (vec3) result vector.
       */
      inline vec3<type> TransformVector( const vec3<type> &V ) const
      {
        return vec3<type>(V.X * M[0][0] + V.Y * M[1][0] + V.Z * M[2][0],
                          V.X * M[0][1] + V.Y * M[1][1] + V.Z * M[2][1],
                          V.X * M[0][2] + V.Y * M[1][2] + V.Z * M[2][2]);
      } /* End of 'VectorTransform' function */

      //Transform vec3 point with inverse matrix
      inline vec3<type> InvTransformPoint( const vec3<type> &P ) const
      {
        EvaluateInverseMatrix();

        return vec3<type>(P.X * InverseM[0][0] + P.Y * InverseM[1][0] + P.Z * InverseM[2][0] + InverseM[3][0],
                          P.X * InverseM[0][1] + P.Y * InverseM[1][1] + P.Z * InverseM[2][1] + InverseM[3][1],
                          P.X * InverseM[0][2] + P.Y * InverseM[1][2] + P.Z * InverseM[2][2] + InverseM[3][2]);
      }/* End of 'InvTransformPoint' function */

      //
      inline type * operator[]( INT Row )
      {
        return M[Row];
      }

      //Transform vec3 vector with inverse matrix
      inline vec3<type> InvTransformVector( const vec3<type> &V ) const
      {
        EvaluateInverseMatrix();

        return vec3<type>(V.X * InverseM[0][0] + V.Y * InverseM[1][0] + V.Z * InverseM[2][0],
                          V.X * InverseM[0][1] + V.Y * InverseM[1][1] + V.Z * InverseM[2][1],
                          V.X * InverseM[0][2] + V.Y * InverseM[1][2] + V.Z * InverseM[2][2]);
      }/* End of 'InvTransformVector' function */

      //Transform vec3 normal with inverse matrix
      inline vec3<type> InvTransformNormal( const vec3<type> &N ) const
      {
        matr<type> Trans = matr<type>(Transpose());

        return vec3<type>(N.X * Trans.M[0][0] + N.Y * Trans.M[1][0] + N.Z * Trans.M[2][0],
                          N.X * Trans.M[0][1] + N.Y * Trans.M[1][1] + N.Z * Trans.M[2][1],
                          N.X * Trans.M[0][2] + N.Y * Trans.M[1][2] + N.Z * Trans.M[2][2]);
      }/* End of 'InvTransformNormal' function */

      //Transform vec3 normal with inverse matrix
      inline vec3<type> TransformNormal( const vec3<type> &N ) const
      {
        matr<type> TrInv = Inverse().Transpose();

        return vec3<type>(N.X * TrInv.M[0][0] + N.Y * TrInv.M[1][0] + N.Z * TrInv.M[2][0],
                          N.X * TrInv.M[0][1] + N.Y * TrInv.M[1][1] + N.Z * TrInv.M[2][1],
                          N.X * TrInv.M[0][2] + N.Y * TrInv.M[1][2] + N.Z * TrInv.M[2][2]);
      }/* End of 'TransformNormal' function */

    }; /* End of 'matr' class */
} /* end of 'mth' namespace */

#endif /* __mth_matr4x4_h_ */
/* END OF 'mth_matr.h' FILE */