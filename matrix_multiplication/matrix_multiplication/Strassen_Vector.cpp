#include "Strassen_Vector.h"
#include "WriteCSV.h"
#include "TimeCheck.h"

TimeCheck Strassen_MyTime;
WriteCSV Strassen_MyFile;

void test_Threshold();
void test_Strassen();

void main()
{
	test_Threshold();

}

void test_Strassen()
{
	int N = 25;

	vector<vector<int>> A(N, vector<int>(N, 0));
	vector<vector<int>> B(N, vector<int>(N, 0));
	vector<vector<int>> C1(N, vector<int>(N, 0));
	vector<vector<int>> C2(N, vector<int>(N, 0));

	CreateRandomMatrix(N, &A);
	CreateEyeMatrix(N, &B);

	Offset ZERO = { 0,0 };

	MatrixMult_Standard(N, &A, &B, &C1);
	
	MatrixMult_Strassen(N,N, ZERO, ZERO, ZERO, &A, &B, &C2);
	

	MatrixCheck(N, &C1, &C2);

}

void test_Threshold()
{
	Strassen_MyFile.makeFile("StrassenTest2_20190423.csv");
	Strassen_MyFile.write("Matrix Size");
	Strassen_MyFile.write("Threshold(4)");
	Strassen_MyFile.write("Threshold(8)");
	Strassen_MyFile.write("Threshold(6)");
	Strassen_MyFile.write("Threshold(32)");
	Strassen_MyFile.write("Threshold(64)");
	Strassen_MyFile.changeRow();

	Offset ZERO = { 0,0 };

	int i;
	for (i = 240; i < 600; i++)
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
		MatrixMult_Strassen(i, i, ZERO, ZERO, ZERO, &A, &B, &C);
		Strassen_MyTime.End();
		Strassen_MyFile.write(Strassen_MyTime.GetTime());

		//Strassen_MyTime.Start();
		//MatrixMult_StrassenThresholdTest(i, 16, ZERO, ZERO, ZERO, &A, &B, &C);
		//Strassen_MyTime.End();
		//Strassen_MyFile.write(Strassen_MyTime.GetTime());

		//Strassen_MyTime.Start();
		//MatrixMult_StrassenThresholdTest(i, 8, ZERO, ZERO, ZERO, &A, &B, &C);
		//Strassen_MyTime.End();
		//Strassen_MyFile.write(Strassen_MyTime.GetTime());

		//Strassen_MyTime.Start();
		//MatrixMult_StrassenThresholdTest(i, 16, ZERO, ZERO, ZERO, &A, &B, &C);
		//Strassen_MyTime.End();
		//Strassen_MyFile.write(Strassen_MyTime.GetTime());

		//Strassen_MyTime.Start();
		//MatrixMult_StrassenThresholdTest(i, 32, ZERO, ZERO, ZERO, &A, &B, &C);
		//Strassen_MyTime.End();
		//Strassen_MyFile.write(Strassen_MyTime.GetTime());

		//Strassen_MyTime.Start();
		//MatrixMult_StrassenThresholdTest(i, 64, ZERO, ZERO, ZERO, &A, &B, &C);
		//Strassen_MyTime.End();
		//Strassen_MyFile.write(Strassen_MyTime.GetTime());

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