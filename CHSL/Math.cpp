#include "core.h"

#include "Math.h"

int cs::mod(int val, int ceil)
{
	return val >= ceil ? val % ceil : val;
}

int cs::floor(float val)
{
	return val > 0 ? ((int)val) : ((int)val - 1);
}

float cs::clamp(float val, float min, float max)
{
	if (val > max)
		return max;

	if (val < min)
		return min;

	return val;
}

int cs::wrap(int val, int min, int max)
{
	if (val >= min && val <= max)
	{
		return val;
	}

	int range = max - min;

	return min + (range + (val - min) % range) % range;
}

float cs::wrapf(float val, float min, float max)
{
	if (val >= min && val <= max)
	{
		return val;
	}

	float range = max - min;

	return min + fmod(range + fmod(val - min, range), range);
}
