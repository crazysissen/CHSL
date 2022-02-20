#define CHSL_LINEAR
#include <CHSL.h>

#include <iostream>
#include <chrono>
#include <map>
#include <CHSL/ShuffleMap.h>
#include <CHSL/RBTree.h>
#include <CHSL/List.h>



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
	cs::List<int> a;

	a.Add(1);
	a.Add(2);
	a.Add(3);

	for (int& i : a)
	{
		std::cout << i << '\n';
	}
}