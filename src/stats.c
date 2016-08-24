/*----------------------------------------------------------------------------
  File    : stats.c
  Contents: statistical functions
  Author  : Kristian Loewe, Christian Borgelt
----------------------------------------------------------------------------*/
#include "stats.h"

/*----------------------------------------------------------------------------
  Functions
----------------------------------------------------------------------------*/

/* mean
 * ----
 * compute the sample mean
 */
extern REAL mean (REAL* data, int n);

/* varm
 * ----
 * compute the unbiased sample variance relative to the given mean m
 */
extern REAL varm (REAL* data, int n, REAL m);

/* var
 * ---
 * compute the unbiased sample variance
 */
extern REAL var (REAL *data, int n);

/* std
 * ---
 * compute the corrected sample standard deviation
 */
extern REAL std (REAL *data, int n);

/* tstat2
 * -----
 * compute t statistic
 *   (two independent samples, equal variances)
 */
extern REAL tstat2 (REAL *x1, REAL *x2, int n1, int n2);

/* fisher_r2z
 * ----------
 * Fisher r-to-z transform
 */
extern REAL fisher_r2z (REAL r);
