#include "Strassen.h"
#include <opencv2/opencv.hpp>
#include "WriteCSV.h"
#include "TimeCheck.h"
       
using cv::Mat;
using std::cout;

TimeCheck Main_MyTime;
WriteCSV Main_MyFile;

int main(int argc, char * argv[])
{
	Main_MyFile.makeFile("OpenCVvsStrassen_20190507.csv");
	Main_MyFile.write("Matrix Size");
	Main_MyFile.write("Naive Multiplication");
	Main_MyFile.write("OpenCV Multiplication");
	Main_MyFile.write("OpenMP Multiplication");
	Main_MyFile.write("Strassen Multiplication");
	Main_MyFile.changeRow();

	for (int i = 5; i < 510; i++)
	{
		Mat cv_A(i, i, CV_32F);
		Mat cv_B(i, i, CV_32F);
		Mat cv_C(i, i, CV_32F);

		vector<vector<int>> vec_A(i, vector<int>(i, 0));
		vector<vector<int>> vec_B(i, vector<int>(i, 0));
		vector<vector<int>> vec_C(i, vector<int>(i, 0));
		vector<vector<int>> vec_C1(i, vector<int>(i, 0));
		vector<vector<int>> vec_C2(i, vector<int>(i, 0));

		srand(time(NULL));

		int ranNb[2];

		for (int j = 0; j < i; j++)
		{
			for (int k = 0; k < i; k++)
			{
				ranNb[0] = (int)(rand() * 10 / 32767); // 0 ~ 10.0 ����
				ranNb[1] = (int)(rand() * 10 / 32767);

				cv_A.at<float>(j, k) = ranNb[0];
				cv_B.at<float>(j, k) = ranNb[1];

				vec_A[j][k] = ranNb[0];
				vec_B[j][k] = ranNb[1];
			}
		}

		Main_MyFile.write(i);

		Main_MyTime.Start();
		MatrixMult_Standard(i, vec_A, vec_B, vec_C2);
		Main_MyTime.End();
		Main_MyFile.write(Main_MyTime.GetTime());

		Main_MyTime.Start();
		cv_C = cv_A * cv_B;
		Main_MyTime.End();
		Main_MyFile.write(Main_MyTime.GetTime());

		Main_MyTime.Start();
		MatrixMult_OpenMP(i, vec_A, vec_B, vec_C1);
		Main_MyTime.End();
		Main_MyFile.write(Main_MyTime.GetTime());

		Main_MyTime.Start();
		MatrixMult_Strassen(i, vec_A, vec_B, vec_C);
		Main_MyTime.End();
		Main_MyFile.write(Main_MyTime.GetTime());

		Main_MyFile.changeRow();
	}

	return EXIT_SUCCESS;
}
