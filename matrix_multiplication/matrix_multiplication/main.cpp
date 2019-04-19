#pragma once

//#include "Strassen_Vector.h"
//#include <opencv2\opencv.hpp>
#include <iostream>
#include <time.h>
#include <chrono>
#include <typeinfo>       

//using cv::Mat;
using std::chrono::high_resolution_clock;
using std::cout;

const int N = 4;
//void main()
//{
//	const int N = 5;
//	vector<vector<int>> A, B, C, D;
//	MatrixInit(N, &A);
//	MatrixInitEye(N, &B);
//	MatrixInitZero(N, &C);
//	MatrixInitZero(N, &D);
//
//	cout << "Standard Mult\n";
//	MatrixMult_Standard(N, &A, &B, &C);
//	MatrixDisp(N, &C);
//
//	cout << "OpenMP Mult\n";
//	MatrixMult_OpenMP(N, &A, &B, &C);
//	MatrixDisp(N, &C);
//
//	cout << "Strassen Mult\n";
//	MatrixMult_Strassen(N, &A, &B, &C);
//	MatrixDisp(N, &C);
//
//	cout << "Strassen Mult Optimization\n";
//	MatrixMult_Optimized_Strassen(N, &A, &B, &D);
//	MatrixDisp(N, &D);
//}
//
//void main()
//{
//	const int N = 100;
//
//	static_assert(1 < N && N < 257, "Matrix dimension must be greater than 1 and less than 257");
//
//	Mat cv_A(N, N, CV_32F);
//	Mat cv_B(N, N, CV_32F);
//	Mat cv_C(N, N, CV_32F);
//
//	vector<vector<float>> A(N, vector<float>(N));
//	vector<vector<float>> B(N, vector<float>(N));
//	vector<vector<float>> C(N, vector<float>(N));
//
//	srand(time(NULL));
//
//	float ranN1, ranN2;
//
//	for (int i = 0; i < N; i++)
//	{
//		for (int j = 0; j < N; j++)
//		{
//			ranN1 = (float)(rand())*10/32767; // 0 ~ 10.0 ³­¼ö
//			ranN2 = (float)(rand())*10/32767;
//			cv_A.at<float>(i, j) = ranN1;
//			cv_B.at<float>(i, j) = ranN2;
//			A[i][j] = ranN1;
//			B[i][j] = ranN2;
//		}
//	}
//
//#ifdef _DEBUG 
//	//cout << "Matrix A: \n";
//	//MatrixDisp<float>(N, A);
//	//cout << "Matrix B: \n";
//	//MatrixDisp<float>(N, B);
//	cout << "(opencv) A x B  \n";
//	cout << cv_A* cv_B << "\n\n";
//#endif
//
//	auto start = high_resolution_clock::now();
//	cv_C = cv_A * cv_B;
//	auto end = high_resolution_clock::now();
//	cout << "opencv run time = " << (end - start).count()/1000 << "micro sec.\n\n";
//
//	//clock_t cstart = clock();
//	//cv_A * cv_B;
//	//cout << "opencv run time = " << clock() - cstart << "mm sec.\n\n";
//
//	start = high_resolution_clock::now();
//	MatrixMult_Standard(N, &A, &B, &C);
//	end = high_resolution_clock::now();
//#ifdef _DEBUG
//	cout << "(Standard) A x B  \n";
//	MatrixDisp(N, &C);
//#endif
//	cout << "standard run time = " << (end - start).count()/1000 << "micro sec.\n\n";
//
//	//cstart = clock();
//	//MatrixMult_Standard<float>(N, A, B, C);
//	//cout << "standard run time = " << clock() - cstart << "mm sec.\n\n";
//
//	start = high_resolution_clock::now();
//	MatrixMult_OpenMP(N, &A, &B, &C);
//	end = high_resolution_clock::now();
//#ifdef _DEBUG
//	cout << "(OpenMP) A x B  \n";
//	MatrixDisp(N, &C);
//#endif
//	cout << "OpenMP run time = " << (end - start).count() / 1000 << "micro sec.\n\n";
//
//	//cstart = clock();
//	//MatrixMult_OpenMP<float>(N, A, B, C);
//	//cout << "OpenMP run time = " << clock() - cstart << "mm sec.\n\n";
//
//
//	start = high_resolution_clock::now();
//	MatrixMult_Strassen(N, &A, &B, &C);
//	end = high_resolution_clock::now();
//#ifdef _DEBUG
//	cout << "(Strassen) A x B  \n";
//	MatrixDisp(N, &C);
//#endif
//	cout << "Strassen run time = " << (end - start).count() / 1000 << "micro sec.\n\n";
//}

template<typename T>
void MatrixSum(const int n, const T *A, const T *B, T *C)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			C[i*n + j] = A[i*n + j] + B[i*n + j];
		}
	}
}

template<typename T>
void MatrixPartialSum(const int n, const int Apitch, const int Bpitch, const int Cpitch, const T *A, const T *B, T *C)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			C[i*Cpitch + j] = A[i*Apitch + j] + B[i*Bpitch + j];
		}
	}
}

template<typename T>
void MatrixSubs(const int n, const T *A, const T *B, T *C)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			C[i*n + j] = A[i*n + j] - B[i*n + j];
		}
	}
}

template<typename T>
void MatrixMult(const int n, const T *A, const T *B, T *C)
{
	int i, j, k;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			for (k = 0; k < n; k++)
			{
				if (k)
				{
					C[i*n + j] += A[i*n + k] * B[k*n + j];
				}
				else
					C[i*n + j] = A[i*n + k] * B[k*n + j];
			}
		}
	}
}

template<typename T>
void MatrixMultStrassen(const int n, T *A/*, T *B, T *C*/)
{
	//if (N <= 2)
	//{
	//	MatrixMult(n, A, B, C);
	//	return;
	//}

	int m = n / 2;

	T *A11 = A;
	//MatrixPartialPrint(m, m, A11);
	T *A12 = A + m;
	//MatrixPartialPrint(m, m, A12);
	T *A21 = A + 2 * m * m;
	//MatrixPartialPrint(m, m, A21);
	T *A22 = A + 2 * m * m + m;
	//MatrixPartialPrint(m, m, A22);

	T** temp_AA = new T*[m];
	for (int i = 0; i < m; ++i)
	{
		temp_AA[i] = new T[m];
	}
	
	MatrixPartialSum(n, m, m, m, A11, A12, *temp_AA);
	MatrixPrint(m, *temp_AA);

	for (int i = 0; i < m; i++)
	{
		delete[] temp_AA[i];
	}

	//delete[] temp_AA;

	//double *P[7];   // allocate temp matrices off heap
	//const int sz = n*n * sizeof(double);
	//for (int i = 0; i < 7; i++)
	//	P[i] = (double *)malloc(sz);
	//double *T = (double *)malloc(sz);
	//double *U = (double *)malloc(sz);

	//T * temp11 = new T;


	//T *B11 = B;
	//T *B12 = B + n;
	//T *B21 = B + 2 * n;
	//T *B22 = B;

	//MatrixSum(m, A21, A22, AA);

	//MatrixPrint(m, A21);
	//MatrixPrint(m, A22);
	//T *A12 = A + n;
	//T *A21 = A + n * 2;
	//T *A22 = A + n * 2;

	//T *B11;
	//T *B12;
	//T *B21;
	//T *B22;


}

template<typename T>
void CreateRandomMatrix(const int n, T *A)
{
	int i, j;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			A[i*n + j] = (T)(rand()) * 10 / 32767;
		}
	}
}

template<typename T>
void CreateZeroMatrix(const int n, T *A)
{
	int i, j;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			A[i][j] = (T)(rand()) * 10 / 32767;
		}
	}
}

template<typename T>
void CreateEyeMatrix(const int n, T *A)
{
	int i, j;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (i == j)
			{
				A[i*n + j] = (T)1;
			}
			else
			{
				A[i*n + j] = (T)0;
			}
		}
	}
}

template<typename T>
void MatrixPrint(const int n, const T *A)
{
	int i, j;

	cout << "[";
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			cout << A[i*n + j];
			if (j != n - 1) { cout << ", "; }
		}
		if (i != n - 1) { cout << ";\n "; }
	}
	cout << "]\n\n";
}

template<typename T>
void MatrixPartialPrint(const int n, const int pitch, const T *A)
{
	int i, j;

	cout << "[";
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			cout << A[i*n*pitch + j];
			if (j != n - 1) { cout << ", "; }
		}
		if (i != n - 1) { cout << ";\n "; }
	}

	cout << "]\n\n";
}

void main()
{
	int MatA[N][N] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };
	int MatB[N][N] = { 0 };
	int MatC[N][N] = { 0 };

	int * A = MatA[0];
	int * B = MatB[0];
	int * C = MatC[0];

	//CreateEyeMatrix(N, A);
	MatrixPrint(N, A);

	//CreateRandomMatrix(N, B);
	//MatrixPrint(N, B);

	MatrixMultStrassen(N, A);

	//MatrixMult_Strassen(N, A, B, C);

	//MatrixPrint(N, B);


}