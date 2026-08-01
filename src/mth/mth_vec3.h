/*************************************************************
 * Copyright (C) 2026
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : mth_vec3.h
 * PURPOSE     : Raytracing project.
 *               Mathematics library.
 *               Vectors handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2026.
 *               GS6.
 * LAST UPDATE : 27.07.2026.
 * NOTE        : Module namespace 'mth'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __mth_vec3_h_
#define __mth_vec3_h_

#include "mth_def.h"

namespace mth
{
  template<typename type>
    class vec3
    {
    private:
      //Matrix2x2 determination find function
      inline type MatrDeterm2x2( type A11, type A12,
                                 type A21, type A22) const
      {
        return A11 * A22 - A21 * A12;
      } /* End of 'MatrDeterm2x2' function */
    public:
      type X, Y, Z;

      //vec3 ctor
      vec3( type N ) : X(N), Y(N), Z(N)
      {
      }/* End of 'vec3' ctor */

      //vec3 ctor
      vec3( VOID )
      {
      } /* End of 'vec3' ctor */

      //vec3 ctor
      vec3( type NewX, type NewY, type NewZ ) : X(NewX), Y(NewY), Z(NewZ)
      {
      } /* End of 'vec3' ctor */

      /* Class constructor.
       * ARGUMENTS:
       *   - other vector:
       *       const vec3<type> &V;
       */
      vec3( const vec3<type> &V ) : X(V.X), Y(V.Y), Z(V.Z)
      {
      } /* End of 'vec3' ctor */

      /* Class constructor.
        * ARGUMENTS:
        *   - 2D vector:
        *       const vec2<vtype> &V;
        */
      vec3( const vec2<type> &V, type C = 0 ) : X(V.X), Y(V.Y), Z(C)
      {
      }/* End of 'vec3' function */

      /* Obtain vector first element pointer function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (type *) pointer to X coordinate.
       */
      inline operator type *( VOID )
      {
        return &X;
      } /* End of 'operator type *' function */

      /* Obtain vector first element pointer function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (const type *) pointer to X coordinate.
       */
      inline operator const type *( VOID ) const
      {
        return &X;
      }/* End of 'operator type const *' function */

      //operator & override (Vec3 Dot Vec3)
      inline type operator&( const vec3 &V ) const
      {
        return X * V.X + Y * V.Y + Z * V.Z;
      } /* End of 'VecDotVec' function */

      /* Obtain vector squared length function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (type) vector squared length.
       */
      type Length( VOID ) const
      {
        return sqrt(*this & *this);
      } /* End of 'Length' function */

       /* Obtain vector squared length function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (type) vector squared length.
       */
      inline type Length2( VOID ) const
      {
        return *this & *this;
      } /* End of 'Length2' function */

      //operator ! override (Vec3 Len)
      inline vec3 operator!( VOID ) const
      {
        return sqrt(Length2);
      } /* End of 'operator!' function */

      inline type Distance( const vec3 &V ) const
      {
        return vec3(X - V.X, Y - V.Y, Z - V.Z).Length();
      }

      /* Add vector function.
       * ARGUMENTS:
       *   - vector to be add:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3 &) self reference.
       */
      inline vec3 & operator+=( const vec3 &V )
      {
        X += V.X;
        Y += V.Y;
        Z += V.Z;
        return *this;
      } /* End of 'operator+=' function */

      /* Substraction vector function.
       * ARGUMENTS:
       *   - vector to be sub:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3 &) self reference.
       */
      inline vec3 & operator-=( const vec3 &V )
      {
        X -= V.X;
        Y -= V.Y;
        Z -= V.Z;
        return *this;
      } /* End of 'operator+=' function */

      /* Multiply vector function.
       * ARGUMENTS:
       *   - vector to be mult:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3 &) self reference.
       */
      inline vec3 & operator*=( const vec3 &V )
      {
        *this = *this * V;

        return *this;
      } /* End of 'operator*=' function */

      /* Multiply vector function.
       * ARGUMENTS:
       *   - nubmer to be mult:
       *       const type &N;
       * RETURNS:
       *   (vec3 &) self reference.
       */
      inline vec3 & operator*=( const type &N )
      {
        *this = *this * N;

        return *this;
      } /* End of 'operator*=' function */

      /* Division vector function.
       * ARGUMENTS:
       *   - vector to be div:
       *       const type &N;
       * RETURNS:
       *   (vec3 &) self reference.
       */
      inline vec3 & operator/=( const type &N )
      {
        *this = *this / N;

        return *this;
      } /* End of 'operator/=' function */

       /* Create Sum of vectors function.
       * ARGUMENTS:
       *   - vector to be add:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3) new vector.
       */
      inline vec3 operator+( const vec3 &V ) const
      {
        return vec3(X + V.X, Y + V.Y, Z + V.Z);
      } /* End of 'operator+' function */

       /* Create Sum of vectors function.
       * ARGUMENTS:
       *   - Scalar to be add:
       *       const type &N;
       * RETURNS:
       *   (vec3) new vector.
       */
      inline vec3 operator+( const type &N ) const
      {
        return vec3(X + N, Y + N, Z + N);
      } /* End of 'operator+' function */

       /* Create substraction of vectors function.
       * ARGUMENTS:
       *   - vector to be substr:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3) new vector.
       */
      inline vec3 operator-( const vec3 &V ) const
      {
        return vec3(X - V.X, Y - V.Y, Z - V.Z);
      } /* End of 'operator-' function */

      /* Substraction scalar from vector function.
       * ARGUMENTS:
       *   - vector to be sub:
       *       const type &N;
       * RETURNS:
       *   (vec3) new vector.
       */
      inline vec3 operator-( const type &N ) const
      {
        return *this + -N;
      } /* End of 'operator+=' function */

      /* Create negative vector function.
       * ARGUMENTS:
       *   None;
       * RETURNS:
       *   (vec3) new vector.
       */
      inline vec3 operator-( VOID ) const
      {
        return *this * -1;
      } /* End of 'operator-' function */

      /* Create division of vectors function.
       * ARGUMENTS:
       *   - number to division:
       *       const type &N;
       * RETURNS:
       *   (vec3) new vector.
       */
      inline vec3 operator/( const type &N ) const
      {
        return vec3(X / N, Y / N, Z / N);
      } /* End of 'operator/' function */

      //operator * override (multiply by component)
      inline vec3 operator*( const vec3 &V ) const
      {
        return vec3(X * V.X, Y * V.Y, Z * V.Z);
      }/* End of 'operator*' function */

      //operator * override (multiply by component)
      inline vec3 operator*( const type &N ) const
      {
        return vec3(X * N, Y * N, Z * N);
      }/* End of 'operator*' function */

      //operator % override (Vec Cross Vec)
      inline vec3 operator%( const vec3 &V ) const
      {
        return vec3(MatrDeterm2x2(Y, Z,
                                V.Y, V.Z),
                  -(MatrDeterm2x2(X, Z,
                                V.X, V.Z)),
                  MatrDeterm2x2(X, Y,
                                V.X, V.Y));
      }/* End of 'operator%' function */

      //operator %= override (Vec Cross Vec)
      inline vec3 & operator%=( const vec3 &V )
      {
        return *this = vec3(MatrDeterm2x2(Y, Z,
                                V.Y, V.Z),
                  -(MatrDeterm2x2(X, Z,
                                V.X, V.Z)),
                  MatrDeterm2x2(X, Y,
                                V.X, V.Y));
      }/* End of 'operator%=' function */

      /* Ceate normalize vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3) self pointer.
       */
      inline vec3 & Normalize( VOID )
      {
        type len = *this & *this;
        if (len != 0 && len != 1)
        {
          len = sqrt(len);
          X /= len;
          Y /= len;
          Z /= len;
        }
        return *this;
      } /* End of 'Normalize' function */

      /* Normalizing vector itself function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3) new vector.
       */
      inline const vec3 Normalizing( VOID ) const
      {
        vec3<type> NewV(*this);

        type len = *this & *this;
        if (len != 0 && len != 1)
          NewV /= sqrt(len);
        return NewV;
      } /* End of 'Normalizing' function */

      /* Zero vector obtain function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3) result zero vector.
       */
      inline static vec3 Zero( VOID )
      {
        return vec3(0);
      }

      /* Compare two vectors for equal values function.
       * ARGUMENTS:
       *   - vector to be compare:
       *       const vec3 &V;
       * RETURNS:
       *   (BOOL) result of comparision.
       */
      template<typename vtype>
        BOOL operator==( const vec3<vtype> &V ) const
        {
          if (X == V.X && Y == V.Y && Z == V.Z)
            return TRUE;
          return FALSE;
        }

      /* Compare two vectors for not equal values function.
       * ARGUMENTS:
       *   - vector to be compare:
       *       const vec3 &V;
       * RETURNS:
       *   (BOOL) result of comparision.
       */
      template<typename vtype>
        BOOL operator!=( const vec3<vtype> &V ) const
        {
          return !(*this == V);
        }

      /* Compare two vectors for less then values function.
       * ARGUMENTS:
       *   - vector to be compare:
       *       const vec3 &V;
       * RETURNS:
       *   (BOOL) result of comparision.
       */
      template<typename vtype>
        BOOL operator<( const vec3<vtype> &V ) const
        {
          return (X < V.X || (X == V.X && Y < V.Y) || (X == V.X && Y == V.Y && Z < V.Z) ? TRUE : FALSE);
        }/* End of 'operator<' function */

      /* Compare two vectors for great then values function.
       * ARGUMENTS:
       *   - vector to be compare:
       *       const vec3 &V;
       * RETURNS:
       *   (BOOL) result of comparision.
       */
      template<typename vtype>
        BOOL operator>( const vec3<vtype> &V ) const
        {
          return !(*this < V) && (*this != V);
        }/* End of 'operator>' function */

      /* Compare two vectors for less or equal then values function.
       * ARGUMENTS:
       *   - vector to be compare:
       *       const vec3 &V;
       * RETURNS:
       *   (BOOL) result of comparision.
       */
      BOOL operator<=( const vec3 &V ) const
      {
        return !(*this > V);
      }

      /* Compare two vectors for great or equal then values function.
       * ARGUMENTS:
       *   - vector to be compare:
       *       const vec3 &V;
       * RETURNS:
       *   (BOOL) result of comparision.
       */
      BOOL operator>=( const vec3 &V ) const
      {
        return !(*this < V);
      }

      /* Random vector with 0..1 range coordinates obtain function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3) result random vector.
       */
      inline static vec3 Rnd0( VOID )
      {
        return vec3(mth::Rnd0(), mth::Rnd0(), mth::Rnd0());
      } /* End of 'Rnd0' function */

      /* Random vector with -1..1 range coordinates obtain function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3) result random vector.
       */
      inline static vec3 Rnd1( VOID )
      {
        return vec3(mth::Rnd1(), mth::Rnd1(), mth::Rnd1());
      } /* End of 'Rnd1' function */

      /* Get minimum of two vectors function.
       * ARGUMENTS:
       *   - vector to be compared:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3) result of comparision.
       */
      inline vec3 Min( const vec3 &V ) const
      {
        return vec3(X < V.X ? X : V.X,
                    Y < V.Y ? Y : V.Y,
                    Z < V.Z ? Z : V.Z);
      } /* End of 'Min' function */

      /* Get maximum of two vectors function.
       * ARGUMENTS:
       *   - vector to be compared:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3) result of comparision.
       */
      inline vec3 Max( const vec3 &V ) const
      {
        return vec3(X > V.X ? X : V.X,
                    Y > V.Y ? Y : V.Y,
                    Z > V.Z ? Z : V.Z);
      } /* End of 

      /* Get maximum of vector components function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (type) result of comparision.
       */
      inline type MaxC( VOID ) const
      {
        return (X > Y && X > Z ? X : (Y > Z ? Y : Z));
      } /* End of 'MaxC' function */

      /* Get minimum of vector components function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (type) result of comparision.
       */
      inline type MinC( VOID ) const
      {
        return (X < Y && X < Z ? X : (Y < Z ? Y : Z));
      } /* End of 'MinC' function */

      /* Get vec3 component by index.
       * ARGUMENTS:
       *   - number to be used to get component:
       *       const INT N;
       * RETURNS:
       *   (type) selected component.
       */
      inline type operator[]( const INT N ) const
      {
        return (N == 0 ? X : (N == 1 ? Y : Z));
      }/* End of 'operator[]' function */
    };
};

template<typename type>
  struct std::formatter<mth::vec3<type>>
  {
    constexpr auto parse( format_parse_context &Ctx )
    {
      auto it = Ctx.begin();
      while (it != Ctx.end() && *it != '}')
        ++it;
      return it;
    }

    //format function
    auto format( const mth::vec3<type> &P, std::format_context &Ctx ) const
    {
      return std::format_to(Ctx.out(), "<{}, {}, {}>", P.X, P.Y, P.Z);
    } /* End of 'format' function */
  };

#endif /* __mth_vec3_h_ */