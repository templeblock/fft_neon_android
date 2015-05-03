#ifndef TEST_SUITE_FFT_INT16_H
#define TEST_SUITE_FFT_INT16_H
#include "para.h"
/* ----------------------------------------------------------------------
** Global defines
** ------------------------------------------------------------------- */
#ifdef __cplusplus
extern "C" {
#endif
/* Max FFT Length and double buffer for real and imag */
#define TEST_LENGTH_SAMPLES (4096)
#define MIN_LENGTH_SAMPLES_CPX (4)
#define MIN_LENGTH_SAMPLES_REAL (MIN_LENGTH_SAMPLES_CPX*2)

#define SNR_THRESHOLD_INT16 15.0f

#define TEST_COUNT 250000

/* ----------------------------------------------------------------------
** Defines each of the tests performed
** ------------------------------------------------------------------- */

//input and output
static ne10_int32_t testInput_i16_unscaled[TEST_LENGTH_SAMPLES * 2];
static ne10_int32_t testInput_i16_scaled[TEST_LENGTH_SAMPLES * 2];
static ne10_int16_t * guarded_in_c = NULL;
static ne10_int16_t * guarded_in_neon = NULL;
static ne10_int16_t * in_c = NULL;
static ne10_int16_t * in_c1 = NULL;
static ne10_int16_t * in_neon = NULL;

static ne10_int16_t * guarded_out_c = NULL;
static ne10_int16_t * guarded_out_neon = NULL;
static ne10_int16_t * out_c = NULL;
static ne10_int16_t * out_c1 = NULL;
static ne10_int16_t * out_neon = NULL;

static ne10_int16_t * temp_out_c = NULL;

static ne10_int16_t * temp_out_c1 = NULL;
static ne10_int16_t * temp_out_c2 = NULL;

static ne10_float32_t snr = 0.0f;

static ne10_int64_t time_c = 0;
static ne10_int64_t time_neon = 0;
static ne10_int64_t time_overhead_c = 0;
static ne10_int64_t time_overhead_neon = 0;
static ne10_float32_t time_speedup = 0.0f;
static ne10_float32_t time_savings = 0.0f;


void fft_c2c_2d_int16_c(ne10_int16_t *src,ne10_int16_t *dst,ne10_int32_t fftRowSize,ne10_int32_t fftColSize);

void ifft_c2c_2d_int16_c(ne10_int16_t *src,ne10_int16_t *dst,ne10_int32_t fftRowSize,ne10_int32_t fftColSize);

void fft_c2c_2d_int16_neon(ne10_int16_t *src,ne10_int16_t *dst,ne10_int32_t fftRowSize,ne10_int32_t fftColSize);

void ifft_c2c_2d_int16_neon(ne10_int16_t *src,ne10_int16_t *dst,ne10_int32_t fftRowSize,ne10_int32_t fftColSize);

void test_fft_c2c_1d_int16_conformance();
#ifdef __cplusplus
}
#endif
#endif