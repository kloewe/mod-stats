/*----------------------------------------------------------------------------
  File    : stats.h
  Contents: statistical functions
  Authors : Kristian Loewe, Christian Borgelt
----------------------------------------------------------------------------*/
#ifndef STATS_H
#define STATS_H

#include <math.h>
#include <assert.h>

/*----------------------------------------------------------------------------
  Preprocessor Definitions
----------------------------------------------------------------------------*/
#ifndef REAL
#define REAL float
#endif

/*--------------------------------------------------------------------------*/
#define float  1                      // to check the definition of REAL
#define double 2

#if   REAL == float                   // if single precision data
#undef  REAL_IS_DOUBLE
#define REAL_IS_DOUBLE  0             // clear indicator for double
#elif REAL == double                  // if double precision data
#undef  REAL_IS_DOUBLE
#define REAL_IS_DOUBLE  1             // set   indicator for double
#else
#error "REAL must be either 'float' or 'double'"
#endif

#undef float                          // delete definitions
#undef double                         // used for type checking
/*--------------------------------------------------------------------------*/

#if !REAL_IS_DOUBLE
#define sqrt sqrtf
#endif

#define R2Z_MAX 18.3684002848385504   // atanh(1-epsilon)

/*----------------------------------------------------------------------------
  Inline Functions
----------------------------------------------------------------------------*/

/* mean
 * ----
 * compute the sample mean
 */
inline REAL mean (REAL *data, int n)
{
  assert(data && (n > 0));

  REAL sum = 0;
  for (int i = 0; i < n; i++)
    sum += data[i];
  return sum /(REAL)n;
}  // mean()

/*--------------------------------------------------------------------------*/

/* varm
 * ----
 * compute the unbiased sample variance relative to the given mean m
 */
inline REAL varm (REAL *data, int n, REAL m)
{
  assert(data && (n > 0));

  REAL v = 0.0f;
  for (int i = 0; i < n; i++) 
    v += (data[i] - m)*(data[i] - m);
  return v /= (REAL)(n-1);
}  // varm()

/*--------------------------------------------------------------------------*/

/* var
 * ---
 * compute the unbiased sample variance
 */
inline REAL var (REAL *data, int n)
{
  return varm(data, n, mean(data, n));
}  // var()

/*--------------------------------------------------------------------------*/

/* std
 * ---
 * compute the corrected sample standard deviation
 */
inline REAL std (REAL *data, int n)
{
  return sqrt(var(data, n));
}  // std()

/*--------------------------------------------------------------------------*/

/* tstat2
 * ------
 * compute t statistic
 *   (two independent samples, equal variances)
 */
inline REAL tstat2 (REAL *x1, REAL *x2, int n1, int n2)
{
  int  tdf = n1 + n2 - 2;             // total degrees of freedom
  REAL m1  = mean(x1, n1);            // sample means
  REAL m2  = mean(x2, n2);
  REAL v1  = varm(x1, n1, m1);        // sample variances
  REAL v2  = varm(x2, n2, m2);
  REAL t   = (m1 - m2)                // t statistic
             / ( sqrt( ( (REAL)(n1-1)*v1 + (REAL)(n2-1)*v2 ) / (REAL)tdf )
                 * sqrt(1/(REAL)n1 + 1/(REAL)n2) );
  return t;
}  // tstat2()

/*--------------------------------------------------------------------------*/

/* fisher_r2z
 * ----------
 * Fisher r-to-z transform
 */
inline REAL fisher_r2z (REAL r)
{
  if (r <= (REAL)-1) return (REAL)-R2Z_MAX;
  if (r >= (REAL)+1) return (REAL)+R2Z_MAX;
  return (REAL)atanh(r);              // compute arcus tangens hyperbolicus
}  // fisher_r2z()

#endif  // #ifndef STATS_H
