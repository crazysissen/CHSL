#pragma once

#include "CHSLTypedef.h"

namespace cs
{
	
	constexpr float c_pi = 3.14159265f;

	constexpr int imod(int val, int ceil);
	constexpr size_t imod(size_t val, size_t ceil);

	constexpr int floor(float val);
	constexpr int ceil(float val);

	constexpr int imax(int a, int b);
	constexpr int imin(int a, int b);
	constexpr float fmax(float a, float b);
	constexpr float fmin(float a, float b);

	constexpr float fclamp(float val, float min, float max);
	constexpr int iclamp(int val, int min, int max);

	constexpr int iwrap(int val, int min, int max);
	constexpr float fwrap(float val, float max);
	constexpr float fwrap(float val, float min, float max);

	constexpr int iabs(int val);

}