#include "Strassen_Vector.h"
#include "TimeCheck.h"

TimeCheck MyCheck;

void main()
{
	const int N = 540;
	
	vector<vector<int>> A(N, vector<int>(N, 0));
	vector<vector<int>> B(N, vector<int>(N, 0));
	vector<vector<int>> C1(N, vector<int>(N, 0));
	vector<vector<int>> C2(N, vector<int>(N, 0));
	vector<vector<int>> C3(4, vector<int>(4, 0));

	CreateRandomMatrix(N, &A);
	CreateEyeMatrix(N, &B);
	
	Offset ZERO = { 0,0 };

	//MyCheck.Start();
	MatrixMult_Standard(N, &A, &B, &C1);
	//MyCheck.End("standard");
	//MatrixPrint(N, &C1);

	//MyCheck.Start();
	MatrixMult_Strassen(N, ZERO, ZERO,ZERO, &A, &B, &C2);
	//MyCheck.End("Strassen");
	//MatrixPrint(N, &C2);

	MatrixCheck(N, &C2, &C1);

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