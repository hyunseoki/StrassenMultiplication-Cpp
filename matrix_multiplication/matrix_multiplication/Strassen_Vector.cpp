#include "Strassen_Vector.h"
#include "WriteCSV.h"
#include "TimeCheck.h"

TimeCheck Strassen_MyTime;
WriteCSV Strassen_MyFile;

void test_Strassen();
void test_OpenMPvsMultiThread();
void test_StrassenvsStandard();
void test_PaddingSize();

//void main()
//{
//	//test_Strassen();
//	//test_OpenMPvsMultiThread();
//	//test_StrassenvsStandard();
//	
//}

void test_Strassen()
{
	//int N = 220;

	for (int N = 220; N < 225; N++)
	{
		vector<vector<int>> A(N, vector<int>(N, 0));
		vector<vector<int>> B(N, vector<int>(N, 0));
		vector<vector<int>> C1(N, vector<int>(N, 0));
		vector<vector<int>> C2(N, vector<int>(N, 0));
		vector<vector<int>> C3(N, vector<int>(N, 0));
		vector<vector<int>> C4(N, vector<int>(N, 0));
		vector<vector<int>> C5(N, vector<int>(N, 0));

		CreateRandomMatrix(N, A);
		CreateEyeMatrix(N, B);

		Offset ZERO = { 0,0 };

		Strassen_MyTime.Start();
		MatrixMult_Standard(N, A, B, C1);
		Strassen_MyTime.End("Standard");

		Strassen_MyTime.Start();
		MatrixMult_OpenMP(N, A, B, C2);
		Strassen_MyTime.End("OpenMP");

		Strassen_MyTime.Start();
		MatrixMult_Strassen(N, A, B, C3);
		Strassen_MyTime.End("Strassen");
		MatrixCheck(N, C1, C3);
	}

}

void test_OpenMPvsMultiThread()
{
	Strassen_MyFile.makeFile("ParallelTest_20190506.csv");
	Strassen_MyFile.write("Matrix Size");
	Strassen_MyFile.write("Standard Sum");
	Strassen_MyFile.write("OpenMP Sum");
	Strassen_MyFile.write("Multithraed Sum");
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
		vector<vector<int>> C1(i, vector<int>(i, 0));

		CreateRandomMatrix(i, A);
		CreateEyeMatrix(i, B);

		Strassen_MyFile.write(i);

		Strassen_MyTime.Start();
		MatrixSum_Standard(i, A, B, C);
		Strassen_MyTime.End();
		Strassen_MyFile.write(Strassen_MyTime.GetTime());

		Strassen_MyTime.Start();
		MatrixSum_OpenMP(i, A, B, C);
		Strassen_MyTime.End();
		Strassen_MyFile.write(Strassen_MyTime.GetTime());

		Strassen_MyTime.Start();
		MatrixSum_MultiThread(i, A, B, C1);
		Strassen_MyTime.End();
		Strassen_MyFile.write(Strassen_MyTime.GetTime());
		
		MatrixCheck(i, C, C1);

		Strassen_MyTime.Start();
		MatrixMult_Standard(i, A, B, C);
		Strassen_MyTime.End();
		Strassen_MyFile.write(Strassen_MyTime.GetTime());

		Strassen_MyTime.Start();
		MatrixMult_OpenMP(i, A, B, C);
		Strassen_MyTime.End();
		Strassen_MyFile.write(Strassen_MyTime.GetTime());

		Strassen_MyTime.Start();
		MatrixMult_MultiThread(i, A, B, C);
		Strassen_MyTime.End();
		Strassen_MyFile.write(Strassen_MyTime.GetTime());
		
		Strassen_MyFile.changeRow();

		
	}
	
	Strassen_MyFile.closeFile();
}

void test_StrassenvsStandard()
{
	Strassen_MyFile.makeFile("StrassenvsStandard_20190507.csv");
	Strassen_MyFile.write("Size");
	Strassen_MyFile.write("Standard Multiplication");
	Strassen_MyFile.write("OpenMP Multiplication");
	Strassen_MyFile.write("Strassen Multiplication");
	Strassen_MyFile.changeRow();

	Offset ZERO = { 0,0 };

	int i;
	for (i = 10; i < 1000; i++)
	{
		vector<vector<int>> A(i, vector<int>(i, 0));
		vector<vector<int>> B(i, vector<int>(i, 0));
		vector<vector<int>> C(i, vector<int>(i, 0));

		CreateRandomMatrix(i, A);
		CreateEyeMatrix(i, B);

		Strassen_MyFile.write(i);

		/*Strassen_MyTime.Start();
		MatrixMult_Standard(i, A, B, C);
		Strassen_MyTime.End();
		Strassen_MyFile.write(Strassen_MyTime.GetTime());*/

		Strassen_MyTime.Start();
		MatrixMult_OpenMP(i, A, B, C);
		Strassen_MyTime.End();
		Strassen_MyFile.write(Strassen_MyTime.GetTime());

		Strassen_MyTime.Start();
		MatrixMult_Strassen(i, A, B, C);
		Strassen_MyTime.End();
		Strassen_MyFile.write(Strassen_MyTime.GetTime());

		Strassen_MyFile.changeRow();
	}

	Strassen_MyFile.closeFile();

	/*Strassen_MyFile.makeFile("ParallelTest_20190505.csv");
	Strassen_MyFile.write("Matrix Size");
	Strassen_MyFile.write("Standard Summation");
	Strassen_MyFile.write("OpenMP Summation");
	Strassen_MyFile.write("Multithraed Summation");
	Strassen_MyFile.changeRow();

	Offset ZERO = { 0,0 };

	int i;
	for (i = 10; i < 2500; i++)
	{
		vector<vector<int>> A(i, vector<int>(i, 0));
		vector<vector<int>> B(i, vector<int>(i, 0));
		vector<vector<int>> C(i, vector<int>(i, 0));

		CreateRandomMatrix(i, A);
		CreateEyeMatrix(i, B);

		Strassen_MyFile.write(i);

		Strassen_MyTime.Start();
		MatrixSum_Standard(i, A, B, C);
		Strassen_MyTime.End();
		Strassen_MyFile.write(Strassen_MyTime.GetTime());

		Strassen_MyTime.Start();
		MatrixSum_OpenMP(i, A, B, C);
		Strassen_MyTime.End();
		Strassen_MyFile.write(Strassen_MyTime.GetTime());

		Strassen_MyTime.Start();
		MatrixPartialSum_MultiThread(i, ZERO, ZERO, ZERO, A, B, C);
		Strassen_MyTime.End();
		Strassen_MyFile.write(Strassen_MyTime.GetTime());

		Strassen_MyFile.changeRow();
	}

	Strassen_MyFile.closeFile();*/
}

void test_PaddingSize()
{
	Strassen_MyFile.makeFile("PaddingSize_20190506.csv");
	Strassen_MyFile.write("Matrix Size");
	Strassen_MyFile.write("Naive Padded Size");
	Strassen_MyFile.write("Optimal Padded Size");
	Strassen_MyFile.changeRow();

	int i;
	for (i = 10; i < 501; i++)
	{

		Strassen_MyFile.write(i);
		Strassen_MyFile.write(FindNaiveFaddingSize(i));
		PadData temp = FindOptimalPaddingSize(i);
		Strassen_MyFile.write(temp.m_Padsize);

		Strassen_MyFile.changeRow();
	}

	Strassen_MyFile.closeFile();

}

int FindNaiveFaddingSize(const int n)
{
	if (n <= 4)     return 4;
	else if (n <= 16)    return 16;
	else if (n <= 32)    return 32;
	else if (n <= 64)    return 64;
	else if (n <= 128)   return 128;
	else if (n <= 256)   return 256;
	else                return 512;
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

	result.m_Padsize = (int) (q * pow(2, cnt));
	result.m_Threshold = (int)q;

	return result;
}
