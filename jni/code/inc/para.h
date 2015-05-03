#ifndef PARA_H
#define PARA_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#ifdef __cplusplus
extern "C" {
#endif
//#include <windows.h>

/* Max FFT Length and double buffer for real and imag */
#define TEST_LENGTH_SAMPLES (4096)
#define MIN_LENGTH_SAMPLES_CPX (4)
#define MIN_LENGTH_SAMPLES_REAL (MIN_LENGTH_SAMPLES_CPX*2)

#define SNR_THRESHOLD_INT16 15.0f

#define TEST_COUNT 250000	

#define ARRAY_GUARD_LEN      4
/////////////////////////////////////////////////////////
// constant values that are used across the library
/////////////////////////////////////////////////////////
#define NE10_OK 0
#define NE10_ERR -1
/////////////////////////////////////////////////////////
// constant values that are used across the library
/////////////////////////////////////////////////////////

#define NE10_PI (ne10_float32_t)(3.1415926535897932384626433832795)
#define NE10_F2I16_MAX         32767
#define NE10_MAXFACTORS             32
#define NE10_FFT_BYTE_ALIGNMENT 8
#define NE10_F2I16_SHIFT       15
#define NE10_F2I16_SAMPPROD    ne10_int32_t
/* algorithms used in FFT */
#define NE10_FFT_ALG_24 0
#define NE10_FFT_ALG_ANY 1
typedef signed char             ne10_int8_t;
typedef unsigned char           ne10_uint8_t;
typedef signed short            ne10_int16_t;
typedef unsigned short          ne10_uint16_t;
typedef signed int              ne10_int32_t;
typedef unsigned int            ne10_uint32_t;
typedef signed long long int    ne10_int64_t;
typedef unsigned long long int  ne10_uint64_t;
typedef float                   ne10_float32_t;
typedef double                  ne10_float64_t;
typedef int                     ne10_result_t;     // resulting [error-]code

typedef struct
{
    ne10_int16_t r;
    ne10_int16_t i;
} ne10_fft_cpx_int16_t;

typedef struct 
{
    ne10_int32_t nfft;
    ne10_int32_t *factors;
    ne10_fft_cpx_int16_t *twiddles;
    ne10_fft_cpx_int16_t *buffer;
} ne10_fft_state_int16_t;

typedef ne10_fft_state_int16_t* ne10_fft_cfg_int16_t;

typedef struct  
{
    ne10_int32_t nfft;
    ne10_int32_t ncfft;
    ne10_int32_t *factors;
    ne10_fft_cpx_int16_t *twiddles;
    ne10_fft_cpx_int16_t *super_twiddles;
    ne10_fft_cpx_int16_t *buffer;
} ne10_fft_r2c_state_int16_t;

typedef ne10_fft_r2c_state_int16_t* ne10_fft_r2c_cfg_int16_t;

typedef struct 
{
    ne10_int32_t r;
    ne10_int32_t i;
} ne10_fft_cpx_int32_t;

#define NE10_F2I16_FIXDIV(c,div) \
    do {    ((c).r) = ( ( ((c).r)/div) );  \
        ((c).i) = ( ( ((c).i)/div) ); }while (0)

#define NE10_MALLOC malloc

#define NE10_FREE(p) \
    do { \
        free(p); \
        p = NULL; \
    }while(0)

#define NE10_BYTE_ALIGNMENT(address, alignment) \
    do { \
        (address) = (((address) + ((alignment) - 1)) & ~ ((alignment) - 1)); \
    }while (0)
	

#define GET_TIME(time, code) { \
        (time) = GetTickCount(); \
        code \
        (time) = GetTickCount() - (time);\
    }

#ifdef __cplusplus
}
#endif
#endif
