#include "core.h"

#include "Math.h"

constexpr int cs::imod(int val, int ceil)
{
	return val >= ceil ? val % ceil : val;
}

//uint cs::mod(uint val, uint ceil)
//{
//	return val >= ceil ? val % ceil : val;
//}

constexpr size_t cs::imod(size_t val, size_t ceil)
{
	return val >= ceil ? val % ceil : val;
}

constexpr int cs::floor(float val)
{
	return val > 0 ? ((int)val) : ((int)val - 1);
}

constexpr int cs::ceil(float val)
{
	return val > 0 ? ((int)val + 1) : ((int)val);
}

constexpr int cs::imax(int a, int b)
{
	return (a > b) ? a : b;
}

constexpr int cs::imin(int a, int b)
{
	return (a < b) ? a : b;
}

constexpr float cs::fmax(float a, float b)
{
	return (a > b) ? a : b;
}

constexpr float cs::fmin(float a, float b)
{
	return (a < b) ? a : b;
}

constexpr float cs::fclamp(float val, float min, float max)
{
	if (val > max)
		return max;

	if (val < min)
		return min;

	return val;
}

constexpr int cs::iclamp(int val, int min, int max)
{
	if (val > max)
		return max;

	if (val < min)
		return min;

	return val;
}

constexpr int cs::iwrap(int val, int min, int max)
{
	if (val >= min && val <= max)
	{
		return val;
	}

	int range = max - min;

	return min + (range + (val - min) % range) % range;
}

constexpr float cs::fwrap(float val, float max)
{
	if (val >= 0 && val <= max)
	{
		return val;
	}

	return fmod(max + fmod(val, max), max);
}

constexpr float cs::fwrap(float val, float min, float max)
{
	return min + fwrap(val - min, max - min);
}

constexpr int cs::iabs(int val)
{
	return val < 0 ? -val : val;
}
