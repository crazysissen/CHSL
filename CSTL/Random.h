#pragma once

#include <random>

namespace cs 
{ 
	class Random
	{
		typedef std::mt19937 RandomEngine;

		typedef unsigned char byte;
		typedef unsigned int uint;

	private:
		RandomEngine* engine;

	public:
		Random();
		Random(uint seed);
		~Random();

		int Get(int max);			// random int 0-max (uninclusive)
		int Get(int min, int max);	// random int min-max (inclusive, uninclusive)

		uint GetUnsigned();
		uint GetUnsigned(uint max);	// random uint 0-max (uninclusive)

		float Getf();						// random float 0.0-1.0
		float Getf(float min, float max);	// random float min-max

		float GetRadian();

		float GetNormal(float mean, float diversion);

		bool Getb();	// random bool true-false

		byte* FillBytes(byte* target, uint ammount);	// fill array of bytes

	private:
		void InitRandom(uint seed);

	};
}