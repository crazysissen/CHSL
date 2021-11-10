#include "core.h"
#include "Box.h"

cs::Box::Box(Vec3 center, Vec3 xV, Vec3 yV, Vec3 zV)
	:
	m_center(center),
	m_x(xV),
	m_y(yV),
	m_z(zV)
{
}

cs::Box::Box(Vec3 center, float width, float height, float depth, float rX, float rY, float rZ)
	:
	m_center(center),
	m_x(1, 0, 0),
	m_y(0, 1, 0),
	m_z(0, 0, 1),
	m_w(width),
	m_h(height),
	m_d(depth)
{
	Mat3 r = Mat::rotation3(rX, rY, rZ);
	m_x = r * m_x;
	m_y = r * m_y;
	m_z = r * m_z;
}

bool cs::Box::Raycast(const Line3& line, float& out) const
{
	const Vec3* d[] = { &m_x, &m_y, &m_z };
	const float* f[] = { &m_w, &m_h, &m_d };

	// Parallel check

	for (int i = 0; i < 3; i++)
	{
		if (d[i]->Parallel3(line.GetDirection()))
		{
			for (int j = 1; j < 3; j++)
			{
				int index = imod(i + j, 3);
				float parallelDist = d[index]->Dot3(m_center - line.GetOrigin());

				if (parallelDist > *f[index])
				{
					return false;
				}
			}

			return true;
		}
	}


}

bool cs::Box::Intersection(const Line3& line, Vec3& out) const
{
	float t;

	if (Raycast(line, t))
	{
		out = line(t);
		return true;
	}

	return false;
}
