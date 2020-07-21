#ifndef __TIMER_H__
#define __TIMER_H__

#include <chrono>

struct Timer
{
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<float> duration;
	float* delta;

	Timer(float* _delta)
	{
		delta = _delta;
		start = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;
		*delta = duration.count();
	}
};

#endif // !__TIMER_H__