/*----------------------------------------------------------------------------
  File    : stats_naive_real.h
  Contents: basic statistical functions (naive implementations)
  Authors : Kristian Loewe
----------------------------------------------------------------------------*/
#ifndef STATS_NAIVE_REAL_H
#define STATS_NAIVE_REAL_H

#include <stdlib.h>
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

  return dot_naive(a, a, n) /(REAL)(n-1);
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

/* tstat_naive
 * ------------
 * compute t statistic
 *   (one sample)
 */
inline REAL tstat_naive (const REAL *a, int n)
{
  REAL m = mean_naive(a, n);          // sample mean
  REAL s = sqrt(varm_naive(a, n, m)); // sample standard deviation
  return m / (s / sqrt((REAL)n));
}  // tstat_naive()

/*--------------------------------------------------------------------------*/

/* tstat2_naive
 * ------------
 * compute t statistic
 *   (two independent samples, equal variances)
 */
inline REAL tstat2_naive (const REAL *x1, const REAL *x2, int n1, int n2)
{
  REAL m1 = mean_naive(x1, n1);       // sample means
  REAL m2 = mean_naive(x2, n2);
  REAL md = m1 - m2;                  // mean difference
  REAL v1 = varm_naive(x1, n1, m1);   // sample variances
  REAL v2 = varm_naive(x2, n2, m2);
  int  df = n1 + n2 - 2;              // degrees of freedom
  return md / ( sqrt( ( (REAL)(n1-1)*v1 + (REAL)(n2-1)*v2 ) / (REAL)df )
                * sqrt(1/(REAL)n1 + 1/(REAL)n2) );
}  // tstat2_naive()

/*--------------------------------------------------------------------------*/

/* welcht_naive
 * ------------
 * compute t statistic
 *   (two independent samples, equal or unequal variances)
 */
inline REAL welcht_naive (const REAL *x1, const REAL *x2, int n1, int n2)
{
  REAL m1 = mean_naive(x1, n1);       // sample means
  REAL m2 = mean_naive(x2, n2);
  REAL md = m1 - m2;                  // mean difference
  REAL v1 = varm_naive(x1, n1, m1);   // sample variances
  REAL v2 = varm_naive(x2, n2, m2);
  return md / sqrt(v1/(REAL)n1 + v2/(REAL)n2);
}  // welcht_naive()

/*--------------------------------------------------------------------------*/

/* pairedt_naive
 * ------------
 * compute t statistic
 *   (dependent/paired samples)
 */
inline REAL pairedt_naive (const REAL *x1, const REAL *x2, int n)
{
#if 0
  REAL m1 = mean_naive(x1, n);        // sample means
  REAL m2 = mean_naive(x2, n);
  REAL md = m1 - m2;                  // mean difference
  REAL sd = 0;                        // standard deviation of the differences
  for (int i = 0; i < n; i++)
    sd += ((x1[i] - x2[i]) - md) * ((x1[i] - x2[i]) - md);
  sd = sqrt(sd/(REAL)(n - 1));
  return md / (sd / sqrt((REAL)n));
#else
  REAL *diff = (REAL *) malloc((size_t)n *sizeof(REAL));
  for (int i = 0; i < n; i++)
    diff[i] = x1[i] - x2[i];
  REAL t = tstat_naive(diff, n);
  free(diff);
  return t;
#endif
}  // pairedt_naive()

/*--------------------------------------------------------------------------*/

/* didt_naive
 * ------------
 * compute t statistic
 *   (difference-in-differences)
 */
inline REAL didt_naive (const REAL *x1, const REAL *x2,
                        const REAL *y1, const REAL *y2, int nx, int ny)
{
  REAL *diffx = (REAL *) malloc((size_t)nx *sizeof(REAL));
  for (int i = 0; i < nx; i++)
    diffx[i] = x2[i] - x1[i];
  REAL mdx = mean_naive(diffx, nx);
  REAL vdx = varm_naive(diffx, nx, mdx);
  free(diffx);

  REAL *diffy = (REAL *) malloc((size_t)ny *sizeof(REAL));
  for (int i = 0; i < ny; i++)
    diffy[i] = y2[i] - y1[i];
  REAL mdy = mean_naive(diffy, ny);
  REAL vdy = varm_naive(diffy, ny, mdy);
  free(diffy);

  REAL md = mdx - mdy;

  int df = nx + ny - 2;
  return md / ( sqrt( ( (REAL)(nx-1)*vdx + (REAL)(ny-1)*vdy ) / (REAL)df )
                * sqrt(1/(REAL)nx + 1/(REAL)ny) );
}  // didt_naive()

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
