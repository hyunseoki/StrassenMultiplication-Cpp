#pragma once

#include "Strassen_Vector.h"
#include <opencv2\opencv.hpp>
#include <time.h>
#include <chrono>

using cv::Mat;
using std::chrono::high_resolution_clock;

void main()
{
	const int N = 5;
	vector<vector<int>> A, B, C, D;
	MatrixInit(N, &A);
	MatrixInitEye(N, &B);
	MatrixInitZero(N, &C);
	MatrixInitZero(N, &D);

	cout << "Standard Mult\n";
	MatrixMult_Standard(N, &A, &B, &C);
	MatrixDisp(N, &C);

	cout << "OpenMP Mult\n";
	MatrixMult_OpenMP(N, &A, &B, &C);
	MatrixDisp(N, &C);

	cout << "Strassen Mult\n";
	MatrixMult_Strassen(N, &A, &B, &C);
	MatrixDisp(N, &C);

	cout << "Strassen Mult Optimization\n";
	MatrixMult_Optimized_Strassen(N, &A, &B, &D);
	MatrixDisp(N, &D);
}

//void main()
//{
//	const int N = 5;
//
//	static_assert(1 < N && N < 257, "Matrix dimension must be greater than 1 and less than 257");
//
//	Mat cv_A(N, N, CV_32F);
//	Mat cv_B(N, N, CV_32F);
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
//	cv_A * cv_B;
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