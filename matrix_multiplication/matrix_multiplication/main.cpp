#pragma once

#include <iostream>
#include <opencv2\opencv.hpp>
#include <time.h>
#include <chrono>

using std::cout;
using cv::Mat;
using std::chrono::high_resolution_clock;

template<typename T, size_t N>
void MatrixDisp(const T A[N][N]);

template<typename T, size_t N>
void MatrixMult_Standard(const T A[N][N], const T B[N][N], T C[N][N]);

template<typename T, size_t N>
void MatrixMult_OpenMP(const T A[N][N], const T B[N][N], T C[N][N]);

void main()
{
	const size_t N = 250;
	static_assert(N < 257, "Matrix dimension must be less than 257");

	Mat cv_A(N, N, CV_32F);
	Mat cv_B(N, N, CV_32F);

	float A[N][N], B[N][N], C[N][N];
	
	srand(time(NULL));

	float ranN1, ranN2;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			ranN1 = (float)(rand())*10/32767; // 0 ~ 10.0 ³­¼ö
			ranN2 = (float)(rand())*10/32767;
			cv_A.at<float>(i, j) = ranN1;
			cv_B.at<float>(i, j) = ranN2;
			A[i][j] = ranN1;
			B[i][j] = ranN2;
		}
	}

#ifdef _DEBUG
	cout << "Matrix A: \n";
	MatrixDisp<float, N>(A);
	cout << "Matrix B: \n";
	MatrixDisp<float, N>(B);

	cout << "(opencv) A x B  \n";
	cout << cv_A* cv_B << "\n\n";
#endif

	auto start = high_resolution_clock::now();
	cv_A * cv_B;
	auto end = high_resolution_clock::now();
	cout << "opencv run time = " << (end - start).count()/1000 << "micro sec.\n\n";

	clock_t cstart = clock();
	cv_A * cv_B;
	cout << "opencv run time = " << clock() - cstart << "mms.\n\n";

	start = high_resolution_clock::now();
	MatrixMult_Standard<float, N>(A, B, C);
	end = high_resolution_clock::now();

#ifdef _DEBUG
	cout << "(Standard) A x B  \n";
	MatrixDisp<float, N>(C);
#endif

	cout << "standard run time = " << (end - start).count()/1000 << "micro sec.\n\n";

	cstart = clock();
	MatrixMult_Standard<float, N>(A, B, C);
	cout << "standard run time = " << clock() - cstart << "mms.\n\n";
///////////////////////////////////////////////////////////////////////////////////////////

	start = high_resolution_clock::now();
	MatrixMult_OpenMP<float, N>(A, B, C);
	end = high_resolution_clock::now();

#ifdef _DEBUG
	cout << "(OpenMP) A x B  \n";
	MatrixDisp<float, N>(C);
#endif

	cout << "OpenMP run time = " << (end - start).count() / 1000 << "micro sec.\n\n";

	cstart = clock();
	MatrixMult_OpenMP<float, N>(A, B, C);
	cout << "OpenMP run time = " << clock() - cstart << "mms.\n\n";
}

template<typename T, size_t N>
void MatrixDisp(const T A[N][N])
{
	static_assert(N > 1, "Matrix dimension must be greater than 1");

	cout << "[";
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << A[i][j];
			if ( j != N-1) { cout << ", "; }
		}

		if (i != N - 1) { cout << ";\n "; }

	}
	cout << "]\n\n";
}

template<typename T, size_t N>
void MatrixMult_Standard(const T A[N][N], const T B[N][N], T C[N][N])
{
	static_assert(N > 1, "Matrix dimension must be greater than 1");

	T dot_product;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			dot_product = 0;

			for (int k = 0; k < N; k++)
			{
				dot_product += A[i][k] * B[k][j];
			}

			C[i][j] = dot_product;
		}
	}
}

template<typename T, size_t N>
void MatrixMult_OpenMP(const T A[N][N], const T B[N][N], T C[N][N])
{
	static_assert(N > 1, "Matrix dimension must be greater than 1");

	T dot_product;
	
	#pragma omp parallel for
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			dot_product = 0;

			for (int k = 0; k < N; k++)
			{
				dot_product += A[i][k] * B[k][j];
			}

			C[i][j] = dot_product;
		}
	}
}