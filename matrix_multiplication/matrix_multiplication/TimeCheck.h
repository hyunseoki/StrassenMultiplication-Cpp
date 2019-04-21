#pragma once
#include <chrono>
#include <iostream>

using std::chrono::high_resolution_clock;
using std::cout;
using std::string;

typedef std::chrono::steady_clock::time_point m_time;

class TimeCheck
{
public:
	TimeCheck();
	~TimeCheck();
	void Start();
	void End();
	float GetTime();
	void End(const char* s);

private:
	m_time m_Start;
	m_time m_End;
	void Print();
	void Print(const char *s);
};

