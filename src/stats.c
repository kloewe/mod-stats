/*----------------------------------------------------------------------------
  File    : stats.c
  Contents: basic statistical functions (cpu dispatcher)
  Author  : Kristian Loewe
----------------------------------------------------------------------------*/
#include "stats.h"
#ifdef ARCH_IS_X86_64
#include "cpuinfo.h"
#endif

/*----------------------------------------------------------------------------
  Function Prototypes
----------------------------------------------------------------------------*/
extern float  ssum     (const float  *a, int n);
extern float  smean    (const float  *a, int n);
extern float  svar     (const float  *a, int n);
extern float  svarm    (const float  *a, int n, float  m);
extern float  svar0    (const float  *a, int n);
extern float  sstd     (const float  *a, int n);
extern float  ststat   (const float  *a, int n);
extern float  ststat2  (const float  *x1, const float  *x2, int n1, int n2);
extern stres  swelcht  (const float  *x1, const float  *x2, int n1, int n2);
extern float  spairedt (const float  *x1, const float  *x2, int n);
extern float  sdidt    (const float  *x1, const float  *x2,
                        const float  *y1, const float  *y2, int nx, int ny);
extern float  sfr2z    (const float  r);

extern double dsum     (const double *a, int n);
extern double dmean    (const double *a, int n);
extern double dvar     (const double *a, int n);
extern double dvarm    (const double *a, int n, double m);
extern double dvar0    (const double *a, int n);
extern double dstd     (const double *a, int n);
extern double dtstat   (const double *a, int n);
extern double dtstat2  (const double *x1, const double *x2, int n1, int n2);
extern dtres  dwelcht  (const double *x1, const double *x2, int n1, int n2);
extern double dpairedt (const double *x1, const double *x2, int n);
extern double ddidt    (const double *x1, const double *x2,
                        const double *y1, const double *y2, int nx, int ny);
extern double dfr2z    (const double r);

extern double dssum    (const float  *a, int n);
// ... TODO

/*----------------------------------------------------------------------------
  Global Variables
----------------------------------------------------------------------------*/
ssum_func     *ssum_ptr     = &ssum_select;
svarm_func    *svarm_ptr    = &svarm_select;

dsum_func     *dsum_ptr     = &dsum_select;
dvarm_func    *dvarm_ptr    = &dvarm_select;

dssum_func    *dssum_ptr    = &dssum_select;
// ... TODO

/*----------------------------------------------------------------------------
  Functions
----------------------------------------------------------------------------*/

float ssum_select (const float *a, int n)
{
  stats_set_impl(STATS_AUTO);
  return (*ssum_ptr)(a,n);
}

float svarm_select (const float *a, int n, float m)
{
  stats_set_impl(STATS_AUTO);
  return (*svarm_ptr)(a,n,m);
}

/*--------------------------------------------------------------------------*/

double dsum_select (const double *a, int n)
{
  stats_set_impl(STATS_AUTO);
  return (*dsum_ptr)(a,n);
}

double dvarm_select (const double *a, int n, double m)
{
  stats_set_impl(STATS_AUTO);
  return (*dvarm_ptr)(a,n,m);
}

/*--------------------------------------------------------------------------*/

double dssum_select (const float *a, int n)
{
  stats_set_impl(STATS_AUTO);
  return (*dssum_ptr)(a,n);
}

// ... TODO

/*--------------------------------------------------------------------------*/

stats_flags stats_set_impl (stats_flags impl) {

  #ifndef ARCH_IS_X86_64
  impl = STATS_NAIVE;
  #endif

  dot_set_impl(impl);
  
  switch (impl) {
    case STATS_AUTO :
    case STATS_AVX :
      if (hasAVX()) {
        // ssum_ptr  = &ssum_avx;
        // ... TODO
        // dsum_ptr  = &dsum_avx;
        // ... TODO
        // dssum_ptr = &dssum_avx;
        // ... TODO
        // return STATS_AVX;
      }
    case STATS_SSE2 :
      if (hasSSE2()) {
        ssum_ptr     = &ssum_sse2;
        svarm_ptr    = &svarm_sse2;

        dsum_ptr     = &dsum_naive;     // TODO
        dvarm_ptr    = &dvarm_naive;    // TODO

        dssum_ptr    = &dssum_naive;    // TODO
        // ... TODO

        return STATS_SSE2;
      }
    case STATS_NAIVE :
      ssum_ptr     = &ssum_naive;
      svarm_ptr    = &svarm_naive;

      dsum_ptr     = &dsum_naive;
      dvarm_ptr    = &dvarm_naive;

      dssum_ptr    = &dssum_naive;
      // ... TODO

      return STATS_NAIVE;
    default :
      return stats_set_impl(STATS_AUTO);
  }
}  // stats_set_impl()
