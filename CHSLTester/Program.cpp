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
	Quaternion q = Quaternion::GetDirection(Vec3(0, 0.5f, 0.5f).Normalized());

	Vec3 v = q * Vec3(0, 0, 1);

	return 0;
}