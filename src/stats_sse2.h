/*----------------------------------------------------------------------------
  File    : stats_sse2.h
  Contents: statistical functions (SSE2-based implementations)
  Author  : Kristian Loewe
----------------------------------------------------------------------------*/
#ifndef STATS_SSE2_H
#define STATS_SSE2_H

#include <assert.h>
#include <math.h>
#include "dot_sse2.h"

#ifndef __SSE2__
#  error "SSE2 is not enabled"
#endif

#include <emmintrin.h>

// alignment check
#include <stdint.h>
#define is_aligned(POINTER, BYTE_COUNT) \
  (((uintptr_t)(const void *)(POINTER)) % (BYTE_COUNT) == 0)

// horizontal sum variant
#ifdef HORZSUM_SSE3
#  ifdef __SSE3__
#    include <pmmintrin.h>
#  else
#    error "HORZSUM_SSE3 requires SSE3."
#  endif
#endif

/*----------------------------------------------------------------------------
  Function Prototypes
----------------------------------------------------------------------------*/
inline float  ssum_sse2    (const float  *a, int n);
inline float  smean_sse2   (const float  *a, int n);
inline float  svar_sse2    (const float  *a, int n);
inline float  svarm_sse2   (const float  *a, int n, float m);
inline float  svar0_sse2   (const float  *a, int n);
inline float  sstd_sse2    (const float  *a, int n);
inline float  ststat2_sse2 (const float *x1, const float *x2, int n1, int n2);

/*----------------------------------------------------------------------------
  Inline Functions
----------------------------------------------------------------------------*/

/* ssum_sse2
 * ---------
 * compute the sum (single precision; SSE2 implementation)
 */
inline float ssum_sse2 (const float *a, int n)
{
  assert(a && (n > 0));

  // initialize total sum
  float s = 0.0f;

  // add up to 3 values without SIMD to achieve alignment
  int aligned = is_aligned(a, 16);
  if (!aligned) {
    int k = 0;
    while (!aligned) {
      s += (*a);
      n--; a++;
      aligned = is_aligned(a, 16);
      if (aligned || (++k > 2) || (n == 0))
        break;
    }
  }

  // initialize 4 sums
  __m128 s4 = _mm_setzero_ps();

  // in each iteration, add 1 value to each of the 4 sums in parallel
  if (is_aligned(a, 16))
    for (int k = 0, nq = 4*(n/4); k < nq; k += 4)
      s4 = _mm_add_ps(s4, _mm_load_ps(a+k));
  else
    for (int k = 0, nq = 4*(n/4); k < nq; k += 4)
      s4 = _mm_add_ps(s4, _mm_loadu_ps(a+k));

  // compute horizontal sum
  #ifdef HORZSUM_SSE3
  s4 = _mm_hadd_ps(s4,s4);
  s4 = _mm_hadd_ps(s4,s4);
  #else
  s4 = _mm_add_ps(s4, _mm_movehl_ps(s4, s4));
  s4 = _mm_add_ss(s4, _mm_shuffle_ps(s4, s4, 1));
  #endif
  s += _mm_cvtss_f32(s4);  // extract horizontal sum from 1st elem.

  // add the remaining values
  for (int k = 4*(n/4); k < n; k++)
    s += a[k];

  return s;
}  // ssum_sse2()

/*--------------------------------------------------------------------------*/

/* smean_sse2
 * ----------
 * compute the sample mean (single precision; SSE2 implementation)
 */
inline float smean_sse2 (const float *a, int n)
{
  assert(a && (n > 0));

  return ssum_sse2(a, n) /(float)n;
}  // smean_sse2()

/*--------------------------------------------------------------------------*/

/* svar0_sse2
 * ----------
 * compute the unbiased sample variance if the mean is 0
 */
inline float svar0_sse2 (const float *a, int n)
{
  assert(a && (n > 0));

  return sdot_sse2(a,a,n) /(float)(n-1);
}  // svar0_sse2()

/*--------------------------------------------------------------------------*/

/* svarm_sse2
 * ----------
 * compute the unbiased sample variance if the mean is m
 */
inline float svarm_sse2 (const float *a, int n, float m)
{
  assert(a && (n > 0));

  // initialize result variable
  float v = 0.0f;

  // add up to 3 values without SIMD to achieve alignment
  int aligned = is_aligned(a, 16);
  if (!aligned) {
    int k = 0;
    while (!aligned) {
      v += ((*a) - m) * ((*a) - m);
      n--; a++;
      aligned = is_aligned(a, 16);
      if (aligned || (++k > 2) || (n == 0))
        break;
    }
  }

  // initialize 4 sums
  __m128 s4 = _mm_setzero_ps();

  __m128 m4 = _mm_set_ps1(m);

  // in each iteration, add 1 value to each of the 4 sums in parallel
  if (is_aligned(a, 16))
    for (int k = 0, nq = 4*(n/4); k < nq; k += 4)
      s4 = _mm_add_ps(s4, _mm_mul_ps(_mm_sub_ps(_mm_load_ps(a+k), m4),
                                     _mm_sub_ps(_mm_load_ps(a+k), m4)));
  else
    for (int k = 0, nq = 4*(n/4); k < nq; k += 4)
      s4 = _mm_add_ps(s4, _mm_mul_ps(_mm_sub_ps(_mm_loadu_ps(a+k), m4),
                                     _mm_sub_ps(_mm_loadu_ps(a+k), m4)));

  // compute horizontal sum
  #ifdef HORZSUM_SSE3
  s4 = _mm_hadd_ps(s4,s4);
  s4 = _mm_hadd_ps(s4,s4);
  #else
  s4 = _mm_add_ps(s4, _mm_movehl_ps(s4, s4));
  s4 = _mm_add_ss(s4, _mm_shuffle_ps(s4, s4, 1));
  #endif
  v += _mm_cvtss_f32(s4);  // extract horizontal sum from 1st elem.

  // add the remaining values
  for (int k = 4*(n/4); k < n; k++)
    v += (a[k] - m) * (a[k] - m);

  return v /= (float)(n-1);
}  // svarm_sse2()

/*--------------------------------------------------------------------------*/

/* svar_sse2
 * ---------
 * compute the unbiased sample variance
 */
inline float svar_sse2 (const float *a, int n)
{
  return svarm_sse2(a, n, smean_sse2(a, n));
}  // svar_sse2()

/*--------------------------------------------------------------------------*/

/* sstd_sse2
 * ---------
 * compute the corrected sample standard deviation
 */
inline float sstd_sse2 (const float *a, int n)
{
  return sqrtf(svar_sse2(a, n));
}  // sstd_sse2()

/*--------------------------------------------------------------------------*/

/* ststat2_sse2
 * ------------
 * compute t statistic
 *   (two independent samples, equal variances)
 */
inline float ststat2_sse2 (const float *x1, const float *x2, int n1, int n2)
{
  int   tdf = n1 + n2 - 2;             // total degrees of freedom
  float m1  = smean_sse2(x1, n1);      // sample means
  float m2  = smean_sse2(x2, n2);
  float v1  = svarm_sse2(x1, n1, m1);  // sample variances
  float v2  = svarm_sse2(x2, n2, m2);
  float t   = (m1 - m2)                // t statistic
             / ( sqrtf( ( (float)(n1-1)*v1 + (float)(n2-1)*v2 ) / (float)tdf )
                 * sqrtf(1/(float)n1 + 1/(float)n2) );
  return t;
}  // ststat2_sse2()

#endif // #ifndef STATS_SSE2_H
