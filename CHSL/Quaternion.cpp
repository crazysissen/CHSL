#include "core.h"
#include "Quaternion.h"

inline cs::Quaternion::Quaternion()	
	: m_x(0), m_y(0), m_z(0), m_w(1)
{
}

cs::Quaternion::Quaternion(Vec4 components)
	: m_vector(components)
{
}

inline cs::Quaternion::Quaternion(cs::Vec3 imaginary, float real)
	: m_imaginary(imaginary), m_w(real)
{
}

inline cs::Quaternion::Quaternion(float x, float y, float z, float w)	
	: m_x(x), m_y(y), m_z(z), m_w(w)
{
}

inline cs::Quaternion::Quaternion(const Quaternion& other)	
	: m_x(other.m_x), m_y(other.m_y), m_z(other.m_z), m_w(other.m_w)
{
}

inline cs::Quaternion cs::Quaternion::Conjugate()
{
	return Quaternion(-m_imaginary, m_w);
}

inline cs::Quaternion cs::Quaternion::Normal()
{
	float in = 1.0f / Norm();
	return Quaternion(m_x * in, m_y * in, m_z * in, m_w * in);
}

inline cs::Quaternion cs::Quaternion::Inverse()
{
	float n = Norm();
	float isn = 1.0f / (n * n);
	return Quaternion(m_x * -isn, m_y * -isn, m_z * -isn, m_w * isn);
}

inline float cs::Quaternion::Norm()
{
	return std::sqrtf(m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w);
}

inline cs::Mat4 cs::Quaternion::Matrix()
{
	return GetMatrix(2.0f);
}

inline cs::Mat4 cs::Quaternion::MatrixUnrestricted()
{
	float n = Norm();
	float s = 2.0f / (n * n);
	return GetMatrix(s);
}

inline cs::Quaternion& cs::Quaternion::ConjugateThis()
{
	m_imaginary = -m_imaginary;
	return *this;
}

inline cs::Quaternion& cs::Quaternion::NormalizeThis()
{
	float in = 1.0f / Norm();
	m_vector *= in;
	return *this;
}

inline cs::Quaternion& cs::Quaternion::InvertThis()
{
	float n = Norm();
	float isn = 1.0f / (n * n);
	m_imaginary *= -isn;
	m_w *= isn;
	return *this;
}

inline cs::Vec3 cs::Quaternion::operator*(Vec3 other)
{
	return (*this * Quaternion(other, 1.0f) * this->Conjugate()).m_imaginary;
}

inline cs::Vec4 cs::Quaternion::operator*(Vec4 other)
{
	return (*this * Quaternion(other) * this->Conjugate()).m_vector;
}

inline cs::Quaternion cs::Quaternion::operator*(Quaternion other)
{
	return Quaternion(
		m_imaginary ^ other.m_imaginary + m_imaginary * other.m_w + other.m_imaginary * m_w,
		m_w * other.m_w - m_imaginary * other.m_imaginary
	);
}

inline cs::Quaternion cs::Quaternion::operator*(float scalar)
{
	return Quaternion(
		m_x * scalar,
		m_y * scalar,
		m_z * scalar,
		m_w * scalar
	);
}

inline cs::Quaternion cs::Quaternion::operator+(Quaternion other)
{
	return Quaternion(
		m_x + other.m_x,
		m_y + other.m_y,
		m_z + other.m_z,
		m_w + other.m_w
	);
}

inline cs::Quaternion cs::Quaternion::GetIdentity()
{
	// Gives the identity
	return Quaternion();
}

inline cs::Quaternion cs::Quaternion::GetAxis(cs::Vec3 axis, float radians)
{
	return Quaternion(axis * std::sin(radians), std::cos(radians));
}

cs::Quaternion cs::Quaternion::GetDeconstruct(Mat3 matrix)
{
	return Quaternion();
}

inline cs::Mat4 cs::Quaternion::GetMatrix(float s)
{
	float x2 = m_x * m_x;
	float xy = m_x * m_y;
	float xz = m_x * m_z;
	float xw = m_x * m_w;
	float y2 = m_y * m_y;
	float yz = m_y * m_z;
	float yw = m_y * m_w;
	float z2 = m_z * m_z;
	float zw = m_z * m_w;

	return Mat4(
		1.0f - s * (y2 + z2),	s * (xy - zw),			s *	(xz + yw),			0.0f,
		s * (xy + zw),			1.0f - s * (x2 + z2),	s * (yz - xw),			0.0f,
		s * (xz - yw),			s * (yz + xw),			1.0f - s * (x2 + y2),	0.0f,
		0.0f,					0.0f,					0.0f,					1.0f
	);
}
