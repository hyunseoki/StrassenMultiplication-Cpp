#pragma once
#include <iostream>
#include <vector>
#include <omp.h>

using std::cout;
using std::vector;

struct MatrixType
{
	int x, y;
};

const MatrixType M_11 = { 0, 0 };
const MatrixType M_12 = { 0, 1 };
const MatrixType M_21 = { 1, 0 };
const MatrixType M_22 = { 1, 1 };

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
void MatrixInitZero(const int n, vector<vector<T>> * A)
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
				(*A)[i][j] = 0;
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
	int i, j, k;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			for (k = 0; k < n; k++)
			{
				if (k)
				{
					(*C)[i][j] += (*A)[i][k] * (*B)[k][j];
				}
				else
					(*C)[i][j] = (*A)[i][k] * (*B)[k][j];
			}
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
			for (k = 0; k < n; k++)
			{
				if (k)
				{
					(*C)[i][j] += (*A)[i][k] * (*B)[k][j];
				}
				else
					(*C)[i][j] = (*A)[i][k] * (*B)[k][j];
			}
		}
	}
}

template<typename T>
void MatrixPartialMult_OpenMP(const int n, const vector<vector<T>> * A, const MatrixType MatrixTypeA, const vector<vector<T>> * B, const MatrixType MatrixTypeB,
	vector<vector<T>> * C, const MatrixType MatrixTypeC)
{
	T dot_product;
	int i, j, k;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			for (k = 0; k < n; k++)
			{
				if (k)
				{
					(*C)[i + n * MatrixTypeC.x][j + n * MatrixTypeC.y] += (*A)[i + n * MatrixTypeA.x][k + n * MatrixTypeA.y] 
						* (*B)[k + n * MatrixTypeB.x][j + n * MatrixTypeB.y];
				}
				else
					(*C)[i + n * MatrixTypeC.x][j + n * MatrixTypeC.y] = (*A)[i + n * MatrixTypeA.x][k + n * MatrixTypeA.y]
					* (*B)[k + n * MatrixTypeB.x][j + n * MatrixTypeB.y];
			}
		}
	}
}

template<typename T>
void MatrixSum(const int n, const vector<vector<T>> * A, const vector<vector<T>> * B, vector<vector<T>> * C)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			(*C)[i][j] = (*A)[i][j] + (*B)[i][j];
		}
	}
}

template<typename T>
void MatrixPartialSum(const int n, const vector<vector<T>> * A, const MatrixType MatrixTypeA, const vector<vector<T>> * B, const MatrixType MatrixTypeB,
	vector<vector<T>> * C, const MatrixType MatrixTypeC)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			(*C)[i + n * MatrixTypeC.x][j + n * MatrixTypeC.y] = (*A)[i + n * MatrixTypeA.x ][j + n * MatrixTypeA.y] 
				+ (*B)[i + n * MatrixTypeB.x][j + n * MatrixTypeB.y];
		}
	}
}

template<typename T>
void MatrixSubs(const int n, const vector<vector<T>> * A, const vector<vector<T>> * B, vector<vector<T>> * C)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			(*C)[i][j] = (*A)[i][j] - (*B)[i][j];
		}
	}
}

template<typename T>
void MatrixPartialSubs(const int n, const vector<vector<T>> * A, const MatrixType MatrixTypeA, const vector<vector<T>> * B, const MatrixType MatrixTypeB,
	vector<vector<T>> * C, const MatrixType MatrixTypeC)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			(*C)[i + n * MatrixTypeC.x][j + n * MatrixTypeC.y] = (*A)[i + n * MatrixTypeA.x][j + n * MatrixTypeA.y]
				- (*B)[i + n * MatrixTypeB.x][j + n * MatrixTypeB.y];
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

	int i, j, median, paddingsize(FindFaddingSize(n));

	if (paddingsize)
	{
		median = paddingsize / 2;
		MatrixPadding(paddingsize, A, B, C);
	}
	else
	{
		median = n / 2;
	}

	vector<vector<T>> A_11(median, vector<T>(median)), A_12(median, vector<T>(median)), A_21(median, vector<T>(median)), A_22(median, vector<T>(median)),
		B_11(median, vector<T>(median)), B_12(median, vector<T>(median)), B_21(median, vector<T>(median)), B_22(median, vector<T>(median)),
		C_11(median, vector<T>(median)), C_12(median, vector<T>(median)), C_21(median, vector<T>(median)), C_22(median, vector<T>(median)),
		M_1(median, vector<T>(median)), M_2(median, vector<T>(median)), M_3(median, vector<T>(median)), M_4(median, vector<T>(median)),
		M_5(median, vector<T>(median)), M_6(median, vector<T>(median)), M_7(median, vector<T>(median)),
		temp_A(median, vector<T>(median)), temp_B(median, vector<T>(median));

	// Matrix Division
	for (i = 0; i < median; i++)
	{
		for (j = 0; j < median; j++)
		{
			A_11[i][j] = (*A)[i][j];
			A_12[i][j] = (*A)[i][j + median];
			A_21[i][j] = (*A)[i + median][j];
			A_22[i][j] = (*A)[i + median][j + median];

			B_11[i][j] = (*B)[i][j];
			B_12[i][j] = (*B)[i][j + median];
			B_21[i][j] = (*B)[i + median][j];
			B_22[i][j] = (*B)[i + median][j + median];
		}
	}

		// M1 = (A11 + A22) * (B11 + B22)
		MatrixSum(median, &A_11, &A_22, &temp_A);
		MatrixSum(median, &B_11, &B_22, &temp_B);
		MatrixMult_Strassen(median, &temp_A, &temp_B, &M_1);

		// M2 = (A21 + A22) * B11
		MatrixSum(median, &A_21, &A_22, &temp_A);
		MatrixMult_Strassen(median, &temp_A, &B_11, &M_2);

		// M3 = A11 * (B12-B22)
		MatrixSubs(median, &B_12, &B_22, &temp_B);
		MatrixMult_Strassen(median, &A_11, &temp_B, &M_3);

		// M4 = A22 * (B21 - B11)
		MatrixSubs(median, &B_21, &B_11, &temp_B);
		MatrixMult_Strassen(median, &A_22, &temp_B, &M_4);

		// M5 = (A11 + A12) * B22
		MatrixSum(median, &A_11, &A_12, &temp_A);
		MatrixMult_Strassen(median, &temp_A, &B_22, &M_5);

		// M6 = (A21 - A11) * (B11 + B12)
		MatrixSubs(median, &A_21, &A_11, &temp_A);
		MatrixSum(median, &B_11, &B_12, &temp_B);
		MatrixMult_Strassen(median, &temp_A, &temp_B, &M_6);

		// M7 = (A12 - A22) * (B21 + B22)
		MatrixSubs(median, &A_12, &A_22, &temp_A);
		MatrixSum(median, &B_21, &B_22, &temp_B);
		MatrixMult_Strassen(median, &temp_A, &temp_B, &M_7);

		// C11 = M1 + M4 - M5 + M7
		MatrixSum(median, &M_1, &M_4, &temp_A);
		MatrixSubs(median, &temp_A, &M_5, &temp_B);
		MatrixSum(median, &temp_B, &M_7, &C_11);

		// C12 = M3 + M5
		MatrixSum(median, &M_3, &M_5, &C_12);

		// C21 = M2 + M4
		MatrixSum(median, &M_2, &M_4, &C_21);

		// C22 = M1 - M2 + M3 + M6
		MatrixSum(median, &M_1, &M_3, &temp_A);
		MatrixSubs(median, &temp_A, &M_2, &temp_B);
		MatrixSum(median, &temp_B, &M_6, &C_22);

	for (i = 0; i < median; i++)
	{
		for (j = 0; j < median; j++)
		{
			(*C)[i][j] = C_11[i][j];
			(*C)[i][j + median] = C_12[i][j];
			(*C)[i + median][j] = C_21[i][j];
			(*C)[i + median][j + median] = C_22[i][j];
		}
	}

	if(!paddingsize) MatrixRemovePadding(n, C);
}

template<typename T>
void MatrixMult_Optimized_Strassen(const int n, vector<vector<T>> * A, vector<vector<T>> * B, vector<vector<T>> * C)
{
	if (n == 2)
	{
		MatrixMult_OpenMP(n, A, B, C);
		return;
	}

	int i, j, median, paddingsize(FindFaddingSize(n));

	if (paddingsize)
	{
		median = paddingsize / 2;
		MatrixPadding(paddingsize, A, B, C);
	}
	else
	{
		median = n / 2;
	}

	vector<vector<T>> A_11(median, vector<T>(median)), A_22(median, vector<T>(median)),
		B_11(median, vector<T>(median)), B_22(median, vector<T>(median)),
		temp_AA(median, vector<T>(median)), temp_BB(median, vector<T>(median)), temp_CC(median, vector<T>(median));

	for (i = 0; i < median; i++)
	{
		for (j = 0; j < median; j++)
		{
			A_11[i][j] = (*A)[i][j];
			A_22[i][j] = (*A)[i + median][j + median];
			B_11[i][j] = (*B)[i][j];
			B_22[i][j] = (*B)[i + median][j + median];
		}
	}

	// C11 = M1 +           M4 - M5      + M7
	// C12 =           M3      + M5
	// C21 =      M2      + M4
	// C22 = M1 - M2 + M3           + M6

	// M1 = (A11 + A22) * (B11 + B22)
	MatrixPartialSum(median, A, M_11, A, M_22, &temp_AA, M_11);
	MatrixPartialSum(median, B, M_11, B, M_22, &temp_BB, M_11);
	MatrixMult_Optimized_Strassen(median, &temp_AA, &temp_BB, &temp_CC);

	MatrixPartialSum(median, &temp_CC, M_11, C, M_11, C, M_11);
	MatrixPartialSum(median, &temp_CC, M_11, C, M_22, C, M_22);

	// M2 = (A21 + A22) * B11 
	MatrixPartialSum(median, A, M_21, A, M_22, &temp_AA, M_11);
	MatrixMult_Standard(median, &temp_AA, &B_11, &temp_CC);
	MatrixMult_Optimized_Strassen(median, &temp_AA, &B_11, &temp_CC);

	MatrixPartialSum(median, &temp_CC, M_11, C, M_21, C, M_21);
	MatrixPartialSubs(median, C, M_22, &temp_CC, M_11, C, M_22);

	// M3 = A11 * (B12-B22)
	MatrixPartialSubs(median, B, M_12, B, M_22, &temp_AA, M_11);
	MatrixMult_Standard(median, &A_11, &temp_AA, &temp_BB);
	//MatrixMult_Optimized_Strassen(median, &A_11, &temp_AA, &temp_BB);

	MatrixPartialSum(median, &temp_BB, M_11, C, M_12, C, M_12);
	MatrixPartialSum(median, &temp_BB, M_11, C, M_22, C, M_22);

	// M4 = A22 * (B21 - B11)
	MatrixPartialSubs(median, B, M_21, B, M_11, &temp_AA, M_11);
	MatrixMult_Standard(median, &A_22, &temp_AA, &temp_BB);
	MatrixMult_Optimized_Strassen(median, &A_22, &temp_AA, &temp_BB);

	MatrixPartialSum(median, &temp_BB, M_11, C, M_11, C, M_11);
	MatrixPartialSum(median, &temp_BB, M_11, C, M_21, C, M_21);

	// M5 = (A11 + A12) * B22
	MatrixPartialSum(median, A, M_11, A, M_12, &temp_AA, M_11);
	MatrixMult_Standard(median, &temp_AA, &B_22, &temp_BB);
	//MatrixMult_Optimized_Strassen(median, &temp_AA, &B_22, &temp_BB);

	MatrixPartialSubs(median, C, M_11, &temp_BB, M_11, C, M_11);
	MatrixPartialSum(median, C, M_12, &temp_BB, M_11, C, M_12);

	// M6 = (A21 - A11) * (B11 + B12)
	MatrixPartialSubs(median, A, M_21, A, M_11, &temp_AA, M_11);
	MatrixPartialSum(median, B, M_11, B, M_12, &temp_BB, M_11);
	MatrixMult_Optimized_Strassen(median, &temp_AA, &temp_BB, &temp_CC);

	MatrixPartialSum(median, C, M_22, &temp_CC, M_11, C, M_22);

	// M7 = (A12 - A22) * (B21 + B22)
	MatrixPartialSubs(median, A, M_12, A, M_22, &temp_AA, M_11);
	MatrixPartialSum(median, B, M_21, B, M_22, &temp_BB, M_11);
	MatrixMult_Standard(median, &temp_AA, &temp_BB, &temp_CC);
	//MatrixMult_Optimized_Strassen(median, &temp_AA, &temp_BB, &temp_CC);

	MatrixPartialSum(median, C, M_11, &temp_CC, M_11, C, M_11);

	if (!paddingsize) MatrixRemovePadding(n, C);
}


int FindFaddingSize(const int n);

template<typename T>
void MatrixPadding(const int n, vector<vector<T>> * A, vector<vector<T>> * B, vector<vector<T>> * C)
{
	int i;

	A->resize(n);
	B->resize(n);
	C->resize(n);

#pragma omp parallel for private(i)
	for (i = 0; i < n; i++)
	{
		(*A)[i].resize(n);
		(*B)[i].resize(n);
		(*C)[i].resize(n);
	}
}

template<typename T>
void MatrixRemovePadding(const int n, vector<vector<T>> * A)
{
	int i;

	A->resize(n);

#pragma omp parallel for private(i)
	for (i = 0; i < n; i++)
	{
		(*A)[i].resize(n);
	}
}
