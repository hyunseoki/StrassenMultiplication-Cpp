#include <vector>
#include "TimeCheck.h"
#include "WriteCSV.h"

TimeCheck TimeTest_MyTime;
WriteCSV MyFile;

using std::vector;

void test_DataStructure(const int N);

void main()
{
	MyFile.makeFile("DataStructure.csv");
	MyFile.write("Size of Matrix");
	MyFile.write("Dynamic Single Array : +");
	MyFile.write("Dynamic Double Array : +");
	MyFile.write("Vector : +");
	MyFile.write("Dynamic Single Array : x");
	MyFile.write("Dynamic Double Array : x");
	MyFile.write("Vector : x");
	MyFile.changeRow();

	int i;
	for (i = 200; i < 500; i++)
	{
		test_DataStructure(i);
	}

	MyFile.closeFile();
}

void test_DataStructure(const int n)
{
	cout << "\n" << n << "\n";

	//int StaticSingleArray1[n*n] = { 0, };
	//int StaticSingleArray2[n*n] = { 0, };
	//int StaticSingleArray3[n*n] = { 0, };

	//int StaticDoubleArray1[n][n] = { 0 };
	//int StaticDoubleArray2[n][n] = { 0 };
	//int StaticDoubleArray3[n][n] = { 0, };

	int *DynamicSingleArray1 = new int [n*n];
	int *DynamicSingleArray2 = new int [n*n];
	int *DynamicSingleArray3 = new int [n*n];
	
	int **DynamicDoubleArray1 = new int *[n];
	int **DynamicDoubleArray2 = new int *[n];
	int **DynamicDoubleArray3 = new int *[n];

	vector<vector<int>> Vector1(n, vector<int>(n));
	vector<vector<int>> Vector2(n, vector<int>(n));
	vector<vector<int>> Vector3(n, vector<int>(n));


	int i, j, k;

	for (i = 0; i < n; i++)
	{
		DynamicDoubleArray1[i] = new int[n];
		DynamicDoubleArray2[i] = new int[n];
		DynamicDoubleArray3[i] = new int[n];
	}

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			DynamicSingleArray1[i*n + j] = 1;
			DynamicSingleArray2[i*n + j] = 1;
			DynamicSingleArray3[i*n + j] = 1;

			DynamicDoubleArray1[i][j] = 1;
			DynamicDoubleArray2[i][j] = 1;
			DynamicDoubleArray3[i][j] = 1;
			Vector1[i][j] = 1;
			Vector2[i][j] = 1;
			Vector3[i][j] = 1;
		}
	}

	MyFile.write(n);

	//TimeTest_MyTime.Start();
	//for (i = 0; i < n; i++)
	//{
	//	for (j = 0; j < n; j++)
	//	{
	//		StaticSingleArray3[i*n + j] = StaticSingleArray1[i*n + j] + StaticSingleArray2[i*n + j];
	//	}
	//}
	//TimeTest_MyTime.End("Static Single Array : Sum");

	TimeTest_MyTime.Start();
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			DynamicSingleArray3[i*n + j] = DynamicSingleArray1[i*n + j] + DynamicSingleArray2[i*n + j];
		}
	}
	TimeTest_MyTime.End("Dynamic Single Array : Sum");
	MyFile.write(TimeTest_MyTime.GetTime());

	//TimeTest_MyTime.Start();
	//for (i = 0; i < n; i++)
	//{
	//	for (j = 0; j < n; j++)
	//	{
	//		StaticDoubleArray3[i][j] = StaticDoubleArray1[i][j] + StaticDoubleArray2[i][j];
	//	}
	//}
	//TimeTest_MyTime.End("Static Double Array : Sum");

	TimeTest_MyTime.Start();
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			DynamicDoubleArray3[i][j] = DynamicDoubleArray1[i][j] + DynamicDoubleArray2[i][j];
		}
	}
	TimeTest_MyTime.End("Dynamic Double Array : Sum");
	MyFile.write(TimeTest_MyTime.GetTime());

	TimeTest_MyTime.Start();
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			Vector3[i][j] = Vector2[i][j] + Vector1[i][j];
		}
	}
	TimeTest_MyTime.End("Vector : Sum");
	MyFile.write(TimeTest_MyTime.GetTime());

	cout << "\n";

	//TimeTest_MyTime.Start();
	//for (i = 0; i < n; i++)
	//{
	//	for (j = 0; j < n; j++)
	//	{
	//		for (k = 0; k < n; k++)
	//		{
	//			if(k)
	//				StaticSingleArray3[i*n + j] += StaticSingleArray1[i*n + k] + StaticSingleArray2[k*n + j];
	//			else
	//				StaticSingleArray3[i*n + j] = StaticSingleArray1[i*n + k] + StaticSingleArray2[k*n + j];
	//		}
	//		
	//	}
	//}
	//TimeTest_MyTime.End("Static Single Array : Multiplication");

	TimeTest_MyTime.Start();
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			for (k = 0; k < n; k++)
			{
				if (k)
					DynamicSingleArray3[i*n + j] += DynamicSingleArray1[i*n + k] + DynamicSingleArray2[k*n + j];
				else
					DynamicSingleArray3[i*n + j] = DynamicSingleArray1[i*n + k] + DynamicSingleArray2[k*n + j];
			}

		}
	}
	TimeTest_MyTime.End("Dynamic Single Array : Multiplication");
	MyFile.write(TimeTest_MyTime.GetTime());

	//TimeTest_MyTime.Start();
	//for (i = 0; i < n; i++)
	//{
	//	for (j = 0; j < n; j++)
	//	{
	//		for (k = 0; k < n; k++)
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
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			for (k = 0; k < n; k++)
			{
				if (k)
					DynamicDoubleArray3[i][j] += DynamicDoubleArray2[i][k] * DynamicDoubleArray1[i][k];
				else
					DynamicDoubleArray3[i][j] = DynamicDoubleArray2[i][k] * DynamicDoubleArray1[i][k];
			}

		}
	}
	TimeTest_MyTime.End("Dynamic Double Array : Multiplication");
	MyFile.write(TimeTest_MyTime.GetTime());

	TimeTest_MyTime.Start();
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			for (k = 0; k < n; k++)
			{
				if (k)
					Vector3[i][j] += Vector2[i][k] * Vector1[i][k];
				else
					Vector3[i][j] = Vector2[i][k] * Vector1[i][k];
			}

		}
	}
	TimeTest_MyTime.End("Vector : Multiplication");
	MyFile.write(TimeTest_MyTime.GetTime());

	MyFile.changeRow();
}