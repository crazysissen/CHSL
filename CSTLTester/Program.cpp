#define CHSL_LINEAR
#include <CHSL.h>

#include <iostream>
#include <chrono>
#include <map>
#include <CHSL/ShuffleMap.h>
#include <CHSL/RBTree.h>



int GetR(int max)
{
	static cs::Random r;

	return r.Get(max);
}

float GetRF()
{
	static cs::Random r;

	return r.Getf();
}

int main()
{
	Mat3 a =
	{
		3, 0, 2,
		2, 0, -2,
		0, 1, 1
	};

	Mat3 i = a.Inverse();

	Vec3 b;

	return 0;
}