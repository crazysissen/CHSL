#define CHSL_LINEAR
#include <CHSL.h>

#include <CHSL/ShuffleMap.h>
#include <CHSL/RBTree.h>
#include <CHSL/List.h>
#include <CHSL/Quadtree.h>
#include <CHSL/Octree.h>
#include <CHSL/Frustum.h>



int main()
{
	Matrix3<float> m3f1 =
	{
		1.0f, 0.5f, -1.0f,
		-2.0f, -1.5f, 3.0f,
		1.5f, 2.5f, -0.5f
	};

	Matrix3<float> m3f2 =
	{
		2.0f, -3.0f, 1.0f,
		0.5f, 0.5f, -1.5f,
		-1.0f, -3.0f, 2.5f
	};

	Matrix3<double> m3d1 =
	{
		1.0, 0.5, -1.0,
		-2.0, -1.5, 3.0,
		1.5, 2.5, -0.5
	};

	Matrix3<double> m3d2 =
	{
		2.0, -3.0, 1.0,
		0.5, 0.5, -1.5,
		-1.0, -3.0, 2.5
	};

	Matrix3<float> m3f3 = m3f1 * m3f2; 
	Matrix3<double> m3d3 = m3d1 * m3d2;

	return 0; 
}