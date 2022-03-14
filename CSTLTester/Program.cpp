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

int main()
{
	cs::List<cs::Box> l;
	cs::Octree<float, cs::Box> q({ -1000, -1000, -1000, 2000, 2000, 2000 }, 16);


	
	cs::ViewFrustum view(
		Vec3(),
		Vec3(),
		0,
		1000,
		0.1f,
		1.0f
	);

	Vec3 v(0, 0, 1);

	bool hit = view.Contains(v);



	const int c = 100000;

	float* floats = new float[c];
	cs::Box* boxes = new cs::Box[c];

	for (int i = 0; i < c; i++)
	{
		floats[i] = GetRF(0, 1);
		boxes[i] = cs::Box(GetRF(-1000, 980), GetRF(-1000, 980), GetRF(-1000, 980), GetRF(1, 20), GetRF(1, 20), GetRF(1, 20));
	}

	for (int i = 0; i < c; i++)
	{
		l.Add(boxes[i]);
	}

	for (int i = 0; i < c; i++)
	{
		q.Add(floats[i], boxes[i]);
	}



	cs::Timer t;
	float lTime = 0;
	float qTime = 0;
	float qError = 0;

	for (int i = 0; i < 100; i++)
	{

		int lCount = 0;
		int qCount = 0;

		cs::ViewFrustum view(
			cs::Vec3(GetRF(-1000, 980), GetRF(-1000, 980), GetRF(-1000, 980)),
			cs::Vec3(GetRF(-3, 3), GetRF(-3, 3), GetRF(-3, 3)),
			0.01f,
			500.0f,
			cs::c_pi * 0.5f
		);

		t.Lap();

		for (int j = 0; j < c; j++)
		{
			if (BTSelector(l[j], &view))
			{
				lCount++;
			}
		}

		lTime += t.Lap();

		q.SearchFuzzy(&view, BTSelector);
		for (float f : q)
		{
			qCount++;
		}

		qTime += t.Lap();
		qError += (float)(qCount - lCount) / lCount;
	}

	float lAverage = lTime / 100;
	float qAverage = qTime / 100;
	float qErrorAverage = qError / 100;
}