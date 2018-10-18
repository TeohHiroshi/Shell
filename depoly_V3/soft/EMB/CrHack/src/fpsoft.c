/*****************************************************************************/
/*                                                  ###                      */
/*       #####          ###    ###                  ###  CREATE: 2013-05-31  */
/*     #######          ###    ###      [CORE]      ###  ~~~~~~~~~~~~~~~~~~  */
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
/*  >>>>>>>>>>>>>>>>>>>>>>>> CrHack 软件浮点函数库 <<<<<<<<<<<<<<<<<<<<<<<<  */
/*  =======================================================================  */
/*****************************************************************************/

#include "defs.h"

/*
=======================================
    32位浮点四舍五入取整
=======================================
*/
CR_API sint_t
fp32_to_sint (
  __CR_IN__ fp32_t  value
    )
{
    if (value < 0.0f)
        value -= 0.5f;
    else
    if (value > 0.0f)
        value += 0.5f;
    return ((sint_t)value);
}

/*
=======================================
    32位浮点转16位浮点
=======================================
*/
CR_API fp16_t
fp32_to_fp16 (
  __CR_IN__ fp32_t  value
    )
{
    int32s  ss = ((cvt_f2i(value) >> 16) & 0x00008000UL);
    int32s  ee = ((cvt_f2i(value) >> 23) & 0x000000FFUL) - (127 - 15);
    int32s  mm = ((cvt_f2i(value) >>  0) & 0x007FFFFFUL);

    if (ee <= 0) {
        if (ee < -10)
            return (0);
        mm = (mm | 0x00800000UL) >> (1 - ee);
        if ((mm & 0x00001000UL) != 0)
            mm += 0x00002000UL;
        return ((fp16_t)(ss | (mm >> 13)));
    }

    if (ee == 0xFF - (127 - 15)) {
        if (mm == 0)
            return ((fp16_t)(ss | 0x7C00));
        mm >>= 13;
        return ((fp16_t)(ss | 0x7C00 | mm | (mm == 0)));
    }

    if ((mm & 0x00001000UL) != 0) {
        mm += 0x00002000UL;
        if ((mm & 0x00800000UL) != 0) {
            ee++;
            mm = 0;
        }
    }

    if (ee > 30)
    {
        /* 制造浮点溢出异常 */
        for (value = 1e10, mm = 10; mm != 0; mm--)
            value *= value;
        return ((fp16_t)(ss | 0x7C00));
    }
    return ((fp16_t)(ss | (ee << 10) | (mm >> 13)));
}

/*
=======================================
    16位浮点转32位浮点
=======================================
*/
CR_API fp32_t
fp16_to_fp32 (
  __CR_IN__ fp16_t  value
    )
{
    int32s  ss = (value >> 15) & 0x00000001UL;
    int32s  ee = (value >> 10) & 0x0000001FUL;
    int32s  mm = (value >>  0) & 0x000003FFUL;

    if (ee == 0) {
        if (mm == 0) {
            ss <<= 31;
            return (cvt_i2f(ss));
        }

        while ((mm & 0x00000400UL) == 0) {
            ee--;
            mm <<= 1;
        }
        ee++;
        mm &= ~0x00000400UL;
    }
    else
    if (ee == 31) {
        if (mm == 0) {
            ss = (ss << 31) | 0x7F800000UL;
            return (cvt_i2f(ss));
        }
        ss = (ss << 31) | 0x7F800000UL | (mm << 13);
        return (cvt_i2f(ss));
    }
    ss = (ss << 31) | ((ee + 127 - 15) << 23) | (mm << 13);
    return (cvt_i2f(ss));
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
