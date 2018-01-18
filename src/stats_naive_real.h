/*----------------------------------------------------------------------------
  File    : stats_naive_real.h
  Contents: this file is to be included from stats_naive.h
  Authors : Kristian Loewe
----------------------------------------------------------------------------*/
#ifndef STATS_NAIVE_REAL_H
#define STATS_NAIVE_REAL_H

#include <stdlib.h>
#include <assert.h>

/*----------------------------------------------------------------------------
  Function Prototypes
----------------------------------------------------------------------------*/
inline REAL sum_naive  (const REAL *a, int n);
inline REAL varm_naive (const REAL *a, int n, REAL m);

/*----------------------------------------------------------------------------
  Inline Functions
----------------------------------------------------------------------------*/

/* sum_naive
 * ---------
 * compute the sum
 */
inline REAL sum_naive (const REAL *a, int n)
{
  assert(a && (n > 0));

  REAL s = 0;
  for (int i = 0; i < n; i++)
    s += a[i];
  return s;
}  // sum_naive()

/*--------------------------------------------------------------------------*/

/* varm_naive
 * ----------
 * compute the unbiased sample variance if the mean is m
 */
inline REAL varm_naive (const REAL *a, int n, REAL m)
{
  assert(a && (n > 1));

  REAL v = 0.0f;
  for (int i = 0; i < n; i++) 
    v += (a[i] - m)*(a[i] - m);
  return v /= (REAL)(n-1);
}  // varm_naive()

#endif  // #ifndef STATS_NAIVE_REAL_H
