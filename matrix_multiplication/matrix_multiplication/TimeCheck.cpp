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

// Return (ms)
float TimeCheck::GetTime()
{
	return (float)(m_End - m_Start).count() / 1000.0f;
}

void TimeCheck::End(const char * s)
{
	m_End = high_resolution_clock::now();
	Print(s);
}

void TimeCheck::Print()
{
	cout << " run time = " << (m_End - m_Start).count() / 1000 << "ms. \n";
}

void TimeCheck::Print(const char * s)
{
	cout << s;
	Print();
}
