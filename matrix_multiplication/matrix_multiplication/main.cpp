#pragma once

#include "Strassen.h"
#include <opencv2\opencv.hpp>
#include <time.h>
#include <chrono>

using cv::Mat;
using std::chrono::high_resolution_clock;

void main()
{
	static_assert(1 < N && N < 257, "Matrix dimension must be greater than 1 and less than 257");

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

// Matrix Disp
#ifdef _DEBUG 
	cout << "Matrix A: \n";
	MatrixDisp<float>(N, A);
	cout << "Matrix B: \n";
	MatrixDisp<float>(N, B);

	cout << "(opencv) A x B  \n";
	cout << cv_A* cv_B << "\n\n";
#endif

	auto start = high_resolution_clock::now();
	cv_A * cv_B;
	auto end = high_resolution_clock::now();
	cout << "opencv run time = " << (end - start).count()/1000 << "micro sec.\n\n";

	clock_t cstart = clock();
	cv_A * cv_B;
	cout << "opencv run time = " << clock() - cstart << "mm sec.\n\n";

	start = high_resolution_clock::now();
	MatrixMult_Standard<float>(N, A, B, C);
	end = high_resolution_clock::now();

// Matrix Disp
#ifdef _DEBUG
	cout << "(Standard) A x B  \n";
	MatrixDisp<float>(N, C);
#endif

	cout << "standard run time = " << (end - start).count()/1000 << "micro sec.\n\n";

	cstart = clock();
	MatrixMult_Standard<float>(N, A, B, C);
	cout << "standard run time = " << clock() - cstart << "mm sec.\n\n";

	start = high_resolution_clock::now();
	MatrixMult_OpenMP<float>(N, A, B, C);
	end = high_resolution_clock::now();

// Matrix Disp
#ifdef _DEBUG
	cout << "(OpenMP) A x B  \n";
	MatrixDisp<float>(N, C);
#endif

	cout << "OpenMP run time = " << (end - start).count() / 1000 << "micro sec.\n\n";

	cstart = clock();
	MatrixMult_OpenMP<float>(N, A, B, C);
	cout << "OpenMP run time = " << clock() - cstart << "mm sec.\n\n";

	//start = high_resolution_clock::now();
	//MatrixMult_Strassen<float>(N, A, B, C);
	//end = high_resolution_clock::now();
	//cout << "Strassen run time = " << (end - start).count() / 1000 << "micro sec.\n\n";
	//MatrixDisp<float>(N, C);
}