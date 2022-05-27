#define CHSL_LINEAR
#include <CHSL.h>

#include <CHSL/ShuffleMap.h>
#include <CHSL/RBTree.h>
#include <CHSL/List.h>
#include <CHSL/Quadtree.h>
#include <CHSL/Octree.h>
#include <CHSL/Frustum.h>



int GetR(int max)
{
	static cs::Random r;

	return r.Get(max);
}

float GetRF(float min, float max)
{
	static cs::Random r;

	return r.Getf(min, max);
}

bool BTSelector(const cs::Box& r, void* d)
{
	return ((cs::Frustum*)d)->IntersectsFuzzy(r);
}

bool BCSelector(const cs::Box& r, void* d)
{
	return ((cs::Frustum*)d)->Contains(r);
}

int predicate(const int& a)
{
	return a;
}

int main()
{
	cs::List<int> l;

	for (int i = 0; i < 100; i++)
		l.Add(i * 2);

	auto pred = [](const int& a) -> int
	{
		return a;
	};

	int i = l.SearchBinary<int>(11, pred);
}