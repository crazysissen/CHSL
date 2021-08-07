#pragma once

namespace cs
{

	int mod(int val, int ceil);

	int floor(float val);

	float clamp(float val, float min, float max);

	int wrap(int val, int min, int max);

	float wrapf(float val, float min, float max);

}