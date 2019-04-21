#include "Strassen_2DArray.h"
#include "TimeCheck.h"
#include <time.h>

//TimeCheck TimeTest_MyTime;
//
//void main()
//{
//	//int A[N][N], B[N][N], C1[N][N], C2[N][N];
//
//	//srand(time(NULL));
//
//	//int ranN1, ranN2;
//
//	//for (int i = 0; i < N; i++)
//	//{
//	//	for (int j = 0; j < N; j++)
//	//	{
//	//		ranN1 = (int)(rand()) * 10 / 32767; // 0 ~ 10.0 ����
//	//		ranN2 = (int)(rand()) * 10 / 32767;
//	//		A[i][j] = ranN1;
//	//		B[i][j] = ranN2;
//	//		C1[i][j] = 0;
//	//		C2[i][j] = 0;
//	//	}
//	//}
//
//	int ** DynamicArray1 = new int *[N];
//	int ** DynamicArray2 = new int *[N];
//	int ** DynamicArray3 = new int *[N];
//	int ** DynamicArray4 = new int *[N];
//
//	CreateZeroMatrix(N, DynamicArray1);
//	CreateZeroMatrix(N, DynamicArray2);
//	CreateZeroMatrix(N, DynamicArray3);
//	CreateZeroMatrix(N, DynamicArray4);
//
//	DynamicArray1[0][0] = 1;
//	DynamicArray2[0][0] = 1;
//
//	Offset ZERO = { 0, 0 };
//	TimeTest_MyTime.Start();
//	MatrixMult_Standard(N, DynamicArray1, DynamicArray2, DynamicArray3);
//	TimeTest_MyTime.End("standard");
//	//MatrixPrint(N, DynamicArray3);
//	TimeTest_MyTime.Start();
//	MatrixMult_Strassen(N, ZERO, ZERO, ZERO, DynamicArray1, DynamicArray2, DynamicArray4);
//	//MatrixPrint(N, DynamicArray4);
//	TimeTest_MyTime.End("strassen");
//	MatrixCheck(N, DynamicArray3, DynamicArray4);
//
//	DestroyMatrix(N, DynamicArray1);
//	DestroyMatrix(N, DynamicArray2);
//	DestroyMatrix(N, DynamicArray3);
//	DestroyMatrix(N, DynamicArray4);
//
//	//MatrixPrint(N, A);
//	//MatrixPrint(N, B);
//
//	//Offset test = { 2,2 };
//	//MatrixSum_Partial(2, test, test, test, A, B, C1);
//	//MatrixPrint(N, C1);
//
//	//MatrixSubs_Partial(2, test, test, test, A, B, C1);
//	//MatrixPrint(N, C1);
//
//	//MatrixMult_Partial(2, test, test, test, A, B, C1);
//	//MatrixPrint(N, C1);
//
//	//TimeTest_MyTime.Start();
//	//MatrixMult_Standard(N, A, B, C1);
//	//TimeTest_MyTime.End("Standard Multi");
//	//MatrixPrint(N, C1);
//
//	//TimeTest_MyTime.Start();
//	//MatrixMult_Strassen(N, A, B, C2);
//	//TimeTest_MyTime.End("Strassen Multi");
//	//MatrixPrint(N, C2);
//	
//	//MatrixCheck(N, C1, C2);
//}