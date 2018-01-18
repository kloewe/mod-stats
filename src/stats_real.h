/*----------------------------------------------------------------------------
  File    : stats_real.h
  Contents: this file is to be included from stats.h
  Authors : Kristian Loewe
----------------------------------------------------------------------------*/
#ifndef STATS_REAL_H
#define STATS_REAL_H

#include <stdlib.h>
#include <assert.h>

/*----------------------------------------------------------------------------
  Function Prototypes
----------------------------------------------------------------------------*/
inline REAL sum     (const REAL *a, int n);
inline REAL mean    (const REAL *a, int n);
inline REAL var     (const REAL *a, int n);
inline REAL varm    (const REAL *a, int n, REAL m);
inline REAL var0    (const REAL *a, int n);
inline REAL std     (const REAL *a, int n);
inline REAL tstat   (const REAL *a, int n);
inline REAL tstat2  (const REAL *x1, const REAL *x2, int n1, int n2);
inline tres welcht  (const REAL *x1, const REAL *x2, int n1, int n2);
inline REAL pairedt (const REAL *x1, const REAL *x2, int n);
inline REAL didt    (const REAL *x1, const REAL *x2,
                     const REAL *y1, const REAL *y2,
                     int nx, int ny);
inline REAL fr2z    (const REAL r);

/*----------------------------------------------------------------------------
  Inline Functions
----------------------------------------------------------------------------*/

inline REAL sum (const REAL *a, int n)
{
  assert(a && (n > 0));

  return (*sum_ptr)(a,n);
}  // sum()

/*--------------------------------------------------------------------------*/

inline REAL mean (const REAL *a, int n)
{
  assert(a && (n > 0));

  return sum(a, n) /(REAL)n;
}  // mean()

/*--------------------------------------------------------------------------*/

inline REAL var (const REAL *a, int n)
{
  assert(a && (n > 1));

  return varm(a, n, mean(a, n));
}  // var()

/*--------------------------------------------------------------------------*/

inline REAL varm (const REAL *a, int n, REAL m)
{
  assert(a && (n > 1));

  return (*varm_ptr)(a,n,m);
}  // varm()

/*--------------------------------------------------------------------------*/

inline REAL var0 (const REAL *a, int n)
{
  assert(a && (n > 1));

  return dot(a, a, n) /(REAL)(n-1);
}  // var0()

/*--------------------------------------------------------------------------*/

inline REAL std (const REAL *a, int n)
{
  assert(a && (n > 1));

  return sqrt(var(a, n));
}  // std()

/*--------------------------------------------------------------------------*/

inline REAL tstat (const REAL *a, int n)
{
  assert(a && (n > 1));

  REAL m = mean(a, n);               // sample mean
  REAL s = sqrt(varm(a, n, m));      // sample standard deviation
  return m / (s / sqrt((REAL)n));
}  // tstat()

/*--------------------------------------------------------------------------*/

inline REAL tstat2 (const REAL *x1, const REAL *x2, int n1, int n2)
{
  assert(x1 && x2 && (n1 > 1) && (n2 > 1));

  REAL m1 = mean(x1, n1);            // sample means
  REAL m2 = mean(x2, n2);
  REAL md = m1 - m2;                 // mean difference
  REAL v1 = varm(x1, n1, m1);        // sample variances
  REAL v2 = varm(x2, n2, m2);
  REAL df = (REAL)n1 + (REAL)n2 - 2; // degrees of freedom
  return md / ( sqrt( ( (REAL)(n1-1)*v1 + (REAL)(n2-1)*v2 ) / df )
                * sqrt(1/(REAL)n1 + 1/(REAL)n2) );
}  // tstat2()

/*--------------------------------------------------------------------------*/

inline tres welcht (const REAL *x1, const REAL *x2, int n1, int n2)
{
  assert(x1 && x2 && (n1 > 1) && (n2 > 1));

  REAL m1 = mean(x1, n1);            // sample means
  REAL m2 = mean(x2, n2);
  REAL md = m1 - m2;                 // mean difference
  REAL v1 = varm(x1, n1, m1);        // sample variances
  REAL v2 = varm(x2, n2, m2);
  REAL n1f = (REAL)n1;
  REAL n2f = (REAL)n2;
  REAL df = ((v1/n1f + v2/n2f) * (v1/n1f + v2/n2f))
              / ((v1*v1)/(n1f*n1f*(n1f-1)) + (v2*v2)/(n2f*n2f*(n2f-1)));
  tres res = { .t = md / sqrt(v1/n1f + v2/n2f), .df = df };
  return res;
}  // welcht()

/*--------------------------------------------------------------------------*/

inline REAL pairedt (const REAL *x1, const REAL *x2, int n)
{
  assert(x1 && x2 && (n > 1));

#if 0
  REAL m1 = mean(x1, n);             // sample means
  REAL m2 = mean(x2, n);
  REAL md = m1 - m2;                 // mean difference
  REAL sd = 0;                       // standard dev. of the differences
  for (int i = 0; i < n; i++)
    sd += ((x1[i] - x2[i]) - md) * ((x1[i] - x2[i]) - md);
  sd = sqrt(sd/(REAL)(n - 1));
  return md / (sd / sqrtf((REAL)n));
#else
  REAL *diff = (REAL *) malloc((size_t)n *sizeof(REAL));
  for (int i = 0; i < n; i++)
    diff[i] = x1[i] - x2[i];
  REAL t = tstat(diff, n);
  free(diff);
  return t;
#endif
}  // pairedt()

/*--------------------------------------------------------------------------*/

inline REAL didt (const REAL *x1, const REAL *x2,
                  const REAL *y1, const REAL *y2, int nx, int ny)
{
  assert(x1 && x2 && y1 && y2 && (nx > 1) && (ny > 1));

  REAL *diffx = (REAL *) malloc((size_t)nx *sizeof(REAL));
  for (int i = 0; i < nx; i++)
    diffx[i] = x2[i] - x1[i];
  REAL mdx = mean(diffx, nx);
  REAL vdx = varm(diffx, nx, mdx);
  free(diffx);

  REAL *diffy = (REAL *) malloc((size_t)ny *sizeof(REAL));
  for (int i = 0; i < ny; i++)
    diffy[i] = y2[i] - y1[i];
  REAL mdy = mean(diffy, ny);
  REAL vdy = varm(diffy, ny, mdy);
  free(diffy);

  REAL md = mdx - mdy;

  REAL df = (REAL)nx + (REAL)ny - 2;
  return md / ( sqrt( ( (REAL)(nx-1)*vdx + (REAL)(ny-1)*vdy ) / df )
                * sqrt(1/(REAL)nx + 1/(REAL)ny) );
}  // didt()

/*--------------------------------------------------------------------------*/

inline REAL fr2z (REAL r)
{
  if (r <= (REAL)-1) return (REAL)-R2Z_MAX;
  if (r >= (REAL)+1) return (REAL)+R2Z_MAX;
  return (REAL)atanh(r);             // compute arcus tangens hyperbolicus
}  // fr2z()

#endif  // #ifndef STATS_REAL_H
