#pragma once
#include <iostream>
#include <vector>

using std::cout;
using std::vector;

template<typename T>
void MatrixInit(const int n, vector<vector<T>> * A)
{
	(*A).resize(n);
	for (int i = 0; i < n; i++)
	{
		(*A)[i].resize(n);
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			(*A)[i][j] = (T)(rand() * 10 / 32767);
		}
	}
}

template<typename T>
void MatrixInitEye(const int n, vector<vector<T>> * A)
{
	(*A).resize(n);
	for (int i = 0; i < n; i++)
	{
		(*A)[i].resize(n);
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i == j)
				(*A)[i][j] = 1;
		}
	}
}

template<typename T>
void MatrixDisp(const int n, const vector<vector<T>> * A)
{
	int i, j;
	cout << "[";
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			cout << (*A)[i][j];
			if (j != n - 1) { cout << ", "; }
		}
		if (i != n - 1) { cout << ";\n "; }
	}
	cout << "]\n\n";
}

template<typename T>
void MatrixMult_Standard(const int n, const vector<vector<T>> * A, const vector<vector<T>> * B, vector<vector<T>> * C)
{
	T dot_product;
	int i, j, k;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			dot_product = 0;

			for (k = 0; k < n; k++)
			{
				dot_product += (*A)[i][k] * (*B)[k][j];
			}

			(*C)[i][j] = dot_product;
		}
	}
}

template<typename T>
void MatrixMult_OpenMP(const int n, const vector<vector<T>> * A, const vector<vector<T>> * B, vector<vector<T>> * C)
{
	T dot_product;
	int i, j, k;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			dot_product = 0;
			for (k = 0; k < n; k++)
			{
				dot_product += (*A)[i][k] * (*B)[k][j];
			}
			(*C)[i][j] = dot_product;
		}
	}
}

template<typename T>
void MatrixSum(const int n, const vector<vector<T>> * A, const vector<vector<T>> * B, vector<vector<T>> * C)
{
	int i, j;
#pragma omp parallel for private(i,j)
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			(*C)[i][j] = (*A)[i][j] + (*B)[i][j];
		}
	}
}

template<typename T>
void MatrixSubs(const int n, const vector<vector<T>> * A, const vector<vector<T>> * B, vector<vector<T>> * C)
{
	int i, j;
#pragma omp parallel for private(i,j)
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			(*C)[i][j] = (*A)[i][j] - (*B)[i][j];
		}
	}
}

template<typename T>
void MatrixMult_Strassen(const int n, vector<vector<T>> * A, vector<vector<T>> * B, vector<vector<T>> * C)
{

	if (n == 2)
	{
		MatrixMult_OpenMP(n, A, B, C);
		return;
	}

	MatrixPadding(n, A);
	MatrixPadding(n, B);
	MatrixPadding(n, C);

	int i, j;
	int mid = n / 2;

	vector<vector<T>> A_11(mid, vector<T>(mid)), A_12(mid, vector<T>(mid)), A_21(mid, vector<T>(mid)), A_22(mid, vector<T>(mid)),
		B_11(mid, vector<T>(mid)), B_12(mid, vector<T>(mid)), B_21(mid, vector<T>(mid)), B_22(mid, vector<T>(mid)),
		C_11(mid, vector<T>(mid)), C_12(mid, vector<T>(mid)), C_21(mid, vector<T>(mid)), C_22(mid, vector<T>(mid)),
		M_1(mid, vector<T>(mid)), M_2(mid, vector<T>(mid)), M_3(mid, vector<T>(mid)), M_4(mid, vector<T>(mid)),
		M_5(mid, vector<T>(mid)), M_6(mid, vector<T>(mid)), M_7(mid, vector<T>(mid)),
		temp_A(mid, vector<T>(mid)), temp_B(mid, vector<T>(mid));

	// Matrix Division
	for (i = 0; i < mid; i++)
	{
		for (j = 0; j < mid; j++)
		{
			A_11[i][j] = (*A)[i][j];
			A_12[i][j] = (*A)[i][j + mid];
			A_21[i][j] = (*A)[i + mid][j];
			A_22[i][j] = (*A)[i + mid][j + mid];

			B_11[i][j] = (*B)[i][j];
			B_12[i][j] = (*B)[i][j + mid];
			B_21[i][j] = (*B)[i + mid][j];
			B_22[i][j] = (*B)[i + mid][j + mid];
		}
	}

	// M1 = (A11 + A22) * (B11 + B22)
	MatrixSum(mid, &A_11, &A_22, &temp_A);
	MatrixSum(mid, &B_11, &B_22, &temp_B);
	MatrixMult_Strassen(mid, &temp_A, &temp_B, &M_1);

	// M2 = (A21 + A22) * B11
	MatrixSum(mid, &A_21, &A_22, &temp_A);
	MatrixMult_Strassen(mid, &temp_A, &B_11, &M_2);

	// M3 = A11 * (B12-B22)
	MatrixSubs(mid, &B_12, &B_22, &temp_B);
	MatrixMult_Strassen(mid, &A_11, &temp_B, &M_3);

	// M4 = A22 * (B21 - B11)
	MatrixSubs(mid, &B_21, &B_11, &temp_B);
	MatrixMult_Strassen(mid, &A_22, &temp_B, &M_4);

	// M5 = (A11 + A12) * B22
	MatrixSum(mid, &A_11, &A_12, &temp_A);
	MatrixMult_Strassen(mid, &temp_A, &B_22, &M_5);

	// M6 = (A21 - A11) * (B11 + B12)
	MatrixSubs(mid, &A_21, &A_11, &temp_A);
	MatrixSum(mid, &B_11, &B_12, &temp_B);
	MatrixMult_Strassen(mid, &temp_A, &temp_B, &M_6);

	// M7 = (A12 - A22) * (B21 + B22)
	MatrixSubs(mid, &A_12, &A_22, &temp_A);
	MatrixSum(mid, &B_21, &B_22, &temp_B);
	MatrixMult_Strassen(mid, &temp_A, &temp_B, &M_7);

	// C11 = M1 + M4 - M5 + M7
	MatrixSum(mid, &M_1, &M_4, &temp_A);
	MatrixSubs(mid, &temp_A, &M_5, &temp_B);
	MatrixSum(mid, &temp_B, &M_7, &C_11);

	// C12 = M3 + M5
	MatrixSum(mid, &M_3, &M_5, &C_12);

	// C21 = M2 + M4
	MatrixSum(mid, &M_2, &M_4, &C_21);

	// C22 = M1 - M2 + M3 + M6
	MatrixSum(mid, &M_1, &M_3, &temp_A);
	MatrixSubs(mid, &temp_A, &M_2, &temp_B);
	MatrixSum(mid, &temp_B, &M_6, &C_22);

	for (i = 0; i < mid; i++)
	{
		for (j = 0; j < mid; j++)
		{
			(*C)[i][j] = C_11[i][j];
			(*C)[i][j + mid] = C_12[i][j];
			(*C)[i + mid][j] = C_21[i][j];
			(*C)[i + mid][j + mid] = C_22[i][j];
		}
	}

	MatrixRemovePadding(n, C);
}

int FindFaddingSize(const int n);

template<typename T>
void MatrixPadding(const int n, vector<vector<T>> * A)
{
	int i;
	int size = FindFaddingSize(n);

	if (size) return;

	A->resize(size);
	for (i = 0; i < size; i++)
	{
		(*A)[i].resize(size);
	}

	MatrixDisp(size, A);
}

template<typename T>
void MatrixRemovePadding(const int n, vector<vector<T>> * A)
{
	int i;

	A->resize(n);

	for (i = 0; i < n; i++)
	{
		(*A)[i].resize(n);
	}
}
