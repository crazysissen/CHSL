#include "core.h"

#include "CSMath.h"

int cs::imod(int val, int ceil)
{
	return val >= ceil ? val % ceil : val;
}

//uint cs::mod(uint val, uint ceil)
//{
//	return val >= ceil ? val % ceil : val;
//}

size_t cs::stmod(size_t val, size_t ceil)
{
	return val >= ceil ? val % ceil : val;
}

int cs::floor(float val)
{
	return val > 0 ? ((int)val) : ((int)val - 1);
}

int cs::ceil(float val)
{
	return val > 0 ? ((int)val + 1) : ((int)val);
}

float cs::fclamp(float val, float min, float max)
{
	if (val > max)
		return max;

	if (val < min)
		return min;

	return val;
}

int cs::iclamp(int val, int min, int max)
{
	if (val > max)
		return max;

	if (val < min)
		return min;

	return val;
}

int cs::iwrap(int val, int min, int max)
{
	if (val >= min && val <= max)
	{
		return val;
	}

	int range = max - min;

	return min + (range + (val - min) % range) % range;
}

float cs::fwrap(float val, float max)
{
	if (val >= 0 && val <= max)
	{
		return val;
	}

	return fmod(max + fmod(val, max), max);
}

float cs::fwrap(float val, float min, float max)
{
	return min + fwrap(val - min, max - min);
}

int cs::iabs(int val)
{
	return val < 0 ? -val : val;
}
