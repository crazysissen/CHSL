#include "core.h"

#include "Color.h"

#define BYTE_MULTIPLIER		(1.0f / 255)
#define TO_BYTE(f)			((unsigned char)((f) * 255.999f))
#define TO_FLOAT(b)			((float)((b) * BYTE_MULTIPLIER))





// Color3f

cs::Color3f::Color3f()
	:
	r(0),
	g(0),
	b(0)
{
}

cs::Color3f::Color3f(float red, float green, float blue)
	:
	r(red),
	g(green),
	b(blue)
{
}

cs::Color3f::Color3f(const Vec3& v)
	:
	r(v.x), 
	g(v.y), 
	b(v.z)
{
}

cs::Color3f::Color3f(unsigned int colorHex)
	:
	r(TO_FLOAT((colorHex & 0xFF0000U) >> 16)),
	g(TO_FLOAT((colorHex & 0x00FF00U) >> 8)),
	b(TO_FLOAT((colorHex & 0x0000FFU)))
{
}

void cs::Color3f::Mutate(float ammount, cs::Random& random, bool monochrome)
{
	if (monochrome)
	{
		float rFloat = random.Getf(-ammount, ammount);

		r += rFloat;
		g += rFloat;
		b += rFloat;
	}
	else
	{
		r += random.Getf(-ammount, ammount);
		g += random.Getf(-ammount, ammount);
		b += random.Getf(-ammount, ammount);
	}

	r = cs::fclamp(r, 0, 1);
	g = cs::fclamp(g, 0, 1);
	b = cs::fclamp(b, 0, 1);
}

cs::Color3f::operator cs::Vec3() const
{
	return Vec3(r, g, b);
}

cs::Color3f::operator cs::Color3() const
{
	return Color3(
		TO_BYTE(r),
		TO_BYTE(g),
		TO_BYTE(b)
	);
}

cs::Color3f::operator cs::Color4() const
{
	return Color4(
		TO_BYTE(r),
		TO_BYTE(g),
		TO_BYTE(b),
		255
	);
}

cs::Color3f::operator cs::Color4f() const
{
	return Color4f(r, g, b, 1.0f);
}

cs::Color3f& cs::Color3f::operator*=(const float& colorMultiplier)
{
	r *= colorMultiplier;
	g *= colorMultiplier;
	b *= colorMultiplier;

	return *this;
}



// Color4f

cs::Color4f::Color4f()
	:
	r(0.0f),
	g(0.0f),
	b(0.0f),
	a(1.0f)
{
}

cs::Color4f::Color4f(const Color3f& c)
	:
	Color4f(c.r, c.g, c.b, 1.0f)
{
}

cs::Color4f::Color4f(const Vec3& v)
	:
	Color4f(v.x, v.y, v.z, 1.0f)
{
}

cs::Color4f::Color4f(const Vec4& v)
	:
	Color4f(v.x, v.y, v.z, v.w)
{
}

cs::Color4f::Color4f(float red, float green, float blue, float alpha)
	:
	r(red),
	g(green),
	b(blue),
	a(alpha)
{
}

cs::Color4f::Color4f(unsigned int colorHex)
	:
	r(TO_FLOAT((colorHex & 0xFF000000U) >> 24)),
	g(TO_FLOAT((colorHex & 0x00FF0000U) >> 16)),
	b(TO_FLOAT((colorHex & 0x0000FF00U) >> 8)),
	a(TO_FLOAT((colorHex & 0x000000FFU)))
{
}

void cs::Color4f::Mutate(float ammount, cs::Random& random, bool monochrome)
{
	if (monochrome)
	{
		float rFloat = random.Getf(-ammount, ammount);

		r += rFloat;
		g += rFloat;
		b += rFloat;
	}
	else
	{
		r += random.Getf(-ammount, ammount);
		g += random.Getf(-ammount, ammount);
		b += random.Getf(-ammount, ammount);
	}

	r = cs::fclamp(r, 0, 1);
	g = cs::fclamp(g, 0, 1);
	b = cs::fclamp(b, 0, 1);
}

cs::Color4f::operator cs::Vec3() const
{
	return Vec3(r, g, b);
}

cs::Color4f::operator cs::Vec4() const
{
	return Vec4(r, g, b, a);
}

cs::Color4f::operator cs::Color3() const
{
	return Color3(
		TO_BYTE(r),
		TO_BYTE(g),
		TO_BYTE(b)
	);
}

cs::Color4f::operator cs::Color4() const
{
	return Color4(
		TO_BYTE(r),
		TO_BYTE(g),
		TO_BYTE(b),
		TO_BYTE(a)
	);
}

cs::Color4f::operator cs::Color3f() const
{
	return Color3f(
		r,
		g,
		b
	);
}


cs::Color4f& cs::Color4f::operator*=(const float& modifier)
{
	r *= modifier;
	g *= modifier;
	b *= modifier;

	return *this;
}



// Color3

cs::Color3::Color3()
	:
	r(0),
	g(0),
	b(0)
{
}

cs::Color3::Color3(unsigned char red, unsigned char green, unsigned char blue)
	:
	r(red),
	g(green),
	b(blue)
{
}

cs::Color3::Color3(const Point3& p)
	:
	Color3(p.x, p.y, p.z)
{
}

cs::Color3::Color3(unsigned int colorHex)
	:
	r((colorHex & 0xFF0000U) >> 16),
	g((colorHex & 0x00FF00U) >> 8),
	b((colorHex & 0x0000FFU))
{
}

cs::Color3::operator cs::Point3() const
{
	return Point3(r, g, b);
}

cs::Color3::operator cs::Point4() const
{
	return Point4(r, g, b, 255);
}

cs::Color3::operator cs::Color4() const
{
	return Color4(r, g, b, 255);
}

cs::Color3::operator cs::Color3f() const
{
	return Color3f(
		TO_BYTE(r),
		TO_BYTE(g),
		TO_BYTE(b)
	);
}

cs::Color3::operator cs::Color4f() const
{
	return Color4f(
		TO_FLOAT(r),
		TO_FLOAT(g),
		TO_FLOAT(b),
		1.0f
	);
}



// Color4

cs::Color4::Color4()
	:
	r(0),
	g(0),
	b(0),
	a(255)
{
}

cs::Color4::Color4(const Color3& c)
	:
	r(c.r),
	g(c.g),
	b(c.b),
	a(255)
{
}

cs::Color4::Color4(const Point3& p, unsigned char a)
	:
	r(p.x), 
	g(p.y), 
	b(p.z), 
	a(a)
{
}

cs::Color4::Color4(const Point4& p)
	:
	r(p.x), 
	g(p.y), 
	b(p.z), 
	a(p.w)
{
}

cs::Color4::Color4(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
	:
	r(red),
	g(green),
	b(blue),
	a(alpha)
{
}

cs::Color4::Color4(unsigned int colorHex)
	:
	r((colorHex & 0xFF000000U) >> 24),
	g((colorHex & 0x00FF0000U) >> 16),
	b((colorHex & 0x0000FF00U) >> 8),
	a((colorHex & 0x000000FFU))
{
}

cs::Color4::operator cs::Color3() const
{
	return Color3(
		r,
		g,
		b
	);
}

cs::Color4::operator cs::Color3f() const
{
	return Color3f(
		TO_FLOAT(r),
		TO_FLOAT(g),
		TO_FLOAT(b)
	);
}

cs::Color4::operator cs::Color4f() const
{
	return Color4f(
		TO_FLOAT(r),
		TO_FLOAT(g),
		TO_FLOAT(b),
		TO_FLOAT(a)
	);
}
