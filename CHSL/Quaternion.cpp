#include "core.h"
#include "Quaternion.h"

cs::Quaternion::Quaternion()	
	: m_x(0), m_y(0), m_z(0), m_w(1)
{
}

cs::Quaternion::Quaternion(float x, float y, float z, float w)	
	: m_x(x), m_y(y), m_z(z), m_w(w)
{
}

cs::Quaternion::Quaternion(const Quaternion& other)	
	: m_x(other.m_x), m_y(other.m_y), m_z(other.m_z), m_w(other.m_w)
{
}

cs::Quaternion cs::Quaternion::operator*(const Quaternion&)
{
	return Quaternion();
}

cs::Quaternion cs::Quaternion::operator+(const Quaternion&)
{
	return Quaternion();
}
