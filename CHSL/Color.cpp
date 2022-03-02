#include "core.h"

#include "Color.h"

const float BYTE_MULTIPLIER = 1.0f / 255;

cs::Color::Color()
	:
	r(0),
	g(0),
	b(0)
{
}

cs::Color::Color(float red, float green, float blue)
	:
	r(red),
	g(green),
	b(blue)
{
}

cs::Color::Color(uint colorHex)
	:
	Color(
		BYTE_MULTIPLIER * ((colorHex & 0xFF0000U) >> 16),
		BYTE_MULTIPLIER * ((colorHex & 0x00FF00U) >> 8),
		BYTE_MULTIPLIER * ((colorHex & 0x0000FFU)))
{
}

void cs::Color::Mutate(float ammount, cs::Random& random, bool monochrome)
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

cs::Color::Bytes cs::Color::GetBytes()
{
	return 
	{ 
		(byte)(fclamp(std::roundf(r * 255), 0, 255U)), 
		(byte)(fclamp(std::roundf(g * 255), 0, 255U)), 
		(byte)(fclamp(std::roundf(b * 255), 0, 255U)),
		byte(255U)
	};
}

cs::Color& cs::Color::operator*=(const float& colorMultiplier)
{
	r *= colorMultiplier;
	g *= colorMultiplier;
	b *= colorMultiplier;

	return *this;
}

cs::ColorA::ColorA()
	:
	Color(0.0f, 0.0f, 0.0f),
	a(0.0f)
{
}

cs::ColorA::ColorA(const Color& c)
	:
	ColorA(c.r, c.g, c.b, 1.0f)
{
}

cs::ColorA::ColorA(float red, float green, float blue, float alpha)
	:
	Color(red, green, blue),
	a(alpha)
{
}

cs::ColorA::ColorA(uint colorHex)
	:
	ColorA(
		BYTE_MULTIPLIER * ((colorHex & 0xFF000000U) >> 24),
		BYTE_MULTIPLIER * ((colorHex & 0x00FF0000U) >> 16),
		BYTE_MULTIPLIER * ((colorHex & 0x0000FF00U) >> 8),
		BYTE_MULTIPLIER * ((colorHex & 0x000000FFU)))
{
}

cs::Color::Bytes cs::ColorA::GetBytes()
{
	return
	{
		(byte)(r * 256),
		(byte)(g * 256),
		(byte)(b * 256),
		(byte)(a * 256)
	};
}
