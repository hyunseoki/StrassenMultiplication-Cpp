#include "WriteCSV.h"

using namespace std;

void makeFile(const char * filename = "log.csv")
{
	MyFile.open(filename);
}

void writeCSV(const char * s)
{
	MyFile<< s << ",";
}

void closeFile()
{
	MyFile.close();
}
