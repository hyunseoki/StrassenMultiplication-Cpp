#pragma once

#include "Strassen_Vector.h"
#include <opencv2\opencv.hpp>
#include <time.h>
#include <chrono>

using cv::Mat;
using std::chrono::high_resolution_clock;

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

const int N = 4;

template<typename T>
void MatrixSum(int n, T *A[], T *B[], T *C[])
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			C[i][j] = A[i][j] + B[i][j];
		}
	}
}

template<typename T>
void MatrixSubs(int n, T *A[], T *B[], T *C[])
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			C[i][j] = A[i][j] - B[i][j];
		}
	}
}

template<typename T>
void MatrixMult(int n, T *A[], T *B[], T *C[])
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
					C[i][j] += A[i][k] * B[k][j];
				}
				else
					C[i][j] = A[i][k] * B[k][j];
			}
		}
	}
}

template<typename T>
void MatrixMult_Strassen(int n, T *A[], T *B[], T *C[])
{
	int m = n / 2;

	T *A11 = A;
	T *A12 = A + n;
	T *A21 = A + n * 2;
	T *A22 = A + n * 2;

	T *B11;
	T *B12;
	T *B21;
	T *B22;

}

template<typename T>
void MatrixPrint(int n, T *A[])
{
	int i, j;

	cout << "[";
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			cout << A[i][j];
			if (j != n - 1) { cout << ", "; }
		}
		if (i != n - 1) { cout << ";\n "; }
	}
	cout << "]\n\n";
}

template<typename T>
void CreateMatrix(int n, T *A[])
{
	int i, j;
	int *temp = new int[n][n];

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			temp[i][j] = (T)(rand()) * 10 / 32767;
		}
	}
	A = temp;

	delete[] temp;
}

template<typename T>
void CreateEyeMatrix(int n, T *A[])
{
	int i, j;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (i == j)
			{
				A[i][j] = (T)1;
			}
			else
			{
				A[i][j] = (T)0;
			}	
		}
	}
}

void main()
{
	int Aarray1[N] = { 1,2,3,1 };
	int Aarray2[N] = { -1,1,2,3 };
	int Aarray3[N] = { 0,4,5,-3 };
	int Aarray4[N] = { -1,1,2,3 };
	int * A[N] = { Aarray1, Aarray2, Aarray3, Aarray4 };

	MatrixPrint(N, A);

	int Barray1[N] = { 1,0,0,0 };
	int Barray2[N] = { 0,1,0,0 };
	int Barray3[N] = { 0,0,1,0 };
	int Barray4[N] = { 0,0,0,1 };
	int *B[N] = { Barray1, Barray2, Barray3, Barray4 };

	MatrixPrint(N, B);

	int Carray1[N] = { 0,0,0,0 };
	int Carray2[N] = { 0,0,0,0 };
	int Carray3[N] = { 0,0,0,0 };
	int Carray4[N] = { 0,0,0,0 };
	int *C[N] = { Carray1, Carray2, Carray3, Carray4 };

	MatrixSum(N, A, B, C);
	MatrixPrint(N, C);

	//int *A[N];
	//CreateMatrix<int>(N, A);
	//MatrixPrint<int>(N, A);

/*	CreateEyeMatrix(N, B);
	MatrixPrint(N, B)*/;

}