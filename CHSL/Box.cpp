#include "core.h"
#include "Box.h"

#include <limits>

cs::BoxUnaligned::BoxUnaligned(Vec3 center, Vec3 xV, Vec3 yV, Vec3 zV)
	:
	m_origin(center),
	m_x(xV.Normalized()),
	m_y(yV.Normalized()),
	m_z(zV.Normalized()),
	m_w(xV.Length()),
	m_h(yV.Length()),
	m_d(zV.Length())
{
}

cs::BoxUnaligned::BoxUnaligned(Vec3 center, float width, float height, float depth)
	:
	m_origin(center),
	m_x(1, 0, 0),
	m_y(0, 1, 0),
	m_z(0, 0, 1),
	m_w(width),
	m_h(height),
	m_d(depth)
{
}

cs::BoxUnaligned::BoxUnaligned(Vec3 center, float width, float height, float depth, float rX, float rY, float rZ)
	:
	BoxUnaligned(center, width, height, depth)
{
	Mat3 r = Mat::rotation3(rX, rY, rZ);
	m_x = r * m_x;
	m_y = r * m_y;
	m_z = r * m_z;
}

bool cs::BoxUnaligned::Raycast(const Line3& line, HitInfo& out) const
{
	constexpr float epsilon = 1.0 / 65536;

	const Vec3* a[] = { &m_x, &m_y, &m_z }; // Side directions
	const float h[] = { m_w, m_h, m_d };		// Halfsides

	// Collision check

	float tMin = -FLT_MAX;
	float tMax = FLT_MAX;

	Vec3 tMinNormal = { 0, 0, 0 };
	Vec3 tMaxNormal = { 0, 0, 0 };

	Vec3 p = m_origin - line.GetOrigin();

	for (int i = 0; i < 3; ++i)
	{
		float e = a[i]->Dot(p);
		float f = a[i]->Dot(line.GetDirection());

		if (fabs(f) > epsilon)
		{
			float fInv = 1.0f / f;

			float t1 =
				(e + h[i]) * fInv;

			float t2 =
				(e - h[i]) * fInv;

			Vec3 n = *(a[i]);
			Vec3 nr = n * -1;

			if (t1 > t2)
			{
				float temp = t1;
				t1 = t2;
				t2 = temp;

				Vec3 tempN = n;
				n = nr;
				nr = tempN;
			}

			if (t1 > tMin)
			{
				tMin = t1;
				tMinNormal = n;
			}

			if (t2 < tMax)
			{
				tMax = t2;
				tMaxNormal = nr;
			}

			if (tMin > tMax || tMax < 0)
			{
				return false;
			}
		}
		else if (-e - h[i] > 0 || -e + h[i] < 0) // If parallel
		{
			return false;
		}
	}

	if (tMin > 0)
	{
		out.t = tMin;
		out.normal = tMinNormal;
	}
	else
	{
		out.t = tMax;
		out.normal = tMaxNormal;
	}

	return true;
}

bool cs::BoxUnaligned::Intersection(const Line3& line, Vec3& out) const
{
	HitInfo h;

	if (Raycast(line, h))
	{
		out = line(h.t);
		return true;
	}

	return false;
}