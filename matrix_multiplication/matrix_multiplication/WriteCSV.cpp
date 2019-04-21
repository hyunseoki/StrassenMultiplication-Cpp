#include "WriteCSV.h"

WriteCSV::WriteCSV()
{
}

WriteCSV::~WriteCSV()
{
}

void WriteCSV::makeFile(const char * filename = "log.csv")
{
	m_sStream.open(filename);
}

void WriteCSV::write(const char * s)
{
	m_sStream << s << ",";
}

void WriteCSV::write(const int s)
{
	m_sStream << s << ",";
}

void WriteCSV::write(const float s)
{
	m_sStream << s << ",";
}

void WriteCSV::changeRow()
{
	m_sStream << "\n";
}

void WriteCSV::closeFile()
{
	m_sStream.close();
}
