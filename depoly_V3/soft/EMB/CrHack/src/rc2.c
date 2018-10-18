/*****************************************************************************/
/*                                                  ###                      */
/*       #####          ###    ###                  ###  CREATE: 2010-07-06  */
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
/*  >>>>>>>>>>>>>>>>>>>>>> CrHack RC2 加密解密函数库 <<<<<<<<<<<<<<<<<<<<<<  */
/*  =======================================================================  */
/*****************************************************************************/

#include "crypto.h"
#include "morder.h"
#include "memlib.h"

/* RC2 常数表 */
static const byte_t _rom_ s_permute[256] =
{
    217, 120, 249, 196, 25,  221, 181, 237,
    40,  233, 253, 121, 74,  160, 216, 157,
    198, 126, 55,  131, 43,  118, 83,  142,
    98,  76,  100, 136, 68,  139, 251, 162,
    23,  154, 89,  245, 135, 179, 79,  19,
    97,  69,  109, 141, 9,   129, 125, 50,
    189, 143, 64,  235, 134, 183, 123, 11,
    240, 149, 33,  34,  92,  107, 78,  130,
    84,  214, 101, 147, 206, 96,  178, 28,
    115, 86,  192, 20,  167, 140, 241, 220,
    18,  117, 202, 31,  59,  190, 228, 209,
    66,  61,  212, 48,  163, 60,  182, 38,
    111, 191, 14,  218, 70,  105, 7,   87,
    39,  242, 29,  155, 188, 148, 67,  3,
    248, 17,  199, 246, 144, 239, 62,  231,
    6,   195, 213, 47,  200, 102, 30,  215,
    8,   232, 234, 222, 128, 82,  238, 247,
    132, 170, 114, 172, 53,  77,  106, 42,
    150, 26,  210, 113, 90,  21,  73,  116,
    75,  159, 208, 94,  4,   24,  164, 236,
    194, 224, 65,  110, 15,  81,  203, 204,
    36,  145, 175, 80,  161, 244, 112, 57,
    153, 124, 58,  133, 35,  184, 180, 122,
    252, 2,   54,  91,  37,  85,  151, 49,
    45,  93,  250, 152, 227, 138, 146, 174,
    5,   223, 41,  16,  103, 108, 186, 201,
    211, 0,   230, 207, 225, 158, 168, 44,
    99,  22,  1,   63,  88,  226, 137, 169,
    13,  56,  52,  27,  171, 51,  255, 176,
    187, 72,  12,  95,  185, 177, 205, 46,
    197, 243, 219, 71,  229, 165, 156, 119,
    10,  166, 32,  104, 254, 127, 193, 173,
};

/*
=======================================
    RC2 设置密钥
=======================================
*/
CR_API void_t
crypto_rc2_key (
  __CR_OT__ sRC2*           ctx,
  __CR_IN__ const void_t*   key,
  __CR_IN__ leng_t          keylen,
  __CR_IN__ uint_t          bits
    )
{
    uint_t  idx;
    byte_t  xxx, *xkey;

    if (keylen > 128) {
        keylen = 128;
    }
    else
    if (keylen == 0) {
        key = "";
        keylen = 1;
        bits = 8;
    }
    if (bits == 0 || bits > 1024)
        bits = (uint_t)(keylen * 8);
    mem_cpy(ctx->xkey, key, keylen);
    xkey = (byte_t*)(ctx->xkey);

    if (keylen < 128)
    {
        idx = 0;
        xxx = xkey[keylen - 1];
        do {
            xxx = s_permute[(xxx + xkey[idx++]) & 255];
            xkey[keylen++] = xxx;
        }
        while (keylen < 128);
    }
    keylen = (bits + 7) >> 3;
    idx = (uint_t)(128 - keylen);
    xxx = s_permute[xkey[idx] & (255 >> (7 & (0 - bits)))];
    xkey[idx] = xxx;
    while (idx-- != 0) {
        xxx = s_permute[xxx ^ xkey[idx + keylen]];
        xkey[idx] = xxx;
    }

#if defined(_CR_ORDER_BE_)
    idx = 63;
    do {
        ctx->xkey[idx] = xchg_int16u(ctx->xkey[idx]);
    }
    while (idx-- != 0);
#endif
}

/*
=======================================
    RC2 加密
=======================================
*/
CR_API void_t
crypto_rc2_enc (
  __CR_IN__ const sRC2*     ctx,
  __CR_OT__ byte_t          dst[8],
  __CR_IN__ const byte_t    src[8]
    )
{
    uint_t  x76, x54, x32, x10, idx;

    x76 = (uint_t)(src[7] << 8) | src[6];
    x54 = (uint_t)(src[5] << 8) | src[4];
    x32 = (uint_t)(src[3] << 8) | src[2];
    x10 = (uint_t)(src[1] << 8) | src[0];

    for (idx = 0; idx < 16; idx++)
    {
        x10 += (x32 & ~x76) + (x54 & x76) + ctx->xkey[4 * idx + 0];
        x10  = (x10 << 1) + ((x10 >> 15) &  1);
        x32 += (x54 & ~x10) + (x76 & x10) + ctx->xkey[4 * idx + 1];
        x32  = (x32 << 2) + ((x32 >> 14) &  3);
        x54 += (x76 & ~x32) + (x10 & x32) + ctx->xkey[4 * idx + 2];
        x54  = (x54 << 3) + ((x54 >> 13) &  7);
        x76 += (x10 & ~x54) + (x32 & x54) + ctx->xkey[4 * idx + 3];
        x76  = (x76 << 5) + ((x76 >> 11) & 31);

        if (idx == 4 || idx == 10) {
            x10 += ctx->xkey[x76 & 63];
            x32 += ctx->xkey[x10 & 63];
            x54 += ctx->xkey[x32 & 63];
            x76 += ctx->xkey[x54 & 63];
        }
    }
    dst[0] = (byte_t)(x10);
    dst[1] = (byte_t)(x10 >> 8);
    dst[2] = (byte_t)(x32);
    dst[3] = (byte_t)(x32 >> 8);
    dst[4] = (byte_t)(x54);
    dst[5] = (byte_t)(x54 >> 8);
    dst[6] = (byte_t)(x76);
    dst[7] = (byte_t)(x76 >> 8);
}

/*
=======================================
    RC2 解密
=======================================
*/
CR_API void_t
crypto_rc2_dec (
  __CR_IN__ const sRC2*     ctx,
  __CR_OT__ byte_t          dst[8],
  __CR_IN__ const byte_t    src[8]
    )
{
    uint_t  x76, x54, x32, x10, idx;

    x76 = (uint_t)(src[7] << 8) | src[6];
    x54 = (uint_t)(src[5] << 8) | src[4];
    x32 = (uint_t)(src[3] << 8) | src[2];
    x10 = (uint_t)(src[1] << 8) | src[0];

    idx = 15;
    do
    {
        x76 &= 65535;
        x76  = (x76 << 11) + (x76 >> 5);
        x76 -= (x10 & ~x54) + (x32 & x54) + ctx->xkey[4 * idx + 3];
        x54 &= 65535;
        x54  = (x54 << 13) + (x54 >> 3);
        x54 -= (x76 & ~x32) + (x10 & x32) + ctx->xkey[4 * idx + 2];
        x32 &= 65535;
        x32  = (x32 << 14) + (x32 >> 2);
        x32 -= (x54 & ~x10) + (x76 & x10) + ctx->xkey[4 * idx + 1];
        x10 &= 65535;
        x10  = (x10 << 15) + (x10 >> 1);
        x10 -= (x32 & ~x76) + (x54 & x76) + ctx->xkey[4 * idx + 0];

        if (idx == 5 || idx == 11) {
            x76 -= ctx->xkey[x54 & 63];
            x54 -= ctx->xkey[x32 & 63];
            x32 -= ctx->xkey[x10 & 63];
            x10 -= ctx->xkey[x76 & 63];
        }
    } while (idx-- != 0);

    dst[0] = (byte_t)(x10);
    dst[1] = (byte_t)(x10 >> 8);
    dst[2] = (byte_t)(x32);
    dst[3] = (byte_t)(x32 >> 8);
    dst[4] = (byte_t)(x54);
    dst[5] = (byte_t)(x54 >> 8);
    dst[6] = (byte_t)(x76);
    dst[7] = (byte_t)(x76 >> 8);
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
