#include "TimeCheck.h"

TimeCheck::TimeCheck()
{
}

TimeCheck::~TimeCheck()
{
}

void TimeCheck::Start()
{
	m_Start = high_resolution_clock::now();
}

void TimeCheck::End()
{
	m_End = high_resolution_clock::now();
	Print();
}

// Return (mmsec)
float TimeCheck::GetTime()
{
	return (m_End - m_Start).count() / 1000;
}

void TimeCheck::End(const char * s)
{
	m_End = high_resolution_clock::now();
	Print(s);
}

void TimeCheck::Print()
{
	cout << " run time = " << (m_End - m_Start).count() / 1000 << "mm sec. \n";
}

void TimeCheck::Print(const char * s)
{
	cout << s;
	Print();
}
