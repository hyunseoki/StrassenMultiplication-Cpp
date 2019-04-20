#include "Strassen_2DArray.h"
#include "TimeCheck.h"
#include <time.h>

TimeCheck MyTime;

void main()
{
	int A[N][N], B[N][N], C1[N][N], C2[N][N];

	srand(time(NULL));

	int ranN1, ranN2;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			ranN1 = (int)(rand()) * 10 / 32767; // 0 ~ 10.0 ����
			ranN2 = (int)(rand()) * 10 / 32767;
			A[i][j] = ranN1;
			B[i][j] = ranN2;
			C1[i][j] = 0;
			C2[i][j] = 0;
		}
	}

	//MatrixPrint(N, A);
	//MatrixPrint(N, B);

	//Offset test = { 2,2 };
	//MatrixSum_Partial(2, test, test, test, A, B, C1);
	//MatrixPrint(N, C1);

	//MatrixSubs_Partial(2, test, test, test, A, B, C1);
	//MatrixPrint(N, C1);

	//MatrixMult_Partial(2, test, test, test, A, B, C1);
	//MatrixPrint(N, C1);

	//MyTime.Start();
	MatrixMult_Standard(N, A, B, C1);
	//MyTime.End("Standard Multi");
	MatrixPrint(N, C1);

	//MyTime.Start();
	MatrixMult_Strassen(N, A, B, C2);
	//MyTime.End("Strassen Multi");
	MatrixPrint(N, C2);
	

	//MatrixCheck(N, C1, C2);
}