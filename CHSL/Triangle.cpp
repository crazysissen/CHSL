#include "core.h"
#include "Triangle.h"

cs::Triangle::Triangle(Vec3 v1, Vec3 v2, Vec3 v3)
    :
    m_vertices{ v1, v2, v3 }
{
}

bool cs::Triangle::Raycast(const Line3& line, HitInfo& out) const
{
	constexpr float epsilon = 1.0 / 65536;

	Vec3 e1 = m_vertices[1] - m_vertices[0];
	Vec3 e2 = m_vertices[2] - m_vertices[0];

	Vec3 q = line.GetDirection().Cross(e2);

	float a = e1.Dot3(q);

	if (a < epsilon && a > -epsilon)
	{
		return false;
	}

	float f = 1.0f / a;

	Vec3 s = line.GetOrigin() - m_vertices[0];
	float u = f * s.Dot3(q);

	if (u < 0)
	{
		return false;
	}

	Vec3 r = s.Cross(e1);
	float v = f * line.GetDirection().Dot3(r);

	if (v < 0 || u + v > 1)
	{
		return false;
	}

	out.t = f * e2.Dot3(r);
	out.normal = (e1.Cross(e2) * -1).Normalized3();
	out.u = u;
	out.v = v;

	return out.t > 0;
}
