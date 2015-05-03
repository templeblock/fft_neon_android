#include <jni.h>
#include "com_example_fftdemo_testfft.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "para.h"
#include "test_suite_fft_int16.h"
#include "NE10_fft_int16.h"
#include "NE10_fft_int16.c.neon.h"
#include "NE10_fft_int16.s.neon.h"
#include "fft_fixed_point.h"
#define DEBUG 0

#if DEBUG
#include <android/log.h>
#  define  D(x...)  __android_log_print(ANDROID_LOG_INFO,"fftdemo",x)
#else
#  define  D(...)  do {} while (0)
#endif


static double now_ms(void);


extern "C" 
{
/*
 * Class:     com_example_fftdemo_testfft
 * Method:    testfft2d
 * Signature: ()Ljava/lang/String;
 */
 JNIEXPORT jstring JNICALL Java_com_example_fftdemo_testfft_testfft2d(JNIEnv *env, jclass)
{
		char*  str;
		char buffer[1024]="FFT\n";
		#if 0
		double  t0, t1, time_c, time_neon;
		double duration;
		ne10_int32_t errc,errn;
		ne10_int32_t testInput_i16_unscaled[TEST_LENGTH_SAMPLES * 2];
		ne10_int32_t testInput_i16_scaled[TEST_LENGTH_SAMPLES * 2];
		ne10_int32_t i = 0;
		ne10_int32_t fftSize = 0;
		ne10_fft_cfg_int16_t cfg;
		ne10_float32_t * out_c_tmp = NULL;
		ne10_float32_t * out_neon_tmp = NULL;
		FILE *fpci=NULL;
		FILE *fpni=NULL;
		FILE *fpco=NULL;
		FILE *fpno=NULL;
		FILE *ifpci=NULL;
		FILE *ifpni=NULL;
		FILE *ifpco=NULL;
		FILE *ifpno=NULL;
		//fprintf (stdout, "----------%30s start\n", __FUNCTION__);

		/* init input memory */
		ne10_int16_t * guarded_in_c = (ne10_int16_t*) NE10_MALLOC ( (TEST_LENGTH_SAMPLES * 2 + ARRAY_GUARD_LEN * 2) * sizeof (ne10_int16_t));
		ne10_int16_t * guarded_in_neon = (ne10_int16_t*) NE10_MALLOC ( (TEST_LENGTH_SAMPLES * 2 + ARRAY_GUARD_LEN * 2) * sizeof (ne10_int16_t));
		ne10_int16_t * in_c = guarded_in_c + ARRAY_GUARD_LEN;
		ne10_int16_t * in_neon = guarded_in_neon + ARRAY_GUARD_LEN;

		/* init dst memory */
		ne10_int16_t * guarded_out_c = (ne10_int16_t*) NE10_MALLOC ( (TEST_LENGTH_SAMPLES * 2 + ARRAY_GUARD_LEN * 2) * sizeof (ne10_int16_t));
		ne10_int16_t * guarded_out_neon = (ne10_int16_t*) NE10_MALLOC ( (TEST_LENGTH_SAMPLES * 2 + ARRAY_GUARD_LEN * 2) * sizeof (ne10_int16_t));
		ne10_int16_t * out_c = guarded_out_c + ARRAY_GUARD_LEN;
		ne10_int16_t * out_neon = guarded_out_neon + ARRAY_GUARD_LEN;

		out_c_tmp = (ne10_float32_t*) NE10_MALLOC ( (TEST_LENGTH_SAMPLES * 2) * sizeof (ne10_float32_t));
		out_neon_tmp = (ne10_float32_t*) NE10_MALLOC ( (TEST_LENGTH_SAMPLES * 2) * sizeof (ne10_float32_t));

		for (i = 0; i < TEST_LENGTH_SAMPLES * 2; i++)
		{
			testInput_i16_unscaled[i] = (ne10_int32_t) (drand48() * 255);
			testInput_i16_scaled[i] = (ne10_int16_t) (drand48() * NE10_F2I16_MAX) - NE10_F2I16_MAX / 2;
		}
		asprintf(&str, "1d:\n");
		strlcat(buffer, str, sizeof buffer);
		free(str);
		fpci=fopen("/data/testimg/fftrci.txt","w");
		fpni=fopen("/data/testimg/fftrni.txt","w");
		fpco=fopen("/data/testimg/fftrco.txt","w");
		fpno=fopen("/data/testimg/fftrno.txt","w");
		ifpci=fopen("/data/testimg/ifftrci.txt","w");
		ifpni=fopen("/data/testimg/ifftrni.txt","w");
		ifpco=fopen("/data/testimg/ifftrco.txt","w");
		ifpno=fopen("/data/testimg/ifftrno.txt","w");
		for (fftSize = MIN_LENGTH_SAMPLES_CPX*32; fftSize <= MIN_LENGTH_SAMPLES_CPX*32; fftSize *= 2)
		{
			//fprintf (stdout, "FFT size %d\n", fftSize);
			cfg = ne10_fft_alloc_c2c_int16 (fftSize);
			if (cfg == NULL)
			{
				//fprintf (stdout, "======ERROR, FFT alloc fails\n");
				//return;
			}

			/* unscaled FFT test */
			memcpy (in_c, testInput_i16_unscaled, 2 * fftSize * sizeof (ne10_int16_t));
			memcpy (in_neon, testInput_i16_unscaled, 2 * fftSize * sizeof (ne10_int16_t));

			errc=GUARD_ARRAY_UINT8 ( (ne10_uint8_t*) out_c, fftSize * 2 * sizeof (ne10_int16_t));
			errn=GUARD_ARRAY_UINT8 ( (ne10_uint8_t*) out_neon, fftSize * 2 * sizeof (ne10_int16_t));
			asprintf(&str, "c%d,n%d\n", errc,errn);
			strlcat(buffer, str, sizeof buffer);
			free(str);
			for(i=0;i<2 * fftSize;i++)
			{
				fprintf(fpci,"%d\n",in_c[i]);
				fprintf(fpni,"%d\n",in_neon[i]);
			}
			t0=now_ms();
			ne10_fft_c2c_1d_int16_c((ne10_fft_cpx_int16_t*) out_c, (ne10_fft_cpx_int16_t*) in_c, cfg, 0, 0);
			t1=now_ms();
			time_c = t1 - t0;
			asprintf(&str, "C:%gms\n", time_c);
			strlcat(buffer, str, sizeof buffer);
			free(str);
			
			t0=now_ms();
			ne10_fft_c2c_1d_int16_neon((ne10_fft_cpx_int16_t*) out_neon, (ne10_fft_cpx_int16_t*) in_neon, cfg, 0, 0);
			t1=now_ms();
			time_neon = t1 - t0;
			asprintf(&str, "N:%gms(x%g faster)\n", time_neon, time_c / (time_neon < 1e-6 ? 1. : time_neon));
			strlcat(buffer, str, sizeof buffer);
			free(str);
			errc=CHECK_ARRAY_GUARD_UINT8 ( (ne10_uint8_t*) out_c, fftSize * 2 * sizeof (ne10_int16_t));
			errn=CHECK_ARRAY_GUARD_UINT8 ( (ne10_uint8_t*) out_neon, fftSize * 2 * sizeof (ne10_int16_t));
			asprintf(&str, "c%d,n%d\n", errc,errn);
			strlcat(buffer, str, sizeof buffer);
			free(str);
			for(i=0;i<2 * fftSize;i++)
			{
				fprintf(fpco,"%d\n",out_c[i]);
				fprintf(fpno,"%d\n",out_neon[i]);
			}
			//conformance test
			for (i = 0; i < TEST_LENGTH_SAMPLES * 2; i++)
			{
				out_c_tmp[i] = (ne10_float32_t) out_c[i];
				out_neon_tmp[i] = (ne10_float32_t) out_neon[i];
			}
			snr = CAL_SNR_FLOAT32 (out_c_tmp, out_neon_tmp, fftSize * 2);
			//assert_false ( (snr < SNR_THRESHOLD_INT16));
			if(snr > SNR_THRESHOLD_INT16)
			{
				asprintf(&str, "%g>SNR_THRESHOLD_INT16\n", snr);
				strlcat(buffer, str, sizeof buffer);
				free(str);
			}
			else
			{
				asprintf(&str, "%g<SNR_THRESHOLD_INT16\n", snr);
				strlcat(buffer, str, sizeof buffer);
				free(str);
			}
			
			/* IFFT test */
			memcpy (in_c, out_c, 2 * fftSize * sizeof (ne10_int16_t));
			memcpy (in_neon, out_neon, 2 * fftSize * sizeof (ne10_int16_t));
			for(i=0;i<2 * fftSize;i++)
			{
				fprintf(ifpci,"%d\n",in_c[i]);
				fprintf(ifpni,"%d\n",in_neon[i]);
			}
			errc=GUARD_ARRAY_UINT8 ( (ne10_uint8_t*) out_c, fftSize * 2 * sizeof (ne10_int16_t));
			errn=GUARD_ARRAY_UINT8 ( (ne10_uint8_t*) out_neon, fftSize * 2 * sizeof (ne10_int16_t));
			asprintf(&str, "c%d,n%d\n", errc,errn);
			strlcat(buffer, str, sizeof buffer);
			free(str);
			t0=now_ms();
			ne10_fft_c2c_1d_int16_c ( (ne10_fft_cpx_int16_t*) out_c, (ne10_fft_cpx_int16_t*) in_c, cfg, 1, 0);
			t1=now_ms();
			time_c = t1 - t0;
			asprintf(&str, "IC:%gms\n", time_c);
			strlcat(buffer, str, sizeof buffer);
			free(str);
			
			t0=now_ms();
			ne10_fft_c2c_1d_int16_neon ( (ne10_fft_cpx_int16_t*) out_neon, (ne10_fft_cpx_int16_t*) in_neon, cfg, 1, 0);
			t1=now_ms();
			time_neon = t1 - t0;
			asprintf(&str, "IN:%gms(x%g faster)\n", time_neon, time_c / (time_neon < 1e-6 ? 1. : time_neon));
			strlcat(buffer, str, sizeof buffer);
			errc=CHECK_ARRAY_GUARD_UINT8 ( (ne10_uint8_t*) out_c, fftSize * 2 * sizeof (ne10_int16_t));
			errn=CHECK_ARRAY_GUARD_UINT8 ( (ne10_uint8_t*) out_neon, fftSize * 2 * sizeof (ne10_int16_t));
			asprintf(&str, "c%d,n%d\n", errc,errn);
			strlcat(buffer, str, sizeof buffer);
			free(str);
			for(i=0;i<2 * fftSize;i++)
			{
				fprintf(ifpco,"%d\n",out_c[i]);
				fprintf(ifpno,"%d\n",out_neon[i]);
			}
			//conformance test
			for (i = 0; i < TEST_LENGTH_SAMPLES * 2; i++)
			{
				out_c_tmp[i] = (ne10_float32_t) out_c[i];
				out_neon_tmp[i] = (ne10_float32_t) out_neon[i];
			}
			snr = CAL_SNR_FLOAT32 (out_c_tmp, out_neon_tmp, fftSize * 2);
			//assert_false ( (snr < SNR_THRESHOLD_INT16));
			if(snr > SNR_THRESHOLD_INT16)
			{
				asprintf(&str, "%g>SNR_THRESHOLD_INT16\n", snr);
				strlcat(buffer, str, sizeof buffer);
				free(str);
			}
			else
			{
				asprintf(&str, "%g<SNR_THRESHOLD_INT16\n", snr);
				strlcat(buffer, str, sizeof buffer);
				free(str);
			}
			
			
			NE10_FREE (cfg);
		}	
		fclose(fpci);
		fclose(fpni);
		fclose(fpco);
		fclose(fpno);
		fclose(ifpci);
		fclose(ifpni);
		fclose(ifpco);
		fclose(ifpno);

		NE10_FREE (guarded_in_c);
		NE10_FREE (guarded_in_neon);
		NE10_FREE (guarded_out_c);
		NE10_FREE (guarded_out_neon);
		NE10_FREE (out_c_tmp);
		NE10_FREE (out_neon_tmp);
		#endif
		
		#if 0
		double  t0, t1, time_c, time_neon;
		double duration;
		ne10_float32_t snr;
		FILE *fp=NULL;
		ne10_int32_t i = 0;
		ne10_int32_t M=7;
		ne10_int32_t N=7;
		ne10_int32_t fftRowSize = powf(2,M);//row
		ne10_int32_t fftColSize = powf(2,N);//col
		ne10_int16_t* src= (ne10_int16_t*) NE10_MALLOC ( (fftRowSize*fftColSize*2) * sizeof (ne10_int16_t));
		ne10_int16_t* dst1c= (ne10_int16_t*) NE10_MALLOC ( (fftRowSize*fftColSize*2) * sizeof (ne10_int16_t));
		ne10_int16_t* dst2c= (ne10_int16_t*) NE10_MALLOC ( (fftRowSize*fftColSize*2) * sizeof (ne10_int16_t));
		ne10_int16_t* dst1neon= (ne10_int16_t*) NE10_MALLOC ( (fftRowSize*fftColSize*2) * sizeof (ne10_int16_t));
		ne10_int16_t* dst2neon= (ne10_int16_t*) NE10_MALLOC ( (fftRowSize*fftColSize*2) * sizeof (ne10_int16_t));
		ne10_float32_t* out_c_tmp = (ne10_float32_t*) NE10_MALLOC ( (fftRowSize*fftColSize * 2) * sizeof (ne10_float32_t));
		ne10_float32_t* out_neon_tmp = (ne10_float32_t*) NE10_MALLOC ( (fftRowSize*fftColSize * 2) * sizeof (ne10_float32_t));
		/* init input memory */
		//ne10_int16_t* guarded_in_c = (ne10_int16_t*) NE10_MALLOC ( (TEST_LENGTH_SAMPLES * 2 + ARRAY_GUARD_LEN * 2) * sizeof (ne10_int16_t));
		//ne10_int16_t* guarded_in_neon = (ne10_int16_t*) NE10_MALLOC ( (TEST_LENGTH_SAMPLES * 2 + ARRAY_GUARD_LEN * 2) * sizeof (ne10_int16_t));
		//srcc = guarded_in_c + ARRAY_GUARD_LEN;
		//srcneon= guarded_in_neon + ARRAY_GUARD_LEN;

		/* init dst memory */
		//ne10_int16_t* guarded_out_c = (ne10_int16_t*) NE10_MALLOC ( (TEST_LENGTH_SAMPLES * 2 + ARRAY_GUARD_LEN * 2) * sizeof (ne10_int16_t));
		//ne10_int16_t* guarded_out_neon = (ne10_int16_t*) NE10_MALLOC ( (TEST_LENGTH_SAMPLES * 2 + ARRAY_GUARD_LEN * 2) * sizeof (ne10_int16_t));
		//dst1c = guarded_out_c + ARRAY_GUARD_LEN;
		//dst1neon = guarded_out_neon + ARRAY_GUARD_LEN;
		
	
		//srand((int)time(NULL));
		//fp=fopen("/data/testimg/src.txt","w");
		for(i=0;i<fftRowSize*fftColSize*2;i++)
		{
			src[i]=rand()%255;
			//fprintf(fp,"%d\n",src[i]);
		}
		//fclose(fp);
	 	
		//GUARD_ARRAY_UINT8 ( (ne10_uint8_t*) dst1c, fftRowSize*fftColSize * 2 * sizeof (ne10_int16_t));
		//GUARD_ARRAY_UINT8 ( (ne10_uint8_t*) dst1neon, fftRowSize*fftColSize * 2 * sizeof (ne10_int16_t));
		t0=now_ms();
		fft_c2c_2d_int16_c(src,dst1c,fftRowSize,fftColSize);
		t1=now_ms();
		time_c = t1 - t0;
		asprintf(&str, "FFT benchmark:\nC version: %g ms\n", time_c);
		strlcat(buffer, str, sizeof buffer);
		free(str);
		t0=now_ms();
		fft_c2c_2d_int16_neon(src,dst1neon,fftRowSize,fftColSize);
		t1=now_ms();
		time_neon = t1 - t0;
		asprintf(&str, "Neon version:%g ms (x%g faster)\n", time_neon, time_c / (time_neon < 1e-6 ? 1. : time_neon));
		strlcat(buffer, str, sizeof buffer);
		free(str);
		#if 0
		fp=fopen("/data/testimg/dstc.txt","w");
		for(i=0;i<fftRowSize*fftColSize*2;i++)
		{
			fprintf(fp,"%d\n",dst1c[i]);
		}
		fclose(fp);
		
		fp=fopen("/data/testimg/dstn.txt","w");
		for(i=0;i<fftRowSize*fftColSize*2;i++)
		{
			fprintf(fp,"%d\n",dst1neon[i]);
		}
		fclose(fp);
		#endif
		//CHECK_ARRAY_GUARD_UINT8 ( (ne10_uint8_t*) dst1c, fftRowSize*fftColSize * 2 * sizeof (ne10_int16_t));
		//CHECK_ARRAY_GUARD_UINT8 ( (ne10_uint8_t*) dst1neon, fftRowSize*fftColSize* 2 * sizeof (ne10_int16_t));
		#if 0
		for (i = 0; i < fftRowSize*fftColSize* 2; i++)
        {
            out_c_tmp[i] = (ne10_float32_t) dst1c[i];
            out_neon_tmp[i] = (ne10_float32_t) dst1neon[i];
        }
		snr = CAL_SNR_FLOAT32 (out_c_tmp, out_neon_tmp,fftRowSize*fftColSize* 2);
		if(snr > SNR_THRESHOLD_INT16)
		{
			asprintf(&str, "snr=%g >SNR_THRESHOLD_INT16\n", snr);
			strlcat(buffer, str, sizeof buffer);
			free(str);
		}
		else
		{
			asprintf(&str, "snr=%g <SNR_THRESHOLD_INT16\n", snr);
			strlcat(buffer, str, sizeof buffer);
			free(str);
		}
		#endif
		ifft_c2c_2d_int16_c(dst1c,dst2c,fftRowSize,fftColSize);
		 	
		ifft_c2c_2d_int16_neon(dst1neon,dst2neon,fftRowSize,fftColSize);
		#if 0
		fp=fopen("/data/testimg/ifftdstc.txt","w");
		for(i=0;i<fftRowSize*fftColSize*2;i++)
		{
			fprintf(fp,"%d\n",dst2c[i]);
		}
		fclose(fp);
		
		fp=fopen("/data/testimg/ifftdstn.txt","w");
		for(i=0;i<fftRowSize*fftColSize*2;i++)
		{
			fprintf(fp,"%d\n",dst2neon[i]);
		}
		fclose(fp);
		#endif
		NE10_FREE(src);
		NE10_FREE(dst1c);
		NE10_FREE(dst2c);
		NE10_FREE(dst1neon);
		NE10_FREE(dst2neon);
		#endif
				
		#if 1
		double  t0, t1, time_c, time_neon;
		double duration;
		int M=7;
		int N=7;
		int fftRowSize = powf(2,M);//row
		int fftColSize = powf(2,N);//col
		FILE *fp=NULL;
		int i;
		int* src= (int*) malloc ( (fftRowSize*fftColSize*2) * sizeof (int));
		fp=fopen("/data/testimg/src.txt","w");
		for(i=0;i<fftRowSize*fftColSize*2;i++)
		{
			src[i]=rand()%255;
			fprintf(fp,"%d\n",src[i]);
		}
		fclose(fp);
		complex_INT *A_In=(complex_INT*)malloc(fftRowSize*fftColSize*sizeof(complex_INT));
		
		for(i=0;i<fftRowSize*fftColSize;i++)
		{
			A_In[i].real=src[2*i];
			A_In[i].image=src[2*i+1];
			//cout<<A_In[i].real<<" "<<A_In[i].image<<endl;
		}
		t0=now_ms();
		fft_2D_fixed_point(fftRowSize,fftColSize,M,N,A_In,0);
		t1=now_ms();
		time_c = t1 - t0;
		asprintf(&str, "FFT benchmark: %g ms\n", time_c);
		strlcat(buffer, str, sizeof buffer);
		free(str);
		#if 1
		fp=fopen("/data/testimg/fft2d.txt","w");
		for(i=0;i<fftRowSize*fftColSize;i++)
		{
			fprintf(fp,"%d\n",A_In[i].real);
			fprintf(fp,"%d\n",A_In[i].image);
		}
		fclose(fp);
		#endif
		t0=now_ms();
		fft_2D_fixed_point(fftRowSize,fftColSize,M,N,A_In,1);
		t1=now_ms();
		time_neon = t1 - t0;
		asprintf(&str, "IFFT benchmark:%g ms\n", time_neon);
		strlcat(buffer, str, sizeof buffer);
		free(str);
		#if 1
		fp=fopen("/data/testimg/ifft2d.txt","w");
		for(i=0;i<fftRowSize*fftColSize;i++)
		{
			fprintf(fp,"%d\n",A_In[i].real);
			fprintf(fp,"%d\n",A_In[i].image);
		}
		fclose(fp);
		#endif
		free(src);
		free(A_In);
		
		
		#endif
		
		return env->NewStringUTF(buffer);
	
	}
}

/* return current time in milliseconds */
static double now_ms(void)
{
    struct timespec res;
    clock_gettime(CLOCK_REALTIME, &res);
    return 1000.0*res.tv_sec + (double)res.tv_nsec/1e6;
}




