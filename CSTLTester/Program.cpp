#include <CHSL.h>

#include <iostream>

class Test
{
public:
	Test(int& ref)
	{
		a = (T*)malloc(sizeof(T) * 10);
		for (int i = 0; i < 10; ++i)
		{
			a[i] = { ref };
		}
	}

private:
	struct T
	{
		int r;
	};

	T* a;
};

int GetR(int max)
{
	static cs::Random r;

	return r.Get(max);
}

int main()
{
	cs::Color c(1.0f, 0.5f, 1.0f);

	cs::Random r;
	cs::Indexer<int, 32> indexer;
	std::vector<int> indices;

	for (int i = 0; i < 20; ++i)
	{
		indices.push_back(indexer.Add(i));
	}

	std::random_shuffle(indices.begin(), indices.end(), GetR);

	for (int i = 0; i < 16; ++i)
	{
		int index = indices.back();
		indices.pop_back();

		indexer.Remove(index);
	}

	for (int j : indexer)
	{
		std::cout << j << '\n';
	}

	
	return 0;
}