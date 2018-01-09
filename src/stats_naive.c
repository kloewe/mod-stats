/*----------------------------------------------------------------------------
  File    : stats_naive.c
  Contents: basic statistical functions (naive implementations)
  Author  : Kristian Loewe
----------------------------------------------------------------------------*/
#include "stats_naive.h"

/*----------------------------------------------------------------------------
  Function Prototypes
----------------------------------------------------------------------------*/
extern float  ssum_naive    (const float  *a, int n);
extern float  smean_naive   (const float  *a, int n);
extern float  svar_naive    (const float  *a, int n);
extern float  svarm_naive   (const float  *a, int n, float  m);
extern float  svar0_naive   (const float  *a, int n);
extern float  sstd_naive    (const float  *a, int n);
extern float  ststat2_naive (const float  *x1, const float  *x2, int n1,
                             int n2);
extern float  sfr2z_naive   (float  r);

extern double dsum_naive    (const double *a, int n);
extern double dmean_naive   (const double *a, int n);
extern double dvar_naive    (const double *a, int n);
extern double dvarm_naive   (const double *a, int n, double m);
extern double dvar0_naive   (const double *a, int n);
extern double dstd_naive    (const double *a, int n);
extern double dtstat2_naive (const double *x1, const double *x2, int n1,
                             int n2);
extern double dfr2z_naive   (double r);

extern double dssum_naive   (const float  *a, int n);
// ... TODO