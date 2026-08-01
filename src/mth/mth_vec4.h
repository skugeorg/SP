/*************************************************************
 * Copyright (C) 2026
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : mth_vec4.h
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

#ifndef __mth_vec4_h_
#define __mth_vec4_h_

#include "mth_def.h"

namespace mth
{
  template<typename type>
    class vec4
    {
    public:
      type X, Y, Z, W;

      //vec4 ctor
      vec4( type N ) : X(N), Y(N), Z(N), W(N)
      {
      }/* End of 'vec4' ctor */

      //vec4 ctor
      vec4( VOID )
      {
      } /* End of 'vec4' ctor */

      //vec4 ctor
      vec4( type NewX, type NewY, type NewZ, type NewW ) : X(NewX), Y(NewY), Z(NewZ), W(NewW)
      {
      } /* End of 'vec4' ctor */

      /* Class constructor.
       * ARGUMENTS:
       *   - other vector:
       *       const vec4<type> &V;
       */
      vec4( const vec4<type> &V ) : X(V.X), Y(V.Y), Z(V.Z), W(V.W)
      {
      } /* End of 'vec4' ctor */

      /* Class constructor.
        * ARGUMENTS:
        *   - 2D vector:
        *       const vec2<vtype> &V;
        */
      vec4( const vec3<type> &V, type C = 0 ) : X(V.X), Y(V.Y), Z(V.Z), W(C)
      {
      }/* End of 'vec4' function */

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

      //operator & override (vec4 Dot vec4)
      inline type operator&( const vec4 &V ) const
      {
        return X * V.X + Y * V.Y + Z * V.Z + W * V.W;
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
      type Length2( VOID ) const
      {
        return *this & *this;
      } /* End of 'Length2' function */

      //operator ! override (vec4 Len)
      inline vec4 operator!( VOID ) const
      {
        return sqrt(Length2);
      } /* End of 'operator!' function */

      /* Add vector function.
       * ARGUMENTS:
       *   - vector to be add:
       *       const vec4 &V;
       * RETURNS:
       *   (vec4 &) self reference.
       */
      inline vec4 & operator+=( const vec4 &V )
      {
        X += V.X;
        Y += V.Y;
        Z += V.Z;
        W += V.W;
        return *this;
      } /* End of 'operator+=' function */

      /* Substraction vector function.
       * ARGUMENTS:
       *   - vector to be sub:
       *       const vec4 &V;
       * RETURNS:
       *   (vec4 &) self reference.
       */
      inline vec4 & operator-=( const vec4 &V )
      {
        X -= V.X;
        Y -= V.Y;
        Z -= V.Z;
        W -= V.W;
        return *this;
      } /* End of 'operator+=' function */

      /* Multiply vector function.
       * ARGUMENTS:
       *   - vector to be mult:
       *       const vec4 &V;
       * RETURNS:
       *   (vec4 &) self reference.
       */
      inline vec4 & operator*=( const vec4 &V )
      {
        *this = *this * V;

        return *this;
      } /* End of 'operator*=' function */

      /* Multiply vector function.
       * ARGUMENTS:
       *   - nubmer to be mult:
       *       const type &N;
       * RETURNS:
       *   (vec4 &) self reference.
       */
      inline vec4 & operator*=( const type &N )
      {
        *this = *this * N;

        return *this;
      } /* End of 'operator*=' function */

      /* Division vector function.
       * ARGUMENTS:
       *   - vector to be div:
       *       const type &N;
       * RETURNS:
       *   (vec4 &) self reference.
       */
      inline vec4 & operator/=( const type &N )
      {
        *this = *this / N;

        return *this;
      } /* End of 'operator/=' function */

       /* Create Sum of vectors function.
       * ARGUMENTS:
       *   - vector to be add:
       *       const vec4 &V;
       * RETURNS:
       *   (vec4) new vector.
       */
      inline vec4 operator+( const vec4 &V ) const
      {
        return vec4(X + V.X, Y + V.Y, Z + V.Z, W + V.W);
      } /* End of 'operator+' function */

       /* Create Sum of vectors function.
       * ARGUMENTS:
       *   - Scalar to be add:
       *       const type &N;
       * RETURNS:
       *   (vec4) new vector.
       */
      inline vec4 operator+( const type &N ) const
      {
        return vec4(X + N, Y + N, Z + N, W + N);
      } /* End of 'operator+' function */

       /* Create substraction of vectors function.
       * ARGUMENTS:
       *   - vector to be substr:
       *       const vec4 &V;
       * RETURNS:
       *   (vec4) new vector.
       */
      inline vec4 operator-( const vec4 &V ) const
      {
        return vec4(X - V.X, Y - V.Y, Z - V.Z, W - V.W);
      } /* End of 'operator-' function */

      /* Substraction scalar from vector function.
       * ARGUMENTS:
       *   - vector to be sub:
       *       const type &N;
       * RETURNS:
       *   (vec4) new vector.
       */
      inline vec4 operator-( const type &N ) const
      {
        return *this + -N;
      } /* End of 'operator+=' function */

      /* Create negative vector function.
       * ARGUMENTS:
       *   None;
       * RETURNS:
       *   (vec4) new vector.
       */
      inline vec4 operator-( VOID ) const
      {
        return *this * -1;
      } /* End of 'operator-' function */

      /* Create division of vectors function.
       * ARGUMENTS:
       *   - number to division:
       *       const type &N;
       * RETURNS:
       *   (vec4) new vector.
       */
      inline vec4 operator/( const type &N ) const
      {
        return vec4(X / N, Y / N, Z / N, W / N);
      } /* End of 'operator/' function */

      //operator * override (multiply by component)
      inline vec4 operator*( const vec4 &V ) const
      {
        return vec4(X * V.X, Y * V.Y, Z * V.Z, W * V.W);
      }/* End of 'operator*' function */

      //operator * override (multiply by component)
      inline vec4 operator*( const type &N ) const
      {
        return vec4(X * N, Y * N, Z * N, W * N);
      }/* End of 'operator*' function */

      /* Ceate normalize vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec4) self pointer.
       */
      inline vec4 & Normalize( VOID )
      {
        type len = *this & *this;
        if (len != 0 && len != 1)
        {
          len = sqrt(len);
          X /= len;
          Y /= len;
          Z /= len;
          W /= len;
        }
        return *this;
      } /* End of 'Normalize' function */

      /* Normalizing vector itself function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec4) new vector.
       */
      inline vec4 & Normalizing( VOID ) const
      {
        vec4<type> NewV(*this);

        type len = *this & *this;
        if (len != 0 && len != 1)
          NewV /= sqrt(len);
        return *this;
      } /* End of 'Normalizing' function */

      /* Zero vector obtain function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec4) result zero vector.
       */
      inline static vec4 Zero( VOID )
      {
        return vec4(0);
      }

      /* Compare two vectors for equal values function.
       * ARGUMENTS:
       *   - vector to be compare:
       *       const vec4 &V;
       * RETURNS:
       *   (BOOL) result of comparision.
       */
      template<typename vtype>
        BOOL operator==( const vec4<vtype> &V ) const
        {
          if (X == V.X && Y == V.Y && Z == V.Z && W == V.W)
            return TRUE;
          return FALSE;
        }

      /* Compare two vectors for not equal values function.
       * ARGUMENTS:
       *   - vector to be compare:
       *       const vec4 &V;
       * RETURNS:
       *   (BOOL) result of comparision.
       */
      template<typename vtype>
        BOOL operator!=( const vec4<vtype> &V ) const
        {
          return !(*this == V);
        }

      /* Compare two vectors for less then values function.
       * ARGUMENTS:
       *   - vector to be compare:
       *       const vec4 &V;
       * RETURNS:
       *   (BOOL) result of comparision.
       */
      template<typename vtype>
        BOOL operator<( const vec4<vtype> &V ) const
        {
          return X < V.X || (X == V.X && Y < V.Y) || (X == V.X && Y == V.Y && Z < V.Z) || (X == V.X && Y == V.Y && Z == V.Z && W < V.W);
        }

      /* Compare two vectors for great then values function.
       * ARGUMENTS:
       *   - vector to be compare:
       *       const vec4 &V;
       * RETURNS:
       *   (BOOL) result of comparision.
       */
      template<typename vtype>
        BOOL operator>( const vec4<vtype> &V ) const
        {
          return !(*this < V) && *this != V;
        }

      /* Compare two vectors for less or equal then values function.
       * ARGUMENTS:
       *   - vector to be compare:
       *       const vec4 &V;
       * RETURNS:
       *   (BOOL) result of comparision.
       */
      template<typename vtype>
        BOOL operator<=( const vec4<vtype> &V ) const
        {
          return !(*this > V);
        }

      /* Compare two vectors for great or equal then values function.
       * ARGUMENTS:
       *   - vector to be compare:
       *       const vec4 &V;
       * RETURNS:
       *   (BOOL) result of comparision.
       */
      template<typename vtype>
        BOOL operator>=( const vec4<vtype> &V ) const
        {
          return !(*this < V);
        }

      /* Random vector with 0..1 range coordinates obtain function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec4) result random vector.
       */
      inline static vec4 Rnd0( VOID )
      {
        return vec4(mth::Rnd0(), mth::Rnd0(), mth::Rnd0(), mth::Rnd0());
      } /* End of 'Rnd0' function */

      /* Random vector with -1..1 range coordinates obtain function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec4) result random vector.
       */
      inline static vec4 Rnd1( VOID )
      {
        return vec4(mth::Rnd1(), mth::Rnd1(), mth::Rnd1(), mth::Rnd1());
      } /* End of 'Rnd1' function */

      /* Get minimum of two vectors function.
       * ARGUMENTS:
       *   - vector to be compared:
       *       const vec4 &V;
       * RETURNS:
       *   (vec4) result of comparision.
       */
      inline vec4 Min( const vec4 &V ) const
      {
        return vec4(X < V.X ? X : V.X,
                    Y < V.Y ? Y : V.Y,
                    Z < V.Z ? Z : V.Z,
                    W < V.W ? W : V.W);
      } /* End of 'Min' function */

      /* Get maximum of two vectors function.
       * ARGUMENTS:
       *   - vector to be compared:
       *       const vec4 &V;
       * RETURNS:
       *   (vec4) result of comparision.
       */
      inline vec4 Max( const vec4 &V ) const
      {
        return vec4(X > V.X ? X : V.X,
                    Y > V.Y ? Y : V.Y,
                    Z > V.Z ? Z : V.Z,
                    W > V.W ? W : V.W);
      } /* End of 

      /* Get maximum of vector components function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (type) result of comparision.
       */
      inline type MaxC( VOID ) const
      {
        return (X > Y && X > Z && X > W ? X : (Y > Z && Y > W ? Y : (Z > W ? Z : W)));
      } /* End of 'MaxC' function */

      /* Get minimum of vector components function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (type) result of comparision.
       */
      inline type MinC( VOID ) const
      {
        return (X < Y && X < Z && X < W ? X : (Y < Z && Y < W ? Y : (Z < W ? Z : W)));
      } /* End of 'MinC' function */

      /* Get vec4 component by index.
       * ARGUMENTS:
       *   - number to be used to get component:
       *       const INT N;
       * RETURNS:
       *   (type) selected component.
       */
      inline type operator[]( const INT N ) const
      {
        return (N == 0 ? X : (N == 1 ? Y : (N == 2 ? Z : W)));
      }/* End of 'operator[]' function */
    };
};

template<typename type>
  struct std::formatter<mth::vec4<type>>
  {
    constexpr auto parse( format_parse_context &Ctx )
    {
      auto it = Ctx.begin();
      while (it != Ctx.end() && *it != '}')
        ++it;
      return it;
    }

    //format function
    auto format( const mth::vec4<type> &P, std::format_context &Ctx ) const
    {
      return std::format_to(Ctx.out(), "<{}, {}, {}, {}>", P.X, P.Y, P.Z, P.W);
    } /* End of 'format' function */
  };

#endif /* __mth_vec4_h_ */