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
  Function Prototypes, Global Variables, and Functions
----------------------------------------------------------------------------*/
#ifdef REAL                     // if REAL is already defined, save its
#  include "real-is-double.inc" // original definition based on the value
#  undef REAL                   // of REAL_IS_DOUBLE, then undefine it
#endif
/*--------------------------------------------------------------------------*/
#define REAL        float       // (re)define REAL to be float
#define tres        stres
#define sum_func    ssum_func
#define varm_func   svarm_func
#define sum_ptr     ssum_ptr
#define varm_ptr    svarm_ptr
#define sum_select  ssum_select
#define varm_select svarm_select
#include "def-or-undef-functions.inc"
#include "stats_real.c"         // single precision versions
#undef REAL
#include "def-or-undef-functions.inc"
#undef tres
#undef sum_func
#undef varm_func
#undef sum_ptr
#undef varm_ptr
#undef sum_select
#undef varm_select
/*--------------------------------------------------------------------------*/
#define REAL        double      // (re)define REAL to be double
#define tres        dtres
#define sum_func    dsum_func
#define varm_func   dvarm_func
#define sum_ptr     dsum_ptr
#define varm_ptr    dvarm_ptr
#define sum_select  dsum_select
#define varm_select dvarm_select
#include "def-or-undef-functions.inc"
#include "stats_real.c"         // double precision versions
#undef REAL
#include "def-or-undef-functions.inc"
#undef tres
#undef sum_func
#undef varm_func
#undef sum_ptr
#undef varm_ptr
#undef sum_select
#undef varm_select
/*--------------------------------------------------------------------------*/
#undef REAL                     // restore original definition of REAL
#ifdef REAL_IS_DOUBLE           // (if necessary)
#  if REAL_IS_DOUBLE
#    define REAL double
#  else
#    define REAL float
#  endif
#endif

/*----------------------------------------------------------------------------
  Function Prototypes
----------------------------------------------------------------------------*/
extern double dssum    (const float  *a, int n);
// ... TODO
extern int    isum     (const int    *a, int n);

/*----------------------------------------------------------------------------
  Global Variables
----------------------------------------------------------------------------*/
dssum_func *dssum_ptr = &dssum_select;
// ... TODO

/*----------------------------------------------------------------------------
  Functions
----------------------------------------------------------------------------*/
double dssum_select (const float *a, int n)
{
  stats_set_impl(STATS_AUTO);
  return (*dssum_ptr)(a,n);
}  // dssum_select()

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
