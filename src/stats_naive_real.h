/*----------------------------------------------------------------------------
  File    : stats_naive_real.h
  Contents: basic statistical functions (naive implementations)
  Authors : Kristian Loewe
----------------------------------------------------------------------------*/
#ifndef STATS_NAIVE_REAL_H
#define STATS_NAIVE_REAL_H

#include <assert.h>

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

/* mean_naive
 * ----------
 * compute the sample mean
 */
inline REAL mean_naive (const REAL *a, int n)
{
  assert(a && (n > 0));

  return sum_naive(a, n) /(REAL)n;
}  // mean_naive()

/*--------------------------------------------------------------------------*/

/* var0_naive
 * ----------
 * compute the unbiased sample variance if the mean is 0
 */
inline REAL var0_naive (const REAL *a, int n)
{
  assert(a && (n > 0));

  return dot_naive(a,a,n) /(REAL)(n-1) ;
}  // var0_naive()

/*--------------------------------------------------------------------------*/

/* varm_naive
 * ----------
 * compute the unbiased sample variance if the mean is m
 */
inline REAL varm_naive (const REAL *a, int n, REAL m)
{
  assert(a && (n > 0));

  REAL v = 0.0f;
  for (int i = 0; i < n; i++) 
    v += (a[i] - m)*(a[i] - m);
  return v /= (REAL)(n-1);
}  // varm_naive()

/*--------------------------------------------------------------------------*/

/* var_naive
 * ---------
 * compute the unbiased sample variance
 */
inline REAL var_naive (const REAL *a, int n)
{
  return varm_naive(a, n, mean_naive(a, n));
}  // var_naive()

/*--------------------------------------------------------------------------*/

/* std_naive
 * ---------
 * compute the corrected sample standard deviation
 */
inline REAL std_naive (const REAL *a, int n)
{
  return sqrt(var_naive(a, n));
}  // std_naive()

/*--------------------------------------------------------------------------*/

/* tstat2_naive
 * ------------
 * compute t statistic
 *   (two independent samples, equal variances)
 */
inline REAL tstat2_naive (const REAL *x1, const REAL *x2, int n1, int n2)
{
  int  tdf = n1 + n2 - 2;             // total degrees of freedom
  REAL m1  = mean_naive(x1, n1);      // sample means
  REAL m2  = mean_naive(x2, n2);
  REAL v1  = varm_naive(x1, n1, m1);  // sample variances
  REAL v2  = varm_naive(x2, n2, m2);
  REAL t   = (m1 - m2)                // t statistic
             / ( sqrt( ( (REAL)(n1-1)*v1 + (REAL)(n2-1)*v2 ) / (REAL)tdf )
                 * sqrt(1/(REAL)n1 + 1/(REAL)n2) );
  return t;
}  // tstat2_naive()

/*--------------------------------------------------------------------------*/

/* fr2z_naive
 * ----------
 * Fisher r-to-z transform
 */
inline REAL fr2z_naive (REAL r)
{
  if (r <= (REAL)-1) return (REAL)-R2Z_MAX;
  if (r >= (REAL)+1) return (REAL)+R2Z_MAX;
  return (REAL)atanh(r);              // compute arcus tangens hyperbolicus
}  // fr2z_naive()

#endif  // #ifndef STATS_NAIVE_REAL_H
