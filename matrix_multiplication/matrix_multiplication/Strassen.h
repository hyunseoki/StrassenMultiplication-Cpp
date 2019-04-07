#pragma once
#include <iostream>

using std::cout;

template<typename T, size_t N>
void MatrixDisp(const T A[N][N])
{
	cout << "[";
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << A[i][j];
			if (j != N - 1) { cout << ", "; }
		}

		if (i != N - 1) { cout << ";\n "; }

	}
	cout << "]\n\n";
}

template<typename T, size_t N>
void MatrixMult_Standard(const T A[N][N], const T B[N][N], T C[N][N])
{
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

template<typename T, size_t N>
void MatrixSum(const T A[N][N], const T B[N][N], T C[N][N])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			C[i][j] = A[i][j] + B[i][j];
		}
	}
}

template<typename T, size_t N>
void MatrixSubs(const T A[N][N], const T B[N][N], T C[N][N])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			C[i][j] = A[i][j] - B[i][j];
		}
	}
}

template<typename T, size_t N>
void MatrixMult_Strassen(const T A[][N], const T B[][N], T C[][N])
{
	int i, j;
	const int mid = N / 2;

	if (N == 2) 
	{  
		MatrixMult_OpenMP<T, N>(A, B, C);
		return;
	}

	T A_11[mid][mid], A_12[mid][mid], A_21[mid][mid], A_22[mid][mid],
		B_11[mid][mid], B_12[mid][mid], B_21[mid][mid], B_22[mid][mid],
		C_11[mid][mid], C_12[mid][mid], C_21[mid][mid], C_22[mid][mid],
		M_1[mid][mid], M_2[mid][mid], M_3[mid][mid], M_4[mid][mid],
		M_5[mid][mid], M_6[mid][mid], M_7[mid][mid], temp_A[mid][mid], temp_B[mid][mid];

	//Matrix Division
	for (i = 0; i < mid; i++)
	{
		for (j =0; j < mid ; j++)
		{
			A_11[i][j] = A[i][j];
			A_12[i][j] = A[i][j + mid];
			A_21[i][j] = A[i + mid][j];
			A_22[i][j] = A[i + mid][j + mid];

			B_11[i][j] = B[i][j];
			B_12[i][j] = B[i][j + mid];
			B_21[i][j] = B[i + mid][j];
			B_22[i][j] = B[i + mid][j + mid];
		}
	}

	MatrixSum<T, mid>(A_11, A_22, temp_A);
	MatrixSum<T, mid>(B_11, B_22, temp_B);

	MatrixMult_Strassen<T, mid>(A_11, A_22, temp_A);

	//MatrixSum<float, N / 2>(A_21, A_22, temp_A);
	//MatrixMult_Strassen<float, N / 2>(temp_A, B_11, M_2);

	//MatrixSubs<float, N / 2>(N / 2, B_12, B_22, temp_B);
	//MatrixMult_Strassen<float, N / 2>(N / 2, A_11, temp_B, M_3);

	//MatrixSubs<float, N / 2>(N / 2, B_21, B_11, temp_B);
	//MatrixMult_Strassen<float, N / 2>(N / 2, A_22, temp_B, M_4);

	//MatrixSum<float, N / 2>(N / 2, A_11, A_12, temp_A);
	//MatrixMult_Strassen<float, N / 2>(N / 2, temp_A, B_22, M_5);

	//MatrixSubs<float, N / 2>(N / 2, A_21, A_11, temp_A);
	//MatrixSum<float, N / 2>(N / 2, B_11, B_12, temp_B);
	//MatrixMult_Strassen<float, N / 2>(N / 2, temp_A, temp_B, M_6);

	//MatrixSubs<float, N / 2>(N / 2, A_12, A_22, temp_A);
	//MatrixSum<float, N / 2>(N / 2, B_21, B_22, temp_B);
	//MatrixMult_Strassen<float, N / 2>(N / 2, temp_A, temp_B, M_7);

	//MatrixSum<float, N / 2>(N / 2, M_1, M_4, temp_A);
	//MatrixSubs<float, N / 2>(N / 2, temp_A, M_5, temp_B);
	//MatrixSum<float, N / 2>(N / 2, temp_B, M_7, C_11);

	//MatrixSum<float, N / 2>(N / 2, M_3, M_5, C_12);

	//MatrixSum<float, N / 2>(N / 2, M_2, M_4, C_21);

	//MatrixSum<float, N / 2>(N / 2, M_1, M_3, temp_A);
	//MatrixSubs<float, N / 2>(N / 2, temp_A, M_2, temp_B);
	//MatrixSum<float, N / 2>(N / 2, temp_B, M_6, C_22);

	//for (i = 0; i < mid; i++)
	//{
	//	for (j = 0; j < mid; j++)
	//	{
	//		C[i][j]             = C_11[i][j];
	//		C[i][j + mid]       = C_12[i][j];
	//		C[i + mid][j]       = C_21[i][j];
	//		C[i + mid][j + mid] = C_22[i][j];
	//	}
	//}
}