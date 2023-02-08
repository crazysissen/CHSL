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

	Vec3 a = { 0, 0, 1 };
	Vec3 b = { -1, 0, 0 };

	Quaternion q = Quaternion::GetDirection(b);

	Vec3 c = q * b;

	return 0;
}