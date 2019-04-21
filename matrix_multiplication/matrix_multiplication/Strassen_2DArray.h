#pragma once
#include <iostream>
#include <time.h>

using std::cout;

namespace ArrayMult
{

}

const int N = 128;
using std::cout;

typedef struct MatrixOffset
{
	int i, j;
}Offset;

template<typename T>
void CreateMatrix(const int n, T** A)
{
	int i;

	for (i = 0; i < n; i++)
	{
		A[i] = new int[n];
	}
}

template<typename T>
void DestroyMatrix(const int n, T** A)
{
	int i;

	for (i = 0; i < n; i++)
	{
		delete A[i];
	}
}

template<typename T>
void CreateRandomMatrix(const int n, T ** A)
{
	CreateMatrix(n, A);

	int i, j;

	srand(time(NULL));

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			A[i][j] = (T)(rand()) * 10 / 32767; // 0 ~ 10.0 ����
		}
	}
}

template<typename T>
void CreateEyeMatrix(const int n, T ** A)
{
	CreateMatrix(n, A);

	int i, j;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			if (i == j)
			{
				A[i][j] = (T)1.0;
			}
			else
				A[i][j] = (T)0.0;
		}
	}
}

template<typename T>
void CreateZeroMatrix(const int n, T ** A)
{
	CreateMatrix(n, A);
	int i, j;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			A[i][j] = (T)0.0;
		}
	}
}

template<typename T>
void MatrixPrint(const int n, const T A[][N])
{
	cout << "[";
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << A[i][j];
			if (j != n - 1) { cout << ", "; }
		}

		if (i != n - 1) { cout << ";\n "; }

	}
	cout << "]\n\n";
}

template<typename T>
void MatrixPrint(const int n, T ** A)
{
	cout << "[";
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << A[i][j];
			if (j != n - 1) { cout << ", "; }
		}

		if (i != n - 1) { cout << ";\n "; }

	}
	cout << "]\n\n";
}

template<typename T>
void MatrixMult_Standard(const int n, const T A[][N], const T B[][N], T C[][N])
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < n; k++)
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
void MatrixMult_Standard(const int n, T ** A, T ** B, T ** C)
{
	int i, j, k;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < n; k++)
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
void MatrixMult_Standard(const int n, const Offset A_Offset, const Offset B_Offset, const Offset C_Offset, T ** A, T ** B, T ** C)
{
	int i, j, k;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < n; k++)
			{
				if (k)
				{
					C[i + C_Offset.i][j + C_Offset.j] += A[i + A_Offset.i][k + A_Offset.j] * B[k + B_Offset.i][j + B_Offset.j];
				}
				else
					C[i + C_Offset.i][j + C_Offset.j] = A[i + A_Offset.i][k + A_Offset.j] * B[k + B_Offset.i][j + B_Offset.j];
			}
		}
	}
}

template<typename T>
void MatrixMult_Partial(const int n, const Offset A_Offset, const Offset B_Offset, const Offset C_Offset, const T A[][N], const T B[][N], T C[][N])
{
	T dot_product;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < n; k++)
			{
				if (k)
				{
					C[i + C_Offset.i][j + C_Offset.j] += A[i + A_Offset.i][k + A_Offset.j] * B[k + B_Offset.i][j + B_Offset.j];
				}
				else
					C[i + C_Offset.i][j + C_Offset.j] = A[i + A_Offset.i][k + A_Offset.j] * B[k + B_Offset.i][j + B_Offset.j];
			}
		}
	}
}

template<typename T>
void MatrixMult_Partial(const int n, const Offset A_Offset, const Offset B_Offset, const Offset C_Offset, T ** A, const T B[][N], T ** C)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < n; k++)
			{
				if (k)
				{
					C[i + C_Offset.i][j + C_Offset.j] += A[i + A_Offset.i][k + A_Offset.j] * B[k + B_Offset.i][j + B_Offset.j];
				}
				else
					C[i + C_Offset.i][j + C_Offset.j] = A[i + A_Offset.i][k + A_Offset.j] * B[k + B_Offset.i][j + B_Offset.j];
			}
		}
	}
}

template<typename T>
void MatrixMult_Partial(const int n, const Offset A_Offset, const Offset B_Offset, const Offset C_Offset, const T A[][N], T ** B, T ** C)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < n; k++)
			{
				if (k)
				{
					C[i + C_Offset.i][j + C_Offset.j] += A[i + A_Offset.i][k + A_Offset.j] * B[k + B_Offset.i][j + B_Offset.j];
				}
				else
					C[i + C_Offset.i][j + C_Offset.j] = A[i + A_Offset.i][k + A_Offset.j] * B[k + B_Offset.i][j + B_Offset.j];
			}
		}
	}
}

template<typename T>
void MatrixMult_Partial(const int n, const Offset A_Offset, const Offset B_Offset, const Offset C_Offset, T ** A, T ** B, T ** C)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < n; k++)
			{
				if (k)
				{
					C[i + C_Offset.i][j + C_Offset.j] += A[i + A_Offset.i][k + A_Offset.j] * B[k + B_Offset.i][j + B_Offset.j];
				}
				else
					C[i + C_Offset.i][j + C_Offset.j] = A[i + A_Offset.i][k + A_Offset.j] * B[k + B_Offset.i][j + B_Offset.j];
			}
		}
	}
}

template<typename T>
void MatrixSum(const int n, const T A[][N], const T B[][N], T C[][N])
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			C[i][j] = A[i][j] + B[i][j];
		}
	}
}

template<typename T>
void MatrixSum(const int n, T **A, T **B, T **C)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			C[i][j] = A[i][j] + B[i][j];
		}
	}
}

template<typename T>
void MatrixSum_Partial(const int n, const Offset A_Offset, const Offset B_Offset, const Offset C_Offset, const T A[][N], const T B[][N], T C[][N])
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			C[i + C_Offset.i][j + C_Offset.j] = A[i + A_Offset.i][j + A_Offset.j] + B[i + B_Offset.i][j + B_Offset.j];
		}
	}
}

template<typename T>
void MatrixSum_Partial(const int n, const Offset A_Offset, const Offset B_Offset, const Offset C_Offset, const T A[][N], T ** B, T C[][N])
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			C[i + C_Offset.i][j + C_Offset.j] = A[i + A_Offset.i][j + A_Offset.j] + B[i + B_Offset.i][j + B_Offset.j];
		}
	}
}

template<typename T>
void MatrixSum_Partial(const int n, const Offset A_Offset, const Offset B_Offset, const T A[][N], const T B[][N], T **C)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			C[i][j] = A[i + A_Offset.i][j + A_Offset.j] + B[i + B_Offset.i][j + B_Offset.j];
		}
	}
}

template<typename T>
void MatrixSum_Partial(const int n, const Offset A_Offset, const Offset B_Offset, T **A, T ** B, T **C)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			C[i][j] = A[i + A_Offset.i][j + A_Offset.j] + B[i + B_Offset.i][j + B_Offset.j];
		}
	}
}

template<typename T>
void MatrixSum_Partial(const int n, const Offset A_Offset, const Offset B_Offset, const Offset C_Offset, T **A, T ** B, T **C)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			C[i + C_Offset.i][j + C_Offset.j] = A[i + A_Offset.i][j + A_Offset.j] + B[i + B_Offset.i][j + B_Offset.j];
		}
	}
}

template<typename T>
void MatrixSubs(const int n, const T A[][N], const T B[][N], T C[][N])
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			C[i][j] = A[i][j] - B[i][j];
		}
	}
}

template<typename T>
void MatrixSubs(const int n, T **A, T **B, T **C)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			C[i][j] = A[i][j] - B[i][j];
		}
	}
}

template<typename T>
void MatrixSubs_Partial(const int n, const Offset A_Offset, const Offset B_Offset, const Offset C_Offset, const T A[][N], const T B[][N], T C[][N])
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			C[i + C_Offset.i][j + C_Offset.j] = A[i + A_Offset.i][j + A_Offset.j] - B[i + B_Offset.i][j + B_Offset.j];
		}
	}
}

template<typename T>
void MatrixSubs_Partial(const int n, const Offset A_Offset, const Offset B_Offset, const T A[][N], const T B[][N], T **C)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			C[i][j] = A[i + A_Offset.i][j + A_Offset.j] - B[i + B_Offset.i][j + B_Offset.j];
		}
	}
}

template<typename T>
void MatrixSubs_Partial(const int n, const Offset A_Offset, const Offset B_Offset, const Offset C_Offset, const T A[][N], T ** B, T C[][N])
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			C[i + C_Offset.i][j + C_Offset.j] = A[i + A_Offset.i][j + A_Offset.j] - B[i + B_Offset.i][j + B_Offset.j];
		}
	}
}

template<typename T>
void MatrixSubs_Partial(const int n, const Offset A_Offset, const Offset B_Offset, const Offset C_Offset, T **A, T ** B, T ** C)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			C[i + C_Offset.i][j + C_Offset.j] = A[i + A_Offset.i][j + A_Offset.j] - B[i + B_Offset.i][j + B_Offset.j];
		}
	}

}

template<typename T>
void MatrixCheck(const int n, const T A[][N], const T B[][N])
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (A[i][j] != B[i][j])
			{
				cout << "not same\n";
				return;
			}
		}
	}
	cout << "same\n";
}

template<typename T>
void MatrixCheck(const int n, T **A, T **B)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (A[i][j] != B[i][j])
			{
				cout << "not same\n";
				return;
			}
		}
	}
	cout << "same\n";
}
//
//template<typename T>
//void MatrixMult_Strassen(const int n, const T A[][N], const T B[][N], T C[][N])
//{
//	if (n == 2)
//	{
//		MatrixMult_Standard(n, A, B, C);
//		return;
//	}
//
//	int i, m = n / 2;
//
//	T** temp1 = new T*[m];
//	T** temp2 = new T*[m];
//	T** temp3 = new T*[m];
//	for (i = 0; i < m; i++)
//	{
//		temp1[i] = new T[m];
//		temp2[i] = new T[m];
//		temp3[i] = new T[m];
//	}
//
//	Offset M11 = { 0, 0 };
//	Offset M12 = { 0, m };
//	Offset M21 = { m, 0 };
//	Offset M22 = { m, m };
//	Offset &ZERO = M11;
//
//	// C11 = M1 +           M4 - M5      + M7
//	// C12 =           M3      + M5
//	// C21 =      M2      + M4
//	// C22 = M1 - M2 + M3           + M6
//
//	// M1 = (A11 + A22) * (B11 + B22)
//	MatrixSum_Partial(m, M11, M22, A, A, temp1);
//	MatrixSum_Partial(m, M11, M22, B, B, temp2);
//
//	MatrixMult_Standard(m, temp1, temp2, temp3);
//
//	MatrixSum_Partial(m, M11, ZERO, M11, C, temp3, C);
//	MatrixSum_Partial(m, M22, ZERO, M22, C, temp3, C);
//
//	// M2 = (A21 + A22) * B11
//	MatrixSum_Partial(m, M21, M22, A, A, temp1);
//	MatrixMult_Partial(m, ZERO, M11, ZERO, temp1, B, temp3);
//
//	MatrixSum_Partial(m, M21, ZERO, M21, C, temp3, C);
//	MatrixSubs_Partial(m, M22, ZERO, M22, C, temp3, C);
//
//	// M3 = A11 * (B12-B22)
//	MatrixSubs_Partial(m, M12, M22, B, B, temp1);
//	
//	MatrixMult_Partial(m, M11, ZERO, ZERO, A, temp1, temp3);
//
//	MatrixSum_Partial(m, M12, ZERO, M12, C, temp3, C);
//	MatrixSum_Partial(m, M22, ZERO, M22, C, temp3, C);
//
//	// M4 = A22 * (B21 - B11)
//	MatrixSubs_Partial(m, M21, M11, B, B, temp1);
//
//	MatrixMult_Partial(m, M22, ZERO, ZERO, A, temp1, temp3);
//
//	MatrixSum_Partial(m, M11, ZERO, M11, C, temp3, C);
//	MatrixSum_Partial(m, M21, ZERO, M21, C, temp3, C);
//
//	// M5 = (A11 + A12) * B22
//	MatrixSum_Partial(m, M11, M12, A, A, temp1);
//
//	MatrixMult_Partial(m, ZERO, M22, ZERO, temp1, B, temp3);
//
//	MatrixSubs_Partial(m, M11, ZERO, M11, C, temp3, C);
//	MatrixSum_Partial(m, M12, ZERO, M12, C, temp3, C);
//
//	// M6 = (A21 - A11) * (B11 + B12)
//	MatrixSubs_Partial(m, M21, M11, A, A, temp1);
//	MatrixSum_Partial(m, M11, M12, B, B, temp2);
//
//	MatrixMult_Partial(m, ZERO, ZERO, ZERO, temp1, temp2, temp3);
//
//	MatrixSum_Partial(m, M22, ZERO, M22, C, temp3, C);
//
//	// M7 = (A12 - A22) * (B21 + B22)
//	MatrixSubs_Partial(m, M12, M22, A, A, temp1);
//	MatrixSum_Partial(m, M21, M22, B, B, temp2);
//
//	MatrixMult_Partial(m, ZERO, ZERO, ZERO, temp1, temp2, temp3);
//
//	MatrixSum_Partial(m, M11, ZERO, M11, C, temp3, C);
//
//	for (i = 0; i < m; i++)
//	{
//		delete(temp1[i]);
//		delete(temp2[i]);
//		delete(temp3[i]);
//	}
//
//	delete(temp1);
//	delete(temp2);
//	delete(temp3);
//}

template<typename T>
void MatrixMult_Strassen(const int n, const Offset A_Offset, const Offset B_Offset, const Offset C_Offset, T **A, T **B, T **C)
{
	if (n == 2)
	{
		MatrixMult_Standard(n, A_Offset, B_Offset, C_Offset, A, B, C);
		return;
	}

	int i, m = n / 2;

	T** temp1 = new T*[m];
	T** temp2 = new T*[m];
	T** temp3 = new T*[m];

	for (i = 0; i < m; i++)
	{
		temp1[i] = new T[m];
		temp2[i] = new T[m];
		temp3[i] = new T[m];
	}

	for (i = 0; i < m; i++)
	{
		for (int j = 0; j < m; j++)
		{
			temp1[i][j] = 0;
			temp2[i][j] = 0;
			temp3[i][j] = 0;
		}
	}

	Offset A11 = { A_Offset.i + 0 ,A_Offset.j + 0 };
	Offset A12 = { A_Offset.i + 0, A_Offset.j + m };
	Offset A21 = { A_Offset.i + m, A_Offset.j + 0 };
	Offset A22 = { A_Offset.i + m, A_Offset.j + m };
	Offset B11 = { B_Offset.i + 0 ,B_Offset.j + 0 };
	Offset B12 = { B_Offset.i + 0, B_Offset.j + m };
	Offset B21 = { B_Offset.i + m, B_Offset.j + 0 };
	Offset B22 = { B_Offset.i + m, B_Offset.j + m };
	Offset C11 = { C_Offset.i + 0 ,C_Offset.j + 0 };
	Offset C12 = { C_Offset.i + 0, C_Offset.j + m };
	Offset C21 = { C_Offset.i + m, C_Offset.j + 0 };
	Offset C22 = { C_Offset.i + m, C_Offset.j + m };
	Offset ZERO = { 0, 0 };

	// C11 = M1 +           M4 - M5      + M7
	// C12 =           M3      + M5
	// C21 =      M2      + M4
	// C22 = M1 - M2 + M3           + M6

	// M1 = (A11 + A22) * (B11 + B22)
	MatrixSum_Partial(m, A11, A22, ZERO, A, A, temp1);
	//MatrixPrint(m, temp1);
	MatrixSum_Partial(m, B11, B22, ZERO, B, B, temp2);
	//MatrixPrint(m, temp2);
	MatrixMult_Strassen(m, ZERO, ZERO, ZERO, temp1, temp2, temp3);

	MatrixSum_Partial(m, C11, ZERO, C11, C, temp3, C);
	//MatrixPrint(m, C);
	MatrixSum_Partial(m, C22, ZERO, C22, C, temp3, C);

	// M2 = (A21 + A22) * B11
	MatrixSum_Partial(m, A21, A22, A, A, temp1);

	MatrixMult_Strassen(m, ZERO, ZERO, B11, temp1, B, temp3);

	MatrixSum_Partial(m, C21, ZERO, C21, C, temp3, C);
	MatrixSubs_Partial(m, C22, ZERO, C22, C, temp3, C);

	// M3 = A11 * (B12-B22)
	MatrixSubs_Partial(m, B12, B22, ZERO, B, B, temp1);

	MatrixMult_Strassen(m, A11, ZERO, ZERO, A, temp1, temp3);

	MatrixSum_Partial(m, C12, ZERO, C12, C, temp3, C);
	MatrixSum_Partial(m, C22, ZERO, C22, C, temp3, C);

	// M4 = A22 * (B21 - B11)
	MatrixSubs_Partial(m, B21, B11, ZERO, B, B, temp1);

	MatrixMult_Strassen(m, A22, ZERO, ZERO, A, temp1, temp3);

	MatrixSum_Partial(m, C11, ZERO, C11, C, temp3, C);
	MatrixSum_Partial(m, C21, ZERO, C21, C, temp3, C);

	// M5 = (A11 + A12) * B22
	MatrixSum_Partial(m, A11, A12, A, A, temp1);

	MatrixMult_Strassen(m, ZERO, ZERO, ZERO, temp1, B, temp3);

	MatrixSubs_Partial(m, C11, ZERO, C11, C, temp3, C);
	MatrixSum_Partial(m, C12, ZERO, C12, C, temp3, C);

	// M6 = (A21 - A11) * (B11 + B12)
	MatrixSubs_Partial(m, A21, A11, ZERO, A, A, temp1);
	MatrixSum_Partial(m, B11, B12, B, B, temp2);

	MatrixMult_Strassen(m, ZERO, ZERO, ZERO, temp1, temp2, temp3);

	MatrixSum_Partial(m, C22, ZERO, C22, C, temp3, C);

	// M7 = (A12 - A22) * (B21 + B22)
	MatrixSubs_Partial(m, A12, A22, ZERO, A, A, temp1);
	MatrixSum_Partial(m, B21, B22, B, B, temp2);

	MatrixMult_Strassen(m, ZERO, ZERO, ZERO, temp1, temp2, temp3);

	MatrixSum_Partial(m, C11, ZERO, C11, C, temp3, C);

	for (i = 0; i < m; i++)
	{
		delete(temp1[i]);
		delete(temp2[i]);
		delete(temp3[i]);
	}

	delete(temp1);
	delete(temp2);
	delete(temp3);
}
