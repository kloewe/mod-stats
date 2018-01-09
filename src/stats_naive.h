/*----------------------------------------------------------------------------
  File    : stats_naive.h
  Contents: basic statistical functions (naive implementations)
  Authors : Kristian Loewe
----------------------------------------------------------------------------*/
#ifndef STATS_NAIVE_H
#define STATS_NAIVE_H

#include <math.h>
#include "dot_naive.h"

/*----------------------------------------------------------------------------
  Preprocessor Definitions
----------------------------------------------------------------------------*/
#ifndef R2Z_MAX
#define R2Z_MAX 18.3684002848385504   // atanh(1-epsilon)
#endif

/*----------------------------------------------------------------------------
  Function Prototypes
----------------------------------------------------------------------------*/
inline float  ssum_naive     (const float  *a, int n);
inline float  smean_naive    (const float  *a, int n);
inline float  svar_naive     (const float  *a, int n);
inline float  svarm_naive    (const float  *a, int n, float  m);
inline float  svar0_naive    (const float  *a, int n);
inline float  sstd_naive     (const float  *a, int n);
inline float  ststat2_naive  (const float  *x1, const float  *x2, int n1,
                              int n2);
inline float  sfr2z_naive    (float  r);

inline double dsum_naive     (const double *a, int n);
inline double dmean_naive    (const double *a, int n);
inline double dvar_naive     (const double *a, int n);
inline double dvarm_naive    (const double *a, int n, double m);
inline double dvar0_naive    (const double *a, int n);
inline double dstd_naive     (const double *a, int n);
inline double dtstat2_naive  (const double *x1, const double *x2, int n1,
                              int n2);
inline double dfr2z_naive    (double r);

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

// --- statistical functions (single precision)
#define REAL float              // (re)define REAL to be float
#define dot_naive    sdot_naive
#define sqrt         sqrtf
#define sum_naive    ssum_naive
#define mean_naive   smean_naive
#define var_naive    svar_naive
#define varm_naive   svarm_naive
#define var0_naive   svar0_naive
#define std_naive    sstd_naive
#define tstat2_naive ststat2_naive
#define fr2z_naive   sfr2z_naive
#include "stats_naive_real.h"
#undef dot_naive
#undef sqrt
#undef sum_naive
#undef mean_naive
#undef var_naive
#undef varm_naive
#undef var0_naive
#undef std_naive
#undef tstat2_naive
#undef fr2z_naive
#undef REAL

/*--------------------------------------------------------------------------*/
#undef STATS_NAIVE_REAL_H       // undef guard to include header a 2nd time
/*--------------------------------------------------------------------------*/

// --- statistical functions (double precision)
#define REAL double             // (re)define REAL to be double
#define dot_naive    ddot_naive
#define sum_naive    dsum_naive
#define mean_naive   dmean_naive
#define var_naive    dvar_naive
#define varm_naive   dvarm_naive
#define var0_naive   dvar0_naive
#define std_naive    dstd_naive
#define tstat2_naive dtstat2_naive
#define fr2z_naive   dfr2z_naive
#include "stats_naive_real.h"
#undef dot_naive
#undef sum_naive
#undef mean_naive
#undef var_naive
#undef varm_naive
#undef var0_naive
#undef std_naive
#undef tstat2_naive
#undef fr2z_naive
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

// --- sum (input: single; summation and output: double)
inline double dssum_naive (const float *a, int n)
{
  double s = 0;
  for (int k = 0; k < n; k++)
    s += a[k];
  return s;
}  // dssum_naive()

#endif  // #ifndef STATS_NAIVE_H
