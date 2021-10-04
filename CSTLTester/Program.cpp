#include <CHSL.h>

#include <iostream>
#include <CHSL/RBTree.h>
#include <CHSL/ShuffleMap.h>

//class Test
//{
//public:
//	Test(int& ref)
//	{
//		a = (T*)malloc(sizeof(T) * 10);
//		for (int i = 0; i < 10; ++i)
//		{
//			a[i] = { ref };
//		}
//	}
//
//private:
//	struct T
//	{
//		int r;
//	};
//
//	T* a;
//};

int GetR(int max)
{
	static cs::Random r;

	return r.Get(max);
}

int main()
{
	cs::ShuffleMap<float, int> map;

	uint id = map.Add(0.5f, 1);
	map.Add(0.6f, 2);
	map.Add(0.4f, 3);
	map.Add(0.45f, 4);
	map.Add(0.6f, 5);
	map.Add(0.6f, 6);
	map.Add(0.7f, 7);

	map.Shuffle(0.5f, id, 0.5f);

	map.Delete(0.5f, id);

	return 0;
}