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
void MatrixTrans(const int Size, vector<vector<T>> &A, vector<vector<T>> &B)
{
	int i, j
	for (i = 0; i<n; i++)
	{
		for (j = 0; j<n; j++)
		{
			B[j*Size + i] = A[i*Size + j];
		}
	}
}

template<typename T>
void CreateRandomMatrix(const int Size, vector<vector<T>> &A)
{
	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
		{
			A[i][j] = (T)(rand() * 10 / 32767);
		}
	}
}

template<typename T>
void CreateEyeMatrix(const int Size, vector<vector<T>> &A)
{
	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
		{
			if (i == j)
				A[i][j] = (T)1.0;
			else
				A[i][j] = (T)0.0;
		}
	}
}

template<typename T>
void CreateZeroMatrix(const int Size, vector<vector<T>> &A)
{
	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
		{
			A[i][j] = 0;
		}
	}
}

template<typename T>
void MatrixPrint(const int Size, const vector<vector<T>> &A)
{
	int i, j;
	cout << "[";
	for (i = 0; i < Size; i++)
	{
		for (j = 0; j < Size; j++)
		{
			cout << A[i][j];
			if (j != Size - 1) { cout << ", "; }
		}
		if (i != Size - 1) { cout << ";\n "; }
	}
	cout << "]\n\n";
}

template<typename T>
void MatrixCheck(const int Size, const vector<vector<T>> &A, const vector<vector<T>> &B)
{
	int i, j;

	for (i = 0; i < Size; i++)
	{
		for (j = 0; j < Size; j++)
		{
			if (A[i][j] != B[i][j])
			{
				cout << "Matrix Size is " << Size << ", not same\n\n";
				return;
			}
		}
	}
	cout << "Matrix Size is " << Size << ", same\n\n";
}

template<typename T>
void MatrixSum_Standard(const int Size, const vector<vector<T>> &A, const vector<vector<T>> &B, vector<vector<T>> &C)
{
	int i, j;

	for (i = 0; i < Size; i++)
	{
		for (j = 0; j < Size; j++)
		{
			C[i][j] = A[i][j] + B[i][j];
		}
	}
}



template<typename T>
void MatrixSum_OpenMP(const int Size, const vector<vector<T>> &A, const vector<vector<T>> &B, vector<vector<T>> &C)
{
	#pragma omp parallel
	{
		int i, j;
		#pragma omp for
		for (i = 0; i < Size; i++)
		{
			for (j = 0; j < Size; j++)
			{
				C[i][j] = A[i][j] + B[i][j];
			}
		}
	}
}

template<typename T>
void MatrixSum_MultiThread(const int Size, const vector<vector<T>> &A, const vector<vector<T>> &B, vector<vector<T>> &C)
{
	const int THREADS_NUM = 16;
	thread t[THREADS_NUM];

	for (int i = 0; i < THREADS_NUM; i++)
	{
		t[i] = thread([&Size, &THREADS_NUM, &i, &A, &B, &C]
		{
			const int n_elements = (Size * Size);
			const int n_operations = n_elements / THREADS_NUM;
			const int rest_operations = n_elements % THREADS_NUM;

			int start_idx, end_idx;

			if (i == 0)
			{
				start_idx = n_operations * i;
				end_idx = (n_operations * (i + 1)) + rest_operations;
			}
			else
			{
				start_idx = n_operations * i + rest_operations;
				end_idx = (n_operations * (i + 1)) + rest_operations;
			}

			for (int idx = start_idx; idx < end_idx; idx++)
			{
				const int row = idx % Size;
				const int col = idx / Size;
	
				C[row][col] = A[row][col] + B[row][col];
			}
		}
		);
	}

	for (int i = 0; i < THREADS_NUM; i++)
	{
		t[i].join();
	}
}


template<typename T>
void MatrixPartialSum_OpenMP(const int Size, const Offset A_Offset, const Offset B_Offset, const Offset C_Offset, const vector<vector<T>> &A, const vector<vector<T>> &B, vector<vector<T>> &C)
{
	#pragma omp parallel
	{
		int i, j;
		#pragma omp for
		for (i = 0; i < Size; i++)
		{
			for (j = 0; j < Size; j++)
			{
				C[i + C_Offset.i][j + C_Offset.j] = A[i + A_Offset.i][j + A_Offset.j] + B[i + B_Offset.i][j + B_Offset.j];
			}
		}
	}
}

template<typename T>
void MatrixPartialSum_Thread(const int Size, const int thread_num, const int thread_idx, const Offset A_Offset, const Offset B_Offset, const Offset C_Offset, const vector<vector<T>> &A, const vector<vector<T>> &B, vector<vector<T>> &C)
{
	const int n_elements = (Size * Size);
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
		const int row = op % Size;
		const int col = op / Size;

		C[C_Offset.i + row][C_Offset.j + col] = A[A_Offset.i + row][A_Offset.j + col] + B[B_Offset.i + row][B_Offset.j + col];
	}
}

template<typename T>
void MatrixPartialSum_MultiThread(const int Size, const Offset A_Offset, const Offset B_Offset, const Offset C_Offset, const vector<vector<T>> &A, const vector<vector<T>> &B, vector<vector<T>> &C)
{
	const int THREADS_NUM = 16;
	thread t[THREADS_NUM];

	for (int i = 0; i < THREADS_NUM; i++)
	{
		t[i] = thread(MatrixPartialSum_Thread<T>, ref(Size), ref(THREADS_NUM), ref(i), ref(A_Offset), ref(B_Offset), ref(C_Offset), ref(A), ref(B), ref(C));
	}

	for (int i = 0; i < THREADS_NUM; i++)
	{
		t[i].join();
	}
}

template<typename T>
void MatrixSubs_OpenMP(const int Size, const vector<vector<T>> &A, const vector<vector<T>> &B, vector<vector<T>> &C)
{
	#pragma omp parallel
	{
		int i, j;
		#pragma omp for
		for (i = 0; i < Size; i++)
		{
			for (j = 0; j < Size; j++)
			{
				C[i][j] = A[i][j] - B[i][j];
			}
		}
	}
}

template<typename T>
void MatrixPartialSubs_OpenMP(const int Size, const Offset A_Offset, const Offset B_Offset, const Offset C_Offset, const vector<vector<T>> &A, const vector<vector<T>> &B, vector<vector<T>> &C)
{

	#pragma omp parallel
	{
		int i, j;
		#pragma omp for
		for (i = 0; i < Size; i++)
		{
			for (j = 0; j < Size; j++)
			{
				C[i + C_Offset.i][j + C_Offset.j] = A[i + A_Offset.i][j + A_Offset.j] - B[i + B_Offset.i][j + B_Offset.j];
			}
		}
	}
}

template<typename T>
void MatrixMult_Standard(const int Size, const vector<vector<T>> &A, const vector<vector<T>> &B, vector<vector<T>> &C)
{
	int i, j, k;
	for (i = 0; i < Size; i++)
	{
		for (j = 0; j < Size; j++)
		{
			for (k = 0; k < Size; k++)
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
void MatrixPartialMult_Standard(const int Size, const Offset A_Offset, const Offset B_Offset, const Offset C_Offset, const vector<vector<T>> &A, const vector<vector<T>> &B, vector<vector<T>> &C)
{
	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
		{
			for (int k = 0; k < Size; k++)
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
void MatrixMult_OpenMP(const int Size, const vector<vector<T>> &A, const vector<vector<T>> &B, vector<vector<T>> &C)
{
	#pragma omp parallel
	{
		int i, j, k;
		#pragma omp for
		for (i = 0; i < Size; i++)
		{
			for (j = 0; j < Size; j++)
			{
				for (k = 0; k < Size; k++)
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
}

template<typename T>
void MatrixPartialMult_OpenMP(const int Size, const Offset A_Offset, const Offset B_Offset, const Offset C_Offset, const vector<vector<T>> &A, const vector<vector<T>> &B, vector<vector<T>> &C)
{
#pragma omp parallel
	{
#pragma omp for
		for (int i = 0; i < Size; i++)
		{
			for (int j = 0; j < Size; j++)
			{
				for (int k = 0; k < Size; k++)
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
}

template<typename T>
void MatrixMult_Thread(const int Size, const int thread_num, const int thread_idx, const vector<vector<T>> &A, const vector<vector<T>> &B, vector<vector<T>> &C)
{
	const int n_elements = (Size * Size);
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
		const int row = op % Size;
		const int col = op / Size;
		T r = 0;
		for (int i = 0; i < Size; ++i) {
			const T e1 = A[row][i];
			const T e2 = B[i][col];
			r += e1 * e2;
		}

		C[row][col] = r;
	}
}

template<typename T>
void MatrixMult_MultiThread(const int Size, const vector<vector<T>> &A, const vector<vector<T>> &B, vector<vector<T>> &C)
{
	const int THREADS_NUM = 16;
	thread t[THREADS_NUM];

	for (int i = 0; i < THREADS_NUM; i++)
	{
		t[i] = thread([&Size, &THREADS_NUM, &i, &A, &B, &C]
			{ 
				const int n_elements = (Size * Size);
				const int n_operations = n_elements / THREADS_NUM;
				const int rest_operations = n_elements % THREADS_NUM;

				int start_idx, end_idx;

				if (i == 0) 
				{
					start_idx = n_operations * i;
					end_idx = (n_operations * (i + 1)) + rest_operations;
				}
				else 
				{
					start_idx = n_operations * i + rest_operations;
					end_idx = (n_operations * (i + 1)) + rest_operations;
				}

				for (int idx = start_idx; idx < end_idx; idx++)
				{
					const int row = idx % Size;
					const int col = idx / Size;
					T sum = 0;
					for (int j = 0; j < Size; j++) 
					{
						const T e1 = A[row][j];
						const T e2 = B[j][col];
						sum += e1 * e2;
					}

					C[row][col] = sum;
				}
			}
		);
	}

	for (int i = 0; i < THREADS_NUM; i++)
	{
		t[i].join();
	}
}

template<typename T>
void MatrixPartialMult_MultiThread(const int Size, const Offset A_Offset, const Offset B_Offset, const Offset C_Offset, const vector<vector<T>> &A, const vector<vector<T>> &B, vector<vector<T>> &C)
{
	const int THREADS_NUM = 16;
	thread t[THREADS_NUM];

	for (int i = 0; i < THREADS_NUM; i++)
	{
		t[i] = thread(MatrixPartialMult_Thread<T>, ref(Size), ref(THREADS_NUM), ref(i), ref(A_Offset), ref(B_Offset), ref(C_Offset), ref(A), ref(B), ref(C));
	}

	for (int i = 0; i < THREADS_NUM; i++)
	{
		t[i].join();
	}
}

template<typename T>
void MatrixPartialMult_Thread(const int Size, const int thread_num, const int thread_idx, const Offset A_Offset, const Offset B_Offset, const Offset C_Offset, const vector<vector<T>> &A, const vector<vector<T>> &B, vector<vector<T>> &C)
{
	const int n_elements = (Size * Size);
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

	int op, i;

	for (op = start_op; op < end_op; ++op)
	{
		const int row = op % Size;
		const int col = op / Size;
		T r = 0;
		for (i = 0; i < Size; ++i) {
			const T e1 = A[A_Offset.i + row][A_Offset.j + i];
			const T e2 = B[B_Offset.i + i][B_Offset.j + col];
			r += e1 * e2;
		}

		C[C_Offset.i + row][C_Offset.j + col] = r;
	}
}

int FindNaiveFaddingSize(const int n);

PadData FindOptimalPaddingSize(const int n);

template<typename T>
void MatrixPadding(const int Size, vector<vector<T>> &A, vector<vector<T>> &B, vector<vector<T>> &C)
{
	int i;

	A.resize(Size);
	B.resize(Size);
	C.resize(Size);

	#pragma omp parallel
	{
		#pragma omp for
		for (i = 0; i < Size; i++)
		{
			A[i].resize(Size);
			B[i].resize(Size);
			C[i].resize(Size);
		}
	}
}

template<typename T>
void MatrixRemovePadding(const int Size, vector<vector<T>> &A)
{
	int i;

	A.resize(Size);

	#pragma omp parallel
	{
		#pragma omp for
		for (i = 0; i < Size; i++)
		{
			A[i].resize(Size);
		}
	}
}

template<typename T>
void MatrixMult_Strassen(const int Size, vector<vector<T>> &A, vector<vector<T>> &B, vector<vector<T>> &C)
{
	if (Size <= 32)
	{
		//MatrixMult_Standard(Size, A, B, C);
		MatrixMult_OpenMP(Size, A, B, C);
	}
	else
	{
		PadData paddata = FindOptimalPaddingSize(Size);
		Offset ZERO = { 0, 0 };

		MatrixPadding(paddata.m_Padsize, A, B, C);
		MatrixMult_StrassenInnerLoop(paddata, paddata.m_Padsize, ZERO, ZERO, ZERO, A, B, C);
		MatrixRemovePadding(Size, C);
	}
}

template<typename T>
void MatrixMult_StrassenInnerLoop(const PadData Paddata, const int Size, const Offset A_Offset, const Offset B_Offset, const Offset C_Offset, vector<vector<T>> &A, vector<vector<T>> &B, vector<vector<T>> &C)
{
	if (Size <= Paddata.m_Threshold)
	{
		//MatrixPartialMult_Standard(Size, A_Offset, B_Offset, C_Offset, A, B, C);
		MatrixPartialMult_OpenMP(Size, A_Offset, B_Offset, C_Offset, A, B, C);
		//MatrixPartialMult_MultiThread(Size, A_Offset, B_Offset, C_Offset, A, B, C);
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
	vector<vector<T>> ZEROMAT(m, vector<T>(m, 0));

	// C11 = M1 +           M4 - M5      + M7
	// C12 =           M3      + M5
	// C21 =      M2      + M4
	// C22 = M1 - M2 + M3           + M6

	// M1 := (A11 + A22) * (B11 + B22)
	MatrixPartialSum_OpenMP(m, A11, A22, ZERO, A, A, temp1);
	MatrixPartialSum_OpenMP(m, B11, B22, ZERO, B, B, temp2);

	MatrixMult_StrassenInnerLoop(Paddata, m, ZERO, ZERO, ZERO, temp1, temp2, temp3);
	MatrixPartialSum_OpenMP(m, C11, ZERO, C11, C, temp3, C);
	MatrixPartialSum_OpenMP(m, C22, ZERO, C22, C, temp3, C);

	// M2 := (A21 + A22) * B11
	MatrixPartialSum_OpenMP(m, A21, A22, ZERO, A, A, temp1);

	
	temp3 = ZEROMAT;
	MatrixMult_StrassenInnerLoop(Paddata, m, ZERO, B11, ZERO, temp1, B, temp3);

	MatrixPartialSum_OpenMP(m, C21, ZERO, C21, C, temp3, C);
	MatrixPartialSubs_OpenMP(m, C22, ZERO, C22, C, temp3, C);

	// M3 := A11 * (B12-B22)
	MatrixPartialSubs_OpenMP(m, B12, B22, ZERO, B, B, temp1);

	temp3 = ZEROMAT;
	MatrixMult_StrassenInnerLoop(Paddata, m, A11, ZERO, ZERO, A, temp1, temp3);

	MatrixPartialSum_OpenMP(m, C12, ZERO, C12, C, temp3, C);
	MatrixPartialSum_OpenMP(m, C22, ZERO, C22, C, temp3, C);

	// M4 := A22 * (B21 - B11)
	MatrixPartialSubs_OpenMP(m, B21, B11, ZERO, B, B, temp1);

	temp3 = ZEROMAT;
	MatrixMult_StrassenInnerLoop(Paddata, m, A22, ZERO, ZERO, A, temp1, temp3);

	MatrixPartialSum_OpenMP(m, C11, ZERO, C11, C, temp3, C);
	MatrixPartialSum_OpenMP(m, C21, ZERO, C21, C, temp3, C);

	// M5 := (A11 + A12) * B22
	MatrixPartialSum_OpenMP(m, A11, A12, ZERO, A, A, temp1);

	temp3 = ZEROMAT;
	MatrixMult_StrassenInnerLoop(Paddata, m, ZERO, B22, ZERO, temp1, B, temp3);

	MatrixPartialSubs_OpenMP(m, C11, ZERO, C11, C, temp3, C);
	MatrixPartialSum_OpenMP(m, C12, ZERO, C12, C, temp3, C);

	// M6 := (A21 - A11) * (B11 + B12)
	MatrixPartialSubs_OpenMP(m, A21, A11, ZERO, A, A, temp1);
	MatrixPartialSum_OpenMP(m, B11, B12, ZERO, B, B, temp2);

	temp3 = ZEROMAT;
	MatrixMult_StrassenInnerLoop(Paddata, m, ZERO, ZERO, ZERO, temp1, temp2, temp3);

	MatrixPartialSum_OpenMP(m, C22, ZERO, C22, C, temp3, C);

	// M7 := (A12 - A22) * (B21 + B22)
	MatrixPartialSubs_OpenMP(m, A12, A22, ZERO, A, A, temp1);
	MatrixPartialSum_OpenMP(m, B21, B22, ZERO, B, B, temp2);

	temp3 = ZEROMAT;
	MatrixMult_StrassenInnerLoop(Paddata, m, ZERO, ZERO, ZERO, temp1, temp2, temp3);

	MatrixPartialSum_OpenMP(m, C11, ZERO, C11, C, temp3, C);
}

