#include "core.h"
#include "Matrix.h"

cs::Mat2 cs::Mat::rotation2(float r)
{
	float c = std::cosf(r);
	float s = std::sinf(r);

	return 
	{
		c, s,
		-s, c
	};
}

cs::Mat2 cs::Mat::scale2(float scale)
{
	return 
	{
		scale, 0,
		0, scale
	};
}

cs::Mat2 cs::Mat::scale2(float xScale, float yScale)
{
	return
	{
		xScale, 0,
		0, yScale
	};
}

cs::Mat2 cs::Mat::scale2(const Vec2& scale)
{
	return
	{
		scale.x, 0,
		0, scale.y
	};
}

cs::Mat3 cs::Mat::translation2(const Vec2& translation)
{
	return translation2(translation.x, translation.y);
}

cs::Mat3 cs::Mat::translation2(float x, float y)
{
	return
	{
		1, 0, x,
		0, 1, y,
		0, 0, 1
	};
}

cs::Vec2 cs::Mat::transform(const Mat2& m, const Vec2& v)
{
	return Vec2(
		v.x * m(0, 0) + v.y * m(1, 0),
		v.x * m(0, 1) + v.y * m(1, 1)
	);
}

cs::Vec2 cs::Mat::transform(const Mat3& m, const Vec2& v)
{
	return Vec2(
		v.x * m(0, 0) + v.y * m(1, 0) + m(2, 0),
		v.x * m(0, 1) + v.y * m(1, 1) + m(2, 1)
	);
}

cs::Mat3 cs::Mat::rotation3(float xR, float yR, float zR)
{
	return rotation3Z(zR) * rotation3X(xR) * rotation3Y(yR);
}

cs::Mat3 cs::Mat::rotation3X(float r)
{
	float c = std::cosf(r);
	float s = std::sinf(r);

	return
	{
		1, 0, 0,
		0, c, s,
		0, -s, c
	};
}

cs::Mat3 cs::Mat::rotation3Y(float r)
{
	float c = std::cosf(r);
	float s = std::sinf(r);

	return
	{
		c, 0, -s,
		0, 1, 0,
		s, 0, c
	};
}

cs::Mat3 cs::Mat::rotation3Z(float r)
{
	float c = std::cosf(r);
	float s = std::sinf(r);

	return
	{
		c, s, 0,
		-s, c, 0,
		0, 0, 1
	};
}

cs::Mat3 cs::Mat::scale3(float scale)
{
	return
	{
		scale, 0, 0,
		0, scale, 0,
		0, 0, scale
	};
}

cs::Mat3 cs::Mat::scale3(float xScale, float yScale, float zScale)
{
	return
	{
		xScale, 0, 0,
		0, yScale, 0,
		0, 0, zScale
	};
}

cs::Mat3 cs::Mat::scale3(const Vec3& scale)
{
	return
	{
		scale.x, 0, 0,
		0, scale.y, 0,
		0, 0, scale.z
	};
}

cs::Mat4 cs::Mat::translation3(const Vec3& translation)
{
	return
	{
		1, 0, 0, translation.x,
		0, 1, 0, translation.y,
		0, 0, 1, translation.z,
		0, 0, 0, 1
	};
}

cs::Mat4 cs::Mat::translation3(float x, float y, float z)
{
	return
	{
		1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1
	};
}

cs::Vec3 cs::Mat::transform(const Mat3& m, const Vec3& v)
{
	return Vec3(
		v.x * m(0, 0) + v.y * m(1, 0) + v.z * m(2, 0),
		v.x * m(0, 1) + v.y * m(1, 1) + v.z * m(2, 1),
		v.x * m(0, 2) + v.y * m(1, 2) + v.z * m(2, 2)
	);

	Matrix4<string> a;
}

cs::Vec3 cs::Mat::transform(const Mat4& m, const Vec3& v)
{
	return Vec3(
		v.x * m(0, 0) + v.y * m(1, 0) + v.z * m(2, 0) + m(3, 0),
		v.x * m(0, 1) + v.y * m(1, 1) + v.z * m(2, 1) + m(3, 1),
		v.x * m(0, 2) + v.y * m(1, 2) + v.z * m(2, 2) + m(3, 2)
	);
}
