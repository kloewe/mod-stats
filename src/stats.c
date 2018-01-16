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
extern float  ststat2  (const float  *x1, const float  *x2, int n1, int n2);
extern float  swelcht  (const float  *x1, const float  *x2, int n1, int n2);
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
extern double dtstat2  (const double *x1, const double *x2, int n1, int n2);
extern double dwelcht  (const double *x1, const double *x2, int n1, int n2);
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
smean_func    *smean_ptr    = &smean_select;
svar_func     *svar_ptr     = &svar_select;
svarm_func    *svarm_ptr    = &svarm_select;
svar0_func    *svar0_ptr    = &svar0_select;
sstd_func     *sstd_ptr     = &sstd_select;
ststat2_func  *ststat2_ptr  = &ststat2_select;
swelcht_func  *swelcht_ptr  = &swelcht_select;
spairedt_func *spairedt_ptr = &spairedt_select;
sdidt_func    *sdidt_ptr    = &sdidt_select;
sfr2z_func    *sfr2z_ptr    = &sfr2z_select;

dsum_func     *dsum_ptr     = &dsum_select;
dmean_func    *dmean_ptr    = &dmean_select;
dvar_func     *dvar_ptr     = &dvar_select;
dvarm_func    *dvarm_ptr    = &dvarm_select;
dvar0_func    *dvar0_ptr    = &dvar0_select;
dstd_func     *dstd_ptr     = &dstd_select;
dtstat2_func  *dtstat2_ptr  = &dtstat2_select;
dwelcht_func  *dwelcht_ptr  = &dwelcht_select;
dpairedt_func *dpairedt_ptr = &dpairedt_select;
ddidt_func    *ddidt_ptr    = &ddidt_select;
dfr2z_func    *dfr2z_ptr    = &dfr2z_select;

dssum_func    *dssum_ptr   = &dssum_select;
// ... TODO

/*----------------------------------------------------------------------------
  Functions
----------------------------------------------------------------------------*/

float ssum_select (const float *a, int n)
{
  stats_set_impl(STATS_AUTO);
  return (*ssum_ptr)(a,n);
}

float smean_select (const float *a, int n)
{
  stats_set_impl(STATS_AUTO);
  return (*smean_ptr)(a,n);
}

float svar_select (const float *a, int n)
{
  stats_set_impl(STATS_AUTO);
  return (*svar_ptr)(a,n);
}

float svarm_select (const float *a, int n, float m)
{
  stats_set_impl(STATS_AUTO);
  return (*svarm_ptr)(a,n,m);
}

float svar0_select (const float *a, int n)
{
  stats_set_impl(STATS_AUTO);
  return (*svar0_ptr)(a,n);
}

float sstd_select (const float *a, int n)
{
  stats_set_impl(STATS_AUTO);
  return (*sstd_ptr)(a,n);
}

float ststat2_select (const float *x1, const float *x2, int n1, int n2)
{
  stats_set_impl(STATS_AUTO);
  return (*ststat2_ptr)(x1,x2,n1,n2);
}

float swelcht_select (const float *x1, const float *x2, int n1, int n2)
{
  stats_set_impl(STATS_AUTO);
  return (*swelcht_ptr)(x1,x2,n1,n2);
}

float spairedt_select (const float *x1, const float *x2, int n)
{
  stats_set_impl(STATS_AUTO);
  return (*spairedt_ptr)(x1,x2,n);
}

float sdidt_select (const float *x1, const float *x2,
                    const float *y1, const float *y2, int nx, int ny)
{
  stats_set_impl(STATS_AUTO);
  return (*sdidt_ptr)(x1,x2,y1,y2,nx,ny);
}

float sfr2z_select (float r) {
  stats_set_impl(STATS_AUTO);
  return (*sfr2z_ptr)(r);
}

/*--------------------------------------------------------------------------*/

double dsum_select (const double *a, int n)
{
  stats_set_impl(STATS_AUTO);
  return (*dsum_ptr)(a,n);
}

double dmean_select (const double *a, int n)
{
  stats_set_impl(STATS_AUTO);
  return (*dmean_ptr)(a,n);
}

double dvar_select (const double *a, int n)
{
  stats_set_impl(STATS_AUTO);
  return (*dvar_ptr)(a,n);
}

double dvarm_select (const double *a, int n, double m)
{
  stats_set_impl(STATS_AUTO);
  return (*dvarm_ptr)(a,n,m);
}

double dvar0_select (const double *a, int n)
{
  stats_set_impl(STATS_AUTO);
  return (*dvar0_ptr)(a,n);
}

double dstd_select (const double *a, int n)
{
  stats_set_impl(STATS_AUTO);
  return (*dstd_ptr)(a,n);
}

double dtstat2_select (const double *x1, const double *x2, int n1, int n2)
{
  stats_set_impl(STATS_AUTO);
  return (*dtstat2_ptr)(x1,x2,n1,n2);
}

double dwelcht_select (const double *x1, const double *x2, int n1, int n2)
{
  stats_set_impl(STATS_AUTO);
  return (*dwelcht_ptr)(x1,x2,n1,n2);
}

double dpairedt_select (const double *x1, const double *x2, int n)
{
  stats_set_impl(STATS_AUTO);
  return (*dpairedt_ptr)(x1,x2,n);
}

double ddidt_select (const double *x1, const double *x2,
                     const double *y1, const double *y2, int nx, int ny)
{
  stats_set_impl(STATS_AUTO);
  return (*ddidt_ptr)(x1,x2,y1,y2,nx,ny);
}

double dfr2z_select (double r)
{
  stats_set_impl(STATS_AUTO);
  return (*dfr2z_ptr)(r);
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
        smean_ptr    = &smean_sse2;
        svar_ptr     = &svar_sse2;
        svarm_ptr    = &svarm_sse2;
        svar0_ptr    = &svar0_sse2;
        sstd_ptr     = &sstd_sse2;
        ststat2_ptr  = &ststat2_sse2;
        swelcht_ptr  = &swelcht_naive;  // TODO
        spairedt_ptr = &spairedt_naive; // TODO
        sdidt_ptr    = &sdidt_naive;    // TODO
        sfr2z_ptr    = &sfr2z_naive;

        dsum_ptr     = &dsum_naive;     // TODO
        dmean_ptr    = &dmean_naive;    // TODO
        dvar_ptr     = &dvar_naive;     // TODO
        dvarm_ptr    = &dvarm_naive;    // TODO
        dvar0_ptr    = &dvar0_naive;    // TODO
        dstd_ptr     = &dstd_naive;     // TODO
        dtstat2_ptr  = &dtstat2_naive;  // TODO
        dwelcht_ptr  = &dwelcht_naive;  // TODO
        dpairedt_ptr = &dpairedt_naive; // TODO
        ddidt_ptr    = &ddidt_naive;    // TODO
        dfr2z_ptr    = &dfr2z_naive;

        dssum_ptr    = &dssum_naive;     // TODO
        // ... TODO

        return STATS_SSE2;
      }
    case STATS_NAIVE :
      ssum_ptr     = &ssum_naive;
      smean_ptr    = &smean_naive;
      svar_ptr     = &svar_naive;
      svarm_ptr    = &svarm_naive;
      svar0_ptr    = &svar0_naive;
      sstd_ptr     = &sstd_naive;
      ststat2_ptr  = &ststat2_naive;
      swelcht_ptr  = &swelcht_naive;
      spairedt_ptr = &spairedt_naive;
      sdidt_ptr    = &sdidt_naive;
      sfr2z_ptr    = &sfr2z_naive;

      dsum_ptr     = &dsum_naive;
      dmean_ptr    = &dmean_naive;
      dvar_ptr     = &dvar_naive;
      dvarm_ptr    = &dvarm_naive;
      dvar0_ptr    = &dvar0_naive;
      dstd_ptr     = &dstd_naive;
      dtstat2_ptr  = &dtstat2_naive;
      dwelcht_ptr  = &dwelcht_naive;
      dpairedt_ptr = &dpairedt_naive;
      ddidt_ptr    = &ddidt_naive;
      dfr2z_ptr    = &dfr2z_naive;

      dssum_ptr    = &dssum_naive;
      // ... TODO

      return STATS_NAIVE;
    default :
      return stats_set_impl(STATS_AUTO);
  }
}  // stats_set_impl()
