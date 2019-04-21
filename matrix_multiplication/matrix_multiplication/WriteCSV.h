#pragma once
#include <fstream>

class WriteCSV
{
public:
	WriteCSV();
	~WriteCSV();
	void makeFile(const char * filename);
	void write(const char * s);
	void WriteCSV::write(const int s);
	void WriteCSV::write(const float s);
	void WriteCSV::changeRow();
	void closeFile();

private:
	std::ofstream m_sStream;
};




