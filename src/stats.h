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

#include <math.h>

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
#    define tstat2  dtstat2
#    define welcht  dwelcht
#    define pairedt dpairedt
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
#    define tstat2  ststat2
#    define welcht  swelcht
#    define pairedt spairedt
#    define fr2z    sfr2z
#  endif
#endif

#define R2Z_MAX 18.3684002848385504   // atanh(1-epsilon)

/*----------------------------------------------------------------------------
  Enum to encode the sets of implementations
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
  Type Definitions
----------------------------------------------------------------------------*/
typedef float  (ssum_func)     (const float  *a, int n);
typedef float  (smean_func)    (const float  *a, int n);
typedef float  (svar_func)     (const float  *a, int n);
typedef float  (svarm_func)    (const float  *a, int n, float  m);
typedef float  (svar0_func)    (const float  *a, int n);
typedef float  (sstd_func)     (const float  *a, int n);
typedef float  (ststat2_func)  (const float  *x1, const float  *x2, int n1,
                                int n2);
typedef float  (swelcht_func)  (const float  *x1, const float  *x2, int n1,
                                int n2);
typedef float  (spairedt_func) (const float  *x1, const float  *x2, int n);
typedef float  (sfr2z_func)    (const float  r);

typedef double (dsum_func)     (const double *a, int n);
typedef double (dmean_func)    (const double *a, int n);
typedef double (dvar_func)     (const double *a, int n);
typedef double (dvarm_func)    (const double *a, int n, double m);
typedef double (dvar0_func)    (const double *a, int n);
typedef double (dstd_func)     (const double *a, int n);
typedef double (dtstat2_func)  (const double *x1, const double *x2, int n1,
                                int n2);
typedef double (dwelcht_func)  (const double *x1, const double *x2, int n1,
                                int n2);
typedef double (dpairedt_func) (const double *x1, const double *x2, int n);
typedef double (dfr2z_func)    (const double r);

typedef double (dssum_func)    (const float  *a, int n);
// ... TODO

/*----------------------------------------------------------------------------
  Global Variables
----------------------------------------------------------------------------*/
extern ssum_func     *ssum_ptr;
extern smean_func    *smean_ptr;
extern svar_func     *svar_ptr;
extern svarm_func    *svarm_ptr;
extern svar0_func    *svar0_ptr;
extern sstd_func     *sstd_ptr;
extern ststat2_func  *ststat2_ptr;
extern swelcht_func  *swelcht_ptr;
extern spairedt_func *spairedt_ptr;
extern sfr2z_func    *sfr2z_ptr;

extern dsum_func     *dsum_ptr;
extern dmean_func    *dmean_ptr;
extern dvar_func     *dvar_ptr;
extern dvarm_func    *dvarm_ptr;
extern dvar0_func    *dvar0_ptr;
extern dstd_func     *dstd_ptr;
extern dtstat2_func  *dtstat2_ptr;
extern dwelcht_func  *dwelcht_ptr;
extern dpairedt_func *dpairedt_ptr;
extern dfr2z_func    *dfr2z_ptr;

extern dssum_func    *dssum_ptr;
// ... TODO

/*----------------------------------------------------------------------------
  Function Prototypes
----------------------------------------------------------------------------*/
inline float  ssum     (const float  *a, int n);
inline float  smean    (const float  *a, int n);
inline float  svar     (const float  *a, int n);
inline float  svarm    (const float  *a, int n, float  m);
inline float  svar0    (const float  *a, int n);
inline float  sstd     (const float  *a, int n);
inline float  ststat2  (const float  *x1, const float  *x2, int n1, int n2);
inline float  swelcht  (const float  *x1, const float  *x2, int n1, int n2);
inline float  spairedt (const float  *x1, const float  *x2, int n);
inline float  sfr2z    (const float  r);

inline double dsum     (const double *a, int n);
inline double dmean    (const double *a, int n);
inline double dvar     (const double *a, int n);
inline double dvarm    (const double *a, int n, double m);
inline double dvar0    (const double *a, int n);
inline double dstd     (const double *a, int n);
inline double dtstat2  (const double *x1, const double *x2, int n1, int n2);
inline double dwelcht  (const double *x1, const double *x2, int n1, int n2);
inline double dpairedt (const double *x1, const double *x2, int n);
inline double dfr2z    (const double r);

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


extern float  ssum_select     (const float  *a, int n);
extern float  smean_select    (const float  *a, int n);
extern float  svar_select     (const float  *a, int n);
extern float  svarm_select    (const float  *a, int n, float m);
extern float  svar0_select    (const float  *a, int n);
extern float  sstd_select     (const float  *a, int n);
extern float  ststat2_select  (const float  *x1, const float  *x2, int n1,
                               int n2);
extern float  swelcht_select  (const float  *x1, const float  *x2, int n1,
                               int n2);
extern float  spairedt_select (const float  *x1, const float  *x2, int n);
extern float  sfr2z_select    (float  r);

extern double dsum_select     (const double *a, int n);
extern double dmean_select    (const double *a, int n);
extern double dvar_select     (const double *a, int n);
extern double dvarm_select    (const double *a, int n, double m);
extern double dvar0_select    (const double *a, int n);
extern double dstd_select     (const double *a, int n);
extern double dtstat2_select  (const double *x1, const double *x2, int n1,
                               int n2);
extern double dwelcht_select  (const double *x1, const double *x2, int n1,
                               int n2);
extern double dpairedt_select (const double *x1, const double *x2, int n);
extern double dfr2z_select    (double r);

extern double dssum_select    (const float  *a, int n);
// ... TODO

extern float  ssum_naive     (const float  *a, int n);
extern float  smean_naive    (const float  *a, int n);
extern float  svar_naive     (const float  *a, int n);
extern float  svarm_naive    (const float  *a, int n, float m);
extern float  svar0_naive    (const float  *a, int n);
extern float  sstd_naive     (const float  *a, int n);
extern float  ststat2_naive  (const float  *x1, const float  *x2, int n1,
                              int n2);
extern float  swelcht_naive  (const float  *x1, const float  *x2, int n1,
                              int n2);
extern float  spairedt_naive (const float  *x1, const float  *x2, int n);
extern float  sfr2z_naive    (float  r);

extern double dsum_naive     (const double *a, int n);
extern double dmean_naive    (const double *a, int n);
extern double dvar_naive     (const double *a, int n);
extern double dvarm_naive    (const double *a, int n, double m);
extern double dvar0_naive    (const double *a, int n);
extern double dstd_naive     (const double *a, int n);
extern double dtstat2_naive  (const double *x1, const double *x2, int n1,
                              int n2);
extern double dwelcht_naive  (const double *x1, const double *x2, int n1,
                              int n2);
extern double dpairedt_naive (const double *x1, const double *x2, int n);
extern double dfr2z_naive    (double r);

extern double dssum_naive    (const float  *a, int n);
// ... TODO

#ifdef ARCH_IS_X86_64
extern float  ssum_sse2     (const float  *a, int n);
extern float  smean_sse2    (const float  *a, int n);
extern float  svar_sse2     (const float  *a, int n);
extern float  svarm_sse2    (const float  *a, int n, float m);
extern float  svar0_sse2    (const float  *a, int n);
extern float  sstd_sse2     (const float  *a, int n);
extern float  ststat2_sse2  (const float  *x1, const float  *x2, int n1,
                             int n2);
extern float  sfr2z_sse2    (float  r);

extern double dsum_sse2     (const double *a, int n);
extern double dmean_sse2    (const double *a, int n);
extern double dvar_sse2     (const double *a, int n);
extern double dvarm_sse2    (const double *a, int n, double m);
extern double dvar0_sse2    (const double *a, int n);
extern double dstd_sse2     (const double *a, int n);
extern double dtstat2_sse2  (const double *x1, const double *x2, int n1,
                             int n2);
extern double dfr2z_sse2    (double r);

extern double dssum_sse2    (const float  *a, int n);
// ... TODO
#endif


/*----------------------------------------------------------------------------
  Inline Functions
----------------------------------------------------------------------------*/

inline float ssum (const float *a, int n) {
  return (*ssum_ptr)(a,n);
}

inline float smean (const float *a, int n) {
  return (*smean_ptr)(a,n);
}

inline float svar (const float *a, int n) {
  return (*svar_ptr)(a,n);
}

inline float svarm (const float *a, int n, float m) {
  return (*svarm_ptr)(a,n,m);
}

inline float svar0 (const float *a, int n) {
  return (*svar0_ptr)(a,n);
}

inline float sstd (const float *a, int n) {
  return (*sstd_ptr)(a,n);
}

inline float ststat2 (const float *x1, const float *x2, int n1, int n2) {
  return (*ststat2_ptr)(x1,x2,n1,n2);
}

inline float swelcht (const float *x1, const float *x2, int n1, int n2) {
  return (*swelcht_ptr)(x1,x2,n1,n2);
}

inline float spairedt (const float *x1, const float *x2, int n) {
  return (*spairedt_ptr)(x1,x2,n);
}

inline float sfr2z (float r) {
  return (*sfr2z_ptr)(r);
}

/*--------------------------------------------------------------------------*/

inline double dsum (const double *a, int n) {
  return (*dsum_ptr)(a,n);
}

inline double dmean (const double *a, int n) {
  return (*dmean_ptr)(a,n);
}

inline double dvar (const double *a, int n) {
  return (*dvar_ptr)(a,n);
}

inline double dvarm (const double *a, int n, double m) {
  return (*dvarm_ptr)(a,n,m);
}

inline double dvar0 (const double *a, int n) {
  return (*dvar0_ptr)(a,n);
}

inline double dstd (const double *a, int n) {
  return (*dstd_ptr)(a,n);
}

inline double dtstat2 (const double *x1, const double *x2, int n1, int n2) {
  return (*dtstat2_ptr)(x1,x2,n1,n2);
}

inline double dwelcht (const double *x1, const double *x2, int n1, int n2) {
  return (*dwelcht_ptr)(x1,x2,n1,n2);
}

inline double dpairedt (const double *x1, const double *x2, int n) {
  return (*dpairedt_ptr)(x1,x2,n);
}

inline double dfr2z (double r) {
  return (*dfr2z_ptr)(r);
}

/*--------------------------------------------------------------------------*/

inline double dssum (const float *a, int n) {
  return (*dssum_ptr)(a,n);
}

// ... TODO

#ifdef __cplusplus
}
#endif

#endif  // #ifndef STATS_H
