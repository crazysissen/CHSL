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
	constexpr float variability = 0.2f;
	constexpr float rootValue = 0.5f;
	constexpr int elements = 200000;
	constexpr int switches = 100000;

	

	cs::Random r(0);

	float* switchValues = new float[switches];
	for (int i = 0; i < switches; i++)
	{
		switchValues[i] = rootValue + r.Getf(-variability, variability);
	}



	// First test

	cs::ShuffleMap<float, int> sMap;
	int id = sMap.Add(rootValue, 0);
	cs::Random r1(1337);
	cs::Timer t1;

	for (int i = 0; i < elements; ++i)
	{
		sMap.Add(r1.Getf(), 0);
	}

	float timeAddSMap = t1.Lap();
	float previousValue = rootValue;

	for (int i = 0; i < switches; i++)
	{
		sMap.Shuffle(previousValue, id, switchValues[i]);
		previousValue = switchValues[i];
	}

	float timeShuffleSMap = t1.Lap();



	// Second test

	std::multimap<float, int> mMap;
	mMap.insert({ rootValue, 0 });
	cs::Random r2(1337);
	cs::Timer t2;

	for (int i = 0; i < elements; ++i)
	{
		mMap.insert({ r2.Getf(), 0 });
	}

	float timeAddMMap = t2.Lap();
	previousValue = rootValue;

	for (int i = 0; i < switches; i++)
	{
		mMap.erase(previousValue);
		mMap.insert({ switchValues[i], 0 });
	}

	float timeShuffleMMap = t2.Lap();



	std::cout << "Time Add SMap: " << timeAddSMap << "\n";
	std::cout << "Time Shuffle SMap: " << timeShuffleSMap << "\n\n";
	std::cout << "Time Add MMap: " << timeAddMMap << "\n";
	std::cout << "Time Shuffle MMap: " << timeShuffleMMap << "\n";

	std::cin.get();



	return 0;
}