/*----------------------------------------------------------------------------
  File    : stats_sse2.c
  Contents: basic statistical functions (SSE2-based implementations)
  Author  : Kristian Loewe
----------------------------------------------------------------------------*/
#include "stats_sse2.h"

/*----------------------------------------------------------------------------
  Function Prototypes
----------------------------------------------------------------------------*/
extern float  ssum_sse2    (const float  *a, int n);
extern float  smean_sse2   (const float  *a, int n);
extern float  svar_sse2    (const float  *a, int n);
extern float  svarm_sse2   (const float  *a, int n, float m);
extern float  svar0_sse2   (const float  *a, int n);
extern float  sstd_sse2    (const float  *a, int n);
extern float  ststat2_sse2 (const float *x1, const float *x2, int n1, int n2);

