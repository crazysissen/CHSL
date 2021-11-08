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
	cs::Line2 a({ 0, 0 }, { 1, 1 });
	cs::Line2 b({ -1, -1 }, { 3, 3 });

	bool e = a.Equivalent(b);

	return 0;
}