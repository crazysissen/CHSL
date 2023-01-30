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
	Mat4 m = Mat::rotation3Y(cs::c_pi * 0.5f);
	Quaternion q1 = Quaternion::GetAxis({ 0, 1, 0 }, cs::c_pi * 0.5f);
	Quaternion q2 = Quaternion::GetAxis({ 0, 1, 0 }, cs::c_pi);
	Quaternion q3 = Quaternion::GetSlerp(q1, q2, 0.5f);

	Vec3 v1(2, 0, 0); 
	Vec3 v2(2, 0, 0);
	Vec3 v3(2, 0, 0);
	v1 = q1 * v1;
	v2 = q2 * v2;
	v3 = q3 * v3;

	return 0; 
}