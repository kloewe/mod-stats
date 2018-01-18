/*----------------------------------------------------------------------------
  File    : stats_real.c
  Contents: this file is to be included from stats.c
  Author  : Kristian Loewe
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  Function Prototypes
----------------------------------------------------------------------------*/
extern REAL sum     (const REAL *a, int n);
extern REAL mean    (const REAL *a, int n);
extern REAL var     (const REAL *a, int n);
extern REAL varm    (const REAL *a, int n, REAL m);
extern REAL var0    (const REAL *a, int n);
extern REAL std     (const REAL *a, int n);
extern REAL tstat   (const REAL *a, int n);
extern REAL tstat2  (const REAL *x1, const REAL *x2, int n1, int n2);
extern tres welcht  (const REAL *x1, const REAL *x2, int n1, int n2);
extern REAL pairedt (const REAL *x1, const REAL *x2, int n);
extern REAL didt    (const REAL *x1, const REAL *x2,
                     const REAL *y1, const REAL *y2, int nx, int ny);
extern REAL fr2z    (const REAL r);

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
