#include "core.h"
#include "Box.h"

#include <limits>

cs::Box::Box(Vec3 center, Vec3 xV, Vec3 yV, Vec3 zV)
	:
	m_center(center),
	m_x(xV),
	m_y(yV),
	m_z(zV)
{
}

cs::Box::Box(Vec3 center, float width, float height, float depth)
	:
	m_center(center),
	m_x(1, 0, 0),
	m_y(0, 1, 0),
	m_z(0, 0, 1),
	m_w(width),
	m_h(height),
	m_d(depth)
{
}

cs::Box::Box(Vec3 center, float width, float height, float depth, float rX, float rY, float rZ)
	:
	Box(center, width, height, depth)
{
	Mat3 r = Mat::rotation3(rX, rY, rZ);
	m_x = r * m_x;
	m_y = r * m_y;
	m_z = r * m_z;
}

bool cs::Box::Raycast(const Line3& line, HitInfo& out) const
{
	constexpr float epsilon = 1.0f / 65536;

	const Vec3* a[] = { &m_x, &m_y, &m_z }; // Side directions
	const float h[] = { m_w, m_h, m_d }; // Halfsides

	// Collision check

	float tMin = -FLT_MAX;
	float tMax = FLT_MAX;
	Vec3 nMin = { 0, 0, 0 };


	Vec3 center = m_center - line.GetOrigin();

	for (int i = 0; i < 3; ++i)
	{
		float e = a[i]->Dot3(center);
		float f = a[i]->Dot3(line.GetDirection());

		if (fabs(f) > epsilon)
		{
			float fInv = 1.0f / f;
			bool swap = fInv > 0;

			float t1 = 
				!swap * (e + h[i]) * fInv +
				swap  *	(e - h[i]) * fInv;

			float t2 =
				swap  *	(e + h[i]) * fInv +
				!swap * (e - h[i]) * fInv;

			if (t1 > tMin)
			{
				tMin = t1;
				nMin = swap ?
					*a[i] :
					-*a[i];
			}

			if (t1 < tMax)
			{
				tMax = t2;
			}

			if (tMin > tMax || tMax < 0 || tMin < 0)
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
		out.normal = nMin;
		return true;
	}

	return false;
}

bool cs::Box::Intersection(const Line3& line, Vec3& out) const
{
	HitInfo h;

	if (Raycast(line, h))
	{
		out = line(h.t);
		return true;
	}

	return false;
}