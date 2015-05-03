/*
 * NE10 Library : test_suite_fft_int16.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//#include "NE10_dsp.h"
//#include "seatest.h"
//#include "unit_test_common.h"
#include "para.h"
#include "NE10_fft_int16.h"
#include "NE10_fft_int16.c.neon.h"
#include "NE10_fft_int16.s.neon.h"
#include "test_suite_fft_int16.h"

void fft_c2c_2d_int16_c(ne10_int16_t *src,ne10_int16_t *dst,ne10_int32_t fftRowSize,ne10_int32_t fftColSize)
{
	ne10_int32_t i = 0;
	ne10_int32_t j = 0;
    ne10_fft_cfg_int16_t cfgrow;
	ne10_fft_cfg_int16_t cfgcol;
    ne10_float32_t * out_c_tmp = NULL;
    FILE *fp=NULL;
	/* init input memory */
    in_c = (ne10_int16_t*) NE10_MALLOC ( (fftRowSize*fftColSize*2) * sizeof (ne10_int16_t));
	/* init dst memory */
	temp_out_c = (ne10_int16_t*) NE10_MALLOC ( (fftRowSize*fftColSize*2) * sizeof (ne10_int16_t));
	temp_out_c1 = (ne10_int16_t*) NE10_MALLOC ( (fftRowSize*fftColSize*2) * sizeof (ne10_int16_t));
	temp_out_c2 = (ne10_int16_t*) NE10_MALLOC ( (fftRowSize*fftColSize*2) * sizeof (ne10_int16_t));
    out_c = (ne10_int16_t*) NE10_MALLOC ( (fftRowSize*fftColSize*2) * sizeof (ne10_int16_t));

	cfgcol = ne10_fft_alloc_c2c_int16 (fftColSize);
    if (cfgcol == NULL)
    {
        //fprintf (stdout, "======ERROR, FFT alloc fails\n");
        //return;
    }
	/* unscaled FFT test */
	memcpy (in_c, src, fftRowSize*fftColSize*2* sizeof (ne10_int16_t));
	#if 0
	fp=fopen("/data/testimg/srcc.txt","w");
	for(i=0;i<fftRowSize*fftColSize*2;i++)
		fprintf(fp,"%d\n",in_c[i]);
	fclose(fp);
	#endif
	/*
	for(i=0;i<fftRowSize;i++)
		{
			printf("----------------------%d---------------------\n",i);
			for(j=0;j<fftColSize;j++)
			{
				printf("%d ",in_c[i*fftColSize*2+2*j]);
				printf("%d ",in_c[i*fftColSize*2+2*j+1]);
				//fprintf(fp,"%d\n",in_c[i*fftColSize*2+2*j]);
				//fprintf(fp,"%d\n",in_c[i*fftColSize*2+2*j+1]);
			}
			printf("\n");
		}
	//printf("\n");
	*/
	#if 0
	fp=fopen("/data/testimg/rowtemp.txt","w");
		//for(j=0;j<fftColSize*2;j++)
		//{
		//	fprintf(fp,"%d\n",in_c[j]);
		//}
		
	ne10_fft_c2c_1d_int16_c ( (ne10_fft_cpx_int16_t*) (temp_out_c), (ne10_fft_cpx_int16_t*) (in_c), cfgcol, 0, 0);
		for(j=0;j<fftColSize*2;j++)
		{
			fprintf(fp,"%d\n",temp_out_c[j]);
		}
		fclose(fp);
	#endif
	for(i=0;i<fftRowSize;i++)
	{
		
		#if 0
		//printf("input:");
		for(j=0;j<fftColSize*2;j++)
		{
			fprintf(fp,"%d ",in_c[j+fftColSize*i*2]);
		}
		//printf("\n");
		#endif
		
        ne10_fft_c2c_1d_int16_c ( (ne10_fft_cpx_int16_t*) (temp_out_c+fftColSize*i*2), (ne10_fft_cpx_int16_t*) (in_c+fftColSize*i*2), cfgcol, 0, 0);
		
		//printf("output:");
		//for(j=0;j<fftColSize*2;j++)
		//{
		//	printf("%d ",temp_out_c[j+fftColSize*i*2]);
		//}
		//printf("\n");
		//printf("\n");
		
	}
	#if 0
	fp=fopen("/data/testimg/fft2rowout.txt","w");
	for(i=0;i<fftRowSize*fftColSize*2;i++)
		fprintf(fp,"%d\n",temp_out_c[i]);
	fclose(fp);
	#endif
	/*
	for(i=0;i<fftRowSize;i++)
		{
			printf("----------------------%d---------------------\n",i);
			for(j=0;j<fftColSize;j++)
			{
				//printf("%d ",temp_out_c[i*fftColSize*2+2*j]);
				//printf("%d ",temp_out_c[i*fftColSize*2+2*j+1]);
				//fprintf(fp,"%d\n",temp_out_c[i*fftColSize*2+2*j]);
				//fprintf(fp,"%d\n",temp_out_c[i*fftColSize*2+2*j+1]);
			}
			printf("\n");
		}
	//printf("\n");
	*/
	#if 0
	printf("------------------------------------------------------\n");
	#endif
	cfgrow = ne10_fft_alloc_c2c_int16 (fftRowSize);
        if (cfgrow == NULL)
        {
            //fprintf (stdout, "======ERROR, FFT alloc fails\n");
            //return;
        }
		
		for(i=0;i<fftRowSize;i++)
		{
			//printf("----------------------%d---------------------\n",i);
			for(j=0;j<fftColSize;j++)
				{
					temp_out_c1[j*fftRowSize*2+i*2]=temp_out_c[i*fftColSize*2+j*2];
					temp_out_c1[j*fftRowSize*2+i*2+1]=temp_out_c[i*fftColSize*2+j*2+1];
				}
		}
		#if 0
		fp=fopen("/data/testimg/fft2colin.txt","w");
		for(i=0;i<fftRowSize*fftColSize*2;i++)
			fprintf(fp,"%d\n",temp_out_c1[i]);
		fclose(fp);
		#endif
		for(i=0;i<fftColSize;i++)
		{
			/*
			#ifdef Debug
			printf("input:");
			for(j=0;j<fftRowSize*2;j++)
				{
					printf("%d ",temp_out_c1[j+fftRowSize*i*2]);
				}
			printf("\n");
			#endif
			*/
			ne10_fft_c2c_1d_int16_c ( (ne10_fft_cpx_int16_t*) (temp_out_c2+fftRowSize*i*2), (ne10_fft_cpx_int16_t*) (temp_out_c1+fftRowSize*i*2), cfgrow, 0, 0);
			/*
			#ifdef Debug
			printf("output:");
			for(j=0;j<fftRowSize*2;j++)
				{
					printf("%d ",temp_out_c2[j+fftRowSize*i*2]);
				}
			printf("\n");
			printf("\n");
			#endif
			*/
		}
		#if 0
		fp=fopen("/data/testimg/fft2colout.txt","w");
		for(i=0;i<fftRowSize*fftColSize*2;i++)
			fprintf(fp,"%d\n",temp_out_c2[i]);
		fclose(fp);
		#endif
		for(i=0;i<fftRowSize;i++)
		{
			for(j=0;j<fftColSize;j++)
				{
					dst[i*fftColSize*2+j*2]=temp_out_c2[j*fftRowSize*2+i*2];
					dst[i*fftColSize*2+j*2+1]=temp_out_c2[j*fftRowSize*2+i*2+1];
				}
		}
		#if 0
		fp=fopen("/data/testimg/fftdstc.txt","w");
		for(i=0;i<fftRowSize*fftColSize*2;i++)
			fprintf(fp,"%d\n",dst[i]);
		fclose(fp);
		#endif
	NE10_FREE(in_c);
	NE10_FREE(temp_out_c);
	NE10_FREE(temp_out_c1);
	NE10_FREE(temp_out_c2);
	NE10_FREE(out_c);
}

void ifft_c2c_2d_int16_c(ne10_int16_t *src,ne10_int16_t *dst,ne10_int32_t fftRowSize,ne10_int32_t fftColSize)
{
	ne10_int32_t i = 0;
	ne10_int32_t j = 0;
    ne10_fft_cfg_int16_t cfgrow;
	ne10_fft_cfg_int16_t cfgcol;
    ne10_float32_t * out_c_tmp = NULL;
    FILE *fp=NULL;
	    /* init input memory */
    in_c = (ne10_int16_t*) NE10_MALLOC ( (fftRowSize*fftColSize*2) * sizeof (ne10_int16_t));
	    /* init dst memory */
	temp_out_c = (ne10_int16_t*) NE10_MALLOC ( (fftRowSize*fftColSize*2) * sizeof (ne10_int16_t));
	temp_out_c1 = (ne10_int16_t*) NE10_MALLOC ( (fftRowSize*fftColSize*2) * sizeof (ne10_int16_t));
	temp_out_c2 = (ne10_int16_t*) NE10_MALLOC ( (fftRowSize*fftColSize*2) * sizeof (ne10_int16_t));
    out_c = (ne10_int16_t*) NE10_MALLOC ( (fftRowSize*fftColSize*2) * sizeof (ne10_int16_t));

	cfgcol = ne10_fft_alloc_c2c_int16 (fftColSize);
        if (cfgcol == NULL)
        {
            //fprintf (stdout, "======ERROR, FFT alloc fails\n");
            //return;
        }
	/* unscaled FFT test */
	memcpy (in_c, src, fftRowSize*fftColSize*2* sizeof (ne10_int16_t));
	#if 0
	for(i=0;i<fftRowSize*fftColSize*2;i++)
		{
			printf("%d ",in_c[i]);
		}
	printf("\n");
	#endif // DEBUG


	for(i=0;i<fftRowSize;i++)
	{
		#if 0
		printf("input:");
		for(j=0;j<fftColSize*2;j++)
		{
			printf("%d ",in_c[j+fftColSize*i*2]);
		}
		printf("\n");
		#endif // DEBUG
        ne10_fft_c2c_1d_int16_c ( (ne10_fft_cpx_int16_t*) (temp_out_c+fftColSize*i*2), (ne10_fft_cpx_int16_t*) (in_c+fftColSize*i*2), cfgcol, 1, 0);
		#if 0
		printf("output:");
		for(j=0;j<fftColSize*2;j++)
		{
			printf("%d ",temp_out_c[j+fftColSize*i*2]);
		}
		printf("\n");
		
		printf("\n");
		#endif
	}
	
	//fp=fopen("ifft2rowout.txt","w");
	for(i=0;i<fftRowSize*fftColSize*2;i++)
		{
			if(temp_out_c[i]>=0)
				temp_out_c[i]=(temp_out_c[i]+fftColSize/2)/fftColSize;
			else
				temp_out_c[i]=(temp_out_c[i]-fftColSize/2)/fftColSize;
			
			//fprintf(fp,"%d\n",temp_out_c[i]);
		}
	//fclose(fp);
	//printf("\n");

	#if 0
	printf("------------------------------------------------------\n");
	#endif
	cfgrow = ne10_fft_alloc_c2c_int16 (fftRowSize);
        if (cfgrow == NULL)
        {
            //fprintf (stdout, "======ERROR, FFT alloc fails\n");
            //return;
        }

		for(i=0;i<fftRowSize;i++)
		{
			for(j=0;j<fftColSize;j++)
				{
					temp_out_c1[j*fftRowSize*2+i*2]=temp_out_c[i*fftColSize*2+j*2];
					temp_out_c1[j*fftRowSize*2+i*2+1]=temp_out_c[i*fftColSize*2+j*2+1];
				}
		}
		for(i=0;i<fftColSize;i++)
		{
			#if 0
			printf("input:");
			for(j=0;j<fftRowSize*2;j++)
				{
					printf("%d ",temp_out_c1[j+fftRowSize*i*2]);
				}
			printf("\n");
			#endif
			ne10_fft_c2c_1d_int16_c ( (ne10_fft_cpx_int16_t*) (temp_out_c2+fftRowSize*i*2), (ne10_fft_cpx_int16_t*) (temp_out_c1+fftRowSize*i*2), cfgrow, 1, 0);
			#if 0
			printf("output:");
			for(j=0;j<fftRowSize*2;j++)
				{
					printf("%d ",temp_out_c2[j+fftRowSize*i*2]);
				}
			printf("\n");
			printf("\n");
			#endif
		}
		for(i=0;i<fftRowSize*fftColSize*2;i++)
		{
					if(temp_out_c2[i]>=0)
					{
						temp_out_c2[i]=(temp_out_c2[i]+fftRowSize/2)/(fftRowSize);
					}
					else
					{
						temp_out_c2[i]=(temp_out_c2[i]-fftRowSize/2)/(fftRowSize);		
					}			
		}
		#if 0
		fp=fopen("ifft2colout.txt","w");
		for(i=0;i<fftRowSize*fftColSize*2;i++)
			fprintf(fp,"%d\n",temp_out_c2[i]);
		fclose(fp);
		#endif
		for(i=0;i<fftRowSize;i++)
		{
			for(j=0;j<fftColSize;j++)
				{
					dst[i*fftColSize*2+j*2]=temp_out_c2[j*fftRowSize*2+i*2];
					dst[i*fftColSize*2+j*2+1]=temp_out_c2[j*fftRowSize*2+i*2+1];
				}
		}
		
}

void fft_c2c_2d_int16_neon(ne10_int16_t *src,ne10_int16_t *dst,ne10_int32_t fftRowSize,ne10_int32_t fftColSize)
{
	ne10_int32_t i = 0;
	ne10_int32_t j = 0;
    ne10_fft_cfg_int16_t cfgrow;
	ne10_fft_cfg_int16_t cfgcol;
    ne10_float32_t * out_c_tmp = NULL;
    FILE *fp=NULL;
	/* init input memory */
    in_c = (ne10_int16_t*) NE10_MALLOC ( (fftRowSize*fftColSize*2) * sizeof (ne10_int16_t));
	/* init dst memory */
	temp_out_c = (ne10_int16_t*) NE10_MALLOC ( (fftRowSize*fftColSize*2) * sizeof (ne10_int16_t));
	temp_out_c1 = (ne10_int16_t*) NE10_MALLOC ( (fftRowSize*fftColSize*2) * sizeof (ne10_int16_t));
	temp_out_c2 = (ne10_int16_t*) NE10_MALLOC ( (fftRowSize*fftColSize*2) * sizeof (ne10_int16_t));
    out_c = (ne10_int16_t*) NE10_MALLOC ( (fftRowSize*fftColSize*2) * sizeof (ne10_int16_t));

	cfgcol = ne10_fft_alloc_c2c_int16 (fftColSize);
        if (cfgcol == NULL)
        {
            //fprintf (stdout, "======ERROR, FFT alloc fails\n");
            //return;
        }
	/* unscaled FFT test */
	memcpy (in_c, src, fftRowSize*fftColSize*2* sizeof (ne10_int16_t));
	#if 0
	fp=fopen("/data/testimg/srcneon.txt","w");
	for(i=0;i<fftRowSize*fftColSize*2;i++)
		fprintf(fp,"%d\n",in_c[i]);
	fclose(fp);
	#endif
	/*
	for(i=0;i<fftRowSize;i++)
		{
			printf("----------------------%d---------------------\n",i);
			for(j=0;j<fftColSize;j++)
			{
				printf("%d ",in_c[i*fftColSize*2+2*j]);
				printf("%d ",in_c[i*fftColSize*2+2*j+1]);
				//fprintf(fp,"%d\n",in_c[i*fftColSize*2+2*j]);
				//fprintf(fp,"%d\n",in_c[i*fftColSize*2+2*j+1]);
			}
			printf("\n");
		}
	//printf("\n");
	*/
	#if 0
		fp=fopen("/data/testimg/rowtempneon.txt","w");
		for(j=0;j<fftColSize*2;j++)
		{
			fprintf(fp,"%d ",in_c[j]);
		}
		
		//printf("\n");
	ne10_fft_c2c_1d_int16_neon ( (ne10_fft_cpx_int16_t*) (temp_out_c), (ne10_fft_cpx_int16_t*) (in_c), cfgcol, 0, 0);
		for(j=0;j<fftColSize*2;j++)
		{
			fprintf(fp,"%d\n",temp_out_c[j]);
		}
		fclose(fp);
	#endif
	for(i=0;i<fftRowSize;i++)
	{
		/*
		#ifdef Debug
		printf("input:");
		for(j=0;j<fftColSize*2;j++)
		{
			printf("%d ",in_c[j+fftColSize*i*2]);
		}
		printf("\n");
		#endif
		*/
        //ne10_fft_c2c_1d_int16_c ( (ne10_fft_cpx_int16_t*) (temp_out_c+fftColSize*i*2), (ne10_fft_cpx_int16_t*) (in_c+fftColSize*i*2), cfgcol, 0, 0);
		ne10_fft_c2c_1d_int16_neon( (ne10_fft_cpx_int16_t*) (temp_out_c+fftColSize*i*2), (ne10_fft_cpx_int16_t*) (in_c+fftColSize*i*2), cfgcol, 0, 0);
		//printf("output:");
		//for(j=0;j<fftColSize*2;j++)
		//{
		//	printf("%d ",temp_out_c[j+fftColSize*i*2]);
		//}
		//printf("\n");
		//printf("\n");
		
	}
	#if 0
	fp=fopen("/data/testimg/fft2rowoutneon.txt","w");
	for(i=0;i<fftRowSize*fftColSize*2;i++)
		fprintf(fp,"%d\n",temp_out_c[i]);
	fclose(fp);
	#endif
	for(i=0;i<fftRowSize;i++)
		{
			printf("----------------------%d---------------------\n",i);
			for(j=0;j<fftColSize;j++)
			{
				//printf("%d ",temp_out_c[i*fftColSize*2+2*j]);
				//printf("%d ",temp_out_c[i*fftColSize*2+2*j+1]);
				//fprintf(fp,"%d\n",temp_out_c[i*fftColSize*2+2*j]);
				//fprintf(fp,"%d\n",temp_out_c[i*fftColSize*2+2*j+1]);
			}
			printf("\n");
		}
	//printf("\n");
	
	#if 0
	printf("------------------------------------------------------\n");
	#endif
	cfgrow = ne10_fft_alloc_c2c_int16 (fftRowSize);
        if (cfgrow == NULL)
        {
            //fprintf (stdout, "======ERROR, FFT alloc fails\n");
            //return;
        }
		
		for(i=0;i<fftRowSize;i++)
		{
			//printf("----------------------%d---------------------\n",i);
			for(j=0;j<fftColSize;j++)
				{
					temp_out_c1[j*fftRowSize*2+i*2]=temp_out_c[i*fftColSize*2+j*2];
					temp_out_c1[j*fftRowSize*2+i*2+1]=temp_out_c[i*fftColSize*2+j*2+1];
				}
		}
		#if 0
		fp=fopen("/data/testimg/fft2colinneon.txt","w");
		for(i=0;i<fftRowSize*fftColSize*2;i++)
			fprintf(fp,"%d\n",temp_out_c1[i]);
		fclose(fp);
		#endif
		for(i=0;i<fftColSize;i++)
		{
			/*
			#ifdef Debug
			printf("input:");
			for(j=0;j<fftRowSize*2;j++)
				{
					printf("%d ",temp_out_c1[j+fftRowSize*i*2]);
				}
			printf("\n");
			#endif
			*/
			//ne10_fft_c2c_1d_int16_c ( (ne10_fft_cpx_int16_t*) (temp_out_c2+fftRowSize*i*2), (ne10_fft_cpx_int16_t*) (temp_out_c1+fftRowSize*i*2), cfgrow, 0, 0);
			ne10_fft_c2c_1d_int16_neon( (ne10_fft_cpx_int16_t*) (temp_out_c2+fftRowSize*i*2), (ne10_fft_cpx_int16_t*) (temp_out_c1+fftRowSize*i*2), cfgrow, 0, 0);
			/*
			#ifdef Debug
			printf("output:");
			for(j=0;j<fftRowSize*2;j++)
				{
					printf("%d ",temp_out_c2[j+fftRowSize*i*2]);
				}
			printf("\n");
			printf("\n");
			#endif
			*/
		}
		#if 0
		fp=fopen("/data/testimg/fft2coloutneon.txt","w");
		for(i=0;i<fftRowSize*fftColSize*2;i++)
			fprintf(fp,"%d\n",temp_out_c2[i]);
		fclose(fp);
		#endif
		
		for(i=0;i<fftRowSize;i++)
		{
			for(j=0;j<fftColSize;j++)
				{
					dst[i*fftColSize*2+j*2]=temp_out_c2[j*fftRowSize*2+i*2];
					dst[i*fftColSize*2+j*2+1]=temp_out_c2[j*fftRowSize*2+i*2+1];
				}
		}
		#if 0
		fp=fopen("/data/testimg/fftdstn.txt","w");
		for(i=0;i<fftRowSize*fftColSize*2;i++)
			fprintf(fp,"%d\n",dst[i]);
		fclose(fp);
		#endif
		NE10_FREE(in_c);
		NE10_FREE(temp_out_c);
		NE10_FREE(temp_out_c1);
		NE10_FREE(temp_out_c2);
		NE10_FREE(out_c);
}

void ifft_c2c_2d_int16_neon(ne10_int16_t *src,ne10_int16_t *dst,ne10_int32_t fftRowSize,ne10_int32_t fftColSize)
{
	ne10_int32_t i = 0;
	ne10_int32_t j = 0;
    ne10_fft_cfg_int16_t cfgrow;
	ne10_fft_cfg_int16_t cfgcol;
    ne10_float32_t * out_c_tmp = NULL;
    FILE *fp=NULL;
	    /* init input memory */
    in_c = (ne10_int16_t*) NE10_MALLOC ( (fftRowSize*fftColSize*2) * sizeof (ne10_int16_t));
	    /* init dst memory */
	temp_out_c = (ne10_int16_t*) NE10_MALLOC ( (fftRowSize*fftColSize*2) * sizeof (ne10_int16_t));
	temp_out_c1 = (ne10_int16_t*) NE10_MALLOC ( (fftRowSize*fftColSize*2) * sizeof (ne10_int16_t));
	temp_out_c2 = (ne10_int16_t*) NE10_MALLOC ( (fftRowSize*fftColSize*2) * sizeof (ne10_int16_t));
    out_c = (ne10_int16_t*) NE10_MALLOC ( (fftRowSize*fftColSize*2) * sizeof (ne10_int16_t));

	cfgcol = ne10_fft_alloc_c2c_int16 (fftColSize);
        if (cfgcol == NULL)
        {
            //fprintf (stdout, "======ERROR, FFT alloc fails\n");
            //return;
        }
	/* unscaled FFT test */
	memcpy (in_c, src, fftRowSize*fftColSize*2* sizeof (ne10_int16_t));
	#if 0
	for(i=0;i<fftRowSize*fftColSize*2;i++)
		{
			printf("%d ",in_c[i]);
		}
	printf("\n");
	#endif // DEBUG


	for(i=0;i<fftRowSize;i++)
	{
		#if 0
		printf("input:");
		for(j=0;j<fftColSize*2;j++)
		{
			printf("%d ",in_c[j+fftColSize*i*2]);
		}
		printf("\n");
		#endif // DEBUG
        //ne10_fft_c2c_1d_int16_c ( (ne10_fft_cpx_int16_t*) (temp_out_c+fftColSize*i*2), (ne10_fft_cpx_int16_t*) (in_c+fftColSize*i*2), cfgcol, 1, 0);
		ne10_fft_c2c_1d_int16_neon ( (ne10_fft_cpx_int16_t*) (temp_out_c+fftColSize*i*2), (ne10_fft_cpx_int16_t*) (in_c+fftColSize*i*2), cfgcol, 1, 0);
		#if 0
		printf("output:");
		for(j=0;j<fftColSize*2;j++)
		{
			printf("%d ",temp_out_c[j+fftColSize*i*2]);
		}
		printf("\n");
		
		printf("\n");
		#endif
	}
	
	//fp=fopen("ifft2rowout.txt","w");
	for(i=0;i<fftRowSize*fftColSize*2;i++)
		{
			if(temp_out_c[i]>=0)
				temp_out_c[i]=(temp_out_c[i]+fftColSize/2)/fftColSize;
			else
				temp_out_c[i]=(temp_out_c[i]-fftColSize/2)/fftColSize;
			
			//fprintf(fp,"%d\n",temp_out_c[i]);
		}
	//fclose(fp);
	//printf("\n");

	#if 0
	printf("------------------------------------------------------\n");
	#endif
	cfgrow = ne10_fft_alloc_c2c_int16 (fftRowSize);
        if (cfgrow == NULL)
        {
            //fprintf (stdout, "======ERROR, FFT alloc fails\n");
            //return;
        }

		for(i=0;i<fftRowSize;i++)
		{
			for(j=0;j<fftColSize;j++)
				{
					temp_out_c1[j*fftRowSize*2+i*2]=temp_out_c[i*fftColSize*2+j*2];
					temp_out_c1[j*fftRowSize*2+i*2+1]=temp_out_c[i*fftColSize*2+j*2+1];
				}
		}
		for(i=0;i<fftColSize;i++)
		{
			#if 0
			printf("input:");
			for(j=0;j<fftRowSize*2;j++)
				{
					printf("%d ",temp_out_c1[j+fftRowSize*i*2]);
				}
			printf("\n");
			#endif
			//ne10_fft_c2c_1d_int16_c ( (ne10_fft_cpx_int16_t*) (temp_out_c2+fftRowSize*i*2), (ne10_fft_cpx_int16_t*) (temp_out_c1+fftRowSize*i*2), cfgrow, 1, 0);
			ne10_fft_c2c_1d_int16_neon ( (ne10_fft_cpx_int16_t*) (temp_out_c2+fftRowSize*i*2), (ne10_fft_cpx_int16_t*) (temp_out_c1+fftRowSize*i*2), cfgrow, 1, 0);
			#if 0
			printf("output:");
			for(j=0;j<fftRowSize*2;j++)
				{
					printf("%d ",temp_out_c2[j+fftRowSize*i*2]);
				}
			printf("\n");
			printf("\n");
			#endif
		}
		for(i=0;i<fftRowSize*fftColSize*2;i++)
		{
					if(temp_out_c2[i]>=0)
					{
						temp_out_c2[i]=(temp_out_c2[i]+fftRowSize/2)/(fftRowSize);
					}
					else
					{
						temp_out_c2[i]=(temp_out_c2[i]-fftRowSize/2)/(fftRowSize);		
					}			
		}
		#if 0
		fp=fopen("ifft2colout.txt","w");
		for(i=0;i<fftRowSize*fftColSize*2;i++)
			fprintf(fp,"%d\n",temp_out_c2[i]);
		fclose(fp);
		#endif
		for(i=0;i<fftRowSize;i++)
		{
			for(j=0;j<fftColSize;j++)
				{
					dst[i*fftColSize*2+j*2]=temp_out_c2[j*fftRowSize*2+i*2];
					dst[i*fftColSize*2+j*2+1]=temp_out_c2[j*fftRowSize*2+i*2+1];
				}
		}
		
}

void test_fft_c2c_1d_int16_conformance()
{
	ne10_int32_t err;
    ne10_int32_t i = 0;
    ne10_int32_t fftSize = 0;
    ne10_fft_cfg_int16_t cfg;
    ne10_float32_t * out_c_tmp = NULL;
    ne10_float32_t * out_neon_tmp = NULL;
	ne10_int16_t src[TEST_LENGTH_SAMPLES*2];
	FILE *file;
    fprintf (stdout, "----------%30s start\n", __FUNCTION__);

    /* init input memory */
    guarded_in_c = (ne10_int16_t*) NE10_MALLOC ( (TEST_LENGTH_SAMPLES * 2 + ARRAY_GUARD_LEN * 2) * sizeof (ne10_int16_t));
    //guarded_in_neon = (ne10_int16_t*) NE10_MALLOC ( (TEST_LENGTH_SAMPLES * 2 + ARRAY_GUARD_LEN * 2) * sizeof (ne10_int16_t));
    in_c = guarded_in_c + ARRAY_GUARD_LEN;
    //in_neon = guarded_in_neon + ARRAY_GUARD_LEN;
	in_c1 = (ne10_int16_t*) NE10_MALLOC ( (TEST_LENGTH_SAMPLES * 2) * sizeof (ne10_int16_t));
    /* init dst memory */
    guarded_out_c = (ne10_int16_t*) NE10_MALLOC ( (TEST_LENGTH_SAMPLES * 2 + ARRAY_GUARD_LEN * 2) * sizeof (ne10_int16_t));
    //guarded_out_neon = (ne10_int16_t*) NE10_MALLOC ( (TEST_LENGTH_SAMPLES * 2 + ARRAY_GUARD_LEN * 2) * sizeof (ne10_int16_t));
    out_c = guarded_out_c + ARRAY_GUARD_LEN;
    //out_neon = guarded_out_neon + ARRAY_GUARD_LEN;
	out_c1 = (ne10_int16_t*) NE10_MALLOC ( (TEST_LENGTH_SAMPLES * 2 ) * sizeof (ne10_int16_t));
    out_c_tmp = (ne10_float32_t*) NE10_MALLOC ( (TEST_LENGTH_SAMPLES * 2) * sizeof (ne10_float32_t));
    //out_neon_tmp = (ne10_float32_t*) NE10_MALLOC ( (TEST_LENGTH_SAMPLES * 2) * sizeof (ne10_float32_t));

    for (i = 0; i < TEST_LENGTH_SAMPLES * 2; i++)
    {
        testInput_i16_unscaled[i] = (ne10_int32_t) (drand48() * 1024) - 512;
        testInput_i16_scaled[i] = (ne10_int16_t) (drand48() * NE10_F2I16_MAX) - NE10_F2I16_MAX / 2;
    }
	printf("input\n");



	for(i=0;i<TEST_LENGTH_SAMPLES*2;i++)
		src[i]=i;
	//src[2]=12;
	//src[4]=25;
	//src[6]=38;
	//src[8]=51;
	//src[10]=64;
	//src[12]=76;
	//src[14]=89;
	file=fopen("data.txt","w");
    //for (fftSize = MIN_LENGTH_SAMPLES_CPX; fftSize <= TEST_LENGTH_SAMPLES; fftSize *= 2)
	for (fftSize = MIN_LENGTH_SAMPLES_CPX*16; fftSize <= MIN_LENGTH_SAMPLES_CPX*16; fftSize *= 2)
    {
		err=0;
        fprintf (stdout, "FFT size %d\n", fftSize);
        cfg = ne10_fft_alloc_c2c_int16 (fftSize);
        if (cfg == NULL)
        {
            fprintf (stdout, "======ERROR, FFT alloc fails\n");
            return;
        }

        /* unscaled FFT test */
		//memcpy (in_c, src, 2 * fftSize * sizeof (ne10_int16_t));
        memcpy (in_c, testInput_i16_unscaled, 2 * fftSize * sizeof (ne10_int16_t));
        //memcpy (in_neon, testInput_i16_unscaled, 2 * fftSize * sizeof (ne10_int16_t));

        GUARD_ARRAY_UINT8 ( (ne10_uint8_t*) out_c, fftSize * 2 * sizeof (ne10_int16_t));
        //GUARD_ARRAY_UINT8 ( (ne10_uint8_t*) out_neon, fftSize * 2 * sizeof (ne10_int16_t));
		for (i = 0; i < fftSize * 2; i++)
		{
				//printf("%d ",in_c[i]);
				in_c1[i]=in_c[i];
				fprintf(file,"%d\n",in_c[i]);
		}
		fclose(file);
		printf("\n");
        ne10_fft_c2c_1d_int16_c    ( (ne10_fft_cpx_int16_t*) out_c, (ne10_fft_cpx_int16_t*) in_c, cfg, 0, 0);
		//ne10_fft_c2c_1d_int16_neon ( (ne10_fft_cpx_int16_t*) out_neon, (ne10_fft_cpx_int16_t*) in_neon, cfg, 0, 0);
		//for (i = 0; i < fftSize * 2; i++)
		//{
		//		printf("%d,%d\n",in_c[i],out_c[i]);
		//}
		//printf("\n");
        //ne10_fft_c2c_1d_int16_neon ( (ne10_fft_cpx_int16_t*) out_neon, (ne10_fft_cpx_int16_t*) in_neon, cfg, 0, 0);

        CHECK_ARRAY_GUARD_UINT8 ( (ne10_uint8_t*) out_c, fftSize * 2 * sizeof (ne10_int16_t));
        //CHECK_ARRAY_GUARD_UINT8 ( (ne10_uint8_t*) out_neon, fftSize * 2 * sizeof (ne10_int16_t));

        //conformance test
        //for (i = 0; i < TEST_LENGTH_SAMPLES * 2; i++)
        //{
        //    out_c_tmp[i] = (ne10_float32_t) out_c[i];
        //    out_neon_tmp[i] = (ne10_float32_t) out_neon[i];
        //}
        //snr = CAL_SNR_FLOAT32 (out_c_tmp, out_neon_tmp, fftSize * 2);
        //assert_false ( (snr < SNR_THRESHOLD_INT16));

        /* IFFT test */
		memcpy (in_c, out_c, 2 * fftSize * sizeof (ne10_int16_t));
        //memcpy (in_c, testInput_i16_unscaled, 2 * fftSize * sizeof (ne10_int16_t));
        //memcpy (in_neon, testInput_i16_unscaled, 2 * fftSize * sizeof (ne10_int16_t));

        GUARD_ARRAY_UINT8 ( (ne10_uint8_t*) out_c, fftSize * 2 * sizeof (ne10_int16_t));
        //GUARD_ARRAY_UINT8 ( (ne10_uint8_t*) out_neon, fftSize * 2 * sizeof (ne10_int16_t));
		//for (i = 0; i < fftSize * 2; i++)
		//{
		//		printf("%d ",in_c[i]);
		//}
		//printf("\n");
		//for (i = 0; i < fftSize ; i++)
		//{
		//		in_c[2*i+1]=-in_c[2*i+1];
		//		//printf("%d ",in_c[i]);
		//}
        //GET_TIME
        //(
        //    time_c,
        //{
        ne10_fft_c2c_1d_int16_c ( (ne10_fft_cpx_int16_t*) out_c, (ne10_fft_cpx_int16_t*) in_c, cfg, 1, 0);
		//}
        //);
		//printf("time_c=%ld\n",time_c);
		//for (i = 0; i < fftSize * 2; i++)
		//{
		//		printf("%d ",out_c[i]);
		//}
		//printf("\n");
		for (i = 0; i < fftSize * 2; i++)
		{
				//printf("%d ",(out_c[i]+fftSize/2)/fftSize);
				if(out_c[i]>=0)
					out_c1[i]=(out_c[i]+fftSize/2)/fftSize;
				else
					out_c1[i]=(out_c[i]-fftSize/2)/fftSize;
		}
		for (i = 0; i < fftSize * 2; i++)
		{
			printf("%d,%d,%d,%d\n",in_c1[i],out_c1[i],in_c[i],out_c[i]);
			if((out_c1[i]-in_c1[i])!=0)
				err++;
		}
		printf("err=%d\n",err);

        //ne10_fft_c2c_1d_int16_neon ( (ne10_fft_cpx_int16_t*) out_neon, (ne10_fft_cpx_int16_t*) in_neon, cfg, 1, 0);

        CHECK_ARRAY_GUARD_UINT8 ( (ne10_uint8_t*) out_c, fftSize * 2 * sizeof (ne10_int16_t));
        //CHECK_ARRAY_GUARD_UINT8 ( (ne10_uint8_t*) out_neon, fftSize * 2 * sizeof (ne10_int16_t));

        //conformance test
        //for (i = 0; i < TEST_LENGTH_SAMPLES * 2; i++)
        //{
        //    out_c_tmp[i] = (ne10_float32_t) out_c[i];
        //    out_neon_tmp[i] = (ne10_float32_t) out_neon[i];
        //}
        //snr = CAL_SNR_FLOAT32 (out_c_tmp, out_neon_tmp, fftSize * 2);
        //assert_false ( (snr < SNR_THRESHOLD_INT16));

        /* scaled FFT test */
        //memcpy (in_c, testInput_i16_scaled, 2 * fftSize * sizeof (ne10_int16_t));
        //memcpy (in_neon, testInput_i16_scaled, 2 * fftSize * sizeof (ne10_int16_t));

       // GUARD_ARRAY_UINT8 ( (ne10_uint8_t*) out_c, fftSize * 2 * sizeof (ne10_int16_t));
        //GUARD_ARRAY_UINT8 ( (ne10_uint8_t*) out_neon, fftSize * 2 * sizeof (ne10_int16_t));

        //ne10_fft_c2c_1d_int16_c ( (ne10_fft_cpx_int16_t*) out_c, (ne10_fft_cpx_int16_t*) in_c, cfg, 0, 1);
        //ne10_fft_c2c_1d_int16_neon ( (ne10_fft_cpx_int16_t*) out_neon, (ne10_fft_cpx_int16_t*) in_neon, cfg, 0, 1);

        //CHECK_ARRAY_GUARD_UINT8 ( (ne10_uint8_t*) out_c, fftSize * 2 * sizeof (ne10_int16_t));
        //CHECK_ARRAY_GUARD_UINT8 ( (ne10_uint8_t*) out_neon, fftSize * 2 * sizeof (ne10_int16_t));

        //conformance test
        //for (i = 0; i < TEST_LENGTH_SAMPLES * 2; i++)
        //{
        //    out_c_tmp[i] = (ne10_float32_t) out_c[i];
        //    out_neon_tmp[i] = (ne10_float32_t) out_neon[i];
        //}
        //snr = CAL_SNR_FLOAT32 (out_c_tmp, out_neon_tmp, fftSize * 2);
        //assert_false ( (snr < SNR_THRESHOLD_INT16));

        /* IFFT test */
        //memcpy (in_c, testInput_i16_scaled, 2 * fftSize * sizeof (ne10_int16_t));
        //memcpy (in_neon, testInput_i16_scaled, 2 * fftSize * sizeof (ne10_int16_t));

        //GUARD_ARRAY_UINT8 ( (ne10_uint8_t*) out_c, fftSize * 2 * sizeof (ne10_int16_t));
        //GUARD_ARRAY_UINT8 ( (ne10_uint8_t*) out_neon, fftSize * 2 * sizeof (ne10_int16_t));

        //ne10_fft_c2c_1d_int16_c ( (ne10_fft_cpx_int16_t*) out_c, (ne10_fft_cpx_int16_t*) in_c, cfg, 1, 1);
        //ne10_fft_c2c_1d_int16_neon ( (ne10_fft_cpx_int16_t*) out_neon, (ne10_fft_cpx_int16_t*) in_neon, cfg, 1, 1);

        //CHECK_ARRAY_GUARD_UINT8 ( (ne10_uint8_t*) out_c, fftSize * 2 * sizeof (ne10_int16_t));
        //CHECK_ARRAY_GUARD_UINT8 ( (ne10_uint8_t*) out_neon, fftSize * 2 * sizeof (ne10_int16_t));

        //conformance test
        //for (i = 0; i < TEST_LENGTH_SAMPLES * 2; i++)
        //{
        //    out_c_tmp[i] = (ne10_float32_t) out_c[i];
        //    out_neon_tmp[i] = (ne10_float32_t) out_neon[i];
        //}
       // snr = CAL_SNR_FLOAT32 (out_c_tmp, out_neon_tmp, fftSize * 2);
        //assert_false ( (snr < SNR_THRESHOLD_INT16));

        NE10_FREE (cfg);
    }

    NE10_FREE (guarded_in_c);
    //NE10_FREE (guarded_in_neon);
    NE10_FREE (guarded_out_c);
    //NE10_FREE (guarded_out_neon);
    NE10_FREE (out_c_tmp);
    //NE10_FREE (out_neon_tmp);
}

//void test_fft_c2c_1d_int16_performance()
//{
//	ne10_int32_t i = 0;
//    ne10_int32_t fftSize = 0;
//    ne10_fft_cfg_int16_t cfg;
//    ne10_int32_t test_loop = 0;
//
//    fprintf (stdout, "----------%30s start\n", __FUNCTION__);
//    fprintf (stdout, "%25s%20s%20s%20s%20s\n", "FFT Length", "C Time in ms", "NEON Time in ms", "Time Savings", "Performance Ratio");
//
//    /* init input memory */
//    guarded_in_c = (ne10_int16_t*) NE10_MALLOC ( (TEST_LENGTH_SAMPLES * 2 + ARRAY_GUARD_LEN * 2) * sizeof (ne10_int16_t));
//    guarded_in_neon = (ne10_int16_t*) NE10_MALLOC ( (TEST_LENGTH_SAMPLES * 2 + ARRAY_GUARD_LEN * 2) * sizeof (ne10_int16_t));
//    in_c = guarded_in_c + ARRAY_GUARD_LEN;
//    in_neon = guarded_in_neon + ARRAY_GUARD_LEN;
//
//    /* init dst memory */
//    guarded_out_c = (ne10_int16_t*) NE10_MALLOC ( (TEST_LENGTH_SAMPLES * 2 + ARRAY_GUARD_LEN * 2) * sizeof (ne10_int16_t));
//    guarded_out_neon = (ne10_int16_t*) NE10_MALLOC ( (TEST_LENGTH_SAMPLES * 2 + ARRAY_GUARD_LEN * 2) * sizeof (ne10_int16_t));
//    out_c = guarded_out_c + ARRAY_GUARD_LEN;
//    out_neon = guarded_out_neon + ARRAY_GUARD_LEN;
//
//    for (i = 0; i < TEST_LENGTH_SAMPLES * 2; i++)
//    {
//        testInput_i16_unscaled[i] = (ne10_int16_t) (drand48() * 1024) - 512;
//        testInput_i16_scaled[i] = (ne10_int16_t) (drand48() * NE10_F2I16_MAX) - NE10_F2I16_MAX / 2;
//    }
//    for (fftSize = MIN_LENGTH_SAMPLES_CPX; fftSize <= TEST_LENGTH_SAMPLES; fftSize *= 2)
//    {
//        fprintf (stdout, "FFT size %d\n", fftSize);
//        cfg = ne10_fft_alloc_c2c_int16 (fftSize);
//        if (cfg == NULL)
//        {
//            fprintf (stdout, "======ERROR, FFT alloc fails\n");
//            return;
//        }
//        test_loop = TEST_COUNT / fftSize;
//
//        /* unscaled FFT test */
//        memcpy (in_c, testInput_i16_unscaled, 2 * fftSize * sizeof (ne10_int16_t));
//        memcpy (in_neon, testInput_i16_unscaled, 2 * fftSize * sizeof (ne10_int16_t));
//
//        GET_TIME
//        (
//            time_c,
//        {
//            for (i = 0; i < test_loop; i++)
//                ne10_fft_c2c_1d_int16_c ( (ne10_fft_cpx_int16_t*) out_c, (ne10_fft_cpx_int16_t*) in_c, cfg, 0, 0);
//        }
//        );
//        GET_TIME
//        (
//            time_neon,
//        {
//            //for (i = 0; i < test_loop; i++)
//            //    ne10_fft_c2c_1d_int16_neon ( (ne10_fft_cpx_int16_t*) out_neon, (ne10_fft_cpx_int16_t*) in_neon, cfg, 0, 0);
//        }
//        );
//
//        time_speedup = (ne10_float32_t) time_c / time_neon;
//        time_savings = ( ( (ne10_float32_t) (time_c - time_neon)) / time_c) * 100;
//        //ne10_log (__FUNCTION__, "Int16 unscaled FFT%21d%20lld%20lld%19.2f%%%18.2f:1\n", fftSize, time_c, time_neon, time_savings, time_speedup);
//
//        /* IFFT test */
//        memcpy (in_c, out_c, 2 * fftSize * sizeof (ne10_int16_t));
//        memcpy (in_neon, out_c, 2 * fftSize * sizeof (ne10_int16_t));
//
//        GET_TIME
//        (
//            time_c,
//        {
//            for (i = 0; i < test_loop; i++)
//                ne10_fft_c2c_1d_int16_c ( (ne10_fft_cpx_int16_t*) out_c, (ne10_fft_cpx_int16_t*) in_c, cfg, 1, 0);
//        }
//        );
//        GET_TIME
//        (
//            time_neon,
//        {
//            //for (i = 0; i < test_loop; i++)
//            //    ne10_fft_c2c_1d_int16_neon ( (ne10_fft_cpx_int16_t*) out_neon, (ne10_fft_cpx_int16_t*) in_neon, cfg, 1, 0);
//        }
//        );
//
//        time_speedup = (ne10_float32_t) time_c / time_neon;
//        time_savings = ( ( (ne10_float32_t) (time_c - time_neon)) / time_c) * 100;
//        //ne10_log (__FUNCTION__, "Int16 unscaled FFT%21d%20lld%20lld%19.2f%%%18.2f:1\n", fftSize, time_c, time_neon, time_savings, time_speedup);
//        /* scaled FFT test */
//        memcpy (in_c, testInput_i16_scaled, 2 * fftSize * sizeof (ne10_int16_t));
//        memcpy (in_neon, testInput_i16_scaled, 2 * fftSize * sizeof (ne10_int16_t));
//
//        GET_TIME
//        (
//            time_c,
//        {
//            for (i = 0; i < test_loop; i++)
//                ne10_fft_c2c_1d_int16_c ( (ne10_fft_cpx_int16_t*) out_c, (ne10_fft_cpx_int16_t*) in_c, cfg, 0, 1);
//        }
//        );
//        GET_TIME
//        (
//            time_neon,
//        {
//        //    for (i = 0; i < test_loop; i++)
//        //        ne10_fft_c2c_1d_int16_neon ( (ne10_fft_cpx_int16_t*) out_neon, (ne10_fft_cpx_int16_t*) in_neon, cfg, 0, 1);
//        }
//        );
//
//        time_speedup = (ne10_float32_t) time_c / time_neon;
//        time_savings = ( ( (ne10_float32_t) (time_c - time_neon)) / time_c) * 100;
//        //ne10_log (__FUNCTION__, "Int16 scaled FFT%21d%20lld%20lld%19.2f%%%18.2f:1\n", fftSize, time_c, time_neon, time_savings, time_speedup);
//
//        /* IFFT test */
//        memcpy (in_c, out_c, 2 * fftSize * sizeof (ne10_int16_t));
//        memcpy (in_neon, out_c, 2 * fftSize * sizeof (ne10_int16_t));
//
//        GET_TIME
//        (
//            time_c,
//        {
//            for (i = 0; i < test_loop; i++)
//                ne10_fft_c2c_1d_int16_c ( (ne10_fft_cpx_int16_t*) out_c, (ne10_fft_cpx_int16_t*) in_c, cfg, 1, 1);
//        }
//        );
//        GET_TIME
//        (
//            time_neon,
//        {
//        //    for (i = 0; i < test_loop; i++)
//        //        ne10_fft_c2c_1d_int16_neon ( (ne10_fft_cpx_int16_t*) out_neon, (ne10_fft_cpx_int16_t*) in_neon, cfg, 1, 1);
//        }
//        );
//
//        time_speedup = (ne10_float32_t) time_c / time_neon;
//        time_savings = ( ( (ne10_float32_t) (time_c - time_neon)) / time_c) * 100;
//        //ne10_log (__FUNCTION__, "Int16 scaled FFT%21d%20lld%20lld%19.2f%%%18.2f:1\n", fftSize, time_c, time_neon, time_savings, time_speedup);
//
//        NE10_FREE (cfg);
//    }
//
//    NE10_FREE (guarded_in_c);
//    NE10_FREE (guarded_in_neon);
//    NE10_FREE (guarded_out_c);
//    NE10_FREE (guarded_out_neon);
//    
//}
//
//void test_fft_r2c_1d_int16_conformance()
//{
//	ne10_fft_r2c_cfg_int16_t cfg;
//    ne10_int32_t i = 0;
//    ne10_int32_t fftSize = 0;
//    ne10_float32_t * out_c_tmp = NULL;
//    ne10_float32_t * out_neon_tmp = NULL;
//
//    //fprintf (stdout, "----------%30s start\n", __FUNCTION__);
//
//    /* init input memory */
//    ne10_int16_t* guarded_in_c = (ne10_int16_t*) NE10_MALLOC ( (TEST_LENGTH_SAMPLES * 2 + ARRAY_GUARD_LEN * 2) * sizeof (ne10_int16_t));
//    ne10_int16_t* guarded_in_neon = (ne10_int16_t*) NE10_MALLOC ( (TEST_LENGTH_SAMPLES * 2 + ARRAY_GUARD_LEN * 2) * sizeof (ne10_int16_t));
//    in_c = guarded_in_c + ARRAY_GUARD_LEN;
//    in_neon = guarded_in_neon + ARRAY_GUARD_LEN;
//
//    /* init dst memory */
//    ne10_int16_t* guarded_out_c = (ne10_int16_t*) NE10_MALLOC ( (TEST_LENGTH_SAMPLES * 2 + ARRAY_GUARD_LEN * 2) * sizeof (ne10_int16_t));
//    ne10_int16_t* guarded_out_neon = (ne10_int16_t*) NE10_MALLOC ( (TEST_LENGTH_SAMPLES * 2 + ARRAY_GUARD_LEN * 2) * sizeof (ne10_int16_t));
//    out_c = guarded_out_c + ARRAY_GUARD_LEN;
//    //out_neon = guarded_out_neon + ARRAY_GUARD_LEN;
//
//    out_c_tmp = (ne10_float32_t*) NE10_MALLOC ( (TEST_LENGTH_SAMPLES * 2) * sizeof (ne10_float32_t));
//    //out_neon_tmp = (ne10_float32_t*) NE10_MALLOC ( (TEST_LENGTH_SAMPLES * 2) * sizeof (ne10_float32_t));
//
//    for (i = 0; i < TEST_LENGTH_SAMPLES * 2; i++)
//    {
//        testInput_i16_unscaled[i] = (ne10_int16_t) (drand48() * 1024) - 512;
//        testInput_i16_scaled[i] = (ne10_int16_t) (drand48() * NE10_F2I16_MAX) - NE10_F2I16_MAX / 2;
//    }
//    for (fftSize = MIN_LENGTH_SAMPLES_REAL; fftSize <= TEST_LENGTH_SAMPLES; fftSize *= 2)
//    {
//        fprintf (stdout, "RFFT size %d\n", fftSize);
//        cfg = ne10_fft_alloc_r2c_int16 (fftSize);
//        if (cfg == NULL)
//        {
//            fprintf (stdout, "======ERROR, FFT alloc fails\n");
//            return;
//        }
//
//        /* unscaled FFT test */
//        memcpy (in_c, testInput_i16_unscaled, fftSize * sizeof (ne10_int16_t));
//        memcpy (in_neon, testInput_i16_unscaled, fftSize * sizeof (ne10_int16_t));
//
//        GUARD_ARRAY_UINT8 ( (ne10_uint8_t*) out_c, (fftSize / 2 + 1) * 2 * sizeof (ne10_int16_t));
//        GUARD_ARRAY_UINT8 ( (ne10_uint8_t*) out_neon, (fftSize / 2 + 1) * 2 * sizeof (ne10_int16_t));
//
//        ne10_fft_r2c_1d_int16_c ( (ne10_fft_cpx_int16_t*) out_c, in_c, cfg, 0);
//        //ne10_fft_r2c_1d_int16_neon ( (ne10_fft_cpx_int16_t*) out_neon, in_neon, cfg, 0);
//
//        CHECK_ARRAY_GUARD_UINT8 ( (ne10_uint8_t*) out_c, (fftSize / 2 + 1) * 2 * sizeof (ne10_int16_t));
//        CHECK_ARRAY_GUARD_UINT8 ( (ne10_uint8_t*) out_neon, (fftSize / 2 + 1) * 2 * sizeof (ne10_int16_t));
//
//        //conformance test
//        for (i = 0; i < (fftSize / 2 + 1) * 2; i++)
//        {
//            out_c_tmp[i] = (ne10_float32_t) out_c[i];
//            out_neon_tmp[i] = (ne10_float32_t) out_neon[i];
//        }
//        snr = CAL_SNR_FLOAT32 (out_c_tmp, out_neon_tmp, (fftSize / 2 + 1) * 2);
//        //assert_false ( (snr < SNR_THRESHOLD_INT16));
//
//        /* IFFT test */
//        for (i = 1; i < (fftSize / 2); i++)
//        {
//            in_c[2 * i] = testInput_i16_unscaled[2 * i];
//            in_c[2 * i + 1] = testInput_i16_unscaled[2 * i + 1];
//            in_c[2 * (fftSize - i)] = in_c[2 * i];
//            in_c[2 * (fftSize - i) + 1] = -in_c[2 * i + 1];
//        }
//        in_c[0] = testInput_i16_unscaled[0];
//        in_c[1] = 0;
//        in_c[fftSize] = testInput_i16_unscaled[1];
//        in_c[fftSize + 1] = 0;
//        memcpy (in_neon, in_c, fftSize * 2 * sizeof (ne10_int16_t));
//
//        GUARD_ARRAY_UINT8 ( (ne10_uint8_t*) out_c, fftSize * sizeof (ne10_int16_t));
//        GUARD_ARRAY_UINT8 ( (ne10_uint8_t*) out_neon, fftSize * sizeof (ne10_int16_t));
//
//        ne10_fft_c2r_1d_int16_c (out_c, (ne10_fft_cpx_int16_t*) in_c, cfg, 0);
//        //ne10_fft_c2r_1d_int16_neon (out_neon, (ne10_fft_cpx_int16_t*) in_neon, cfg, 0);
//
//        CHECK_ARRAY_GUARD_UINT8 ( (ne10_uint8_t*) out_c, fftSize * sizeof (ne10_int16_t));
//        CHECK_ARRAY_GUARD_UINT8 ( (ne10_uint8_t*) out_neon, fftSize * sizeof (ne10_int16_t));
//
//        //conformance test
//        for (i = 0; i < fftSize; i++)
//        {
//            out_c_tmp[i] = (ne10_float32_t) out_c[i];
//            out_neon_tmp[i] = (ne10_float32_t) out_neon[i];
//        }
//        snr = CAL_SNR_FLOAT32 (out_c_tmp, out_neon_tmp, fftSize);
//        //assert_false ( (snr < SNR_THRESHOLD_INT16));
//
//        /* scaled FFT test */
//        memcpy (in_c, testInput_i16_scaled, fftSize * sizeof (ne10_int16_t));
//        memcpy (in_neon, testInput_i16_scaled, fftSize * sizeof (ne10_int16_t));
//
//        GUARD_ARRAY_UINT8 ( (ne10_uint8_t*) out_c, (fftSize / 2 + 1) * 2 * sizeof (ne10_int16_t));
//        GUARD_ARRAY_UINT8 ( (ne10_uint8_t*) out_neon, (fftSize / 2 + 1) * 2 * sizeof (ne10_int16_t));
//
//        ne10_fft_r2c_1d_int16_c ( (ne10_fft_cpx_int16_t*) out_c, in_c, cfg, 1);
//        //ne10_fft_r2c_1d_int16_neon ( (ne10_fft_cpx_int16_t*) out_neon, in_neon, cfg, 1);
//
//        CHECK_ARRAY_GUARD_UINT8 ( (ne10_uint8_t*) out_c, (fftSize / 2 + 1) * 2 * sizeof (ne10_int16_t));
//        CHECK_ARRAY_GUARD_UINT8 ( (ne10_uint8_t*) out_neon, (fftSize / 2 + 1) * 2 * sizeof (ne10_int16_t));
//
//        //conformance test
//        for (i = 0; i < (fftSize / 2 + 1) * 2; i++)
//        {
//            out_c_tmp[i] = (ne10_float32_t) out_c[i];
//            out_neon_tmp[i] = (ne10_float32_t) out_neon[i];
//        }
//        snr = CAL_SNR_FLOAT32 (out_c_tmp, out_neon_tmp, (fftSize / 2 + 1) * 2);
//        assert_false ( (snr < SNR_THRESHOLD_INT16));
//
//        /* IFFT test */
//        for (i = 1; i < (fftSize / 2); i++)
//        {
//            in_c[2 * i] = testInput_i16_scaled[2 * i];
//            in_c[2 * i + 1] = testInput_i16_scaled[2 * i + 1];
//            in_c[2 * (fftSize - i)] = in_c[2 * i];
//            in_c[2 * (fftSize - i) + 1] = -in_c[2 * i + 1];
//        }
//        in_c[0] = testInput_i16_scaled[0];
//        in_c[1] = 0;
//        in_c[fftSize] = testInput_i16_scaled[1];
//        in_c[fftSize + 1] = 0;
//        memcpy (in_neon, in_c, fftSize * 2 * sizeof (ne10_int16_t));
//
//        GUARD_ARRAY_UINT8 ( (ne10_uint8_t*) out_c, fftSize * sizeof (ne10_int16_t));
//        GUARD_ARRAY_UINT8 ( (ne10_uint8_t*) out_neon, fftSize * sizeof (ne10_int16_t));
//
//        ne10_fft_c2r_1d_int16_c (out_c, (ne10_fft_cpx_int16_t*) in_c, cfg, 1);
//        //ne10_fft_c2r_1d_int16_neon (out_neon, (ne10_fft_cpx_int16_t*) in_neon, cfg, 1);
//
//        CHECK_ARRAY_GUARD_UINT8 ( (ne10_uint8_t*) out_c, fftSize * sizeof (ne10_int16_t));
//        CHECK_ARRAY_GUARD_UINT8 ( (ne10_uint8_t*) out_neon, fftSize * sizeof (ne10_int16_t));
//
//        //conformance test
//        for (i = 0; i < fftSize; i++)
//        {
//            out_c_tmp[i] = (ne10_float32_t) out_c[i];
//            out_neon_tmp[i] = (ne10_float32_t) out_neon[i];
//        }
//        snr = CAL_SNR_FLOAT32 (out_c_tmp, out_neon_tmp, fftSize);
//        assert_false ( (snr < SNR_THRESHOLD_INT16));
//
//        NE10_FREE (cfg);
//    }
//
//    NE10_FREE (guarded_in_c);
//    NE10_FREE (guarded_in_neon);
//    NE10_FREE (guarded_out_c);
//    NE10_FREE (guarded_out_neon);
//    NE10_FREE (out_c_tmp);
//    NE10_FREE (out_neon_tmp);
//}
//
//void test_fft_r2c_1d_int16_performance()
//{
//
//    ne10_int32_t i = 0;
//    ne10_int32_t fftSize = 0;
//    ne10_fft_r2c_cfg_int16_t cfg;
//    ne10_int32_t test_loop = 0;
//
//    fprintf (stdout, "----------%30s start\n", __FUNCTION__);
//    fprintf (stdout, "%25s%20s%20s%20s%20s\n", "FFT Length", "C Time in ms", "NEON Time in ms", "Time Savings", "Performance Ratio");
//
//    /* init input memory */
//    guarded_in_c = (ne10_int16_t*) NE10_MALLOC ( (TEST_LENGTH_SAMPLES * 2 + ARRAY_GUARD_LEN * 2) * sizeof (ne10_int16_t));
//    guarded_in_neon = (ne10_int16_t*) NE10_MALLOC ( (TEST_LENGTH_SAMPLES * 2 + ARRAY_GUARD_LEN * 2) * sizeof (ne10_int16_t));
//    in_c = guarded_in_c + ARRAY_GUARD_LEN;
//    in_neon = guarded_in_neon + ARRAY_GUARD_LEN;
//
//    /* init dst memory */
//    guarded_out_c = (ne10_int16_t*) NE10_MALLOC ( (TEST_LENGTH_SAMPLES * 2 + ARRAY_GUARD_LEN * 2) * sizeof (ne10_int16_t));
//    guarded_out_neon = (ne10_int16_t*) NE10_MALLOC ( (TEST_LENGTH_SAMPLES * 2 + ARRAY_GUARD_LEN * 2) * sizeof (ne10_int16_t));
//    out_c = guarded_out_c + ARRAY_GUARD_LEN;
//    out_neon = guarded_out_neon + ARRAY_GUARD_LEN;
//
//    for (i = 0; i < TEST_LENGTH_SAMPLES * 2; i++)
//    {
//        testInput_i16_unscaled[i] = (ne10_int16_t) (drand48() * 1024) - 512;
//        testInput_i16_scaled[i] = (ne10_int16_t) (drand48() * NE10_F2I16_MAX) - NE10_F2I16_MAX / 2;
//    }
//    for (fftSize = MIN_LENGTH_SAMPLES_REAL; fftSize <= TEST_LENGTH_SAMPLES; fftSize *= 2)
//    {
//        fprintf (stdout, "FFT size %d\n", fftSize);
//        cfg = ne10_fft_alloc_r2c_int16 (fftSize);
//        if (cfg == NULL)
//        {
//            fprintf (stdout, "======ERROR, FFT alloc fails\n");
//            return;
//        }
//        test_loop = TEST_COUNT / fftSize;
//
//        /* unscaled FFT test */
//        memcpy (in_c, testInput_i16_unscaled , fftSize * sizeof (ne10_int16_t));
//        memcpy (in_neon, testInput_i16_unscaled , fftSize * sizeof (ne10_int16_t));
//
//        GET_TIME
//        (
//            time_c,
//        {
//            for (i = 0; i < test_loop; i++)
//                ne10_fft_r2c_1d_int16_c ( (ne10_fft_cpx_int16_t*) out_c, in_c, cfg, 0);
//        }
//        );
//        GET_TIME
//        (
//            time_neon,
//        {
//            for (i = 0; i < test_loop; i++)
//                ne10_fft_r2c_1d_int16_neon ( (ne10_fft_cpx_int16_t*) out_neon, in_neon, cfg, 0);
//        }
//        );
//
//        time_speedup = (ne10_float32_t) time_c / time_neon;
//        time_savings = ( ( (ne10_float32_t) (time_c - time_neon)) / time_c) * 100;
//        //ne10_log (__FUNCTION__, "Int16 unscaled FFT%21d%20lld%20lld%19.2f%%%18.2f:1\n", fftSize, time_c, time_neon, time_savings, time_speedup);
//
//        /* IFFT test */
//        for (i = 1; i < (fftSize / 2); i++)
//        {
//            in_c[2 * i] = testInput_i16_unscaled[2 * i];
//            in_c[2 * i + 1] = testInput_i16_unscaled[2 * i + 1];
//            in_c[2 * (fftSize - i)] = in_c[2 * i];
//            in_c[2 * (fftSize - i) + 1] = -in_c[2 * i + 1];
//        }
//        in_c[0] = testInput_i16_unscaled[0];
//        in_c[1] = 0;
//        in_c[fftSize] = testInput_i16_unscaled[1];
//        in_c[fftSize + 1] = 0;
//        memcpy (in_neon, in_c, fftSize * 2 * sizeof (ne10_int16_t));
//
//        GET_TIME
//        (
//            time_c,
//        {
//            for (i = 0; i < test_loop; i++)
//                ne10_fft_c2r_1d_int16_c (out_c, (ne10_fft_cpx_int16_t*) in_c, cfg, 0);
//        }
//        );
//        GET_TIME
//        (
//            time_neon,
//        {
//            for (i = 0; i < test_loop; i++)
//                ne10_fft_c2r_1d_int16_neon (out_neon, (ne10_fft_cpx_int16_t*) in_neon, cfg, 0);
//        }
//        );
//
//        time_speedup = (ne10_float32_t) time_c / time_neon;
//        time_savings = ( ( (ne10_float32_t) (time_c - time_neon)) / time_c) * 100;
//        //ne10_log (__FUNCTION__, "Int16 unscaled FFT%21d%20lld%20lld%19.2f%%%18.2f:1\n", fftSize, time_c, time_neon, time_savings, time_speedup);
//
//        /* scaled FFT test */
//        memcpy (in_c, testInput_i16_scaled , fftSize * sizeof (ne10_int16_t));
//        memcpy (in_neon, testInput_i16_scaled , fftSize * sizeof (ne10_int16_t));
//
//        GET_TIME
//        (
//            time_c,
//        {
//            for (i = 0; i < test_loop; i++)
//                ne10_fft_r2c_1d_int16_c ( (ne10_fft_cpx_int16_t*) out_c, in_c, cfg, 1);
//        }
//        );
//        GET_TIME
//        (
//            time_neon,
//        {
//            for (i = 0; i < test_loop; i++)
//                ne10_fft_r2c_1d_int16_neon ( (ne10_fft_cpx_int16_t*) out_neon, in_neon, cfg, 1);
//        }
//        );
//
//        time_speedup = (ne10_float32_t) time_c / time_neon;
//        time_savings = ( ( (ne10_float32_t) (time_c - time_neon)) / time_c) * 100;
//        //ne10_log (__FUNCTION__, "Int16 scaled FFT%21d%20lld%20lld%19.2f%%%18.2f:1\n", fftSize, time_c, time_neon, time_savings, time_speedup);
//
//        /* IFFT test */
//        for (i = 1; i < (fftSize / 2); i++)
//        {
//            in_c[2 * i] = testInput_i16_scaled[2 * i];
//            in_c[2 * i + 1] = testInput_i16_scaled[2 * i + 1];
//            in_c[2 * (fftSize - i)] = in_c[2 * i];
//            in_c[2 * (fftSize - i) + 1] = -in_c[2 * i + 1];
//        }
//        in_c[0] = testInput_i16_scaled[0];
//        in_c[1] = 0;
//        in_c[fftSize] = testInput_i16_scaled[1];
//        in_c[fftSize + 1] = 0;
//        memcpy (in_neon, in_c, fftSize * 2 * sizeof (ne10_int16_t));
//
//        GET_TIME
//        (
//            time_c,
//        {
//            for (i = 0; i < test_loop; i++)
//                ne10_fft_c2r_1d_int16_c (out_c, (ne10_fft_cpx_int16_t*) in_c, cfg, 1);
//        }
//        );
//       GET_TIME
//        (
//            time_neon,
//        {
//            for (i = 0; i < test_loop; i++)
//                ne10_fft_c2r_1d_int16_neon (out_neon, (ne10_fft_cpx_int16_t*) in_neon, cfg, 1);
//        }
//        );
//
//        time_speedup = (ne10_float32_t) time_c / time_neon;
//        time_savings = ( ( (ne10_float32_t) (time_c - time_neon)) / time_c) * 100;
//        //ne10_log (__FUNCTION__, "Int16 scaled FFT%21d%20lld%20lld%19.2f%%%18.2f:1\n", fftSize, time_c, time_neon, time_savings, time_speedup);
//
//        NE10_FREE (cfg);
//    }
//
//    NE10_FREE (guarded_in_c);
//    NE10_FREE (guarded_in_neon);
//    NE10_FREE (guarded_out_c);
//    NE10_FREE (guarded_out_neon);
//}
//
//void test_fft_c2c_1d_int16()
//{
//#if defined (SMOKE_TEST)||(REGRESSION_TEST)
//    test_fft_c2c_1d_int16_conformance();
//#endif
//
//#if defined (PERFORMANCE_TEST)
//    test_fft_c2c_1d_int16_performance();
//#endif
//}
//
//void test_fft_r2c_1d_int16()
//{
//#if defined (SMOKE_TEST)||(REGRESSION_TEST)
//    test_fft_r2c_1d_int16_conformance();
//#endif
//
//#if defined (PERFORMANCE_TEST)
//    test_fft_r2c_1d_int16_performance();
//#endif
//}

//static void my_test_setup (void)
//{
//    ne10_log_buffer_ptr = ne10_log_buffer;
//}

//void test_fixture_fft_c2c_1d_int16 (void)
//{
//    test_fixture_start();               // starts a fixture
//
//    fixture_setup (my_test_setup);
//
//    run_test (test_fft_c2c_1d_int16);       // run tests
//
//    test_fixture_end();                 // ends a fixture
//}

//void test_fixture_fft_r2c_1d_int16 (void)
//{
//    test_fixture_start();               // starts a fixture
//
//    fixture_setup (my_test_setup);
//
//    run_test (test_fft_r2c_1d_int16);       // run tests
//
//    test_fixture_end();                 // ends a fixture
//}

