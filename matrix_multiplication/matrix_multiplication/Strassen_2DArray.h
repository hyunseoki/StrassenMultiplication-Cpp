#pragma once
#include <iostream>

using std::cout;

namespace ArrayMult
{

}

const int N = 4;
using std::cout;

typedef struct MatrixOffset
{
	int i, j;
}Offset;

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
void MatrixCheck(const int n, const T A[][N], const T B[][N])
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (A[i][j] != B[i][j])
			{
				cout << "Matrix A and B are not same\n";
				return;
			}
		}
	}
	cout << "Matrix A and B are same\n";
}

template<typename T>
void MatrixMult_Strassen(const int n, const T A[][N], const T B[][N], T C[][N])
{
	if (n == 2)
	{
		MatrixMult_Standard(n, A, B, C);
		return;
	}

	int i, j, m = n / 2;

	T** temp1 = new T*[m];
	T** temp2 = new T*[m];
	T** temp3 = new T*[m];
	for (i = 0; i < m; i++)
	{
		temp1[i] = new T[m];
		temp2[i] = new T[m];
		temp3[i] = new T[m];
	}

	Offset A11 = { 0, 0 };
	Offset A12 = { 0, m };
	Offset A21 = { m, 0 };
	Offset A22 = { m, m };
	Offset &B11 = A11;
	Offset &B12 = A12;
	Offset &B21 = A21;
	Offset &B22 = A22;
	Offset &C11 = A11;
	Offset &C12 = A12;
	Offset &C21 = A21;
	Offset &C22 = A22;
	Offset &ZERO = A11;

	// C11 = M1 +           M4 - M5      + M7
	// C12 =           M3      + M5
	// C21 =      M2      + M4
	// C22 = M1 - M2 + M3           + M6

	// M1 = (A11 + A22) * (B11 + B22)
	MatrixSum_Partial(m, A11, A22, A, A, temp1);
	MatrixSum_Partial(m, B11, B22, B, B, temp2);

	MatrixMult_Standard(m, temp1, temp2, temp3);

	MatrixSum_Partial(m, C11, ZERO, C11, C, temp3, C);
	MatrixSum_Partial(m, C22, ZERO, C22, C, temp3, C);

	// M2 = (A21 + A22) * B11 
	MatrixSum_Partial(m, A21, A22, A, A, temp1);
	MatrixMult_Partial(m, ZERO, B11, ZERO, temp1, B, temp3);

	MatrixSum_Partial(m, C21, ZERO, C21, C, temp3, C);
	MatrixSubs_Partial(m, C22, ZERO, C22, C, temp3, C);

	// M3 = A11 * (B12-B22)
	MatrixSubs_Partial(m, B12, B22, B, B, temp1);
	
	MatrixMult_Partial(m, A11, ZERO, ZERO, A, temp1, temp3);

	MatrixSum_Partial(m, C12, ZERO, C12, C, temp3, C);
	MatrixSum_Partial(m, C22, ZERO, C22, C, temp3, C);

	// M4 = A22 * (B21 - B11)
	MatrixSubs_Partial(m, B21, B11, B, B, temp1);

	MatrixMult_Partial(m, A22, ZERO, ZERO, A, temp1, temp3);

	MatrixSum_Partial(m, C11, ZERO, C11, C, temp3, C);
	MatrixSum_Partial(m, C21, ZERO, C21, C, temp3, C);

	// M5 = (A11 + A12) * B22
	MatrixSum_Partial(m, A11, A12, A, A, temp1);

	MatrixMult_Partial(m, ZERO, B22, ZERO, temp1, B, temp3);

	MatrixSubs_Partial(m, C11, ZERO, C11, C, temp3, C);
	MatrixSum_Partial(m, C12, ZERO, C12, C, temp3, C);

	// M6 = (A21 - A11) * (B11 + B12)
	MatrixSubs_Partial(m, A21, A11, A, A, temp1);
	MatrixSum_Partial(m, B11, B12, B, B, temp2);

	MatrixMult_Partial(m, ZERO, ZERO, ZERO, temp1, temp2, temp3);

	MatrixSum_Partial(m, C22, ZERO, C22, C, temp3, C);

	// M7 = (A12 - A22) * (B21 + B22)
	MatrixSubs_Partial(m, A12, A22, A, A, temp1);
	MatrixSum_Partial(m, B21, B22, B, B, temp2);

	MatrixMult_Partial(m, ZERO, ZERO, ZERO, temp1, temp2, temp3);

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
