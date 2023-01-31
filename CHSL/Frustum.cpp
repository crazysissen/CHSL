#include "core.h"
#include "Frustum.h"

cs::Frustum::Frustum()
	:
	sides
	{ 
		cs::Plane({ 0, 0, 0 }, { 0, 0, -1 }),
		cs::Plane({ 0, 0, 0 }, { 0, 0, 1 }),
		cs::Plane({ 0, 0, 0 }, { 0, 1, 0 }),
		cs::Plane({ 0, 0, 0 }, { 1, 0, 0 }),
		cs::Plane({ 0, 0, 0 }, { 0, -1, 0 }),
		cs::Plane( { 0, 0, 0 }, { -1, 0, 0 })
	}
{
}

cs::Frustum::Frustum(const cs::Plane& nearPlane, const cs::Plane& farPlane, const cs::Plane& a, const cs::Plane& b, const cs::Plane& c, const cs::Plane& d)
	:
	sides{ nearPlane, farPlane, a, b, c, d }
{
}

cs::Frustum::Frustum(const Frustum& lVal)
	:
	sides{ lVal.sides[0], lVal.sides[1], lVal.sides[2], lVal.sides[3], lVal.sides[4], lVal.sides[5] }
{
}

bool cs::Frustum::Contains(const cs::Vec3& vector)
{
	bool outside = false;

	for (int i = 0; i < 6; i++)
	{
		outside |= sides[i].IsBelow(vector);
	}

	return !outside;
}

bool cs::Frustum::Contains(const cs::Box3& box)
{
	for (int i = 0; i < 6; i++)
	{
		bool outside = false;

		outside |= sides[i].IsBelow(box.position);
		outside |= sides[i].IsBelow(Vec3(box.position.x, box.position.y, box.position.z + box.size.z));
		outside |= sides[i].IsBelow(Vec3(box.position.x, box.position.y + box.size.y, box.position.z));
		outside |= sides[i].IsBelow(Vec3(box.position.x, box.position.y + box.size.y, box.position.z + box.size.z));
		outside |= sides[i].IsBelow(Vec3(box.position.x + box.size.x, box.position.y, box.position.z));
		outside |= sides[i].IsBelow(Vec3(box.position.x + box.size.x, box.position.y + box.size.y, box.position.z));
		outside |= sides[i].IsBelow(Vec3(box.position.x + box.size.x, box.position.y, box.position.z + box.size.z));
		outside |= sides[i].IsBelow(Vec3(box.position.x + box.size.x, box.position.y + box.size.y, box.position.z + box.size.z));

		if (outside)
		{
			return false;
		}
	}

	return true;
}

bool cs::Frustum::Intersects(const cs::Box3& box)
{
	return false;
}

bool cs::Frustum::IntersectsFuzzy(const cs::Box3& box)
{
	for (int i = 0; i < 6; i++)
	{
		bool outside = true;

		outside &= sides[i].IsBelow(box.position);
		outside &= sides[i].IsBelow(Vec3(box.position.x, box.position.y, box.position.z + box.size.z));
		outside &= sides[i].IsBelow(Vec3(box.position.x, box.position.y + box.size.y, box.position.z));
		outside &= sides[i].IsBelow(Vec3(box.position.x, box.position.y + box.size.y, box.position.z + box.size.z));
		outside &= sides[i].IsBelow(Vec3(box.position.x + box.size.x, box.position.y, box.position.z));
		outside &= sides[i].IsBelow(Vec3(box.position.x + box.size.x, box.position.y + box.size.y, box.position.z));
		outside &= sides[i].IsBelow(Vec3(box.position.x + box.size.x, box.position.y, box.position.z + box.size.z));
		outside &= sides[i].IsBelow(Vec3(box.position.x + box.size.x, box.position.y + box.size.y, box.position.z + box.size.z));

		if (outside)
		{
			return false;
		}
	}

	return true;
}

bool cs::Frustum::Intersects(const cs::BoxUnaligned& box)
{
	return false;
}

bool cs::Frustum::IntersectsFuzzy(const cs::BoxUnaligned& box)
{
	return false;
}



cs::ViewFrustum::ViewFrustum()
	:
	Frustum(),
	m_position(0, 0, 0),
	m_orientation(1, 0, 0, 0, 1, 0, 0, 0, 1),
	m_defaultOrigins{ {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0} },
	m_defaultSideDirections{ {0, 1, 0}, {1, 0, 0}, {0, -1, 0}, {-1, 0, 0} }
{
}

cs::ViewFrustum::ViewFrustum(const cs::Vec3& position, const cs::Mat3& direction, float nearPlane, float farPlane, float yAngle, float aspectRatio)
{
	UpdateNearPlane(nearPlane);
	UpdateFarPlane(farPlane);
	UpdateViewAngle(yAngle, aspectRatio);
	SetViewDirection(direction);
	SetPosition(position);
}

cs::ViewFrustum::ViewFrustum(const cs::Vec3& position, const cs::Vec3& angles, float nearPlane, float farPlane, float yAngle, float aspectRatio)
	:
	ViewFrustum(position, Mat::rotation3(angles.x, angles.y, angles.z), nearPlane, farPlane, yAngle, aspectRatio)
{
}

cs::ViewFrustum::ViewFrustum(const ViewFrustum& lVal)
	:
	Frustum(lVal),
	m_position(lVal.m_position),
	m_orientation(lVal.m_orientation),
	m_defaultOrigins{ lVal.m_defaultOrigins[0], lVal.m_defaultOrigins[1], lVal.m_defaultOrigins[2], lVal.m_defaultOrigins[3], lVal.m_defaultOrigins[4], lVal.m_defaultOrigins[5] },
	m_defaultSideDirections{ lVal.m_defaultSideDirections[0], lVal.m_defaultSideDirections[1], lVal.m_defaultSideDirections[2], lVal.m_defaultSideDirections[3] }
{
}

void cs::ViewFrustum::SetPosition(const cs::Vec3& position)
{
	Vec3 diff = position - m_position;
	m_position = position;

	for (int i = 0; i < 6; i++)
	{
		sides[i].SetOrigin(sides[i].GetOrigin() + diff);
	}
}

void cs::ViewFrustum::SetNearPlane(float nearPlane)
{
	UpdateNearPlane(nearPlane);
	sides[0].SetOrigin(m_position + m_orientation * m_defaultOrigins[0]);
}

void cs::ViewFrustum::SetFarPlane(float farPlane)
{
	UpdateFarPlane(farPlane);
	sides[1].SetOrigin(m_position + m_orientation * m_defaultOrigins[1]);
}

void cs::ViewFrustum::SetViewDirection(const cs::Mat3& direction)
{
	m_orientation = direction;

	sides[0].SetOrigin(m_position + m_orientation * m_defaultOrigins[0]);
	sides[0].SetNormal(m_orientation * Vec3(0, 0, -1));

	sides[1].SetOrigin(m_position + m_orientation * m_defaultOrigins[1]);
	sides[1].SetNormal(m_orientation * Vec3(0, 0, 1));

	for (int i = 0; i < 4; i++)
	{
		sides[i + 2].SetOrigin(m_position + m_orientation * m_defaultOrigins[i + 2]);
		sides[i + 2].SetNormal(m_orientation * m_defaultSideDirections[i]);
	}
}

void cs::ViewFrustum::SetViewDirection(const cs::Vec3& angles)
{
	SetViewDirection(Mat::rotation3(angles.x, angles.y, angles.z));
}

void cs::ViewFrustum::SetViewAngle(float yAngle, float aspectRatio)
{
	UpdateViewAngle(yAngle, aspectRatio);

	for (int i = 0; i < 4; i++)
	{
		sides[i + 2].SetOrigin(m_position + m_orientation * m_defaultOrigins[i + 2]);
		sides[i + 2].SetNormal(m_orientation * m_defaultSideDirections[i]);
	}
}

void cs::ViewFrustum::UpdateNearPlane(float nearPlane)
{
	m_defaultOrigins[0] = Vec3(0, 0, nearPlane);
}

void cs::ViewFrustum::UpdateFarPlane(float farPlane)
{
	m_defaultOrigins[1] = Vec3(0, 0, farPlane);
}

void cs::ViewFrustum::UpdateViewDirection(const cs::Mat3& direction)
{
	m_orientation = direction;
}

void cs::ViewFrustum::UpdateViewAngle(float yAngle, float aspectRatio)
{
	Mat3 rY = Mat::rotation3X(yAngle * 0.5f);					// Top of screen
	Mat3 rX = Mat::rotation3Y(yAngle * aspectRatio * 0.5f);	// Left of screen

	// -y
	m_defaultOrigins[4] = rY * Vec3(0, 0, 1);
	m_defaultSideDirections[2] = Vec3(0, -m_defaultOrigins[4].z, m_defaultOrigins[4].y);

	// +y
	m_defaultOrigins[2] = Vec3(0, -m_defaultOrigins[4].y, m_defaultOrigins[4].z);
	m_defaultSideDirections[0] = Vec3(0, m_defaultOrigins[2].z, -m_defaultOrigins[2].y);

	// +x
	m_defaultOrigins[3] = rX * Vec3(0, 0, 1); // -x
	m_defaultSideDirections[1] = Vec3(m_defaultOrigins[3].z, 0, -m_defaultOrigins[3].x);

	// -x
	m_defaultOrigins[5] = Vec3(-m_defaultOrigins[3].x, 0, m_defaultOrigins[3].z);
	m_defaultSideDirections[3] = Vec3(-m_defaultOrigins[5].z, 0, m_defaultOrigins[5].x);
}
