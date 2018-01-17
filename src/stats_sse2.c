/*----------------------------------------------------------------------------
  File    : stats_sse2.c
  Contents: basic statistical functions (SSE2-based implementations)
  Author  : Kristian Loewe
----------------------------------------------------------------------------*/
#include "stats_sse2.h"

/*----------------------------------------------------------------------------
  Function Prototypes
----------------------------------------------------------------------------*/
extern float  ssum_sse2     (const float  *a, int n);
extern float  svarm_sse2    (const float  *a, int n, float m);
