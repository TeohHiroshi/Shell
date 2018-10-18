/*****************************************************************************/
/*                                                  ###                      */
/*       #####          ###    ###                  ###  CREATE: 2011-11-23  */
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
/*  >>>>>>>>>>>>>>>>>>>> CrHack E 分度温度转毫伏函数库 <<<<<<<<<<<<<<<<<<<<  */
/*  =======================================================================  */
/*****************************************************************************/

#include "phylib.h"

/* -270 - 0 (摄氏度) */
#define N_COE1  14
static const double _rom_ s_coe1[N_COE1] =
{
     0.000000000000E+00,  0.586655087080E-01,
     0.454109771240E-04, -0.779980486860E-06,
    -0.258001608430E-07, -0.594525830570E-09,
    -0.932140586670E-11, -0.102876055340E-12,
    -0.803701236210E-15, -0.439794973910E-17,
    -0.164147763550E-19, -0.396736195160E-22,
    -0.558273287210E-25, -0.346578420130E-28,
};

/* 0 - 1000 (摄氏度) */
#define N_COE2  11
static const double _rom_ s_coe2[N_COE2] =
{
     0.000000000000E+00,  0.586655087100E-01,
     0.450322755820E-04,  0.289084072120E-07,
    -0.330568966520E-09,  0.650244032700E-12,
    -0.191974955040E-15, -0.125366004970E-17,
     0.214892175690E-20, -0.143880417820E-23,
     0.359608994810E-27,
};

/*
=======================================
    E 分度温度转毫伏
=======================================
*/
CR_API double
type_e_t2mv (
  __CR_IN__ double  t
    )
{
    double  mv;
    ufast_t ii;

    if (t < -270.0 || t > 1000.0)
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
