#define CHSL_LINEAR
#include <CHSL.h>

#include <CHSL/ShuffleMap.h>
#include <CHSL/RBTree.h>
#include <CHSL/List.h>
#include <CHSL/Quadtree.h>
#include <CHSL/Octree.h>
#include <CHSL/Frustum.h>



#define TEST_COUNT 5000000

int main()
{
	cs::Random r;

	Mat4* m0 = new Mat4[TEST_COUNT];
	Mat4* m1 = new Mat4[TEST_COUNT];
	Mat4* m2 = new Mat4[TEST_COUNT];

	for (int i = 0; i < TEST_COUNT; i++)
	{
		m0[i] = Mat4(
			r.Getf(), r.Getf(), r.Getf(), r.Getf(),
			r.Getf(), r.Getf(), r.Getf(), r.Getf(),
			r.Getf(), r.Getf(), r.Getf(), r.Getf(),
			r.Getf(), r.Getf(), r.Getf(), r.Getf()
		);

		m0[i] = Mat4(
			r.Getf(), r.Getf(), r.Getf(), r.Getf(),
			r.Getf(), r.Getf(), r.Getf(), r.Getf(),
			r.Getf(), r.Getf(), r.Getf(), r.Getf(),
			r.Getf(), r.Getf(), r.Getf(), r.Getf()
		);
	}

	cs::Timer timer;

	for (int i = 0; i < TEST_COUNT; i++)
	{
		m2[i] = m0[i] * m1[i];
	}

	float time = timer.Lap();

	std::cout << time << "\n";

	/*Vec4 vector = Vec4(r.Getf(), r.Getf(), r.Getf(), r.Getf());
	Mat4 matrix = Mat4(
		r.Getf(), r.Getf(), r.Getf(), r.Getf(),
		r.Getf(), r.Getf(), r.Getf(), r.Getf(),
		r.Getf(), r.Getf(), r.Getf(), r.Getf(),
		r.Getf(), r.Getf(), r.Getf(), r.Getf()
	);*/

	//Vec4 result = matrix * vector;
	//Vec4d control = (Mat4d)matrix * (Vec4d)vector;

	return 0;
}