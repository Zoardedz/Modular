#pragma once
#include <chrono>

class DirTimer
{
public:
	DirTimer() noexcept;
	float Mark() noexcept;
	float Peek() const noexcept;
private:
	std::chrono::steady_clock::time_point last;
};