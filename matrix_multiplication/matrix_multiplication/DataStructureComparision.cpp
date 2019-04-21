#include <vector>
#include "TimeCheck.h"

TimeCheck TimeTest_MyTime;

using std::vector;

void test_DataStructure(const int N);

//void main()
//{
//	int i;
//	for (i = 500; i < 510; i++)
//	{
//		Test(i);
//	}
//}

void test_DataStructure(const int N)
{
	cout << "\n" << N << "\n";

	//int StaticSingleArray1[N*N] = { 0, };
	//int StaticSingleArray2[N*N] = { 0, };
	//int StaticSingleArray3[N*N] = { 0, };

	//int StaticDoubleArray1[N][N] = { 0 };
	//int StaticDoubleArray2[N][N] = { 0 };
	//int StaticDoubleArray3[N][N] = { 0, };

	int *DynamicSingleArray1 = new int [N*N];
	int *DynamicSingleArray2 = new int [N*N];
	int *DynamicSingleArray3 = new int [N*N];
	
	int **DynamicDoubleArray1 = new int *[N];
	int **DynamicDoubleArray2 = new int *[N];
	int **DynamicDoubleArray3 = new int *[N];

	vector<vector<int>> Vector1(N, vector<int>(N));
	vector<vector<int>> Vector2(N, vector<int>(N));
	vector<vector<int>> Vector3(N, vector<int>(N));


	int i, j, k;

	for (i = 0; i < N; i++)
	{
		DynamicDoubleArray1[i] = new int[N];
		DynamicDoubleArray2[i] = new int[N];
		DynamicDoubleArray3[i] = new int[N];
	}

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			DynamicSingleArray1[i*N + j] = 1;
			DynamicSingleArray2[i*N + j] = 1;
			DynamicSingleArray3[i*N + j] = 1;

			DynamicDoubleArray1[i][j] = 1;
			DynamicDoubleArray2[i][j] = 1;
			DynamicDoubleArray3[i][j] = 1;
			Vector1[i][j] = 1;
			Vector2[i][j] = 1;
			Vector3[i][j] = 1;
		}
	}
	//TimeTest_MyTime.Start();
	//for (i = 0; i < N; i++)
	//{
	//	for (j = 0; j < N; j++)
	//	{
	//		StaticSingleArray3[i*N + j] = StaticSingleArray1[i*N + j] + StaticSingleArray2[i*N + j];
	//	}
	//}
	//TimeTest_MyTime.End("Static Single Array : Sum");

	TimeTest_MyTime.Start();
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			DynamicSingleArray3[i*N + j] = DynamicSingleArray1[i*N + j] + DynamicSingleArray2[i*N + j];
		}
	}
	TimeTest_MyTime.End("Dynamic Single Array : Sum");

	//TimeTest_MyTime.Start();
	//for (i = 0; i < N; i++)
	//{
	//	for (j = 0; j < N; j++)
	//	{
	//		StaticDoubleArray3[i][j] = StaticDoubleArray1[i][j] + StaticDoubleArray2[i][j];
	//	}
	//}
	//TimeTest_MyTime.End("Static Double Array : Sum");

	TimeTest_MyTime.Start();
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			DynamicDoubleArray3[i][j] = DynamicDoubleArray1[i][j] + DynamicDoubleArray2[i][j];
		}
	}
	TimeTest_MyTime.End("Dynamic Double Array : Sum");

	TimeTest_MyTime.Start();
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			Vector3[i][j] = Vector2[i][j] + Vector1[i][j];
		}
	}
	TimeTest_MyTime.End("Vector : Sum");

	cout << "\n";

	//TimeTest_MyTime.Start();
	//for (i = 0; i < N; i++)
	//{
	//	for (j = 0; j < N; j++)
	//	{
	//		for (k = 0; k < N; k++)
	//		{
	//			if(k)
	//				StaticSingleArray3[i*N + j] += StaticSingleArray1[i*N + k] + StaticSingleArray2[k*N + j];
	//			else
	//				StaticSingleArray3[i*N + j] = StaticSingleArray1[i*N + k] + StaticSingleArray2[k*N + j];
	//		}
	//		
	//	}
	//}
	//TimeTest_MyTime.End("Static Single Array : Multiplication");

	TimeTest_MyTime.Start();
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			for (k = 0; k < N; k++)
			{
				if (k)
					DynamicSingleArray3[i*N + j] += DynamicSingleArray1[i*N + k] + DynamicSingleArray2[k*N + j];
				else
					DynamicSingleArray3[i*N + j] = DynamicSingleArray1[i*N + k] + DynamicSingleArray2[k*N + j];
			}

		}
	}
	TimeTest_MyTime.End("Dynamic Single Array : Multiplication");

	//TimeTest_MyTime.Start();
	//for (i = 0; i < N; i++)
	//{
	//	for (j = 0; j < N; j++)
	//	{
	//		for (k = 0; k < N; k++)
	//		{
	//			if (k)
	//			{
	//				StaticDoubleArray3[i][j] += StaticDoubleArray2[i][k] * StaticDoubleArray1[k][j];
	//			}
	//			else
	//				StaticDoubleArray3[i][j] = StaticDoubleArray2[i][k] * StaticDoubleArray1[k][j];
	//		}
	//	}
	//}
	//TimeTest_MyTime.End("Static Double Array : Multiplication");

	TimeTest_MyTime.Start();
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			for (k = 0; k < N; k++)
			{
				if (k)
					DynamicDoubleArray3[i][j] += DynamicDoubleArray2[i][k] * DynamicDoubleArray1[i][k];
				else
					DynamicDoubleArray3[i][j] = DynamicDoubleArray2[i][k] * DynamicDoubleArray1[i][k];
			}

		}
	}
	TimeTest_MyTime.End("Dynamic Double Array : Multiplication");

	TimeTest_MyTime.Start();
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			for (k = 0; k < N; k++)
			{
				if (k)
					Vector3[i][j] += Vector2[i][k] * Vector1[i][k];
				else
					Vector3[i][j] = Vector2[i][k] * Vector1[i][k];
			}

		}
	}
	TimeTest_MyTime.End("Vector : Multiplication");
}