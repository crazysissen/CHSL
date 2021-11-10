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
	m_z(0, 0, 1)
{
}

bool cs::Box::Raycast(const Line3& line, float& out) const
{
	return false;
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
