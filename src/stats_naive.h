/*----------------------------------------------------------------------------
  File    : stats_naive.h
  Contents: basic statistical functions (naive implementations)
  Authors : Kristian Loewe
----------------------------------------------------------------------------*/
#ifndef STATS_NAIVE_H
#define STATS_NAIVE_H

#include <math.h>

/*----------------------------------------------------------------------------
  Preprocessor Definitions
----------------------------------------------------------------------------*/
#ifndef R2Z_MAX
#define R2Z_MAX 18.3684002848385504   // atanh(1-epsilon)
#endif

/*----------------------------------------------------------------------------
  Function Prototypes
----------------------------------------------------------------------------*/
// see also stats_naive_real.h

inline double dssum_naive    (const float  *a, int n);
// ... TODO

/*----------------------------------------------------------------------------
  Inline Functions
----------------------------------------------------------------------------*/
#ifdef REAL                     // if REAL is already defined, save its
#  include "real-is-double.inc" // original definition based on the value
#  undef REAL                   // of REAL_IS_DOUBLE, then undefine it
#endif
/*--------------------------------------------------------------------------*/
#define REAL float              // (re)define REAL to be float
#define sqrt          sqrtf
#define sum_naive     ssum_naive
#define varm_naive    svarm_naive
#include "stats_naive_real.h"   // single precision versions
#undef sqrt
#undef sum_naive
#undef varm_naive
#undef REAL
/*--------------------------------------------------------------------------*/
#undef STATS_NAIVE_REAL_H       // undef guard to include header a 2nd time
/*--------------------------------------------------------------------------*/
#define REAL double             // (re)define REAL to be double
#define sum_naive     dsum_naive
#define varm_naive    dvarm_naive
#include "stats_naive_real.h"   // double precision versions
#undef sum_naive
#undef varm_naive
#undef REAL
/*--------------------------------------------------------------------------*/
#undef REAL                     // restore original definition of REAL
#ifdef REAL_IS_DOUBLE           // (if necessary)
#  if REAL_IS_DOUBLE
#    define REAL double
#  else
#    define REAL float
#  endif
#endif
/*--------------------------------------------------------------------------*/

inline double dssum_naive (const float *a, int n)
{
  double s = 0;
  for (int k = 0; k < n; k++)
    s += a[k];
  return s;
}  // dssum_naive()

#endif  // #ifndef STATS_NAIVE_H
