#include <iostream>
#include <time.h>
#include <opencv2\opencv.hpp>

using std::cout;
using namespace cv;

template<typename T, size_t N>
void MatrixMult_Standard(const T A[N][N], const T B[N][N]);

template<typename T, size_t N>
void MatrixMult_OpenMP(const T A[N][N], const T B[N][N]);

template<typename T, size_t N>
void MatrixDisp(const T A[N][N]);

void main()
{
	const size_t N = 8;

	float data1[] = { 
		1.2f, 2.3f, 3.2f, 4.5f,	1.2f, 2.3f, 3.2f, 4.5f,
		1.2f, 2.3f, 3.2f, 4.5f, 1.2f, 2.3f, 3.2f, 4.5f,
		1.2f, 2.3f, 3.2f, 4.5f, 1.2f, 2.3f, 3.2f, 4.5f,
		1.2f, 2.3f, 3.2f, 4.5f, 1.2f, 2.3f, 3.2f, 4.5f,
		1.2f, 2.3f, 3.2f, 4.5f,	1.2f, 2.3f, 3.2f, 4.5f,
		1.2f, 2.3f, 3.2f, 4.5f, 1.2f, 2.3f, 3.2f, 4.5f,
		1.2f, 2.3f, 3.2f, 4.5f, 1.2f, 2.3f, 3.2f, 4.5f,
		1.2f, 2.3f, 3.2f, 4.5f, 1.2f, 2.3f, 3.2f, 4.5f,
	};
	float data2[] = {
		1.2f, 2.3f, 3.2f, 4.5f,	1.2f, 2.3f, 3.2f, 4.5f,
		1.2f, 2.3f, 3.2f, 4.5f, 1.2f, 2.3f, 3.2f, 4.5f,
		1.2f, 2.3f, 3.2f, 4.5f, 1.2f, 2.3f, 3.2f, 4.5f,
		1.2f, 2.3f, 3.2f, 4.5f, 1.2f, 2.3f, 3.2f, 4.5f,
		1.2f, 2.3f, 3.2f, 4.5f,	1.2f, 2.3f, 3.2f, 4.5f,
		1.2f, 2.3f, 3.2f, 4.5f, 1.2f, 2.3f, 3.2f, 4.5f,
		1.2f, 2.3f, 3.2f, 4.5f, 1.2f, 2.3f, 3.2f, 4.5f,
		1.2f, 2.3f, 3.2f, 4.5f, 1.2f, 2.3f, 3.2f, 4.5f,
	};

	float A[N][N]{
		1.2f, 2.3f, 3.2f, 4.5f,	1.2f, 2.3f, 3.2f, 4.5f,
		1.2f, 2.3f, 3.2f, 4.5f, 1.2f, 2.3f, 3.2f, 4.5f,
		1.2f, 2.3f, 3.2f, 4.5f, 1.2f, 2.3f, 3.2f, 4.5f,
		1.2f, 2.3f, 3.2f, 4.5f, 1.2f, 2.3f, 3.2f, 4.5f,
		1.2f, 2.3f, 3.2f, 4.5f,	1.2f, 2.3f, 3.2f, 4.5f,
		1.2f, 2.3f, 3.2f, 4.5f, 1.2f, 2.3f, 3.2f, 4.5f,
		1.2f, 2.3f, 3.2f, 4.5f, 1.2f, 2.3f, 3.2f, 4.5f,
		1.2f, 2.3f, 3.2f, 4.5f, 1.2f, 2.3f, 3.2f, 4.5f,
	};

	float B[N][N]{
		1.2f, 2.3f, 3.2f, 4.5f,	1.2f, 2.3f, 3.2f, 4.5f,
		1.2f, 2.3f, 3.2f, 4.5f, 1.2f, 2.3f, 3.2f, 4.5f,
		1.2f, 2.3f, 3.2f, 4.5f, 1.2f, 2.3f, 3.2f, 4.5f,
		1.2f, 2.3f, 3.2f, 4.5f, 1.2f, 2.3f, 3.2f, 4.5f,
		1.2f, 2.3f, 3.2f, 4.5f,	1.2f, 2.3f, 3.2f, 4.5f,
		1.2f, 2.3f, 3.2f, 4.5f, 1.2f, 2.3f, 3.2f, 4.5f,
		1.2f, 2.3f, 3.2f, 4.5f, 1.2f, 2.3f, 3.2f, 4.5f,
		1.2f, 2.3f, 3.2f, 4.5f, 1.2f, 2.3f, 3.2f, 4.5f,
	};

	Mat m1(N, N, CV_32F, data1);
	Mat m2(N, N, CV_32F, data2);

#ifdef _DEBUG
	cout << "Matrix A: \n";
	MatrixDisp<float, N>(A);
	cout << "Matrix B: \n";
	MatrixDisp<float, N>(B);
	cout << "(opencv) A x B  \n";
#endif

#ifdef _DEBUG
	cout << m1* m2 << "\n\n";
#endif

	clock_t start1 = clock();
	m1 * m2;
	cout << "opencv run time = " << clock() - start1 << "millisec.\n\n";

	clock_t start = clock();
	MatrixMult_Standard<float, N>(A, B);
	cout << "standard run time = " << clock() - start << "millisec.\n\n";

}

template<typename T, size_t N>
void MatrixMult_Standard(const T A[N][N], const T B[N][N])
{
	static_assert(N > 1, "Matrix dimension must be greater than 1");

	T C[N][N];
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

#ifdef _DEBUG
	cout << "(Standard) A x B \n";
	MatrixDisp<float, N>(C);
#endif
}

template<typename T, size_t N>
void MatrixDisp(const T A[N][N])
{
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
void MatrixMult_OpenMP(const T A[N][N], const T B[N][N])
{

}