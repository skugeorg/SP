/*************************************************************
 * Copyright (C) 2026
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : mth_vec2.h
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

#ifndef __mth_vec2_h_
#define __mth_vec2_h_

#include "mth_def.h"

namespace mth
{
  template<typename type>
    class vec2
    {
    public:
      type X, Y;

      //vec2 ctor
      vec2( type N ) : X(N), Y(N)
      {
      }/* End of 'vec2' ctor */

      //vec2 ctor
      vec2( VOID )
      {
      } /* End of 'vec2' ctor */

      //vec2 ctor
      vec2( type NewX, type NewY ) : X(NewX), Y(NewY)
      {
      } /* End of 'vec2' ctor */

      /* Class constructor.
       * ARGUMENTS:
       *   - other vector:
       *       const vec2<type> &V;
       */
      vec2( const vec2<type> &V ) : X(V.X), Y(V.Y)
      {
      } /* End of 'vec2' ctor */

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

      //operator & override (Vec2 Dot Vec2)
      inline type operator&( const vec2 &V ) const
      {
        return X * V.X + Y * V.Y;
      } /* End of 'VecDotVec' function */

      /* Obtain vector squared length function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (type) vector squared length.
       */
      type Length( VOID ) const
      {
        return sqrt(Length2());
      }/* End of 'Length2' function */

       /* Obtain vector squared length function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (type) vector squared length.
       */
      type Length2( VOID ) const
      {
        return *this & *this;
      }/* End of 'Length2' function */

      //operator ! override (Vec2 Len)
      inline type operator!( VOID ) const
      {
        return sqrt(Length2());
      } /* End of 'operator!' function */

      /* negative vector function.
       * ARGUMENTS:
       *   - vector to be add:
       *       const vec2 &V;
       * RETURNS:
       *   (vec2 &) self reference.
       */
      inline vec2 operator-( VOID ) const
      {
        return vec2(-X, -Y);
      } /* End of 'operator+=' function */

      /* Add vector function.
       * ARGUMENTS:
       *   - vector to be add:
       *       const vec2 &V;
       * RETURNS:
       *   (vec2 &) self reference.
       */
      inline vec2 & operator+=( const vec2 &V )
      {
        X += V.X;
        Y += V.Y;
        return *this;
      } /* End of 'operator+=' function */

      /* Substraction vector function.
       * ARGUMENTS:
       *   - vector to be sub:
       *       const vec2 &V;
       * RETURNS:
       *   (vec2 &) self reference.
       */
      inline vec2 & operator-=( const vec2 &V )
      {
        X -= V.X;
        Y -= V.Y;
        return *this;
      } /* End of 'operator+=' function */

      /* Multiply vector function.
       * ARGUMENTS:
       *   - vector to be mult:
       *       const vec2 &V;
       * RETURNS:
       *   (vec2 &) self reference.
       */
      inline vec2 & operator*=( const vec2 &V )
      {
        *this = *this * V;

        return *this;
      } /* End of 'operator*=' function */

      /* Multiply vector function.
       * ARGUMENTS:
       *   - nubmer to be mult:
       *       const type &N;
       * RETURNS:
       *   (vec2 &) self reference.
       */
      inline vec2 & operator*=( const type &N )
      {
        *this = *this * N;

        return *this;
      } /* End of 'operator*=' function */

      /* Division vector function.
       * ARGUMENTS:
       *   - vector to be div:
       *       const type &N;
       * RETURNS:
       *   (vec2 &) self reference.
       */
      inline vec2 & operator/=( const type &N )
      {
        *this = *this / N;

        return *this;
      } /* End of 'operator/=' function */

       /* Create Sum of vectors function.
       * ARGUMENTS:
       *   - vector to be add:
       *       const vec2 &V;
       * RETURNS:
       *   (vec2) new vector.
       */
      inline vec2 operator+( const vec2 &V ) const
      {
        return vec2(X + V.X, Y + V.Y);
      } /* End of 'operator+' function */

       /* Create substraction of vectors function.
       * ARGUMENTS:
       *   - vector to be substr:
       *       const vec2 &V;
       * RETURNS:
       *   (vec2) new vector.
       */
      inline vec2 operator-( const vec2 &V ) const
      {
        return vec2(X - V.X, Y - V.Y);
      } /* End of 'operator-' function */

      /* Create negative vector function.
       * ARGUMENTS:
       *   None;
       * RETURNS:
       *   (vec2) new vector.
       */
      inline vec2 operator-( INT ) const
      {
        return *this * type(-1);
      } /* End of 'operator-' function */

      /* Create division of vectors function.
       * ARGUMENTS:
       *   - number to division:
       *       const type &N;
       * RETURNS:
       *   (vec2) new vector.
       */
      inline vec2 operator/( const type &N ) const
      {
        return vec2(X / N, Y / N);
      } /* End of 'operator/' function */

      //operator * override (multiply by component)
      inline vec2 operator*( const vec2 &V ) const
      {
        return vec2(X * V.X, Y * V.Y);
      }/* End of 'operator*' function */

      //operator * override (multiply by component)
      inline vec2 operator*( const type &N ) const
      {
        return vec2(X * N, Y * N);
      }/* End of 'operator*' function */

      /* Normalize vector itself function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec2) self pointer.
       */
      inline vec2 & Normalize( VOID )
      {
        type len = *this & *this;
        if (len != 0 && len != 1)
        {
          len = sqrt(len);
          X /= len;
          Y /= len;
        }
        return *this;
      } /* End of 'Normalize' function */

      /* Normalizing vector itself function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec2) new vector.
       */
      inline vec2 & Normalizing( VOID ) const
      {
        vec2<type> NewV(*this);

        type len = *this & *this;
        if (len != 0 && len != 1)
          NewV /= sqrt(len);
        return *this;
      } /* End of 'Normalizing' function */

      /* Zero vector obtain function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec2) result zero vector.
       */
      inline static vec2 Zero( VOID )
      {
        return vec2(0);
      }

      /* Compare two vectors for equal values function.
       * ARGUMENTS:
       *   - vector to be compare:
       *       const vec2 &V;
       * RETURNS:
       *   (BOOL) result of comparision.
       */
      BOOL operator==( const vec2 &V ) const
      {
        if (X == V.X && Y == V.Y)
          return TRUE;
        return FALSE;
      }

      /* Compare two vectors for not equal values function.
       * ARGUMENTS:
       *   - vector to be compare:
       *       const vec2 &V;
       * RETURNS:
       *   (BOOL) result of comparision.
       */
      BOOL operator!=( const vec2 &V ) const
      {
        return !(*this == V);
      }

      /* Compare two vectors for less then values function.
       * ARGUMENTS:
       *   - vector to be compare:
       *       const vec2 &V;
       * RETURNS:
       *   (BOOL) result of comparision.
       */
      BOOL operator<( const vec2 &V ) const
      {
        return (X < V.X || (X == V.X && Y < V.Y) ? TRUE : FALSE);
      }

      /* Compare two vectors for great then values function.
       * ARGUMENTS:
       *   - vector to be compare:
       *       const vec2 &V;
       * RETURNS:
       *   (BOOL) result of comparision.
       */
      BOOL operator>( const vec2 &V ) const
      {
        return !(*this < V) && *this != V;
      }

      /* Compare two vectors for less or equal then values function.
       * ARGUMENTS:
       *   - vector to be compare:
       *       const vec2 &V;
       * RETURNS:
       *   (BOOL) result of comparision.
       */
      BOOL operator<=( const vec2 &V ) const
      {
        return !(*this > V);
      }

      /* Compare two vectors for great or equal then values function.
       * ARGUMENTS:
       *   - vector to be compare:
       *       const vec2 &V;
       * RETURNS:
       *   (BOOL) result of comparision.
       */
      BOOL operator>=( const vec2 &V ) const
      {
        return !(*this < V);
      }

      /* Random vector with 0..1 range coordinates obtain function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec2) result random vector.
       */
      inline static vec2 Rnd0( VOID )
      {
        return vec2(mth::Rnd0(), mth::Rnd0());
      } /* End of 'Rnd0' function */

      /* Random vector with -1..1 range coordinates obtain function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec2) result random vector.
       */
      inline static vec2 Rnd1( VOID )
      {
        return vec2(mth::Rnd1(), mth::Rnd1());
      } /* End of 'Rnd1' function */

      /* Get minimum of two vectors function.
       * ARGUMENTS:
       *   - vector to be compared:
       *       const vec2 &V;
       * RETURNS:
       *   (vec2) result of comparision.
       */
      inline vec2 Min( const vec2 &V ) const
      {
        return vec2(X < V.X ? X : V.X,
                    Y < V.Y ? Y : V.Y);
      } /* End of 'Min' function */

      /* Get maximum of two vectors function.
       * ARGUMENTS:
       *   - vector to be compared:
       *       const vec2 &V;
       * RETURNS:
       *   (vec2) result of comparision.
       */
      inline vec2 Max( const vec2 &V ) const
      {
        return vec2(X > V.X ? X : V.X,
                    Y > V.Y ? Y : V.Y);
      } /* End of 'Max' function */

      /* Get maximum of vector components function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (type) result of comparision.
       */
      inline type MaxC( VOID ) const
      {
        return (X > Y ? X : Y);
      } /* End of 'MaxC' function */

      /* Get minimum of vector components function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (type) result of comparision.
       */
      inline type MinC( VOID ) const
      {
        return (X < Y ? X : Y);
      } /* End of 'MinC' function */

      /* Get vec2 component by index.
       * ARGUMENTS:
       *   - number to be used to get component:
       *       const INT N;
       * RETURNS:
       *   (type) selected component.
       */
      inline type operator[]( const INT N ) const
      {
        return (N == 0 ? X : Y);
      }/* End of 'operator[]' function */

      //format function
      auto format( const vec2 &P, std::format_context &Ctx ) const
      {
        return std::format_to(Ctx.out(), "<{}, {}>", P.X, P.Y);
      } /* End of 'format' function */
    };
}

template<typename type>
  struct std::formatter<mth::vec2<type>>
  {
    constexpr auto parse( format_parse_context &Ctx )
    {
      auto it = Ctx.begin();
      while (it != Ctx.end() && *it != '}')
        ++it;
      return it;
    }
  };

#endif /* __mth_vec2_h_ */