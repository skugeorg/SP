#ifndef __def_h_
#define __def_h_

#include <iostream>
#include <fstream>
#include <filesystem>
#include <format>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <vector>
#include <thread>
#include <atomic>
#include <string>
#include <chrono>
#include <map>

#include <windows.h>

#include "mth\mth.h"

#ifdef WIN32
#include <commondf.h>
#else /* WIN32 */
#define WIN32
#include <commondf.h>
#undef WIN32
#endif /* WIN32 */

using namespace std;

typedef double DBL;
typedef long long INT64;
typedef unsigned long long UINT64;

/* Debug memory allocation support */
#ifdef _DEBUG
#  define _CRTDBG_MAP_ALLOC
#  include <crtdbg.h>
#  define SetDbgMemHooks() \
  _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | \
  _CRTDBG_ALLOC_MEM_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))
static struct __Dummy
{
  /* Structure constructor */
  __Dummy( VOID )
  {
    SetDbgMemHooks();
  } /* End of '__Dummy' constructor */
} __oops;
#endif /* _DEBUG */

#ifdef _DEBUG
#  ifdef _CRTDBG_MAP_ALLOC
#    define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#  endif /* _CRTDBG_MAP_ALLOC */
#endif /* _DEBUG */

/* Stock declaration class */
template<typename T>
  class stock : public std::vector<T>
  {
  public:
    /* Push value in the stock.
     * ARGUMENTS:
     *   - value:
     *       const T &X;
     * RETURNS:
     *   (stock &) value stock reference.
     */
    stock & operator<<( const T &X )
    {
      this->push_back(X);
      return *this;
    }
    template<typename WalkType>
      void Walk( WalkType WalkFunc )
      {
        for (auto &x : *this)
          WalkFunc(x);
      }
  };

namespace gert
{
  using vec2 = mth::vec2<DBL>;
  using vec3 = mth::vec3<DBL>;
  using vec4 = mth::vec4<DBL>;
  using matr = mth::matr<DBL>;
  using ray = mth::ray<DBL>;
  using camera = mth::camera<DBL>;
}

#endif /* __def_h_ */
