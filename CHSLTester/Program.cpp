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
	Quaternion q = Quaternion::GetEuler(0.5f * cs::c_pi, 0.5f * cs::c_pi, 0.0f);
	Vec3 v = { 0, 0, 1 };
	Vec3 vr = q * v;

	return 0;
}