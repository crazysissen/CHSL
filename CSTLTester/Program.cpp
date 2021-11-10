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
	

	return 0;
}