#include "Clock.h"

Clock::Clock() :
	deltaTime_(1.0f / 30.0f),
	timeScale_(1.0f),
	isPaused_(false)
{
}

void Clock::startTimer()
{
	startingTimePoint_ = std::chrono::high_resolution_clock::now();
}

void Clock::endTimer()
{
	endingTimePoint_ = std::chrono::high_resolution_clock::now();
	deltaTime_ = std::chrono::duration_cast<std::chrono::milliseconds>(endingTimePoint_ - startingTimePoint_).count();
}