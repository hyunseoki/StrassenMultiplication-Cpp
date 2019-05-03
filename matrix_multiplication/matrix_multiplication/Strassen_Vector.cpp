#include "Strassen_Vector.h"
#include "WriteCSV.h"
#include "TimeCheck.h"


TimeCheck Strassen_MyTime;
WriteCSV Strassen_MyFile;

void test_Threshold();
void test_Strassen();
void test_OpenMPvsMultiThread();

void main()
{
	//test_OpenMPvsMultiThread();
	test_Strassen();
	//test_Threshold();

}

void test_Strassen()
{
	//int N = 220;

	for (int N = 128; N < 145; N++)
	{
		vector<vector<int>> A(N, vector<int>(N, 0));
		vector<vector<int>> B(N, vector<int>(N, 0));
		vector<vector<int>> C1(N, vector<int>(N, 0));
		vector<vector<int>> C2(N, vector<int>(N, 0));
		vector<vector<int>> C3(N, vector<int>(N, 0));
		vector<vector<int>> C4(N, vector<int>(N, 0));
		vector<vector<int>> C5(N, vector<int>(N, 0));

		CreateRandomMatrix(N, &A);
		CreateEyeMatrix(N, &B);

		Offset ZERO = { 0,0 };

		//Strassen_MyTime.Start();
		MatrixMult_Standard(N, &A, &B, &C1);
		//Strassen_MyTime.End("Standard");

		//Strassen_MyTime.Start();
		MatrixMult_Strassen(N,N, ZERO, ZERO, ZERO, &A, &B, &C2);
		//Strassen_MyTime.End("Strassen");

		//Strassen_MyTime.Start();
		MatrixMult_Strassen(N, &A, &B, &C2);
		//Strassen_MyTime.End("Strassen");
		MatrixCheck(N, &C1, &C2);
	}

}

void test_OpenMPvsMultiThread()
{
	Strassen_MyFile.makeFile("ParallelTest_20190502.csv");
	Strassen_MyFile.write("Matrix Size");
	Strassen_MyFile.write("Standard Multiplication");
	Strassen_MyFile.write("OpenMP Multiplication");
	Strassen_MyFile.write("Multithraed Multiplication");
	Strassen_MyFile.changeRow();

	Offset ZERO = { 0,0 };

	int i;
	for (i = 10; i < 501; i++)
	{
		vector<vector<int>> A(i, vector<int>(i, 0));
		vector<vector<int>> B(i, vector<int>(i, 0));
		vector<vector<int>> C(i, vector<int>(i, 0));

		CreateRandomMatrix(i, &A);
		CreateEyeMatrix(i, &B);

		Strassen_MyFile.write(i);

		Strassen_MyTime.Start();
		MatrixMult_Standard(i, &A, &B, &C);
		Strassen_MyTime.End();
		Strassen_MyFile.write(Strassen_MyTime.GetTime());

		Strassen_MyTime.Start();
		MatrixMult_OpenMP(i, &A, &B, &C);
		Strassen_MyTime.End();
		Strassen_MyFile.write(Strassen_MyTime.GetTime());

		Strassen_MyTime.Start();
		MatrixMult_MultiThread(i, &A, &B, &C);
		Strassen_MyTime.End();
		Strassen_MyFile.write(Strassen_MyTime.GetTime());
	
		Strassen_MyFile.changeRow();
	}
	
	Strassen_MyFile.closeFile();
}

void test_Threshold()
{
	Strassen_MyFile.makeFile("Threshold_20190503.csv");
	Strassen_MyFile.write("Threshold");
	Strassen_MyFile.write("MatrixSize(64)");
	Strassen_MyFile.write("MatrixSize(128)");
	Strassen_MyFile.write("MatrixSize(256)");
	Strassen_MyFile.write("MatrixSize(512)");
	Strassen_MyFile.write("MatrixSize(1024)");
	Strassen_MyFile.write("MatrixSize(2048)");
	Strassen_MyFile.changeRow();

	Offset ZERO = { 0,0 };

	int i;
	for (i = 0; i < 8; i++)
	{
		vector<vector<int>> A1(64, vector<int>(64, 0));
		vector<vector<int>> B1(64, vector<int>(64, 0));
		vector<vector<int>> C1(64, vector<int>(64, 0));

		CreateRandomMatrix(64, &A1);
		CreateEyeMatrix(64, &B1);

		vector<vector<int>> A2(128, vector<int>(128, 0));
		vector<vector<int>> B2(128, vector<int>(128, 0));
		vector<vector<int>> C2(128, vector<int>(128, 0));

		CreateRandomMatrix(128, &A2);
		CreateEyeMatrix(128, &B2);

		vector<vector<int>> A3(256, vector<int>(256, 0));
		vector<vector<int>> B3(256, vector<int>(256, 0));
		vector<vector<int>> C3(256, vector<int>(256, 0));

		CreateRandomMatrix(256, &A3);
		CreateEyeMatrix(256, &B3);

		vector<vector<int>> A4(512, vector<int>(512, 0));
		vector<vector<int>> B4(512, vector<int>(512, 0));
		vector<vector<int>> C4(512, vector<int>(512, 0));

		CreateRandomMatrix(512, &A4);
		CreateEyeMatrix(512, &B4);

		vector<vector<int>> A5(1024, vector<int>(1024, 0));
		vector<vector<int>> B5(1024, vector<int>(1024, 0));
		vector<vector<int>> C5(1024, vector<int>(1024, 0));

		CreateRandomMatrix(1024, &A5);
		CreateEyeMatrix(1024, &B5);

		vector<vector<int>> A6(2048, vector<int>(2048, 0));
		vector<vector<int>> B6(2048, vector<int>(2048, 0));
		vector<vector<int>> C6(2048, vector<int>(2048, 0));

		CreateRandomMatrix(2048, &A6);
		CreateEyeMatrix(2048, &B6);

		//CreateEyeMatrix(i, &B);
		//CreateEyeMatrix(i, &B);
		//CreateEyeMatrix(i, &B);

		int idx = pow(2, i);
		Strassen_MyFile.write(idx);

		Strassen_MyTime.Start();
		MatrixMult_StrassenThresholdTest(64, pow(2, i), ZERO, ZERO, ZERO, &A1, &B1, &C1);
		Strassen_MyTime.End();
		Strassen_MyFile.write(Strassen_MyTime.GetTime());

		Strassen_MyTime.Start();
		MatrixMult_StrassenThresholdTest(128, pow(2, i), ZERO, ZERO, ZERO, &A2, &B2, &C2);
		Strassen_MyTime.End();
		Strassen_MyFile.write(Strassen_MyTime.GetTime());

		Strassen_MyTime.Start();
		MatrixMult_StrassenThresholdTest(256, pow(2, i), ZERO, ZERO, ZERO, &A3, &B3, &C3);
		Strassen_MyTime.End();
		Strassen_MyFile.write(Strassen_MyTime.GetTime());

		Strassen_MyTime.Start();
		MatrixMult_StrassenThresholdTest(512, pow(2, i), ZERO, ZERO, ZERO, &A4, &B4, &C4);
		Strassen_MyTime.End();
		Strassen_MyFile.write(Strassen_MyTime.GetTime());

		Strassen_MyTime.Start();
		MatrixMult_StrassenThresholdTest(1024, pow(2, i), ZERO, ZERO, ZERO, &A5, &B5, &C5);
		Strassen_MyTime.End();
		Strassen_MyFile.write(Strassen_MyTime.GetTime());

		Strassen_MyTime.Start();
		MatrixMult_StrassenThresholdTest(2018, pow(2, i), ZERO, ZERO, ZERO, &A6, &B6, &C6);
		Strassen_MyTime.End();
		Strassen_MyFile.write(Strassen_MyTime.GetTime());

		Strassen_MyFile.changeRow();
	}

	Strassen_MyFile.closeFile();
}

int FindPaddingSize(const int n)
{
	if (!(n & (n - 1))) return 0;
	else if (n < 4)     return 4;
	else if (n < 8)     return 8;
	else if (n < 16)    return 16;
	else if (n < 32)    return 32;
	else if (n < 64)    return 64;
	else if (n < 128)   return 128;
	else if (n < 256)   return 256;
	else if (n < 512)   return 512;
	else                return 1024;
}

PadData FindOptimalPaddingSize(const int n)
{
	int cnt = 0;
	float q = (float) n;
	PadData result;

	while (q >= 64)
	{
		q = round(q / 2);
		cnt++;
	}

	result.m_Padsize = (int)q * pow(2, cnt);
	result.m_Threshold = (int)q;

	return result;
}
