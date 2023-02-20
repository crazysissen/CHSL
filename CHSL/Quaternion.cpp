#include "core.h"
#include "Quaternion.h"

cs::Quaternion::Quaternion()	
	: x(0), y(0), z(0), w(1)
{
}

cs::Quaternion::Quaternion(const Vec4& components)
	: vector(components)
{
}

cs::Quaternion::Quaternion(const Vec3& imaginary, float real)
	: imaginary(imaginary), w(real)
{
}

cs::Quaternion::Quaternion(float x, float y, float z, float w)	
	: x(x), y(y), z(z), w(w)
{
}

cs::Quaternion::Quaternion(const Quaternion& other)	
	: x(other.x), y(other.y), z(other.z), w(other.w)
{
}

cs::Quaternion cs::Quaternion::Conjugate() const
{
	return Quaternion(-imaginary, w);
}

cs::Quaternion cs::Quaternion::Normal() const
{
	float in = 1.0f / Norm();
	return Quaternion(x * in, y * in, z * in, w * in);
}

cs::Quaternion cs::Quaternion::Inverse() const
{
	float n = Norm();
	float isn = 1.0f / (n * n);
	return Quaternion(x * -isn, y * -isn, z * -isn, w * isn);
}

float cs::Quaternion::Norm() const
{
	return std::sqrtf(x * x + y * y + z * z + w * w);
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
	imaginary = -imaginary;
	return *this;
}

cs::Quaternion& cs::Quaternion::NormalizeThis()
{
	float in = 1.0f / Norm();
	vector *= in;
	return *this;
}

cs::Quaternion& cs::Quaternion::InvertThis()
{
	float n = Norm();
	float isn = 1.0f / (n * n);
	imaginary *= -isn;
	w *= isn;
	return *this;
}

cs::Vec3 cs::Quaternion::operator*(const Vec3& other) const
{
	return (*this * Quaternion(other, 1.0f) * this->Conjugate()).imaginary;
}

cs::Vec4 cs::Quaternion::operator*(const Vec4& other) const
{
	return (*this * Quaternion(other) * this->Conjugate()).vector;
}

cs::Quaternion cs::Quaternion::operator*(const Quaternion& other) const
{
	return Quaternion(
		imaginary % other.imaginary + imaginary * other.w + other.imaginary * w,
		w * other.w - imaginary * other.imaginary
	);
}

cs::Quaternion cs::Quaternion::operator*(float scalar) const
{
	return Quaternion(
		x * scalar,
		y * scalar,
		z * scalar,
		w * scalar
	);
}

cs::Quaternion cs::Quaternion::operator+(const Quaternion& other) const
{
	return Quaternion(
		x + other.x,
		y + other.y,
		z + other.z,
		w + other.w
	);
}

cs::Quaternion& cs::Quaternion::operator=(const Quaternion& other)
{
	vector = other.vector;
	return *this;
}

cs::Quaternion& cs::Quaternion::operator+=(const Quaternion& other)
{
	vector = (*this + other).vector;
	return *this;
}

cs::Quaternion& cs::Quaternion::operator*=(const Quaternion& other)
{
	vector = (*this * other).vector;
	return *this;
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

cs::Quaternion cs::Quaternion::GetEuler(const Vec3& euler)
{
	return GetEuler(euler.x, euler.y, euler.z);
}

cs::Quaternion cs::Quaternion::GetEuler(float pitch, float yaw, float roll)
{
	float sx = sinf(pitch * 0.5f);
	float sy = sinf(yaw * 0.5f);
	float sz = sinf(roll * 0.5f);
	float cx = cosf(pitch * 0.5f);
	float cy = cosf(yaw * 0.5f);
	float cz = cosf(roll * 0.5f);

	Quaternion q;
	q.x = cx * sy * sz + sx * cy * cz;
	q.y = cx * sy * cz - sx * cy * sz;
	q.z = sx * sy * cz + cx * cy * sz;
	q.w = cx * cy * cz - sx * sy * sz;

	return q;
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

cs::Quaternion cs::Quaternion::GetDirection(const Vec3& direction, Vec3 up)
{
	up = (up - direction * (up * direction)).Normalize();

	Vec3 right = up % direction;

	Quaternion q;
	q.w = 0.5f * std::sqrtf(1.0f + right.x + up.y + direction.z);

	float rec = 0.25f / q.w;

	q.x = rec * (up.z - direction.y);
	q.y = rec * (direction.x - right.z);
	q.z = rec * (right.y - up.x);

	return q;
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
	float dot = from.vector * to.vector;
	float theta = std::acosf(dot);

	float invSine = 1.0f / std::sinf(theta);

	return from * (std::sin(theta * (1 - lambda)) * invSine) + to * (std::sin(theta * lambda) * invSine);
}

cs::Mat4 cs::Quaternion::GetMatrix(float s) const
{
	float x2 = x * x;
	float xy = x * y;
	float xz = x * z;
	float xw = x * w;
	float y2 = y * y;
	float yz = y * z;
	float yw = y * w;
	float z2 = z * z;
	float zw = z * w;

	return Mat4(
		1.0f - s * (y2 + z2),	s * (xy - zw),			s *	(xz + yw),			0.0f,
		s * (xy + zw),			1.0f - s * (x2 + z2),	s * (yz - xw),			0.0f,
		s * (xz - yw),			s * (yz + xw),			1.0f - s * (x2 + y2),	0.0f,
		0.0f,					0.0f,					0.0f,					1.0f
	);
}
