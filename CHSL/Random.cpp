#include "core.h"

#include <ctime>
#include <random>

#include "Random.h"

namespace
{

	std::uniform_real_distribution<float> standardFloatDist, standardRadianDist;
	std::uniform_int_distribution<short> standardByteDist;
	std::uniform_int_distribution<int> standardBoolDist;
	std::uniform_int_distribution<unsigned int> standardUnsignedDist;

}

cs::Random::Random()
{
	InitRandom((uint)time(0));
}

cs::Random::Random(uint seed)
{
	InitRandom(seed);
}

cs::Random::~Random()
{
	delete(engine);
}

void cs::Random::InitRandom(uint seed)
{
	static bool init = false;

	engine = new RandomEngine();
	engine->seed(seed);

	if (!init)
	{
		init = true;

		standardFloatDist = std::uniform_real_distribution<float>(0.0f, 1.0f);
		standardRadianDist = std::uniform_real_distribution<float>(-(float)std::_Pi, (float)std::_Pi);
		standardBoolDist = std::uniform_int_distribution<int>(0, 1);
		standardUnsignedDist = std::uniform_int_distribution<unsigned int>(0, UINT_MAX);
		standardByteDist = std::uniform_int_distribution<short>(0, 255);
	}
}

int cs::Random::Get(int max)
{
	return Get(0, max - 1);
}

int cs::Random::Get(int min, int max)
{
	std::uniform_int_distribution<int> randomDist(min, max - 1);
	return randomDist(*engine);
}

uint cs::Random::GetUnsigned()
{
	return uint();
}

uint cs::Random::GetUnsigned(uint max)
{
	std::uniform_int_distribution<uint> randomDist(0, max - 1);
	return randomDist(*engine);
}

float cs::Random::Getf()
{
	return (standardFloatDist)(*engine);
}

// Get float [ min - max ]
float cs::Random::Getf(float min, float max)
{
	std::uniform_real_distribution<float> randomDist(min, max);
	return randomDist(*engine);
}

float cs::Random::GetRadian()
{
	return (standardRadianDist)(*engine);
}

float cs::Random::GetNormal(float mean, float diversion)
{
	std::normal_distribution<float> randomDist(mean, diversion);
	return randomDist(*engine);
}

bool cs::Random::Getb()
{
	return (standardBoolDist)(*engine) == 0;
}

byte* cs::Random::FillBytes(byte* target, uint ammount)
{
	for (uint i = 0; i < ammount; ++i)
	{
		target[i] = (byte)(standardByteDist)(*engine);
	}

	return target;
}

