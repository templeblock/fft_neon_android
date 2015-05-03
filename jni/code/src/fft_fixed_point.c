#include "fft_fixed_point.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***********************************************查找表*************************************************************/

//全局变量,2的整数次幂表
int Pow2_table[20] = {1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288};

//对上表进行定点化后的sin函数查找表，即将上表中每个数乘上 2^8 = 256
int sin_table_INT_128[]={
	 0,  13,  25,  38,  50,  62,  74,  86,
	98, 109, 121, 132, 142, 152, 162, 172,
	181, 190, 198, 206, 213, 220, 226, 231,
	237, 241, 245, 248, 251, 253, 255, 256,
	256, 256, 255, 253, 251, 248, 245, 241,
	237, 231, 226, 220, 213, 206, 198, 190,
	181, 172, 162, 152, 142, 132, 121, 109,
	 98,  86,  74,  62,  50,  38,  25,  13
	
};
//FFT中点数为128的cos函数定点化后的查找表，
int cos_table_INT_128[]={
	256,  256,  255,  253,  251,  248,  245,  241,
	237,  231,  226,  220,  213,  206,  198,  190,
	181,  172,  162,  152,  142,  132,  121,  109,
	 98,   86,   74,   62,   50,   38,   25,   13,
	  0,  -13,  -25,  -38,  -50,  -62,  -74,  -86,
	 -98, -109, -121, -132, -142, -152, -162, -172,
	-181, -190, -198, -206, -213, -220, -226, -231,
	-237, -241, -245, -248, -251, -253, -255, -256
};

//FFT中输入序列重新排序后的序列 注意:只适用于点数为128
int reverse_matrix_128[]={
	0,  64,  32,  96,  16,  80,  48, 112,   8,  72,  40, 104,  24,  88,  56, 120,
	4,  68,  36, 100,  20,  84,  52, 116,  12,  76,  44, 108,  28,  92,  60, 124,
	2,  66,  34,  98,  18,  82,  50, 114,  10,  74,  42, 106,  26,  90,  58, 122,
	6,  70,  38, 102,  22,  86,  54, 118,  14,  78,  46, 110,  30,  94,  62, 126,
	1,  65,  33,  97,  17,  81,  49, 113,   9,  73,  41, 105,  25,  89,  57, 121,
	5,  69,  37, 101,  21,  85,  53, 117,  13,  77,  45, 109,  29,  93,  61, 125,
	3,  67,  35,  99,  19,  83,  51, 115,  11,  75,  43, 107,  27,  91,  59, 123,
	7,  71,  39, 103,  23,  87,  55, 119,  15,  79,  47, 111,  31,  95,  63, 127
};
//表中每个数乘上 2^8 = 256
int sin_table_INT_64[]={
	0,25,50,74,98,121,142,162,
	181,198,213,226,237,245,251,255,
	256,255,251,245,237,226,213,198,
	181,162,142,121,98,74,50,25};
int cos_table_INT_64[]={
	256,255,251,245,237,226,213,198,
	181,162,142,121,98,74,50,25,0,
	-25,-49,-74,-97,-120,-142,-162,-181,
	-197,-212,-225,-236,-244,-251,-254};
int reverse_matrix_64[]={ 
	0,32,16,48,8,40,24,56,
	4,36,20,52,12,44,28,60,
	2,34,18,50,10,42,26,58,   
	6,38,22,54,14,46,30,62,    
	1,33,17,49,9,41,25,57,   
	5,37,21,53,13,45,29,61,
	3,35,19,51,11,43,27,59,
    7,39,23,55,15,47,31,63};
/***********************************************查找表*************************************************************/

void reverse(int len, int M,int *b)
{
	//注意b在外面必须初始化为0
    int i,j;

	//a的初始化,a用于存放变址后序列的二进制数
	char *a = (char *)malloc(sizeof(char)*M); // a用于存放M位二进制数
	memset(a,0,sizeof(char)*M);

    for(i=1; i<len; i++)     // i = 0 时，顺序一致
    {
        j = 0;
        while(a[j] != 0)
        {
            a[j] = 0;
            j++;
        }

        a[j] = 1;
        for(j=0; j<M; j++)
        {
            b[i] = b[i]+a[j] * Pow2_table[M-1-j];    //pow(2,M-1-j),将二进制a转换为10进制b
        }
    }
	free(a);
}
void fft_fixed_point(int fft_nLen, int fft_M, complex_INT * A)
{
	int i;
	int L,dist,p,t;
	int temp1,temp2;
	complex_INT *pr1,*pr2;
	
    int WN_Re,WN_Im;       //WN的实部和虚部
	int X1_Re,X1_Im;       //临时变量的实部和虚部
	int X2_Re,X2_Im;     
	int WN_X2_Re,WN_X2_Im;
	for(L = 1; L <= fft_M; L++)         //完成M次蝶形的迭代过程
	{
		dist = Pow2_table[L-1];             //dist = pow(2,L-1); 蝶形运算两节点间的距离
		temp1 = Pow2_table[fft_M-L];        //temp1 = pow(2,fft_M-L);
		temp2 = Pow2_table[L];              //temp2 = pow(2,L); 
		for(t=0; t<dist; t++)                 //循环完成因子WN的变化
		{
			p = t * temp1;                    //p = t*pow(2,fft_M-L);  
			if(fft_M==7)
			{
				WN_Re = cos_table_INT_128[p];          //Q15
				WN_Im = -sin_table_INT_128[p];
			}
			if(fft_M==6)
			{
				WN_Re = cos_table_INT_64[p];          //Q15
				WN_Im = -sin_table_INT_64[p];
			}
			//循环完成相同因子WN的蝶形运算
			for(i = t; i < fft_nLen; i = i + temp2)           //i=i+pow(2,L)   Note: i=i+pow(2,L) 
			{
				pr1 = A+i;
				pr2 = pr1+dist;

				X1_Re = pr1->real;        //X1_Re = A[i].real; 
				X1_Im = pr1->image;       //X1_Im = A[i].image;
				X2_Re = pr2->real;        //X2_Re = A[i+dist].real;
				X2_Im = pr2->image;       //X2_Im = A[i+dist].image;


				//计算WN * X2(k),是个复数
				WN_X2_Re = ((long long)WN_Re * X2_Re - (long long)WN_Im * X2_Im) >> Q_INPUT;
				WN_X2_Im = ((long long)WN_Im * X2_Re + (long long)WN_Re * X2_Im) >> Q_INPUT;
				
				//计算X(k) = X1(k) + WN * X2(k);
				pr1->real = X1_Re + WN_X2_Re;     //A[i].real = X1_Re + WN_X2_Re;
				pr1->image = X1_Im + WN_X2_Im;    //A[i].image = X1_Im + WN_X2_Im; 

				//计算X(k) = X1(k) - WN * X2(k);
				pr2->real = X1_Re - WN_X2_Re;     //A[i+dist].real = X1_Re - WN_X2_Re;
				pr2->image = X1_Im - WN_X2_Im;    //A[i+dist].image = X1_Im - WN_X2_Im;
			}
		}
	}
}
void fft_2D_fixed_point(int mLen,int nLen,int M,int N,complex_INT *A_In,int flag)
{
	int i,j;
	complex_INT * A;
	int len = mLen * nLen;

	int *b = NULL;
	if(N==7)
		b = reverse_matrix_128;      //直接查逆序表，提高效率
	else if(N==6)
		b = reverse_matrix_64;      //直接查逆序表，提高效率
	if (flag == DXT_INVERSE)
	{
		complex_INT *p = A_In;

		for(i=0; i<len; i++)
		{
			//逆变换公式与正变换公式区别,其结果的虚部与真实结果的虚部差一个负号
			//但通常情况下，都是对ifft的模值处理，即Re*Re + Im*Im,故对结果没什么影响
			//只是应该知道有这个区别
			(p->image) *= -1;    //A_In[i].image = -A_In[i].image;
			p++;
		}
	}	

	//A用于处理矩阵中每行的数据
	A = (complex_INT *)malloc(sizeof(complex_INT)*nLen);


	//对矩阵的每一行做FFT变换
	for(i=0; i<mLen; i++)
	{
		complex_INT *pr1 = A;
		complex_INT *pr2 = NULL;
		complex_INT *pr3 = A_In + (i<<N);   //不同行的起始地址

		for(j=0; j<nLen; j++)
		{
			pr2 = pr3 + b[j];                       //取代上段代码，提高访问效率
			pr1->real = pr2->real;        
			pr1->image = pr2->image;
			pr1++;
		}//pr1保存倒位序处理后的结果


		fft_fixed_point(nLen,N,A);                                 //进行FFT变换，变换后的结果仍存于A

		if (flag == DXT_FORWARD)
		{
			pr1 = A;             //重新置位指针
			pr2 = pr3;

			for(j=0; j<nLen; j++)
			{
				pr2->real = pr1->real;
				pr2->image = pr1->image;
				pr1++;
				pr2++;
			}
		}
		else
		{
			pr1 = A;             //重新置位指针
			pr2 = pr3;

			for(j=0; j<nLen; j++)
			{
				pr2->real = pr1->real >> N;
				pr2->image = pr1->image >>N;
				pr1++;
				pr2++;
			}	
		}

	}
	free(A);
	

	//A用于处理矩阵中每列的数据
	A = (complex_INT *)malloc(sizeof(complex_INT)*mLen);
	if(M==7)
		b = reverse_matrix_128;      //直接查逆序表，提高效率
	else if(M==6)
		b = reverse_matrix_64;      //直接查逆序表，提高效率

	//对矩阵的每一列做FFT变换
	for(i=0; i<nLen; i++)
	{
		complex_INT *pr1 = A;
		complex_INT *pr2 = NULL;
		complex_INT *pr3 = A_In + i;   //不同列的起始地址

		for(j=0; j<mLen; j++)
		{
			pr2 = pr3 + (b[j]<<N);
			pr1->real = pr2->real;
			pr1->image = pr2->image;
			pr1++;
		}

		fft_fixed_point(mLen,M,A);      //进行FFT变换，变换后的结果仍存于A

		if (flag == DXT_FORWARD)
		{
			pr1 = A;             //重新置位指针
			pr2 = pr3;

			for(j=0; j<mLen; j++)
			{
				pr2->real = pr1->real;
				pr2->image = pr1->image;
				pr1++;
				pr2 += nLen;
			}	
		}
		else
		{
			pr1 = A;             //重新置位指针
			pr2 = pr3;

			for(j=0; j<mLen; j++)
			{
				pr2->real = pr1->real >> M;
				pr2->image =(-1)*( pr1->image >> M);
				pr1++;
				pr2 += nLen;
			}
		}
	}
	free(A);
}
