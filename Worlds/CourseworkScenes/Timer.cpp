#include "Timer.h"



Timer::Timer()
{
}


Timer::~Timer()
{
}

void Timer::start()
{
	_lastChecked = std::chrono::high_resolution_clock::now();
}

float Timer::delta()
{
	auto now = std::chrono::high_resolution_clock::now();
	float result = (now - _lastChecked).count() * 0.000000001f;
	_lastChecked = now;
	return result;
}
