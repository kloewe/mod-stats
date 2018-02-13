/*----------------------------------------------------------------------------
  File    : def-or-undef-functions.inc
  Contents: This file is included from within stats.h to add a prefix to
            the function names when compiling stats_real.h twice using
            different defintions of REAL. The goal is to have single and
            double precision versions of these functions. When this file is
            included while REAL is not defined, the definitions used for
            prefixing are being undefined.
  Author  : Kristian Loewe
----------------------------------------------------------------------------*/

#ifdef REAL
#  define float  1
#  define double 2
#  if   REAL == float
#    define sum         ssum
#    define mean        smean
#    define var         svar
#    define varm        svarm
#    define var0        svar0
#    define std         sstd
#    define tstat       ststat
#    define mdiff       smdiff
#    define tstat2      ststat2
#    define welcht      swelcht
#    define pairedt     spairedt
#    define didt        sdidt

#    define sum_w       ssum_w
#    define mean_w      smean_w
#    define var_w       svar_w
#    define var0_w      svar0_w
#    define std_w       sstd_w
#    define tstat_w     ststat_w
#    define mdiff_w     smdiff_w
#    define tstat2_w    ststat2_w
#    define welcht_w    swelcht_w
#    define pairedt_w   spairedt_w
#    define didt_w      sdidt_w

#    define fr2z        sfr2z

#  elif REAL == double
#    define sum         dsum
#    define mean        dmean
#    define var         dvar
#    define varm        dvarm
#    define var0        dvar0
#    define std         dstd
#    define tstat       dtstat
#    define mdiff       dmdiff
#    define tstat2      dtstat2
#    define welcht      dwelcht
#    define pairedt     dpairedt
#    define didt        ddidt

#    define sum_w       dsum_w
#    define mean_w      dmean_w
#    define var_w       dvar_w
#    define var0_w      dvar0_w
#    define std_w       dstd_w
#    define tstat_w     dtstat_w
#    define mdiff_w     dmdiff_w
#    define tstat2_w    dtstat2_w
#    define welcht_w    dwelcht_w
#    define pairedt_w   dpairedt_w
#    define didt_w      ddidt_w

#    define fr2z        dfr2z

#  else
#    error "REAL must be either 'float' or 'double'"
#  endif
#  undef float
#  undef double

#else
#  undef sum
#  undef mean
#  undef var
#  undef varm
#  undef var0
#  undef std
#  undef tstat
#  undef mdiff
#  undef tstat2
#  undef welcht
#  undef pairedt
#  undef didt

#  undef sum_w
#  undef mean_w
#  undef var_w
#  undef var0_w
#  undef std_w
#  undef tstat_w
#  undef mdiff_w
#  undef tstat2_w
#  undef welcht_w
#  undef pairedt_w
#  undef didt_w

#  undef fr2z
#endif
