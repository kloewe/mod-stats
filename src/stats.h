/*----------------------------------------------------------------------------
  File    : stats.h
  Contents: basic statistical functions (cpu dispatcher)
  Author  : Kristian Loewe
----------------------------------------------------------------------------*/
#ifndef STATS_H
#define STATS_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "dot.h"

/*----------------------------------------------------------------------------
  Preprocessor Definitions
----------------------------------------------------------------------------*/
#if defined(__x86_64) || defined(__x86_64__) || defined(__amd64) \
    || defined(__amd64__) || defined(_M_AMD64)  || defined(_M_X64)
#define ARCH_IS_X86_64
#endif

#ifdef REAL                     // if REAL is already defined, save its
#  include "real-is-double.inc" // original definition based on the value
#  if REAL_IS_DOUBLE
#    define dot     ddot
#    define sum     dsum
#    define mean    dmean
#    define var     dvar
#    define varm    dvarm
#    define var0    dvar0
#    define std     dstd
#    define tstat   dtstat
#    define tstat2  dtstat2
#    define welcht  dwelcht
#    define pairedt dpairedt
#    define didt    ddidt
#    define fr2z    dfr2z
#  else
#    define sqrt    sqrtf
#    define dot     sdot
#    define sum     ssum
#    define mean    smean
#    define var     svar
#    define varm    svarm
#    define var0    svar0
#    define std     sstd
#    define tstat   ststat
#    define tstat2  ststat2
#    define welcht  swelcht
#    define pairedt spairedt
#    define didt    sdidt
#    define fr2z    sfr2z
#  endif
#endif

#define R2Z_MAX 18.3684002848385504   // atanh(1-epsilon)

/*----------------------------------------------------------------------------
  Type Definitions: enum to encode the sets of implementations
----------------------------------------------------------------------------*/
typedef enum {
    STATS_NAIVE     = 1,   // plain C
    STATS_SSE2      = 2,   // SSE2
    STATS_AVX       = 3,   // AVX
    STATS_AVXFMA    = 4,   // AVX+FMA3
    STATS_AVX512    = 5,   // AVX512
    STATS_AVX512FMA = 6,   // AVX512+FMA3
    STATS_AUTO      = 100  // automatic choice
} stats_flags;
// Using stats_set_impl(), these values are used to specify the set of
// implementations to be used. The values/sets are ordered chronologically
// wrt the advent of the prerequisite instruction set extensions, with
// STATS_NAIVE representing the plain C fallback implementations, and
// STATS_AUTO indicating that the best set of implementations should be
// chosen automatically.

/*----------------------------------------------------------------------------
  Type Definitions: functions
----------------------------------------------------------------------------*/
typedef float  (ssum_func)     (const float  *a, int n);
typedef float  (svarm_func)    (const float  *a, int n, float  m);

typedef double (dsum_func)     (const double *a, int n);
typedef double (dvarm_func)    (const double *a, int n, double m);

typedef double (dssum_func)    (const float  *a, int n);
// ... TODO

/*----------------------------------------------------------------------------
  Global Variables: function pointers
----------------------------------------------------------------------------*/
extern ssum_func  *ssum_ptr;
extern svarm_func *svarm_ptr;

extern dsum_func  *dsum_ptr;
extern dvarm_func *dvarm_ptr;

extern dssum_func *dssum_ptr;
// ... TODO

/*----------------------------------------------------------------------------
  Type Definitions: structs
----------------------------------------------------------------------------*/
typedef struct stres {
  float t;
  float df;
} stres;

typedef struct dtres {
  double t;
  double df;
} dtres;

/*----------------------------------------------------------------------------
  Function Prototypes
----------------------------------------------------------------------------*/
// see also stats_real.h

inline double dssum    (const float  *a, int n);

/* stats_set_impl
 * ------------
 * specify the set of implementations that is used
 *
 * If the requested set of implementations is not supported, the function
 * will select the next best set of implementations that is supported.
 *
 * parameters
 * impl  indicates which set of implementations should be used
 *       STATS_NAIVE     -> plain C implementations
 *       STATS_SSE2      -> SSE2 implementations
 *       STATS_AVX       -> AVX implementations
 *       STATS_AVXFMA    -> AVX+FMA3 implementations
 *       STATS_AVX512    -> AVX512 implementations
 *       STATS_AVX512FMA -> AVX512+FMA3 implementations
 *       STATS_AUTO      -> automatically choose the best available set
 *       (see also the above enum)
 *
 * returns
 * the enum value corresponding to the selected set of implementations
 */
extern stats_flags stats_set_impl (stats_flags impl);


extern float  ssum_select  (const float  *a, int n);
extern float  svarm_select (const float  *a, int n, float m);

extern double dsum_select  (const double *a, int n);
extern double dvarm_select (const double *a, int n, double m);

extern double dssum_select (const float  *a, int n);
// ... TODO

extern float  ssum_naive   (const float  *a, int n);
extern float  svarm_naive  (const float  *a, int n, float m);

extern double dsum_naive   (const double *a, int n);
extern double dvarm_naive  (const double *a, int n, double m);

extern double dssum_naive  (const float  *a, int n);
// ... TODO

#ifdef ARCH_IS_X86_64
extern float  ssum_sse2    (const float  *a, int n);
extern float  svarm_sse2   (const float  *a, int n, float m);

extern double dsum_sse2    (const double *a, int n);
extern double dvarm_sse2   (const double *a, int n, double m);

// extern double dssum_sse2    (const float  *a, int n);
// ... TODO
#endif

/*----------------------------------------------------------------------------
  Inline Functions
----------------------------------------------------------------------------*/
#ifdef REAL                     // if REAL is already defined, save its
#  include "real-is-double.inc" // original definition based on the value
#  undef REAL                   // of REAL_IS_DOUBLE, then undefine it
#endif
/*--------------------------------------------------------------------------*/
#define REAL      float         // (re)define REAL to be float
#define sqrt      sqrtf
#define dot       sdot
#define tres      stres
#define sum_ptr   ssum_ptr
#define varm_ptr  svarm_ptr
#define sum       ssum
#define mean      smean
#define var       svar
#define varm      svarm
#define var0      svar0
#define std       sstd
#define tstat     ststat
#define tstat2    ststat2
#define welcht    swelcht
#define pairedt   spairedt
#define didt      sdidt
#define fr2z      sfr2z
#include "stats_real.h"         // single precision versions
#undef sqrt
#undef dot
#undef tres
#undef sum_ptr
#undef varm_ptr
#undef sum
#undef mean
#undef var
#undef varm
#undef var0
#undef std
#undef tstat
#undef tstat2
#undef welcht
#undef pairedt
#undef didt
#undef fr2z
#undef REAL
/*--------------------------------------------------------------------------*/
#undef STATS_REAL_H             // undef guard to include header a 2nd time
/*--------------------------------------------------------------------------*/
#define REAL      double        // (re)define REAL to be double
#define dot       ddot
#define tres      dtres
#define sum_ptr   dsum_ptr
#define varm_ptr  dvarm_ptr
#define sum       dsum
#define mean      dmean
#define var       dvar
#define varm      dvarm
#define var0      dvar0
#define std       dstd
#define tstat     dtstat
#define tstat2    dtstat2
#define welcht    dwelcht
#define pairedt   dpairedt
#define didt      ddidt
#define fr2z      dfr2z
#include "stats_real.h"         // double precision versions
#undef dot
#undef tres
#undef sum_ptr
#undef varm_ptr
#undef sum
#undef mean
#undef var
#undef varm
#undef var0
#undef std
#undef tstat
#undef tstat2
#undef welcht
#undef pairedt
#undef didt
#undef fr2z
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

inline double dssum (const float *a, int n) {
  return (*dssum_ptr)(a,n);
}  // dssum()

// ... TODO

#ifdef __cplusplus
}
#endif

#endif  // #ifndef STATS_H
