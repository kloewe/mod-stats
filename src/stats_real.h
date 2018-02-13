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

// one sample
inline REAL sum       (const REAL *a, int n);
inline REAL mean      (const REAL *a, int n);
inline REAL var       (const REAL *a, int n);
inline REAL varm      (const REAL *a, int n, REAL m);
inline REAL var0      (const REAL *a, int n);
inline REAL std       (const REAL *a, int n);
inline REAL tstat     (const REAL *a, int n);

// two samples
inline REAL mdiff     (const REAL *x1, const REAL *x2, int n1, int n2);
inline REAL tstat2    (const REAL *x1, const REAL *x2, int n1, int n2);
inline tres welcht    (const REAL *x1, const REAL *x2, int n1, int n2);
inline REAL pairedt   (const REAL *x1, const REAL *x2, int n);

// difference-in-differences
inline REAL didt      (const REAL *x1, const REAL *x2,
                       const REAL *y1, const REAL *y2, int nx, int ny);

// wrappers (same signature across functions)
inline REAL sum_w     (const REAL *a, const int *n);
inline REAL mean_w    (const REAL *a, const int *n);
inline REAL var_w     (const REAL *a, const int *n);
inline REAL var0_w    (const REAL *a, const int *n);
inline REAL std_w     (const REAL *a, const int *n);
inline REAL tstat_w   (const REAL *a, const int *n);
inline REAL mdiff_w   (const REAL *a, const int *n);
inline REAL tstat2_w  (const REAL *a, const int *n);
inline REAL pairedt_w (const REAL *a, const int *n);
inline REAL didt_w    (const REAL *a, const int *n);

// Fisher r-to-z transform
inline REAL fr2z      (const REAL r);

/*----------------------------------------------------------------------------
  Inline Functions
----------------------------------------------------------------------------*/

inline REAL sum (const REAL *a, int n)
{
  assert(a && (n > 0));

  return (*sum_ptr)(a,n);
}  // sum()

/*--------------------------------------------------------------------------*/

inline REAL sum_w (const REAL *a, const int *n)
{
  assert(a && n);

  return sum(a, *n);
}  // sum_w()

/*--------------------------------------------------------------------------*/

inline REAL mean (const REAL *a, int n)
{
  assert(a && (n > 0));

  return sum(a, n) /(REAL)n;
}  // mean()

/*--------------------------------------------------------------------------*/

inline REAL mean_w (const REAL *a, const int *n)
{
  assert(a && n);

  return mean(a, *n);
}  // mean_w()

/*--------------------------------------------------------------------------*/

inline REAL var (const REAL *a, int n)
{
  assert(a && (n > 1));

  return varm(a, n, mean(a, n));
}  // var()

/*--------------------------------------------------------------------------*/

inline REAL var_w (const REAL *a, const int *n)
{
  assert(a && n);

  return var(a, *n);
}  // var_w()

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

inline REAL var0_w (const REAL *a, const int *n)
{
  assert(a && n);

  return var0(a, *n);
}  // var0_w()

/*--------------------------------------------------------------------------*/

inline REAL std (const REAL *a, int n)
{
  assert(a && (n > 1));

  return sqrt(var(a, n));
}  // std()

/*--------------------------------------------------------------------------*/

inline REAL std_w (const REAL *a, const int *n)
{
  assert(a && n);

  return std(a, *n);
}  // std_w()

/*--------------------------------------------------------------------------*/

inline REAL tstat (const REAL *a, int n)
{
  assert(a && (n > 1));

  REAL m = mean(a, n);               // sample mean
  REAL s = sqrt(varm(a, n, m));      // sample standard deviation
  return m / (s / sqrt((REAL)n));
}  // tstat()

/*--------------------------------------------------------------------------*/

inline REAL tstat_w (const REAL *a, const int *n)
{
  assert(a && n);

  return tstat(a, *n);
}  // tstat_w()

/*--------------------------------------------------------------------------*/

// mean difference
inline REAL mdiff (const REAL *x1, const REAL *x2, int n1, int n2)
{
  assert(x1 && x2 && (n1 > 0) && (n2 > 0));

  return mean(x1, n1) - mean(x2, n2);
}  // mdiff()

/*--------------------------------------------------------------------------*/

inline REAL mdiff_w (const REAL *a, const const int *n)
{
  assert(a && n);

  return mdiff(a, a+n[0], n[0], n[1]);
}  // mdiff_w()

/*--------------------------------------------------------------------------*/

inline REAL tstat2 (const REAL *x1, const REAL *x2, int n1, int n2)
{
  assert(x1 && x2 && (n1 > 1) && (n2 > 1));

  REAL m1 = mean(x1, n1);            // sample means
  REAL m2 = mean(x2, n2);
  REAL md = m1 - m2;                 // mean difference = diff. of means
  REAL v1 = varm(x1, n1, m1);        // sample variances
  REAL v2 = varm(x2, n2, m2);
  REAL df = (REAL)n1 + (REAL)n2 - 2; // degrees of freedom

  return md / ( sqrt( ( (REAL)(n1-1)*v1 + (REAL)(n2-1)*v2 ) / df )
                * sqrt(1/(REAL)n1 + 1/(REAL)n2) );
}  // tstat2()

/*--------------------------------------------------------------------------*/

inline REAL tstat2_w (const REAL *a, const int *n)
{
  assert(a && n);

  return tstat2(a, a+n[0], n[0], n[1]);
}  // tstat2_w()

/*--------------------------------------------------------------------------*/

inline tres welcht (const REAL *x1, const REAL *x2, int n1, int n2)
{
  assert(x1 && x2 && (n1 > 1) && (n2 > 1));

  REAL m1 = mean(x1, n1);            // sample means
  REAL m2 = mean(x2, n2);
  REAL md = m1 - m2;                 // mean difference = diff. of means
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
  REAL md = mdiff(x1, x2, n, n);     // mean difference = diff. of means
  REAL sd = 0;                       // standard dev. of the differences
  for (int i = 0; i < n; i++)
    sd += ((x1[i] - x2[i]) - md) * ((x1[i] - x2[i]) - md);
  sd = sqrt(sd/(REAL)(n - 1));
  return md / (sd / sqrt((REAL)n));
#else
  REAL *diff = (REAL *) malloc((size_t)n *sizeof(REAL));
  // TODO if (!diff) ...
  for (int i = 0; i < n; i++)
    diff[i] = x1[i] - x2[i];
  REAL t = tstat(diff, n);
  free(diff);
  return t;
#endif
}  // pairedt()

/*--------------------------------------------------------------------------*/

inline REAL pairedt_w (const REAL *a, const int *n)
{
  assert(a && n);

  return pairedt(a, a+n[0], n[0]);
}  // pairedt_w()

/*--------------------------------------------------------------------------*/

inline REAL didt (const REAL *x1, const REAL *x2,
                  const REAL *y1, const REAL *y2, int nx, int ny)
{
  assert(x1 && x2 && y1 && y2 && (nx > 1) && (ny > 1));

  REAL *diffx = (REAL *) malloc((size_t)(nx+ny) *sizeof(REAL));
  // TODO if (!diffx) ...
  for (int i = 0; i < nx; i++)
    diffx[i] = x2[i] - x1[i];
  REAL mdx = mean(diffx, nx);
  REAL vdx = varm(diffx, nx, mdx);

  REAL *diffy = diffx + nx;
  for (int i = 0; i < ny; i++)
    diffy[i] = y2[i] - y1[i];
  REAL mdy = mean(diffy, ny);
  REAL vdy = varm(diffy, ny, mdy);

  free(diffx);

  REAL md = mdx - mdy;

  REAL df = (REAL)nx + (REAL)ny - 2;
  return md / ( sqrt( ( (REAL)(nx-1)*vdx + (REAL)(ny-1)*vdy ) / df )
                * sqrt(1/(REAL)nx + 1/(REAL)ny) );
}  // didt()

/*--------------------------------------------------------------------------*/

inline REAL didt_w (const REAL *a, const int *n)
{
  assert(a && n);

  return didt(a, a+n[0], a+2*n[0], a+2*n[0]+n[1], n[0], n[1]);
}  // didt_w()

/*--------------------------------------------------------------------------*/

inline REAL fr2z (REAL r)
{
  if (r <= (REAL)-1) return (REAL)-R2Z_MAX;
  if (r >= (REAL)+1) return (REAL)+R2Z_MAX;
  return (REAL)atanh(r);             // compute arcus tangens hyperbolicus
}  // fr2z()

#endif  // #ifndef STATS_REAL_H
