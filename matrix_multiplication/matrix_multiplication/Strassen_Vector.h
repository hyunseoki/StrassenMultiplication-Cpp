#pragma once
#include <iostream>
#include <vector>
#include <omp.h>
#include <thread>
#include <cmath>

using std::cout;
using std::vector;
using std::thread;
using std::ref;

typedef struct MatrixOffset
{
	int i, j;
}Offset;

struct PadData
{
	int m_Threshold, m_Padsize;
};

template<typename T>
void MatrixTrans(const int n, vector<vector<T>> * A, vector<vector<T>> * B)
{
	int i, j
	for (i = 0; i<n; i++)
	{
		for (j = 0; j<n; j++)
		{
			B[j*n + i] = A[i*n + j];
		}
	}
}

template<typename T>
void CreateRandomMatrix(const int n, vector<vector<T>> * A)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			(*A)[i][j] = (T)(rand() * 10 / 32767);
		}
	}
}

template<typename T>
void CreateEyeMatrix(const int n, vector<vector<T>> * A)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i == j)
				(*A)[i][j] = (T)1.0;
			else
				(*A)[i][j] = (T)0.0;
		}
	}
}

template<typename T>
void CreateZeroMatrix(const int n, vector<vector<T>> * A)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			(*A)[i][j] = 0;
		}
	}
}

template<typename T>
void MatrixPrint(const int n, const vector<vector<T>> * A)
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
void MatrixSum(const int n, const vector<vector<T>> * A, const vector<vector<T>> * B, vector<vector<T>> * C)
{
	#pragma omp parallel
	{
		int i, j;
		#pragma omp for
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				(*C)[i][j] = (*A)[i][j] + (*B)[i][j];
			}
		}
	}
}

template<typename T>
void MatrixSum_Partial(const int n, const Offset A_Offset, const Offset B_Offset, const Offset C_Offset, const vector<vector<T>> * A, const vector<vector<T>> * B, vector<vector<T>> * C)
{
	#pragma omp parallel
	{
		int i, j;
		#pragma omp for
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				(*C)[i + C_Offset.i][j + C_Offset.j] = (*A)[i + A_Offset.i][j + A_Offset.j] + (*B)[i + B_Offset.i][j + B_Offset.j];
			}
		}
	}
}

template<typename T>
void MatrixSubs(const int n, const vector<vector<T>> * A, const vector<vector<T>> * B, vector<vector<T>> * C)
{
	#pragma omp parallel
	{
		int i, j;
		#pragma omp for
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				(*C)[i][j] = (*A)[i][j] - (*B)[i][j];
			}
		}
	}
}

template<typename T>
void MatrixSubs_Partial(const int n, const Offset A_Offset, const Offset B_Offset, const Offset C_Offset, const vector<vector<T>> * A, const vector<vector<T>> * B, vector<vector<T>> * C)
{

	#pragma omp parallel
	{
		int i, j;
		#pragma omp for
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				(*C)[i + C_Offset.i][j + C_Offset.j] = (*A)[i + A_Offset.i][j + A_Offset.j] - (*B)[i + B_Offset.i][j + B_Offset.j];
			}
		}
	}
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
	#pragma omp parallel
	{
		int i, j, k;
		#pragma omp for
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
}

template<typename T>
void MatrixMult_Thread(const int n, const int thread_num, const int thread_idx, const vector<vector<T>> * A, const vector<vector<T>> * B, vector<vector<T>> * C)
{
	const int n_elements = (n * n);
	const int n_operations = n_elements / thread_num;
	const int rest_operations = n_elements % thread_num;

	int start_op, end_op;

	if (thread_idx == 0) {
		// First thread does more job
		start_op = n_operations * thread_idx;
		end_op = (n_operations * (thread_idx + 1)) + rest_operations;
	}
	else {
		start_op = n_operations * thread_idx + rest_operations;
		end_op = (n_operations * (thread_idx + 1)) + rest_operations;
	}

	for (int op = start_op; op < end_op; ++op)
	{
		const int row = op % n;
		const int col = op / n;
		T r = 0;
		for (int i = 0; i < n; ++i) {
			const T e1 = (*A)[row][i];
			const T e2 = (*B)[i][col];
			r += e1 * e2;
		}

		(*C)[row][col] = r;
	}
}

template<typename T>
void MatrixMult_MultiThread(const int n, const vector<vector<T>> * A, const vector<vector<T>> * B, vector<vector<T>> * C)
{
	const int THREADS_NUM = 16;
	thread t[THREADS_NUM];

	for (int i = 0; i < THREADS_NUM; i++)
	{
		t[i] = thread(MatrixMult_Thread<T>, ref(n), ref(THREADS_NUM), ref(i), ref(A), ref(B), ref(C));
	}

	for (int i = 0; i < THREADS_NUM; i++)
	{
		t[i].join();
	}
}

template<typename T>
void MatrixMult_Partial(const int n, const Offset A_Offset, const Offset B_Offset, const Offset C_Offset, const vector<vector<T>> * A, const vector<vector<T>> * B, vector<vector<T>> * C)
{
	#pragma omp parallel
	{
		#pragma omp for
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				for (int k = 0; k < n; k++)
				{
					if (k)
					{
						(*C)[i + C_Offset.i][j + C_Offset.j] += (*A)[i + A_Offset.i][k + A_Offset.j] * (*B)[k + B_Offset.i][j + B_Offset.j];
					}
					else
						(*C)[i + C_Offset.i][j + C_Offset.j] = (*A)[i + A_Offset.i][k + A_Offset.j] * (*B)[k + B_Offset.i][j + B_Offset.j];
				}
			}
		}
	}
}

int FindPaddingSize(const int n);

PadData FindOptimalPaddingSize(const int n);

template<typename T>
void MatrixPadding(const int n, vector<vector<T>> * A, vector<vector<T>> * B, vector<vector<T>> * C)
{
	int i;

	A->resize(n);
	B->resize(n);
	C->resize(n);

	#pragma omp parallel
	{
		#pragma omp for
		for (i = 0; i < n; i++)
		{
			(*A)[i].resize(n);
			(*B)[i].resize(n);
			(*C)[i].resize(n);
		}
	}
}

template<typename T>
void MatrixRemovePadding(const int n, vector<vector<T>> * A)
{
	int i;

	A->resize(n);

	#pragma omp parallel
	{
		#pragma omp for
		for (i = 0; i < n; i++)
		{
			(*A)[i].resize(n);
		}
	}
}

template<typename T>
void MatrixCheck(const int n, vector<vector<T>> * A, vector<vector<T>> * B)
{
	int i, j;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if ((*A)[i][j] != (*B)[i][j])
			{
				cout << "Matrix Size is " << n << ", not same\n\n";
				return;
			}
		}
	}
	cout << "Matrix Size is " << n << ", same\n\n";
}

template<typename T>
void MatrixMult_Strassen(const int n, const Offset A_Offset, const Offset B_Offset, const Offset C_Offset, vector<vector<T>> * A, vector<vector<T>> * B, vector<vector<T>> * C)
{
	if (n == 4)
	{
		MatrixMult_Partial(n, A_Offset, B_Offset, C_Offset, A, B, C);
		return;
	}

	int m, paddingsize(FindPaddingSize(n));

	if (paddingsize)
	{
		m = paddingsize / 2;
		MatrixPadding(paddingsize, A, B, C);
	}
	else
	{
		m = n / 2;
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

	vector<vector<T>> temp1(m, vector<T>(m, 0));
	vector<vector<T>> temp2(m, vector<T>(m, 0));
	vector<vector<T>> temp3(m, vector<T>(m, 0));
	vector<vector<T>> ZEROVEC(m, vector<T>(m, 0));

	// C11 = M1 +           M4 - M5      + M7
	// C12 =           M3      + M5
	// C21 =      M2      + M4
	// C22 = M1 - M2 + M3           + M6

	// M1 := (A11 + A22) * (B11 + B22)
	MatrixSum_Partial(m, A11, A22, ZERO, A, A, &temp1);
	MatrixSum_Partial(m, B11, B22, ZERO, B, B, &temp2);

	MatrixMult_Strassen(m, ZERO, ZERO, ZERO, &temp1, &temp2, &temp3);

	MatrixSum_Partial(m, C11, ZERO, C11, C, &temp3, C);
	MatrixSum_Partial(m, C22, ZERO, C22, C, &temp3, C);

	// M2 := (A21 + A22) * B11
	MatrixSum_Partial(m, A21, A22, ZERO, A, A, &temp1);

	temp3 = ZEROVEC;

	MatrixMult_Strassen(m, ZERO, B11, ZERO, &temp1, B, &temp3);

	MatrixSum_Partial(m, C21, ZERO, C21, C, &temp3, C);
	MatrixSubs_Partial(m, C22, ZERO, C22, C, &temp3, C);

	// M3 := A11 * (B12-B22)
	MatrixSubs_Partial(m, B12, B22, ZERO, B, B, &temp1);

	temp3 = ZEROVEC;

	MatrixMult_Strassen(m, A11, ZERO, ZERO, A, &temp1, &temp3);

	MatrixSum_Partial(m, C12, ZERO, C12, C, &temp3, C);
	MatrixSum_Partial(m, C22, ZERO, C22, C, &temp3, C);

	// M4 := A22 * (B21 - B11)
	MatrixSubs_Partial(m, B21, B11, ZERO, B, B, &temp1);

	temp3 = ZEROVEC;

	MatrixMult_Strassen(m, A22, ZERO, ZERO, A, &temp1, &temp3);

	MatrixSum_Partial(m, C11, ZERO, C11, C, &temp3, C);
	MatrixSum_Partial(m, C21, ZERO, C21, C, &temp3, C);

	// M5 := (A11 + A12) * B22
	MatrixSum_Partial(m, A11, A12, ZERO, A, A, &temp1);

	temp3 = ZEROVEC;

	MatrixMult_Strassen(m, ZERO, B22, ZERO, &temp1, B, &temp3);

	MatrixSubs_Partial(m, C11, ZERO, C11, C, &temp3, C);
	MatrixSum_Partial(m, C12, ZERO, C12, C, &temp3, C);

	// M6 := (A21 - A11) * (B11 + B12)
	MatrixSubs_Partial(m, A21, A11, ZERO, A, A, &temp1);
	MatrixSum_Partial(m, B11, B12, ZERO, B, B, &temp2);

	temp3 = ZEROVEC;

	MatrixMult_Strassen(m, ZERO, ZERO, ZERO, &temp1, &temp2, &temp3);

	MatrixSum_Partial(m, C22, ZERO, C22, C, &temp3, C);

	// M7 := (A12 - A22) * (B21 + B22)
	MatrixSubs_Partial(m, A12, A22, ZERO, A, A, &temp1);
	MatrixSum_Partial(m, B21, B22, ZERO, B, B, &temp2);

	temp3 = ZEROVEC;

	MatrixMult_Strassen(m, ZERO, ZERO, ZERO, &temp1, &temp2, &temp3);

	MatrixSum_Partial(m, C11, ZERO, C11, C, &temp3, C);

	if (!paddingsize) MatrixRemovePadding(n, C);
}

template<typename T>
void MatrixMult_Strassen(const int k, const int n, const Offset A_Offset, const Offset B_Offset, const Offset C_Offset, vector<vector<T>> * A, vector<vector<T>> * B, vector<vector<T>> * C)
{
	if (A_Offset.i > k || A_Offset.j > k || B_Offset.i > k || B_Offset.j > k)
	{
		return;
	}

	if (n <= 64)
	{
		MatrixMult_Partial(n, A_Offset, B_Offset, C_Offset, A, B, C);
		return;
	}

	int m, paddingsize(FindPaddingSize(n));

	if (paddingsize)
	{
		m = paddingsize / 2;
		MatrixPadding(paddingsize, A, B, C);
	}
	else
	{
		m = n / 2;
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

	vector<vector<T>> temp1(m, vector<T>(m, 0));
	vector<vector<T>> temp2(m, vector<T>(m, 0));
	vector<vector<T>> temp3(m, vector<T>(m, 0));
	vector<vector<T>> ZEROVEC(m, vector<T>(m, 0));

	// C11 = M1 +           M4 - M5      + M7
	// C12 =           M3      + M5
	// C21 =      M2      + M4
	// C22 = M1 - M2 + M3           + M6

	// M1 := (A11 + A22) * (B11 + B22)
	MatrixSum_Partial(m, A11, A22, ZERO, A, A, &temp1);
	MatrixSum_Partial(m, B11, B22, ZERO, B, B, &temp2);

	MatrixMult_Strassen(k, m, ZERO, ZERO, ZERO, &temp1, &temp2, &temp3);

	MatrixSum_Partial(m, C11, ZERO, C11, C, &temp3, C);
	MatrixSum_Partial(m, C22, ZERO, C22, C, &temp3, C);

	// M2 := (A21 + A22) * B11
	MatrixSum_Partial(m, A21, A22, ZERO, A, A, &temp1);

	temp3 = ZEROVEC;

	MatrixMult_Strassen(k, m, ZERO, B11, ZERO, &temp1, B, &temp3);

	MatrixSum_Partial(m, C21, ZERO, C21, C, &temp3, C);
	MatrixSubs_Partial(m, C22, ZERO, C22, C, &temp3, C);

	// M3 := A11 * (B12-B22)
	MatrixSubs_Partial(m, B12, B22, ZERO, B, B, &temp1);

	temp3 = ZEROVEC;

	MatrixMult_Strassen(k, m, A11, ZERO, ZERO, A, &temp1, &temp3);

	MatrixSum_Partial(m, C12, ZERO, C12, C, &temp3, C);
	MatrixSum_Partial(m, C22, ZERO, C22, C, &temp3, C);

	// M4 := A22 * (B21 - B11)
	MatrixSubs_Partial(m, B21, B11, ZERO, B, B, &temp1);

	temp3 = ZEROVEC;

	MatrixMult_Strassen(k, m, A22, ZERO, ZERO, A, &temp1, &temp3);

	MatrixSum_Partial(m, C11, ZERO, C11, C, &temp3, C);
	MatrixSum_Partial(m, C21, ZERO, C21, C, &temp3, C);

	// M5 := (A11 + A12) * B22
	MatrixSum_Partial(m, A11, A12, ZERO, A, A, &temp1);

	temp3 = ZEROVEC;

	MatrixMult_Strassen(k, m, ZERO, B22, ZERO, &temp1, B, &temp3);

	MatrixSubs_Partial(m, C11, ZERO, C11, C, &temp3, C);
	MatrixSum_Partial(m, C12, ZERO, C12, C, &temp3, C);

	// M6 := (A21 - A11) * (B11 + B12)
	MatrixSubs_Partial(m, A21, A11, ZERO, A, A, &temp1);
	MatrixSum_Partial(m, B11, B12, ZERO, B, B, &temp2);

	temp3 = ZEROVEC;

	MatrixMult_Strassen(k, m, ZERO, ZERO, ZERO, &temp1, &temp2, &temp3);

	MatrixSum_Partial(m, C22, ZERO, C22, C, &temp3, C);

	// M7 := (A12 - A22) * (B21 + B22)
	MatrixSubs_Partial(m, A12, A22, ZERO, A, A, &temp1);
	MatrixSum_Partial(m, B21, B22, ZERO, B, B, &temp2);

	temp3 = ZEROVEC;

	MatrixMult_Strassen(k, m, ZERO, ZERO, ZERO, &temp1, &temp2, &temp3);

	MatrixSum_Partial(m, C11, ZERO, C11, C, &temp3, C);

	if (!paddingsize) MatrixRemovePadding(n, C);
}

template<typename T>
void MatrixMult_Strassen_MultiThread(const int k, const int n, const Offset A_Offset, const Offset B_Offset, const Offset C_Offset, vector<vector<T>> * A, vector<vector<T>> * B, vector<vector<T>> * C)
{
	if (A_Offset.i > k || A_Offset.j > k || B_Offset.i > k || B_Offset.j > k)
	{
		return;
	}

	if (n <= 64)
	{
		MatrixMult_Partial(n, A_Offset, B_Offset, C_Offset, A, B, C);
		return;
	}

	int m, paddingsize(FindPaddingSize(n));

	if (paddingsize)
	{
		m = paddingsize / 2;
		MatrixPadding(paddingsize, A, B, C);
	}
	else
	{
		m = n / 2;
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

	vector<vector<T>> temp1(m, vector<T>(m, 0));
	vector<vector<T>> temp2(m, vector<T>(m, 0));
	vector<vector<T>> temp3(m, vector<T>(m, 0));
	vector<vector<T>> ZEROVEC(m, vector<T>(m, 0));

	// C11 = M1 +           M4 - M5      + M7
	// C12 =           M3      + M5
	// C21 =      M2      + M4
	// C22 = M1 - M2 + M3           + M6

	// M1 := (A11 + A22) * (B11 + B22)
	//thread t0;
	thread t0(MatrixSum_Partial<T>,m, A11, A22, ZERO, A, A, &temp1);
	thread t1(MatrixSum_Partial<T>,m, B11, B22, ZERO, B, B, &temp2);
	t0.join();
	t1.join();


	MatrixMult_Strassen(k, m, ZERO, ZERO, ZERO, &temp1, &temp2, &temp3);
	
	thread t2(MatrixSum_Partial<T>, m, C11, ZERO, C11, C, &temp3, C);
	thread t3(MatrixSum_Partial<T>, m, C22, ZERO, C22, C, &temp3, C);
	t2.join();
	t3.join();

	// M2 := (A21 + A22) * B11
	thread t4(MatrixSum_Partial<T>, m, A21, A22, ZERO, A, A, &temp1);
	t4.join();

	temp3 = ZEROVEC;

	MatrixMult_Strassen(k, m, ZERO, B11, ZERO, &temp1, B, &temp3);

	thread t5(MatrixSum_Partial<T>, m, C21, ZERO, C21, C, &temp3, C);
	thread t6(MatrixSubs_Partial<T>, m, C22, ZERO, C22, C, &temp3, C);
	t5.join();
	t6.join();

	// M3 := A11 * (B12-B22)
	thread t7(MatrixSubs_Partial<T>, m, B12, B22, ZERO, B, B, &temp1);

	t7.join();

	temp3 = ZEROVEC;

	MatrixMult_Strassen(k, m, A11, ZERO, ZERO, A, &temp1, &temp3);


	thread t8(MatrixSum_Partial<T>, m, C12, ZERO, C12, C, &temp3, C);
	thread t9(MatrixSum_Partial<T>, m, C22, ZERO, C22, C, &temp3, C);
	t8.join();
	t9.join();

	// M4 := A22 * (B21 - B11)
	thread t10(MatrixSubs_Partial<T>, m, B21, B11, ZERO, B, B, &temp1);

	t10.join();

	temp3 = ZEROVEC;

	MatrixMult_Strassen(k, m, A22, ZERO, ZERO, A, &temp1, &temp3);

	thread t11(MatrixSum_Partial<T>, m, C11, ZERO, C11, C, &temp3, C);
	thread t12(MatrixSum_Partial<T>, m, C21, ZERO, C21, C, &temp3, C);
	t11.join();
	t12.join();

	// M5 := (A11 + A12) * B22
	thread t13(MatrixSum_Partial<T>, m, A11, A12, ZERO, A, A, &temp1);

	t13.join();

	temp3 = ZEROVEC;

	MatrixMult_Strassen(k, m, ZERO, B22, ZERO, &temp1, B, &temp3);

	thread t14(MatrixSubs_Partial<T>, m, C11, ZERO, C11, C, &temp3, C);
	thread t15(MatrixSum_Partial<T>, m, C12, ZERO, C12, C, &temp3, C);
	t14.join();
	t15.join();
	// M6 := (A21 - A11) * (B11 + B12)

	thread t16(MatrixSubs_Partial<T>, m, A21, A11, ZERO, A, A, &temp1);
	thread t17(MatrixSum_Partial<T>, m, B11, B12, ZERO, B, B, &temp2);
	t16.join();
	t17.join();

	//temp3 = ZEROVEC;

	MatrixMult_Strassen(k, m, ZERO, ZERO, ZERO, &temp1, &temp2, &temp3);

	thread t18(MatrixSum_Partial<T>, m, C22, ZERO, C22, C, &temp3, C);
	t18.join();
	// M7 := (A12 - A22) * (B21 + B22)

	thread t19(MatrixSubs_Partial<T>, m, A12, A22, ZERO, A, A, &temp1);
	thread t20(MatrixSum_Partial<T>, m, B21, B22, ZERO, B, B, &temp2);
	t19.join();
	t20.join();

	temp3 = ZEROVEC;

	MatrixMult_Strassen(k, m, ZERO, ZERO, ZERO, &temp1, &temp2, &temp3);

	MatrixSum_Partial(m, C11, ZERO, C11, C, &temp3, C);

	if (!paddingsize) MatrixRemovePadding(n, C);
}

template<typename T>
void MatrixMult_StrassenThresholdTest(const int n, const int k, const Offset A_Offset, const Offset B_Offset, const Offset C_Offset, vector<vector<T>> * A, vector<vector<T>> * B, vector<vector<T>> * C)
{
	if (n <= k)
	{
		MatrixMult_Partial(n, A_Offset, B_Offset, C_Offset, A, B, C);
		return;
	}

	int m, paddingsize(FindPaddingSize(n));

	if (paddingsize)
	{
		m = paddingsize / 2;
		MatrixPadding(paddingsize, A, B, C);
	}
	else
	{
		m = n / 2;
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

	vector<vector<T>> temp1(m, vector<T>(m, 0));
	vector<vector<T>> temp2(m, vector<T>(m, 0));
	vector<vector<T>> temp3(m, vector<T>(m, 0));
	vector<vector<T>> ZEROVEC(m, vector<T>(m, 0));

	// C11 = M1 +           M4 - M5      + M7
	// C12 =           M3      + M5
	// C21 =      M2      + M4
	// C22 = M1 - M2 + M3           + M6

	// M1 := (A11 + A22) * (B11 + B22)
	MatrixSum_Partial(m, A11, A22, ZERO, A, A, &temp1);
	MatrixSum_Partial(m, B11, B22, ZERO, B, B, &temp2);

	MatrixMult_Strassen(m, ZERO, ZERO, ZERO, &temp1, &temp2, &temp3);

	MatrixSum_Partial(m, C11, ZERO, C11, C, &temp3, C);
	MatrixSum_Partial(m, C22, ZERO, C22, C, &temp3, C);

	// M2 := (A21 + A22) * B11
	MatrixSum_Partial(m, A21, A22, ZERO, A, A, &temp1);

	temp3 = ZEROVEC;

	MatrixMult_Strassen(m, ZERO, B11, ZERO, &temp1, B, &temp3);

	MatrixSum_Partial(m, C21, ZERO, C21, C, &temp3, C);
	MatrixSubs_Partial(m, C22, ZERO, C22, C, &temp3, C);

	// M3 := A11 * (B12-B22)
	MatrixSubs_Partial(m, B12, B22, ZERO, B, B, &temp1);

	temp3 = ZEROVEC;

	MatrixMult_Strassen(m, A11, ZERO, ZERO, A, &temp1, &temp3);

	MatrixSum_Partial(m, C12, ZERO, C12, C, &temp3, C);
	MatrixSum_Partial(m, C22, ZERO, C22, C, &temp3, C);

	// M4 := A22 * (B21 - B11)
	MatrixSubs_Partial(m, B21, B11, ZERO, B, B, &temp1);

	temp3 = ZEROVEC;

	MatrixMult_Strassen(m, A22, ZERO, ZERO, A, &temp1, &temp3);

	MatrixSum_Partial(m, C11, ZERO, C11, C, &temp3, C);
	MatrixSum_Partial(m, C21, ZERO, C21, C, &temp3, C);

	// M5 := (A11 + A12) * B22
	MatrixSum_Partial(m, A11, A12, ZERO, A, A, &temp1);

	temp3 = ZEROVEC;

	MatrixMult_Strassen(m, ZERO, B22, ZERO, &temp1, B, &temp3);

	MatrixSubs_Partial(m, C11, ZERO, C11, C, &temp3, C);
	MatrixSum_Partial(m, C12, ZERO, C12, C, &temp3, C);

	// M6 := (A21 - A11) * (B11 + B12)
	MatrixSubs_Partial(m, A21, A11, ZERO, A, A, &temp1);
	MatrixSum_Partial(m, B11, B12, ZERO, B, B, &temp2);

	temp3 = ZEROVEC;

	MatrixMult_Strassen(m, ZERO, ZERO, ZERO, &temp1, &temp2, &temp3);

	MatrixSum_Partial(m, C22, ZERO, C22, C, &temp3, C);

	// M7 := (A12 - A22) * (B21 + B22)
	MatrixSubs_Partial(m, A12, A22, ZERO, A, A, &temp1);
	MatrixSum_Partial(m, B21, B22, ZERO, B, B, &temp2);

	temp3 = ZEROVEC;

	MatrixMult_Strassen(m, ZERO, ZERO, ZERO, &temp1, &temp2, &temp3);

	MatrixSum_Partial(m, C11, ZERO, C11, C, &temp3, C);

	if (!paddingsize) MatrixRemovePadding(n, C);
}

template<typename T>
void MatrixMult_Strassen(const int Size, vector<vector<T>> * A, vector<vector<T>> * B, vector<vector<T>> * C)
{
	if (Size <= 32)
	{
		MatrixMult_MultiThread(Size, A, B, C);
	}
	else
	{
		PadData paddata = FindOptimalPaddingSize(Size);
		Offset ZERO = { 0, 0 };

		MatrixPadding(paddata.m_Padsize, A, B, C);
		MatrixMult_StrassenInnerLoop(paddata, Size, ZERO, ZERO, ZERO, A, B, C);
		MatrixRemovePadding(Size, C);
	}
}

template<typename T>
void MatrixMult_StrassenInnerLoop(const PadData &Paddata, const int &Size, const Offset A_Offset, const Offset B_Offset, const Offset C_Offset, vector<vector<T>> * A, vector<vector<T>> * B, vector<vector<T>> * C)
{
	if (Size <= Paddata.m_Threshold)
	{
		MatrixMult_Partial(Size, A_Offset, B_Offset, C_Offset, A, B, C);
		return;
	}

	int m = Size / 2;

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

	vector<vector<T>> temp1(m, vector<T>(m, 0));
	vector<vector<T>> temp2(m, vector<T>(m, 0));
	vector<vector<T>> temp3(m, vector<T>(m, 0));
	vector<vector<T>> ZEROVEC(m, vector<T>(m, 0));

	// C11 = M1 +           M4 - M5      + M7
	// C12 =           M3      + M5
	// C21 =      M2      + M4
	// C22 = M1 - M2 + M3           + M6

	// M1 := (A11 + A22) * (B11 + B22)
	MatrixSum_Partial(m, A11, A22, ZERO, A, A, &temp1);
	MatrixSum_Partial(m, B11, B22, ZERO, B, B, &temp2);

	MatrixMult_StrassenInnerLoop(Paddata, m, ZERO, ZERO, ZERO, &temp1, &temp2, &temp3);
	MatrixSum_Partial(m, C11, ZERO, C11, C, &temp3, C);
	MatrixSum_Partial(m, C22, ZERO, C22, C, &temp3, C);

	// M2 := (A21 + A22) * B11
	MatrixSum_Partial(m, A21, A22, ZERO, A, A, &temp1);

	temp3 = ZEROVEC;

	MatrixMult_StrassenInnerLoop(Paddata, m, ZERO, B11, ZERO, &temp1, B, &temp3);

	MatrixSum_Partial(m, C21, ZERO, C21, C, &temp3, C);
	MatrixSubs_Partial(m, C22, ZERO, C22, C, &temp3, C);

	// M3 := A11 * (B12-B22)
	MatrixSubs_Partial(m, B12, B22, ZERO, B, B, &temp1);

	temp3 = ZEROVEC;

	MatrixMult_StrassenInnerLoop(Paddata, m, A11, ZERO, ZERO, A, &temp1, &temp3);

	MatrixSum_Partial(m, C12, ZERO, C12, C, &temp3, C);
	MatrixSum_Partial(m, C22, ZERO, C22, C, &temp3, C);

	// M4 := A22 * (B21 - B11)
	MatrixSubs_Partial(m, B21, B11, ZERO, B, B, &temp1);

	temp3 = ZEROVEC;

	MatrixMult_StrassenInnerLoop(Paddata, m, A22, ZERO, ZERO, A, &temp1, &temp3);

	MatrixSum_Partial(m, C11, ZERO, C11, C, &temp3, C);
	MatrixSum_Partial(m, C21, ZERO, C21, C, &temp3, C);

	// M5 := (A11 + A12) * B22
	MatrixSum_Partial(m, A11, A12, ZERO, A, A, &temp1);

	temp3 = ZEROVEC;

	MatrixMult_StrassenInnerLoop(Paddata, m, ZERO, B22, ZERO, &temp1, B, &temp3);

	MatrixSubs_Partial(m, C11, ZERO, C11, C, &temp3, C);
	MatrixSum_Partial(m, C12, ZERO, C12, C, &temp3, C);

	// M6 := (A21 - A11) * (B11 + B12)
	MatrixSubs_Partial(m, A21, A11, ZERO, A, A, &temp1);
	MatrixSum_Partial(m, B11, B12, ZERO, B, B, &temp2);

	temp3 = ZEROVEC;

	MatrixMult_StrassenInnerLoop(Paddata, m, ZERO, ZERO, ZERO, &temp1, &temp2, &temp3);

	MatrixSum_Partial(m, C22, ZERO, C22, C, &temp3, C);

	// M7 := (A12 - A22) * (B21 + B22)
	MatrixSubs_Partial(m, A12, A22, ZERO, A, A, &temp1);
	MatrixSum_Partial(m, B21, B22, ZERO, B, B, &temp2);

	temp3 = ZEROVEC;

	MatrixMult_StrassenInnerLoop(Paddata, m, ZERO, ZERO, ZERO, &temp1, &temp2, &temp3);

	MatrixSum_Partial(m, C11, ZERO, C11, C, &temp3, C);
}

