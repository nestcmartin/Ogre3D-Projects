#ifndef __CLOCK_H__
#define __CLOCK_H__

#include <chrono>

class Clock
{
private:
	std::chrono::time_point<std::chrono::steady_clock> startingTimePoint_;
	std::chrono::time_point<std::chrono::steady_clock> endingTimePoint_;

	float deltaTime_;
	float timeScale_;
	bool isPaused_;

public:
	Clock();
	~Clock() {}

	void startTimer();
	void endTimer();

	float getDeltaTime() const { return deltaTime_ / 1000.0f; }
	float getTimeScale() const { return timeScale_; }
	void setTimeScale(float scale) { timeScale_ = scale; }
	bool isPaused() const { return isPaused_; }
	void setPaused(bool wantPaused) { isPaused_ = wantPaused; }
};

#endif // !__CLOCK_H__