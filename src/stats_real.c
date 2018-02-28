/*----------------------------------------------------------------------------
  File    : stats_real.c
  Contents: this file is to be included from stats.c
  Author  : Kristian Loewe
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  Function Prototypes
----------------------------------------------------------------------------*/

// one sample
extern REAL sum       (const REAL *a, int n);
extern REAL mean      (const REAL *a, int n);
extern REAL var       (const REAL *a, int n);
extern REAL varm      (const REAL *a, int n, REAL m);
extern REAL var0      (const REAL *a, int n);
extern REAL std       (const REAL *a, int n);
extern REAL tstat     (const REAL *a, int n);

// two samples
extern REAL mdiff     (const REAL *x1, const REAL *x2, int n1, int n2);
extern REAL tstat2    (const REAL *x1, const REAL *x2, int n1, int n2);
extern tres welcht    (const REAL *x1, const REAL *x2, int n1, int n2);
extern REAL pairedt   (const REAL *x1, const REAL *x2, int n);

// difference-in-differences
extern REAL didt      (const REAL *x1, const REAL *x2,
                       const REAL *y1, const REAL *y2, int nx, int ny);

// wrappers (same signature across functions)
extern REAL sum_w     (const REAL *a, const int *n);
extern REAL mean_w    (const REAL *a, const int *n);
extern REAL var_w     (const REAL *a, const int *n);
extern REAL var0_w    (const REAL *a, const int *n);
extern REAL std_w     (const REAL *a, const int *n);
extern REAL tstat_w   (const REAL *a, const int *n);
extern REAL mdiff_w   (const REAL *a, const int *n);
extern REAL tstat2_w  (const REAL *a, const int *n);
extern REAL pairedt_w (const REAL *a, const int *n);
extern REAL didt_w    (const REAL *a, const int *n);

// permutation
extern REAL perm      (const REAL *a, int *n, int ntotal, const int *prm,
                       int np, Func1 *func, REAL *tmp, REAL *s);

// Fisher r-to-z transform
extern REAL fr2z      (const REAL r);

/*----------------------------------------------------------------------------
  Global Variables
----------------------------------------------------------------------------*/
sum_func  *sum_ptr  = &sum_select;
varm_func *varm_ptr = &varm_select;

/*----------------------------------------------------------------------------
  Functions
----------------------------------------------------------------------------*/

REAL sum_select (const REAL *a, int n)
{
  stats_set_impl(STATS_AUTO);
  return (*sum_ptr)(a,n);
}  // sum_select()

/*--------------------------------------------------------------------------*/

REAL varm_select (const REAL *a, int n, REAL m)
{
  stats_set_impl(STATS_AUTO);
  return (*varm_ptr)(a,n,m);
}  // varm_select()
