#include "core.h"

#include "Easing.h"

cs::EaseFunction cs::ease::getFunction(EaseType easeType)
{
	if (easeType < 0 || easeType >= EaseTypeCount)
	{
		return linear;
	}

	static EaseFunction functions[] =
	{
		linear,
		in,
		out,
		inOut,
		inOutResponsive,

		inSin,
		outSin,
		inOutSin,

		inCubic,
		outCubic,
		
		inQuad,
		outQuad,

		inCircular,
		outCircular,

		inBounce,
		outBounce,

		inElastic,
		outElastic
	};

	return functions[easeType];
}

float cs::ease::linear(float x)
{
	x = cs::fclamp(x, 0.0f, 1.0f);

	return x;
}

float cs::ease::in(float x)
{
	x = cs::fclamp(x, 0.0f, 1.0f);

	return x * x;
}

float cs::ease::out(float x)
{
	x = cs::fclamp(x, 0.0f, 1.0f);

	return x * (2 - x);
}

float cs::ease::inOut(float x)
{
	x = cs::fclamp(x, 0.0f, 1.0f);

	return 3 * x * x - 2 * x * x * x;
}

float cs::ease::inOutResponsive(float x)
{
	x = 1 - inOut(x);

	return 1 - x * x;
}

float cs::ease::inSin(float x)
{
	x = cs::fclamp(x, 0.0f, 1.0f) - 1;

	return 1 + sinf(x * c_pi * 0.5f);
}

float cs::ease::outSin(float x)
{
	x = cs::fclamp(x, 0.0f, 1.0f);

	return sinf(x * c_pi * 0.5f);
}

float cs::ease::inOutSin(float x)
{
	x = cs::fclamp(x, 0.0f, 1.0f);

	return 0.5f * (1 + sinf((x - 0.5f) * c_pi));
}

float cs::ease::inCubic(float x)
{
	x = cs::fclamp(x, 0.0f, 1.0f);

	return x * x * x;
}

float cs::ease::outCubic(float x)
{
	x = cs::fclamp(x, 0.0f, 1.0f) - 1;
	
	return 1 + x * x * x;
}

float cs::ease::inQuad(float x)
{
	x = cs::fclamp(x, 0.0f, 1.0f);
	x *= x;

	return x * x;
}

float cs::ease::outQuad(float x)
{
	return 1 - inQuad(1 - x);
}

float cs::ease::inCircular(float x)
{
	x = cs::fclamp(x, 0.0f, 1.0f);

	return 1 - sqrtf(1 - x * x);
}

float cs::ease::outCircular(float x)
{
	x = cs::fclamp(x, 0.0f, 1.0f) - 1; // <-- note -1

	return sqrtf(1 - x * x);
}

float cs::ease::inBounce(float x)
{
	x = cs::fclamp(x, 0.0f, 1.0f);

	return powf(2, 6 * x - 6) * fabs(sinf(x * c_pi * 3.5f));
}

float cs::ease::outBounce(float x)
{
	x = cs::fclamp(x, 0.0f, 1.0f);

	return 1 - powf(2, x * (-6)) * fabs(cosf(x * c_pi * 3.5f));
}

float cs::ease::inElastic(float x)
{
	x = cs::fclamp(x, 0.0f, 1.0f);
	float x2 = x * x;

	return x2 * x2 * sinf(x * c_pi * 4.5f);
}

float cs::ease::outElastic(float x)
{
	x = cs::fclamp(x, 0.0f, 1.0f);
	float x2 = x * x;

	return 1 - x2 * x2 * cosf(x * c_pi * 4.5f);
}
