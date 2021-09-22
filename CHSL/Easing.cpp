#include "core.h"

#include "Easing.h"

cs::EaseFunction cs::Ease::getFunction(EaseType easeType)
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

float cs::Ease::linear(float x)
{
	x = cs::fclamp(x, 0.0f, 1.0f);

	return x;
}

float cs::Ease::in(float x)
{
	x = cs::fclamp(x, 0.0f, 1.0f);

	return x * x;
}

float cs::Ease::out(float x)
{
	x = cs::fclamp(x, 0.0f, 1.0f);

	return x * (2 - x);
}

float cs::Ease::inOut(float x)
{
	x = cs::fclamp(x, 0.0f, 1.0f);

	return 3 * x * x - 2 * x * x * x;
}

float cs::Ease::inOutResponsive(float x)
{
	x = 1 - inOut(x);

	return 1 - x * x;
}

float cs::Ease::inSin(float x)
{
	x = cs::fclamp(x, 0.0f, 1.0f) - 1;

	return 1 + sinf(x * c_pi * 0.5f);
}

float cs::Ease::outSin(float x)
{
	x = cs::fclamp(x, 0.0f, 1.0f);

	return sinf(x * c_pi * 0.5f);
}

float cs::Ease::inOutSin(float x)
{
	x = cs::fclamp(x, 0.0f, 1.0f);

	return 0.5f * (1 + sinf((x - 0.5f) * c_pi));
}

float cs::Ease::inCubic(float x)
{
	x = cs::fclamp(x, 0.0f, 1.0f);

	return x * x * x;
}

float cs::Ease::outCubic(float x)
{
	x = cs::fclamp(x, 0.0f, 1.0f) - 1;
	
	return 1 + x * x * x;
}

float cs::Ease::inQuad(float x)
{
	x = cs::fclamp(x, 0.0f, 1.0f);
	x *= x;

	return x * x;
}

float cs::Ease::outQuad(float x)
{
	return 1 - inQuad(1 - x);
}

float cs::Ease::inCircular(float x)
{
	x = cs::fclamp(x, 0.0f, 1.0f);

	return 1 - sqrtf(1 - x * x);
}

float cs::Ease::outCircular(float x)
{
	x = cs::fclamp(x, 0.0f, 1.0f) - 1; // <-- note -1

	return sqrtf(1 - x * x);
}

float cs::Ease::inBounce(float x)
{
	x = cs::fclamp(x, 0.0f, 1.0f);

	return powf(2, 6 * x - 6) * fabs(sinf(x * c_pi * 3.5f));
}

float cs::Ease::outBounce(float x)
{
	x = cs::fclamp(x, 0.0f, 1.0f);

	return 1 - powf(2, x * (-6)) * fabs(cosf(x * c_pi * 3.5f));
}

float cs::Ease::inElastic(float x)
{
	x = cs::fclamp(x, 0.0f, 1.0f);
	float x2 = x * x;

	return x2 * x2 * sinf(x * c_pi * 4.5f);
}

float cs::Ease::outElastic(float x)
{
	x = cs::fclamp(x, 0.0f, 1.0f);
	float x2 = x * x;

	return 1 - x2 * x2 * cosf(x * c_pi * 4.5f);
}
