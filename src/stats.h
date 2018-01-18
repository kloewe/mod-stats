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
extern ssum_func     *ssum_ptr;
extern svarm_func    *svarm_ptr;

extern dsum_func     *dsum_ptr;
extern dvarm_func    *dvarm_ptr;

extern dssum_func    *dssum_ptr;
// ... TODO

/*----------------------------------------------------------------------------
  Type Definitions: structs
----------------------------------------------------------------------------*/
typedef struct stres {
  float tstat;
  float df;
} stres;

typedef struct dtres {
  double tstat;
  double df;
} dtres;

/*----------------------------------------------------------------------------
  Function Prototypes
----------------------------------------------------------------------------*/
inline float  ssum     (const float  *a, int n);
inline float  smean    (const float  *a, int n);
inline float  svar     (const float  *a, int n);
inline float  svarm    (const float  *a, int n, float  m);
inline float  svar0    (const float  *a, int n);
inline float  sstd     (const float  *a, int n);
inline float  ststat   (const float  *a, int n);
inline float  ststat2  (const float  *x1, const float  *x2, int n1, int n2);
inline stres  swelcht  (const float  *x1, const float  *x2, int n1, int n2);
inline float  spairedt (const float  *x1, const float  *x2, int n);
inline float  sdidt    (const float  *x1, const float  *x2,
                        const float  *y1, const float  *y2,
                        int nx, int ny);
inline float  sfr2z    (const float  r);

inline double dsum     (const double *a, int n);
inline double dmean    (const double *a, int n);
inline double dvar     (const double *a, int n);
inline double dvarm    (const double *a, int n, double m);
inline double dvar0    (const double *a, int n);
inline double dstd     (const double *a, int n);
inline double dtstat   (const double *a, int n);
inline double dtstat2  (const double *x1, const double *x2, int n1, int n2);
inline dtres  dwelcht  (const double *x1, const double *x2, int n1, int n2);
inline double dpairedt (const double *x1, const double *x2, int n);
inline double ddidt    (const double *x1, const double *x2,
                        const double *y1, const double *y2,
                        int nx, int ny);
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
extern float  svarm_select    (const float  *a, int n, float m);

extern double dsum_select     (const double *a, int n);
extern double dvarm_select    (const double *a, int n, double m);

extern double dssum_select    (const float  *a, int n);
// ... TODO

extern float  ssum_naive     (const float  *a, int n);
extern float  svarm_naive    (const float  *a, int n, float m);

extern double dsum_naive     (const double *a, int n);
extern double dvarm_naive    (const double *a, int n, double m);

extern double dssum_naive    (const float  *a, int n);
// ... TODO

#ifdef ARCH_IS_X86_64
extern float  ssum_sse2     (const float  *a, int n);
extern float  svarm_sse2    (const float  *a, int n, float m);

extern double dsum_sse2     (const double *a, int n);
extern double dvarm_sse2    (const double *a, int n, double m);

// extern double dssum_sse2    (const float  *a, int n);
// ... TODO
#endif


/*----------------------------------------------------------------------------
  Inline Functions
----------------------------------------------------------------------------*/

inline float ssum (const float *a, int n)
{
  assert(a && (n > 0));

  return (*ssum_ptr)(a,n);
}

inline float smean (const float *a, int n)
{
  assert(a && (n > 0));

  return ssum(a, n) /(float)n;
}

inline float svar (const float *a, int n)
{
  assert(a && (n > 1));

  return svarm(a, n, smean(a, n));
}

inline float svarm (const float *a, int n, float m)
{
  assert(a && (n > 1));

  return (*svarm_ptr)(a,n,m);
}

inline float svar0 (const float *a, int n)
{
  assert(a && (n > 1));

  return sdot(a, a, n) /(float)(n-1);
}

inline float sstd (const float *a, int n)
{
  assert(a && (n > 1));

  return sqrtf(svar(a, n));
}

inline float ststat (const float *a, int n)
{
  assert(a && (n > 1));

  float m = smean(a, n);            // sample mean
  float s = sqrtf(svarm(a, n, m));  // sample standard deviation
  return m / (s / sqrtf((float)n));
}

inline float ststat2 (const float *x1, const float *x2, int n1, int n2)
{
  assert(x1 && x2 && (n1 > 1) && (n2 > 1));

  float m1 = smean(x1, n1);         // sample means
  float m2 = smean(x2, n2);
  float md = m1 - m2;               // mean difference
  float v1 = svarm(x1, n1, m1);     // sample variances
  float v2 = svarm(x2, n2, m2);
  float df = (float)n1 + (float)n2 - 2; // degrees of freedom
  return md / ( sqrtf( ( (float)(n1-1)*v1 + (float)(n2-1)*v2 ) / df )
                * sqrtf(1/(float)n1 + 1/(float)n2) );
}

inline stres swelcht (const float *x1, const float *x2, int n1, int n2)
{
  assert(x1 && x2 && (n1 > 1) && (n2 > 1));

  float m1 = smean(x1, n1);         // sample means
  float m2 = smean(x2, n2);
  float md = m1 - m2;               // mean difference
  float v1 = svarm(x1, n1, m1);     // sample variances
  float v2 = svarm(x2, n2, m2);
  float n1f = (float)n1;
  float n2f = (float)n2;
  float df = ((v1/n1f + v2/n2f) * (v1/n1f + v2/n2f))
              / ((v1*v1)/(n1f*n1f*(n1f-1)) + (v2*v2)/(n2f*n2f*(n2f-1)));
  stres res = { .tstat = md / sqrtf(v1/n1f + v2/n2f), .df = df };
  return res;
}

inline float spairedt (const float *x1, const float *x2, int n)
{
  assert(x1 && x2 && (n > 1));

#if 0
  float m1 = smean(x1, n);          // sample means
  float m2 = smean(x2, n);
  float md = m1 - m2;               // mean difference
  float sd = 0;                     // standard dev. of the differences
  for (int i = 0; i < n; i++)
    sd += ((x1[i] - x2[i]) - md) * ((x1[i] - x2[i]) - md);
  sd = sqrtf(sd/(float)(n - 1));
  return md / (sd / sqrtf((float)n));
#else
  float *diff = (float *) malloc((size_t)n *sizeof(float));
  for (int i = 0; i < n; i++)
    diff[i] = x1[i] - x2[i];
  float t = ststat(diff, n);
  free(diff);
  return t;
#endif
}

inline float sdidt (const float *x1, const float *x2,
                    const float *y1, const float *y2, int nx, int ny)
{
  assert(x1 && x2 && y1 && y2 && (nx > 1) && (ny > 1));

  float *diffx = (float *) malloc((size_t)nx *sizeof(float));
  for (int i = 0; i < nx; i++)
    diffx[i] = x2[i] - x1[i];
  float mdx = smean(diffx, nx);
  float vdx = svarm(diffx, nx, mdx);
  free(diffx);

  float *diffy = (float *) malloc((size_t)ny *sizeof(float));
  for (int i = 0; i < ny; i++)
    diffy[i] = y2[i] - y1[i];
  float mdy = smean(diffy, ny);
  float vdy = svarm(diffy, ny, mdy);
  free(diffy);

  float md = mdx - mdy;

  float df = (float)nx + (float)ny - 2;
  return md / ( sqrtf( ( (float)(nx-1)*vdx + (float)(ny-1)*vdy ) / df )
                * sqrtf(1/(float)nx + 1/(float)ny) );
}

inline float sfr2z (float r)
{
  if (r <= (float)-1) return (float)-R2Z_MAX;
  if (r >= (float)+1) return (float)+R2Z_MAX;
  return (float)atanh(r);              // compute arcus tangens hyperbolicus
}  // sfr2z()


/*--------------------------------------------------------------------------*/

inline double dsum (const double *a, int n)
{
  return (*dsum_ptr)(a,n);
}

inline double dmean (const double *a, int n)
{
  assert(a && (n > 0));

  return dsum(a, n) /(double)n;
}

inline double dvar (const double *a, int n)
{
  assert(a && (n > 1));

  return dvarm(a, n, dmean(a, n));
}

inline double dvarm (const double *a, int n, double m)
{
  assert(a && (n > 1));

  return (*dvarm_ptr)(a,n,m);
}

inline double dvar0 (const double *a, int n)
{
  assert(a && (n > 1));

  return ddot(a, a, n) /(float)(n-1);
}

inline double dstd (const double *a, int n)
{
  assert(a && (n > 1));

  return sqrt(dvar(a, n));
}

inline double dtstat (const double *a, int n)
{
  assert(a && (n > 1));

  double m = dmean(a, n);            // sample mean
  double s = sqrt(dvarm(a, n, m));   // sample standard deviation
  return m / (s / sqrt((double)n));
}

inline double dtstat2 (const double *x1, const double *x2, int n1, int n2)
{
  assert(x1 && x2 && (n1 > 1) && (n2 > 1));

  double m1 = dmean(x1, n1);         // sample means
  double m2 = dmean(x2, n2);
  double md = m1 - m2;               // mean difference
  double v1 = dvarm(x1, n1, m1);     // sample variances
  double v2 = dvarm(x2, n2, m2);
  double df = (double)n1 + (double)n2 - 2; // degrees of freedom
  return md / ( sqrt( ( (double)(n1-1)*v1 + (double)(n2-1)*v2 ) / df )
                * sqrt(1/(double)n1 + 1/(double)n2) );
}

inline dtres dwelcht (const double *x1, const double *x2, int n1, int n2)
{
  assert(x1 && x2 && (n1 > 1) && (n2 > 1));

  double m1 = dmean(x1, n1);         // sample means
  double m2 = dmean(x2, n2);
  double md = m1 - m2;               // mean difference
  double v1 = dvarm(x1, n1, m1);     // sample variances
  double v2 = dvarm(x2, n2, m2);
  double n1f = (double)n1;
  double n2f = (double)n2;
  double df = ((v1/n1f + v2/n2f) * (v1/n1f + v2/n2f))
              / ((v1*v1)/(n1f*n1f*(n1f-1)) + (v2*v2)/(n2f*n2f*(n2f-1)));
  dtres  res = { .tstat = md / sqrt(v1/n1f + v2/n2f), .df = df };
  return res;
}

inline double dpairedt (const double *x1, const double *x2, int n)
{
  assert(x1 && x2 && (n > 1));

#if 0
  double m1 = dmean(x1, n);           // sample means
  double m2 = dmean(x2, n);
  double md = m1 - m2;                // mean difference
  double sd = 0;                      // standard dev. of the differences
  for (int i = 0; i < n; i++)
    sd += ((x1[i] - x2[i]) - md) * ((x1[i] - x2[i]) - md);
  sd = sqrt(sd/(double)(n - 1));
  return md / (sd / sqrt((double)n));
#else
  double *diff = (double *) malloc((size_t)n *sizeof(double));
  for (int i = 0; i < n; i++)
    diff[i] = x1[i] - x2[i];
  double t = dtstat(diff, n);
  free(diff);
  return t;
#endif
}

inline double ddidt (const double *x1, const double *x2,
                     const double *y1, const double *y2, int nx, int ny)
{
  assert(x1 && x2 && y1 && y2 && (nx > 1) && (ny > 1));

  double *diffx = (double *) malloc((size_t)nx *sizeof(double));
  for (int i = 0; i < nx; i++)
    diffx[i] = x2[i] - x1[i];
  double mdx = dmean(diffx, nx);
  double vdx = dvarm(diffx, nx, mdx);
  free(diffx);

  double *diffy = (double *) malloc((size_t)ny *sizeof(double));
  for (int i = 0; i < ny; i++)
    diffy[i] = y2[i] - y1[i];
  double mdy = dmean(diffy, ny);
  double vdy = dvarm(diffy, ny, mdy);
  free(diffy);

  double md = mdx - mdy;

  double df = (double)nx + (double)ny - 2;
  return md / ( sqrt( ( (double)(nx-1)*vdx + (double)(ny-1)*vdy ) / df )
                * sqrt(1/(double)nx + 1/(double)ny) );
}

inline double dfr2z (double r)
{
  if (r <= (double)-1) return (double)-R2Z_MAX;
  if (r >= (double)+1) return (double)+R2Z_MAX;
  return (double)atanh(r);              // compute arcus tangens hyperbolicus
}  // dfr2z()

/*--------------------------------------------------------------------------*/

inline double dssum (const float *a, int n) {
  return (*dssum_ptr)(a,n);
}

// ... TODO

#ifdef __cplusplus
}
#endif

#endif  // #ifndef STATS_H
