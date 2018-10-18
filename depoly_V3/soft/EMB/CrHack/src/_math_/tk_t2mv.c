/*****************************************************************************/
/*                                                  ###                      */
/*       #####          ###    ###                  ###  CREATE: 2011-11-24  */
/*     #######          ###    ###      [MATH]      ###  ~~~~~~~~~~~~~~~~~~  */
/*    ########          ###    ###                  ###  MODIFY: XXXX-XX-XX  */
/*    ####  ##          ###    ###                  ###  ~~~~~~~~~~~~~~~~~~  */
/*   ###       ### ###  ###    ###    ####    ####  ###   ##  +-----------+  */
/*  ####       ######## ##########  #######  ###### ###  ###  |  A NEW C  |  */
/*  ###        ######## ########## ########  ###### ### ###   | FRAMEWORK |  */
/*  ###     ## #### ### ########## ###  ### ###     ######    |  FOR ALL  |  */
/*  ####   ### ###  ### ###    ### ###  ### ###     ######    | PLATFORMS |  */
/*  ########## ###      ###    ### ######## ####### #######   |  AND ALL  |  */
/*   #######   ###      ###    ### ########  ###### ###  ###  | COMPILERS |  */
/*    #####    ###      ###    ###  #### ##   ####  ###   ##  +-----------+  */
/*  =======================================================================  */
/*  >>>>>>>>>>>>>>>>>>>> CrHack K 分度温度转毫伏函数库 <<<<<<<<<<<<<<<<<<<<  */
/*  =======================================================================  */
/*****************************************************************************/

#include "phylib.h"

#ifndef _CR_NO_STDC_
    #if defined(_CR_OS_ANDROID_) && (ANDROID_API <= 19)
        #if defined(__pure2)
            #undef  __pure2
        #endif
    #endif
    #include <math.h>
#endif

/* -270 - 0 (摄氏度) */
#define N_COE1  11
static const double _rom_ s_coe1[N_COE1] =
{
     0.000000000000E+00,  0.394501280250E-01,
     0.236223735980E-04, -0.328589067840E-06,
    -0.499048287770E-08, -0.675090591730E-10,
    -0.574103274280E-12, -0.310888728940E-14,
    -0.104516093650E-16, -0.198892668780E-19,
    -0.163226974860E-22,
};

/* 0 - 1372 (摄氏度) */
#define N_COE2  10
static const double _rom_ s_coe2[N_COE2] =
{
    -0.176004136860E-01,  0.389212049750E-01,
     0.185587700320E-04, -0.994575928740E-07,
     0.318409457190E-09, -0.560728448890E-12,
     0.560750590590E-15, -0.320207200030E-18,
     0.971511471520E-22, -0.121047212750E-25,
};

/*
=======================================
    K 分度温度转毫伏
=======================================
*/
CR_API double
type_k_t2mv (
  __CR_IN__ double  t
    )
{
    double  mv;
    double  xx;
    ufast_t ii;

    if (t < -270.0 || t > 1372.0)
        return (CR_PHY_INV);
    if (t < 0.0) {
        mv = s_coe1[N_COE1 - 1] * t;
        for (ii = N_COE1 - 2; ii != 0; ii--)
            mv = (mv + s_coe1[ii]) * t;
        mv += s_coe1[0];
    }
    else {
        mv = s_coe2[N_COE2 - 1] * t;
        for (ii = N_COE2 - 2; ii != 0; ii--)
            mv = (mv + s_coe2[ii]) * t;
        mv += s_coe2[0];
        xx  = t - 0.1269686E+03;
        xx *= xx;
        mv += 0.1185976E+00 * exp(-0.1183432E-03 * xx);
    }
    return (mv);
}

/*****************************************************************************/
/* _________________________________________________________________________ */
/* uBMAzRBoAKAHaACQD6FoAIAPqbgA/7rIA+5CM9uKw8D4Au7u7mSIJ0t18mYz0mYz9rAQZCgHc */
/* wRIZIgHZovGBXUAZg+v0GbB+gRmgcJ7BAAAisIlAwB1Av7LSHUC/s9IdQL+w0h1Av7HZkZmgf */
/* 4JLgIAdb262gPsqAh0+zP/uQB9ZYsFZYktq+L3sMi/AAK7gAKJAUtLdfq5IANXvT8BiQzfBIv */
/* FLaAAweAEmff53wb+Adjx3kQE2xwy5Io8ithkigcFgACJBN8E3sneNvwB2xyLHDkdfA2JHSyA */
/* adtAAQPdZYgHR0dNdbZfSYP5UHWr/kQEtAHNFg+Eef/DWAKgDw== |~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ >>> END OF FILE <<< */
/*****************************************************************************/
