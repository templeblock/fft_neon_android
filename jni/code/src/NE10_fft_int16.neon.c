/*
 * NE10 Library : dsp/NE10_fft_int16.neon.c
 */

//#include <arm_neon.h>

//#include "NE10_types.h"
//#include "NE10_macros.h"
//#include "NE10_fft.h"
#include "para.h"
#include "NE10_fft_int16.c.neon.h"
static inline void ne10_fft4_forward_int16_unscaled (ne10_fft_cpx_int16_t * Fout,
        ne10_fft_cpx_int16_t * Fin)

{
    ne10_int16_t s0_r, s0_i, s1_r, s1_i, s2_r, s2_i;
    ne10_int16_t tmp_r, tmp_i;

    s2_r = Fin[0].r - Fin[2].r;
    s2_i = Fin[0].i - Fin[2].i;

    tmp_r = Fin[0].r + Fin[2].r;
    tmp_i = Fin[0].i + Fin[2].i;

    s0_r = Fin[1].r + Fin[3].r;
    s0_i = Fin[1].i + Fin[3].i;

    s1_r = Fin[1].r - Fin[3].r;
    s1_i = Fin[1].i - Fin[3].i;
    Fout[2].r = tmp_r - s0_r;
    Fout[2].i = tmp_i - s0_i;
    Fout[0].r = tmp_r + s0_r;
    Fout[0].i = tmp_i + s0_i;

    Fout[1].r = s2_r + s1_i;
    Fout[1].i = s2_i - s1_r;
    Fout[3].r = s2_r - s1_i;
    Fout[3].i = s2_i + s1_r;
}

static inline void ne10_fft4_backward_int16_unscaled (ne10_fft_cpx_int16_t * Fout,
        ne10_fft_cpx_int16_t * Fin)

{
    ne10_int16_t s0_r, s0_i, s1_r, s1_i, s2_r, s2_i;
    ne10_int16_t tmp_r, tmp_i;

    s2_r = Fin[0].r - Fin[2].r;
    s2_i = Fin[0].i - Fin[2].i;

    tmp_r = Fin[0].r + Fin[2].r;
    tmp_i = Fin[0].i + Fin[2].i;

    s0_r = Fin[1].r + Fin[3].r;
    s0_i = Fin[1].i + Fin[3].i;

    s1_r = Fin[1].r - Fin[3].r;
    s1_i = Fin[1].i - Fin[3].i;

    Fout[2].r = tmp_r - s0_r;
    Fout[2].i = tmp_i - s0_i;
    Fout[0].r = tmp_r + s0_r;
    Fout[0].i = tmp_i + s0_i;

    Fout[1].r = s2_r - s1_i;
    Fout[1].i = s2_i + s1_r;
    Fout[3].r = s2_r + s1_i;
    Fout[3].i = s2_i - s1_r;
}
static inline void ne10_fft4_forward_int16_scaled (ne10_fft_cpx_int16_t * Fout,
        ne10_fft_cpx_int16_t * Fin)

{
    ne10_int16_t s0_r, s0_i, s1_r, s1_i, s2_r, s2_i;
    ne10_int16_t tmp_r, tmp_i;

    s2_r = (Fin[0].r - Fin[2].r) >> 2;
    s2_i = (Fin[0].i - Fin[2].i) >> 2;
    tmp_r = (Fin[0].r + Fin[2].r) >> 2;
    tmp_i = (Fin[0].i + Fin[2].i) >> 2;

    s0_r = (Fin[1].r + Fin[3].r) >> 2;
    s0_i = (Fin[1].i + Fin[3].i) >> 2;
    s1_r = (Fin[1].r - Fin[3].r) >> 2;
    s1_i = (Fin[1].i - Fin[3].i) >> 2;

    Fout[2].r = tmp_r - s0_r;
    Fout[2].i = tmp_i - s0_i;
    Fout[0].r = tmp_r + s0_r;
    Fout[0].i = tmp_i + s0_i;

    Fout[1].r = s2_r + s1_i;
    Fout[1].i = s2_i - s1_r;
    Fout[3].r = s2_r - s1_i;
    Fout[3].i = s2_i + s1_r;
}

static inline void ne10_fft4_backward_int16_scaled (ne10_fft_cpx_int16_t * Fout,
        ne10_fft_cpx_int16_t * Fin)

{
    ne10_int16_t s0_r, s0_i, s1_r, s1_i, s2_r, s2_i;
    ne10_int16_t tmp_r, tmp_i;

    s2_r = (Fin[0].r - Fin[2].r) >> 2;
    s2_i = (Fin[0].i - Fin[2].i) >> 2;
    tmp_r = (Fin[0].r + Fin[2].r) >> 2;
    tmp_i = (Fin[0].i + Fin[2].i) >> 2;

    s0_r = (Fin[1].r + Fin[3].r) >> 2;
    s0_i = (Fin[1].i + Fin[3].i) >> 2;
    s1_r = (Fin[1].r - Fin[3].r) >> 2;
    s1_i = (Fin[1].i - Fin[3].i) >> 2;

    Fout[2].r = tmp_r - s0_r;
    Fout[2].i = tmp_i - s0_i;
    Fout[0].r = tmp_r + s0_r;
    Fout[0].i = tmp_i + s0_i;

    Fout[1].r = s2_r - s1_i;
    Fout[1].i = s2_i + s1_r;
    Fout[3].r = s2_r + s1_i;
    Fout[3].i = s2_i - s1_r;
}
static inline void ne10_fft8_forward_int16_unscaled (ne10_fft_cpx_int16_t * Fout,
        ne10_fft_cpx_int16_t * Fin)

{
    ne10_int16_t s0_r, s0_i, s1_r, s1_i, s2_r, s2_i, s3_r, s3_i, s4_r, s4_i, s5_r, s5_i, s6_r, s6_i, s7_r, s7_i;
    ne10_int16_t t0_r, t0_i, t1_r, t1_i, t2_r, t2_i, t3_r, t3_i, t4_r, t4_i, t5_r, t5_i;
    const ne10_int16_t TW_81 = 23169;

    s0_r = Fin[0].r + Fin[4].r;
    s0_i = Fin[0].i + Fin[4].i;
    s1_r = Fin[0].r - Fin[4].r;
    s1_i = Fin[0].i - Fin[4].i;
    s2_r = Fin[1].r + Fin[5].r;
    s2_i = Fin[1].i + Fin[5].i;
    s3_r = Fin[1].r - Fin[5].r;
    s3_i = Fin[1].i - Fin[5].i;
    s4_r = Fin[2].r + Fin[6].r;
    s4_i = Fin[2].i + Fin[6].i;
    s5_r = Fin[2].r - Fin[6].r;
    s5_i = Fin[2].i - Fin[6].i;
    s6_r = Fin[3].r + Fin[7].r;
    s6_i = Fin[3].i + Fin[7].i;
    s7_r = Fin[3].r - Fin[7].r;
    s7_i = Fin[3].i - Fin[7].i;

    t0_r = s0_r - s4_r;
    t0_i = s0_i - s4_i;
    t1_r = s0_r + s4_r;
    t1_i = s0_i + s4_i;
    t2_r = s2_r + s6_r;
    t2_i = s2_i + s6_i;
    t3_r = s2_r - s6_r;
    t3_i = s2_i - s6_i;
    Fout[0].r = t1_r + t2_r;
    Fout[0].i = t1_i + t2_i;
    Fout[4].r = t1_r - t2_r;
    Fout[4].i = t1_i - t2_i;
    Fout[2].r = t0_r + t3_i;
    Fout[2].i = t0_i - t3_r;
    Fout[6].r = t0_r - t3_i;
    Fout[6].i = t0_i + t3_r;

    t4_r = (ne10_int16_t) ( ( (NE10_F2I16_SAMPPROD) (s3_r + s3_i) * TW_81) >> NE10_F2I16_SHIFT);
    t4_i = - (ne10_int16_t) ( ( (NE10_F2I16_SAMPPROD) (s3_r - s3_i) * TW_81) >> NE10_F2I16_SHIFT);
    t5_r = (ne10_int16_t) ( ( (NE10_F2I16_SAMPPROD) (s7_r - s7_i) * TW_81) >> NE10_F2I16_SHIFT);
    t5_i = (ne10_int16_t) ( ( (NE10_F2I16_SAMPPROD) (s7_r + s7_i) * TW_81) >> NE10_F2I16_SHIFT);

    t0_r = s1_r - s5_i;
    t0_i = s1_i + s5_r;
    t1_r = s1_r + s5_i;
    t1_i = s1_i - s5_r;
    t2_r = t4_r - t5_r;
    t2_i = t4_i - t5_i;
    t3_r = t4_r + t5_r;
    t3_i = t4_i + t5_i;
    Fout[1].r = t1_r + t2_r;
    Fout[1].i = t1_i + t2_i;
    Fout[5].r = t1_r - t2_r;
    Fout[5].i = t1_i - t2_i;
    Fout[3].r = t0_r + t3_i;
    Fout[3].i = t0_i - t3_r;
    Fout[7].r = t0_r - t3_i;
    Fout[7].i = t0_i + t3_r;
}

static inline void ne10_fft8_backward_int16_unscaled (ne10_fft_cpx_int16_t * Fout,
        ne10_fft_cpx_int16_t * Fin)

{
    ne10_int16_t s0_r, s0_i, s1_r, s1_i, s2_r, s2_i, s3_r, s3_i, s4_r, s4_i, s5_r, s5_i, s6_r, s6_i, s7_r, s7_i;
    ne10_int16_t t0_r, t0_i, t1_r, t1_i, t2_r, t2_i, t3_r, t3_i, t4_r, t4_i, t5_r, t5_i;
    const ne10_int16_t TW_81 = 23169;

    s0_r = Fin[0].r + Fin[4].r;
    s0_i = Fin[0].i + Fin[4].i;
    s1_r = Fin[0].r - Fin[4].r;
    s1_i = Fin[0].i - Fin[4].i;
    s2_r = Fin[1].r + Fin[5].r;
    s2_i = Fin[1].i + Fin[5].i;
    s3_r = Fin[1].r - Fin[5].r;
    s3_i = Fin[1].i - Fin[5].i;
    s4_r = Fin[2].r + Fin[6].r;
    s4_i = Fin[2].i + Fin[6].i;
    s5_r = Fin[2].r - Fin[6].r;
    s5_i = Fin[2].i - Fin[6].i;
    s6_r = Fin[3].r + Fin[7].r;
    s6_i = Fin[3].i + Fin[7].i;
    s7_r = Fin[3].r - Fin[7].r;
    s7_i = Fin[3].i - Fin[7].i;

    t0_r = s0_r - s4_r;
    t0_i = s0_i - s4_i;
    t1_r = s0_r + s4_r;
    t1_i = s0_i + s4_i;
    t2_r = s2_r + s6_r;
    t2_i = s2_i + s6_i;
    t3_r = s2_r - s6_r;
    t3_i = s2_i - s6_i;
    Fout[0].r = t1_r + t2_r;
    Fout[0].i = t1_i + t2_i;
    Fout[4].r = t1_r - t2_r;
    Fout[4].i = t1_i - t2_i;
    Fout[2].r = t0_r - t3_i;
    Fout[2].i = t0_i + t3_r;
    Fout[6].r = t0_r + t3_i;
    Fout[6].i = t0_i - t3_r;

    t4_r = (ne10_int16_t) ( ( (NE10_F2I16_SAMPPROD) (s3_r - s3_i) * TW_81) >> NE10_F2I16_SHIFT);
    t4_i = (ne10_int16_t) ( ( (NE10_F2I16_SAMPPROD) (s3_r + s3_i) * TW_81) >> NE10_F2I16_SHIFT);
    t5_r = (ne10_int16_t) ( ( (NE10_F2I16_SAMPPROD) (s7_r + s7_i) * TW_81) >> NE10_F2I16_SHIFT);
    t5_i = - (ne10_int16_t) ( ( (NE10_F2I16_SAMPPROD) (s7_r - s7_i) * TW_81) >> NE10_F2I16_SHIFT);

    t0_r = s1_r + s5_i;
    t0_i = s1_i - s5_r;
    t1_r = s1_r - s5_i;
    t1_i = s1_i + s5_r;
    t2_r = t4_r - t5_r;
    t2_i = t4_i - t5_i;
    t3_r = t4_r + t5_r;
    t3_i = t4_i + t5_i;
    Fout[1].r = t1_r + t2_r;
    Fout[1].i = t1_i + t2_i;
    Fout[5].r = t1_r - t2_r;
    Fout[5].i = t1_i - t2_i;
    Fout[3].r = t0_r - t3_i;
    Fout[3].i = t0_i + t3_r;
    Fout[7].r = t0_r + t3_i;
    Fout[7].i = t0_i - t3_r;
}
static inline void ne10_fft8_forward_int16_scaled (ne10_fft_cpx_int16_t * Fout,
        ne10_fft_cpx_int16_t * Fin)

{
    ne10_int16_t s0_r, s0_i, s1_r, s1_i, s2_r, s2_i, s3_r, s3_i, s4_r, s4_i, s5_r, s5_i, s6_r, s6_i, s7_r, s7_i;
    ne10_int16_t t0_r, t0_i, t1_r, t1_i, t2_r, t2_i, t3_r, t3_i, t4_r, t4_i, t5_r, t5_i;
    const ne10_int16_t TW_81 = 23169;

    s0_r = (Fin[0].r + Fin[4].r) >> 3;
    s0_i = (Fin[0].i + Fin[4].i) >> 3;
    s1_r = (Fin[0].r - Fin[4].r) >> 3;
    s1_i = (Fin[0].i - Fin[4].i) >> 3;
    s2_r = (Fin[1].r + Fin[5].r) >> 3;
    s2_i = (Fin[1].i + Fin[5].i) >> 3;
    s3_r = (Fin[1].r - Fin[5].r) >> 3;
    s3_i = (Fin[1].i - Fin[5].i) >> 3;
    s4_r = (Fin[2].r + Fin[6].r) >> 3;
    s4_i = (Fin[2].i + Fin[6].i) >> 3;
    s5_r = (Fin[2].r - Fin[6].r) >> 3;
    s5_i = (Fin[2].i - Fin[6].i) >> 3;
    s6_r = (Fin[3].r + Fin[7].r) >> 3;
    s6_i = (Fin[3].i + Fin[7].i) >> 3;
    s7_r = (Fin[3].r - Fin[7].r) >> 3;
    s7_i = (Fin[3].i - Fin[7].i) >> 3;

    t0_r = s0_r - s4_r;
    t0_i = s0_i - s4_i;
    t1_r = s0_r + s4_r;
    t1_i = s0_i + s4_i;
    t2_r = s2_r + s6_r;
    t2_i = s2_i + s6_i;
    t3_r = s2_r - s6_r;
    t3_i = s2_i - s6_i;
    Fout[0].r = t1_r + t2_r;
    Fout[0].i = t1_i + t2_i;
    Fout[4].r = t1_r - t2_r;
    Fout[4].i = t1_i - t2_i;
    Fout[2].r = t0_r + t3_i;
    Fout[2].i = t0_i - t3_r;
    Fout[6].r = t0_r - t3_i;
    Fout[6].i = t0_i + t3_r;

    t4_r = (ne10_int16_t) ( ( (NE10_F2I16_SAMPPROD) (s3_r + s3_i) * TW_81) >> NE10_F2I16_SHIFT);
    t4_i = - (ne10_int16_t) ( ( (NE10_F2I16_SAMPPROD) (s3_r - s3_i) * TW_81) >> NE10_F2I16_SHIFT);
    t5_r = (ne10_int16_t) ( ( (NE10_F2I16_SAMPPROD) (s7_r - s7_i) * TW_81) >> NE10_F2I16_SHIFT);
    t5_i = (ne10_int16_t) ( ( (NE10_F2I16_SAMPPROD) (s7_r + s7_i) * TW_81) >> NE10_F2I16_SHIFT);

    t0_r = s1_r - s5_i;
    t0_i = s1_i + s5_r;
    t1_r = s1_r + s5_i;
    t1_i = s1_i - s5_r;
    t2_r = t4_r - t5_r;
    t2_i = t4_i - t5_i;
    t3_r = t4_r + t5_r;
    t3_i = t4_i + t5_i;
    Fout[1].r = t1_r + t2_r;
    Fout[1].i = t1_i + t2_i;
    Fout[5].r = t1_r - t2_r;
    Fout[5].i = t1_i - t2_i;
    Fout[3].r = t0_r + t3_i;
    Fout[3].i = t0_i - t3_r;
    Fout[7].r = t0_r - t3_i;
    Fout[7].i = t0_i + t3_r;
}

static inline void ne10_fft8_backward_int16_scaled (ne10_fft_cpx_int16_t * Fout,
        ne10_fft_cpx_int16_t * Fin)

{
    ne10_int16_t s0_r, s0_i, s1_r, s1_i, s2_r, s2_i, s3_r, s3_i, s4_r, s4_i, s5_r, s5_i, s6_r, s6_i, s7_r, s7_i;
    ne10_int16_t t0_r, t0_i, t1_r, t1_i, t2_r, t2_i, t3_r, t3_i, t4_r, t4_i, t5_r, t5_i;
    const ne10_int16_t TW_81 = 23169;

    s0_r = (Fin[0].r + Fin[4].r) >> 3;
    s0_i = (Fin[0].i + Fin[4].i) >> 3;
    s1_r = (Fin[0].r - Fin[4].r) >> 3;
    s1_i = (Fin[0].i - Fin[4].i) >> 3;
    s2_r = (Fin[1].r + Fin[5].r) >> 3;
    s2_i = (Fin[1].i + Fin[5].i) >> 3;
    s3_r = (Fin[1].r - Fin[5].r) >> 3;
    s3_i = (Fin[1].i - Fin[5].i) >> 3;
    s4_r = (Fin[2].r + Fin[6].r) >> 3;
    s4_i = (Fin[2].i + Fin[6].i) >> 3;
    s5_r = (Fin[2].r - Fin[6].r) >> 3;
    s5_i = (Fin[2].i - Fin[6].i) >> 3;
    s6_r = (Fin[3].r + Fin[7].r) >> 3;
    s6_i = (Fin[3].i + Fin[7].i) >> 3;
    s7_r = (Fin[3].r - Fin[7].r) >> 3;
    s7_i = (Fin[3].i - Fin[7].i) >> 3;

    t0_r = s0_r - s4_r;
    t0_i = s0_i - s4_i;
    t1_r = s0_r + s4_r;
    t1_i = s0_i + s4_i;
    t2_r = s2_r + s6_r;
    t2_i = s2_i + s6_i;
    t3_r = s2_r - s6_r;
    t3_i = s2_i - s6_i;
    Fout[0].r = t1_r + t2_r;
    Fout[0].i = t1_i + t2_i;
    Fout[4].r = t1_r - t2_r;
    Fout[4].i = t1_i - t2_i;
    Fout[2].r = t0_r - t3_i;
    Fout[2].i = t0_i + t3_r;
    Fout[6].r = t0_r + t3_i;
    Fout[6].i = t0_i - t3_r;

    t4_r = (ne10_int16_t) ( ( (NE10_F2I16_SAMPPROD) (s3_r - s3_i) * TW_81) >> NE10_F2I16_SHIFT);
    t4_i = (ne10_int16_t) ( ( (NE10_F2I16_SAMPPROD) (s3_r + s3_i) * TW_81) >> NE10_F2I16_SHIFT);
    t5_r = (ne10_int16_t) ( ( (NE10_F2I16_SAMPPROD) (s7_r + s7_i) * TW_81) >> NE10_F2I16_SHIFT);
    t5_i = - (ne10_int16_t) ( ( (NE10_F2I16_SAMPPROD) (s7_r - s7_i) * TW_81) >> NE10_F2I16_SHIFT);

    t0_r = s1_r + s5_i;
    t0_i = s1_i - s5_r;
    t1_r = s1_r - s5_i;
    t1_i = s1_i + s5_r;
    t2_r = t4_r - t5_r;
    t2_i = t4_i - t5_i;
    t3_r = t4_r + t5_r;
    t3_i = t4_i + t5_i;
    Fout[1].r = t1_r + t2_r;
    Fout[1].i = t1_i + t2_i;
    Fout[5].r = t1_r - t2_r;
    Fout[5].i = t1_i - t2_i;
    Fout[3].r = t0_r - t3_i;
    Fout[3].i = t0_i + t3_r;
    Fout[7].r = t0_r + t3_i;
    Fout[7].i = t0_i - t3_r;
}
/**
 * @addtogroup C2C_FFT_IFFT
 * @{
 */

/**
 * @brief Mixed radix-2/4 complex FFT/IFFT of 16-bit fixed point data.
 * @param[out]  *fout            point to the output buffer (out-of-place)
 * @param[in]   *fin             point to the input buffer (out-of-place)
 * @param[in]   cfg              point to the config struct
 * @param[in]   inverse_fft      the flag of IFFT, 0: FFT, 1: IFFT
 * @param[in]   scaled_flag      scale flag, 0 unscaled, 1 scaled
 * @return none.
 * The function implements a mixed radix-2/4 complex FFT/IFFT. The length of 2^N(N is 1, 2, 3, 4, 5, 6 ....etc) is supported.
 * Otherwise, this FFT is an out-of-place algorithm. When you want to get an in-place FFT, it creates a temp buffer as
 *  output buffer and then copies the temp buffer back to input buffer. For the usage of this function, please check test/test_suite_fft_int16.c
 */
void ne10_fft_c2c_1d_int16_neon (ne10_fft_cpx_int16_t *fout,
                                 ne10_fft_cpx_int16_t *fin,
                                 ne10_fft_cfg_int16_t cfg,
                                 ne10_int32_t inverse_fft,
                                 ne10_int32_t scaled_flag)
{
    if (scaled_flag)
    {
        if (inverse_fft)
        {
            switch (cfg->nfft)
            {
            case 4:
                ne10_fft4_backward_int16_scaled (fout, fin);
                break;
            case 8:
                ne10_fft8_backward_int16_scaled (fout, fin);
                break;
            default:
                ne10_mixed_radix_fft_backward_int16_scaled_neon (fout, fin, cfg->factors, cfg->twiddles, cfg->buffer);
                break;
            }
        }
        else
        {
            switch (cfg->nfft)
            {
            case 4:
                ne10_fft4_forward_int16_scaled (fout, fin);
                break;
            case 8:
                ne10_fft8_forward_int16_scaled (fout, fin);
                break;
            default:
                ne10_mixed_radix_fft_forward_int16_scaled_neon (fout, fin, cfg->factors, cfg->twiddles, cfg->buffer);
                break;
            }
        }
    }
    else
    {
        if (inverse_fft)
        {
            switch (cfg->nfft)
            {
            case 4:
                ne10_fft4_backward_int16_unscaled (fout, fin);
                break;
            case 8:
                ne10_fft8_backward_int16_unscaled (fout, fin);
                break;
            default:
                ne10_mixed_radix_fft_backward_int16_unscaled_neon (fout, fin, cfg->factors, cfg->twiddles, cfg->buffer);
                break;
            }
        }
        else
        {
            switch (cfg->nfft)
            {
            case 4:
                ne10_fft4_forward_int16_unscaled (fout, fin);
                break;
            case 8:
                ne10_fft8_forward_int16_unscaled (fout, fin);
                break;
            default:
                ne10_mixed_radix_fft_forward_int16_unscaled_neon (fout, fin, cfg->factors, cfg->twiddles, cfg->buffer);
                break;
            }
        }
    }
}

/**
 * @}
 */ //end of C2C_FFT_IFFT group

