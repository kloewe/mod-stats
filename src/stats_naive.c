/*----------------------------------------------------------------------------
  File    : stats_naive.c
  Contents: basic statistical functions (naive implementations)
  Author  : Kristian Loewe
----------------------------------------------------------------------------*/
#include "stats_naive.h"

/*----------------------------------------------------------------------------
  Function Prototypes
----------------------------------------------------------------------------*/
extern float  ssum_naive     (const float  *a, int n);
extern float  svarm_naive    (const float  *a, int n, float  m);

extern double dsum_naive     (const double *a, int n);
extern double dvarm_naive    (const double *a, int n, double m);

extern double dssum_naive    (const float  *a, int n);
// ... TODO
