#include "core.h"

#include "Timer.h"

using namespace std::chrono;

const double NS = 1.0f / 1000000000;

cs::Timer::Timer()
{
	timestamp = steady_clock::now();
}

float cs::Timer::Lap()
{
	auto previous = timestamp;
	timestamp = steady_clock::now();

	return (float)(NS * (timestamp - previous).count());
}

float cs::Timer::Peek() const
{
	return (float)(NS * (steady_clock::now() - timestamp).count());
}
