#pragma once
#include <fstream>

class WriteCSV
{
public:
	WriteCSV();
	~WriteCSV();
	void makeFile(const char * filename);
	void write(const char * s);
	void write(const int s);
	void write(const float s);
	void changeRow();
	void closeFile();

private:
	std::ofstream m_sStream;
};




