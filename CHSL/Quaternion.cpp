#include "core.h"
#include "Quaternion.h"

cs::Quaternion::Quaternion()	
	: m_x(0), m_y(0), m_z(0), m_w(1)
{
}

cs::Quaternion::Quaternion(const Vec4& components)
	: m_vector(components)
{
}

cs::Quaternion::Quaternion(const Vec3& imaginary, float real)
	: m_imaginary(imaginary), m_w(real)
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

cs::Quaternion cs::Quaternion::Conjugate() const
{
	return Quaternion(-m_imaginary, m_w);
}

cs::Quaternion cs::Quaternion::Normal() const
{
	float in = 1.0f / Norm();
	return Quaternion(m_x * in, m_y * in, m_z * in, m_w * in);
}

cs::Quaternion cs::Quaternion::Inverse() const
{
	float n = Norm();
	float isn = 1.0f / (n * n);
	return Quaternion(m_x * -isn, m_y * -isn, m_z * -isn, m_w * isn);
}

float cs::Quaternion::Norm() const
{
	return std::sqrtf(m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w);
}

cs::Mat4 cs::Quaternion::Matrix() const
{
	return GetMatrix(2.0f);
}

cs::Mat4 cs::Quaternion::MatrixUnrestricted() const
{
	float n = Norm();
	float s = 2.0f / (n * n);
	return GetMatrix(s);
}

cs::Quaternion& cs::Quaternion::ConjugateThis()
{
	m_imaginary = -m_imaginary;
	return *this;
}

cs::Quaternion& cs::Quaternion::NormalizeThis()
{
	float in = 1.0f / Norm();
	m_vector *= in;
	return *this;
}

cs::Quaternion& cs::Quaternion::InvertThis()
{
	float n = Norm();
	float isn = 1.0f / (n * n);
	m_imaginary *= -isn;
	m_w *= isn;
	return *this;
}

cs::Vec3 cs::Quaternion::operator*(const Vec3& other) const
{
	return (*this * Quaternion(other, 1.0f) * this->Conjugate()).m_imaginary;
}

cs::Vec4 cs::Quaternion::operator*(const Vec4& other) const
{
	return (*this * Quaternion(other) * this->Conjugate()).m_vector;
}

cs::Quaternion cs::Quaternion::operator*(const Quaternion& other) const
{
	return Quaternion(
		m_imaginary % other.m_imaginary + m_imaginary * other.m_w + other.m_imaginary * m_w,
		m_w * other.m_w - m_imaginary * other.m_imaginary
	);
}

cs::Quaternion cs::Quaternion::operator*(float scalar) const
{
	return Quaternion(
		m_x * scalar,
		m_y * scalar,
		m_z * scalar,
		m_w * scalar
	);
}

cs::Quaternion cs::Quaternion::operator+(const Quaternion& other) const
{
	return Quaternion(
		m_x + other.m_x,
		m_y + other.m_y,
		m_z + other.m_z,
		m_w + other.m_w
	);
}

cs::Quaternion cs::Quaternion::GetIdentity()
{
	// Gives the identity
	return Quaternion();
}

cs::Quaternion cs::Quaternion::GetAxis(const Vec3& axis, float radians)
{
	return Quaternion(axis.Normalized() * std::sin(radians * 0.5f), std::cos(radians * 0.5f));
}

cs::Quaternion cs::Quaternion::GetAxisNormalized(const Vec3& axis, float radians)
{
	return Quaternion(axis * std::sin(radians * 0.5f), std::cos(radians * 0.5f));
}

cs::Quaternion cs::Quaternion::GetDeconstruct(const Mat3& matrix)
{
	return GetDeconstruct(Mat4(matrix));
}

cs::Quaternion cs::Quaternion::GetFromTo(const Vec3& from, const Vec3& to)
{
	float comp = std::sqrtf(2.0f + from * to);

	return Quaternion(
		(from % to) * (1.0f / comp),
		comp * 0.5f
	);
}

cs::Quaternion cs::Quaternion::GetDirection(const Vec3& direction)
{
	return GetFromTo({ 0, 0, 1.0f }, direction);
}

cs::Quaternion cs::Quaternion::GetDeconstruct(const Mat4& matrix)
{
	float w = 0.5f * std::sqrtf(matrix.Trace()); 
	float inv = 0.25f / w;

	return Quaternion(
		(matrix(1, 2) - matrix(2, 1)) * inv,
		(matrix(2, 0) - matrix(0, 2)) * inv,
		(matrix(0, 1) - matrix(1, 0)) * inv,
		w
	);
}

cs::Quaternion cs::Quaternion::GetSlerp(const Quaternion& from, const Quaternion& to, float lambda)
{
	float dot = from.m_vector * to.m_vector;
	float theta = std::acosf(dot);

	float invSine = 1.0f / std::sinf(theta);

	return from * (std::sin(theta * (1 - lambda)) * invSine) + to * (std::sin(theta * lambda) * invSine);
}

cs::Mat4 cs::Quaternion::GetMatrix(float s) const
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
