#ifndef __FFT_FIXED_POINT_H_
#define __FFT_FIXED_POINT_H_
#ifdef __cplusplus
extern "C" {
#endif

#define DXT_FORWARD  0
#define DXT_INVERSE  1

#define Q_INPUT 8

typedef struct{
	int real;
	int image;
}complex_INT;


void reverse(int len, int M,int *b);
void fft_fixed_point(int fft_nLen, int fft_M, complex_INT * A);
void fft_2D_fixed_point(int mLen,int nLen,int M,int N,complex_INT *A_In,int flag);
#ifdef __cplusplus
}
#endif
#endif