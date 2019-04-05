#include <iostream>
#include <time.h>

using std::cout;

template<typename T, size_t N>
void MatrixMult(T A[N][N], T B[N][N]);
template<typename T, size_t N>
void MatrixDisp(T A[N][N]);

void main()
{
	const size_t N = 2;

	int A[N][N]{
		{1,0},
		{0,1},
	};

	int B[N][N]{
		{4,3},
		{4,2},
	};

	clock_t start = clock();

	MatrixMult<int, 2>(A, B);

	cout << "run time = " << clock() - start << "millisec.\n";
	
}

template<typename T, size_t N>
void MatrixMult(T A[N][N], T B[N][N])
{
	static_assert(N > 1, "Matrix dimension must be greater than 1");

	T C[N][N];

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			T dot_product = 0;

			for (int k = 0; k < N; k++)
			{
				dot_product += A[i][k] * B[k][j];
			}

			C[i][j] = dot_product;
			cout << C[i][j] << " ";
		}

		cout << "\n";
	}
}

template<typename T, size_t N>
void MatrixDisp(T A[N][N])
{

}