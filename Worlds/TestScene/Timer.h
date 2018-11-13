#pragma once
#include <chrono>
class Timer
{
public:
	Timer();
	~Timer();
	void start();
	float delta();
private:

	std::chrono::time_point<std::chrono::high_resolution_clock> _lastChecked;
};

