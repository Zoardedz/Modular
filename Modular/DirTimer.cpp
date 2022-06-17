#include "DirTimer.h"

using namespace std::chrono;

DirTimer::DirTimer() noexcept
{
	last = steady_clock::now();
}

float DirTimer::Mark() noexcept
{
	const auto old = last;
	last = steady_clock::now();
	const duration<float> frameTime = last - old;
	return frameTime.count();
}

float DirTimer::Peek() const noexcept
{
	return duration<float>(steady_clock::now() - last).count();
}