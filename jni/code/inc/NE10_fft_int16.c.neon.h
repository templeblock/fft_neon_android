#ifndef NE10_FFT_INT16_C_NEON_H
#define NE10_FFT_INT16_C_NEON_H
#include "para.h"
#ifdef __cplusplus
extern "C" {
#endif
static inline void ne10_fft4_forward_int16_unscaled (ne10_fft_cpx_int16_t * Fout,
        ne10_fft_cpx_int16_t * Fin);
static inline void ne10_fft4_backward_int16_unscaled (ne10_fft_cpx_int16_t * Fout,
        ne10_fft_cpx_int16_t * Fin);
static inline void ne10_fft4_forward_int16_scaled (ne10_fft_cpx_int16_t * Fout,
        ne10_fft_cpx_int16_t * Fin);
static inline void ne10_fft4_backward_int16_scaled (ne10_fft_cpx_int16_t * Fout,
        ne10_fft_cpx_int16_t * Fin);
static inline void ne10_fft8_forward_int16_unscaled (ne10_fft_cpx_int16_t * Fout,
        ne10_fft_cpx_int16_t * Fin);
static inline void ne10_fft8_backward_int16_unscaled (ne10_fft_cpx_int16_t * Fout,
        ne10_fft_cpx_int16_t * Fin);
static inline void ne10_fft8_forward_int16_scaled (ne10_fft_cpx_int16_t * Fout,
        ne10_fft_cpx_int16_t * Fin);
static inline void ne10_fft8_backward_int16_scaled (ne10_fft_cpx_int16_t * Fout,
        ne10_fft_cpx_int16_t * Fin);
void ne10_fft_c2c_1d_int16_neon (ne10_fft_cpx_int16_t *fout,
                                 ne10_fft_cpx_int16_t *fin,
                                 ne10_fft_cfg_int16_t cfg,
                                 ne10_int32_t inverse_fft,
                                 ne10_int32_t scaled_flag);

#ifdef __cplusplus
}
#endif
#endif
