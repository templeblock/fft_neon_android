#ifndef NE10_FFT_INT16_H
#define NE10_FFT_INT16_H
#include "para.h"
#ifdef __cplusplus
extern "C" {
#endif
//int round(float a);
//double drand48(void);
ne10_int32_t ne10_factor (ne10_int32_t n, ne10_int32_t * facbuf);
static void ne10_mixed_radix_butterfly_int16_c (ne10_fft_cpx_int16_t * Fout,
        ne10_fft_cpx_int16_t   * Fin,
        ne10_int32_t * factors,
        ne10_fft_cpx_int16_t * twiddles,
        ne10_fft_cpx_int16_t * buffer,
        ne10_int32_t scaled_flag);
static void ne10_mixed_radix_butterfly_inverse_int16_c (ne10_fft_cpx_int16_t * Fout,
        ne10_fft_cpx_int16_t   * Fin,
        ne10_int32_t * factors,
        ne10_fft_cpx_int16_t * twiddles,
        ne10_fft_cpx_int16_t * buffer,
        ne10_int32_t scaled_flag);
static void ne10_fft_split_r2c_1d_int16 (ne10_fft_cpx_int16_t *dst,
        const ne10_fft_cpx_int16_t *src,
        ne10_fft_cpx_int16_t *twiddles,
        ne10_int32_t ncfft,
        ne10_int32_t scaled_flag);
static void ne10_fft_split_c2r_1d_int16 (ne10_fft_cpx_int16_t *dst,
        const ne10_fft_cpx_int16_t *src,
        ne10_fft_cpx_int16_t *twiddles,
        ne10_int32_t ncfft,
        ne10_int32_t scaled_flag);
ne10_fft_cfg_int16_t ne10_fft_alloc_c2c_int16 (ne10_int32_t nfft);
void ne10_fft_c2c_1d_int16_c (ne10_fft_cpx_int16_t *fout,
                              ne10_fft_cpx_int16_t *fin,
                              ne10_fft_cfg_int16_t cfg,
                              ne10_int32_t inverse_fft,
                              ne10_int32_t scaled_flag);
ne10_fft_r2c_cfg_int16_t ne10_fft_alloc_r2c_int16 (ne10_int32_t nfft);
void ne10_fft_r2c_1d_int16_c (ne10_fft_cpx_int16_t *fout,
                              ne10_int16_t *fin,
                              ne10_fft_r2c_cfg_int16_t cfg,
                              ne10_int32_t scaled_flag);
void ne10_fft_c2r_1d_int16_c (ne10_int16_t *fout,
                              ne10_fft_cpx_int16_t *fin,
                              ne10_fft_r2c_cfg_int16_t cfg,
                              ne10_int32_t scaled_flag);

ne10_int32_t GUARD_ARRAY_UINT8 (ne10_uint8_t* array, ne10_uint32_t array_length);

ne10_int32_t CHECK_ARRAY_GUARD_UINT8 (ne10_uint8_t* array, ne10_uint32_t array_length);

ne10_float32_t CAL_SNR_FLOAT32 (ne10_float32_t *pRef, ne10_float32_t *pTest, ne10_uint32_t buffSize);
#ifdef __cplusplus
}
#endif
#endif
