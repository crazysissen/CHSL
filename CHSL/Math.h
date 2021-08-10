#pragma once

#include "CHSLTypedef.h"

namespace cs
{

	int mod(int val, int ceil);
	uint mod(uint val, uint ceil);
	size_t mod(size_t val, size_t ceil);

	int floor(float val);

	float clamp(float val, float min, float max);

	int wrap(int val, int min, int max);

	float wrapf(float val, float min, float max);

}