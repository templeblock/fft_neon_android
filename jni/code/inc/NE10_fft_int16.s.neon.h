#ifndef NE10_FFT_INT16_S_NEON_H
#define NE10_FFT_INT16_S_NEON_H
#include "para.h"
#ifdef __cplusplus
extern "C" {
#endif
void ne10_mixed_radix_fft_backward_int16_scaled_neon(ne10_fft_cpx_int16_t * Fout,
        ne10_fft_cpx_int16_t   * Fin,
        ne10_int32_t * factors,
        ne10_fft_cpx_int16_t * twiddles,
        ne10_fft_cpx_int16_t * buffer);
void ne10_mixed_radix_fft_forward_int16_scaled_neon(ne10_fft_cpx_int16_t * Fout,
        ne10_fft_cpx_int16_t   * Fin,
        ne10_int32_t * factors,
        ne10_fft_cpx_int16_t * twiddles,
        ne10_fft_cpx_int16_t * buffer);
void ne10_mixed_radix_fft_backward_int16_unscaled_neon(ne10_fft_cpx_int16_t * Fout,
        ne10_fft_cpx_int16_t   * Fin,
        ne10_int32_t * factors,
        ne10_fft_cpx_int16_t * twiddles,
        ne10_fft_cpx_int16_t * buffer);
void ne10_mixed_radix_fft_forward_int16_unscaled_neon(ne10_fft_cpx_int16_t * Fout,
        ne10_fft_cpx_int16_t   * Fin,
        ne10_int32_t * factors,
        ne10_fft_cpx_int16_t * twiddles,
        ne10_fft_cpx_int16_t * buffer);

#ifdef __cplusplus
}
#endif
#endif
