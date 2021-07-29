#pragma once

namespace cs
{

	template<typename T>
	class _Vec2
	{
	public:
		T x, y;

	public:
		_Vec2()
		{
			x = 0;
			y = 0;
		}
		_Vec2(T X, T Y)
		{
			x = X;
			y = Y;
		}
		_Vec2(const _Vec2& copy)
		{
			x = copy.x;
			y = copy.y;
		}

		float Length2Sq()
		{
			return ((float)x) * x + ((float)y) * y;
		}
		float Length2()
		{
			return std::sqrtf(Length2Sq());
		}

		_Vec2& Normalize2()
		{
			float tempLength = Length2();
			(x /= (T)tempLength);
			(y /= (T)tempLength);
			return *this;
		}

		_Vec2 Normalized2() const
		{
			return _Vec2(*this).Normalize2();
		}

#ifdef CSTL_DX
		DirectX::XMVECTOR GetXM2(float z = 0.0f, float w = 0.0f)
		{
			return DirectX::XMVectorSet((float)x, (float)y, z, w);
		}

		_Vec2& RotateZ(float angle)
		{
			dx::XMVECTOR vec = dx::XMVector3Transform(GetXM2(), dx::XMMatrixRotationZ(-angle));

			x = (T)dx::XMVectorGetX(vec);
			y = (T)dx::XMVectorGetY(vec);

			return *this;
		}
#endif

		// Conversion

		template<typename T2>
		explicit operator _Vec2<T2>() const
		{
			return _Vec2<T2>((T2)x, (T2)y);
		}

		// Copy

		_Vec2 operator-() const
		{

			return *this;
		}

		_Vec2& operator+=(const _Vec2& b)
		{
			x += b.x;
			y += b.y;

			return *this;
		}
		_Vec2& operator-=(const _Vec2& b)
		{
			x -= b.x;
			y -= b.y;

			return *this;
		}
		_Vec2& operator*=(const _Vec2& b)
		{
			x *= b.x;
			y *= b.y;

			return *this;
		}
		_Vec2& operator/=(const _Vec2& b)
		{
			x /= b.x;
			y /= b.y;

			return *this;
		}

		_Vec2& operator*=(const T& b)
		{
			x *= b;
			y *= b;

			return *this;
		}
		_Vec2& operator/=(const T& b)
		{
			x /= b;
			y /= b;

			return *this;
		}

		// Evaluation

		bool operator==(const _Vec2& b) const
		{
			return x == b.x && y == b.y;
		}
		bool operator!=(const _Vec2& b) const
		{
			return x != b.x || y != b.y;
		}
	};

	template<typename T>
	class _Vec3 : public _Vec2<T>
	{
	public:
		using _Vec2<T>::x;
		using _Vec2<T>::y;
		T z;
		
	public:
		_Vec3()
			:
			_Vec2<T>(0, 0),
			z(0)
		{
		}

		_Vec3(T X, T Y, T Z)
			:
			_Vec2<T>(X, Y),
			z(Z)
		{
		}

		_Vec3(const _Vec3& copy)
			:
			_Vec2<T>(copy),
			z(copy.z)
		{
		}

		_Vec3(const _Vec2<T>& downsample)
			:
			_Vec2<T>(downsample),
			z(0)
		{
		}

		float Length3Sq()
		{
			return ((float)x) * x + ((float)y) * y + ((float)z) * z;
		}
		float Length3()
		{
			return std::sqrtf(Length3Sq());
		}

		_Vec3& Normalize3()
		{
			float tempLength = Length3();
			x /= tempLength;
			y /= tempLength;
			z /= tempLength;
			return *this;
		}
		_Vec3 Normalized3() const
		{
			return _Vec3(*this).Normalize3();
		}

#ifdef CSTL_DX
		DirectX::XMVECTOR GetXM3(float w = 1.0f)
		{
			return DirectX::XMVectorSet((float)x, (float)y, (float)z, w);
		}

		_Vec3& RotateX(float angle)
		{
			dx::XMVECTOR vec = dx::XMVector3Transform(GetXM3(), dx::XMMatrixRotationX(-angle));

			y = (T)dx::XMVectorGetY(vec);
			z = (T)dx::XMVectorGetZ(vec);

			return *this;
		}

		_Vec3& RotateY(float angle)
		{
			dx::XMVECTOR vec = dx::XMVector3Transform(GetXM3(), dx::XMMatrixRotationY(-angle));

			x = (T)dx::XMVectorGetX(vec);
			z = (T)dx::XMVectorGetZ(vec);

			return *this;
		}

		_Vec3& Rotate3D(const _Vec3& rotation)
		{
			_Vec3 temp = -rotation;

			dx::XMVECTOR vec = dx::XMVector3Transform(GetXM3(), dx::XMMatrixRotationRollPitchYawFromVector(temp.GetXM3()));

			x = (T)dx::XMVectorGetX(vec);
			y = (T)dx::XMVectorGetY(vec);
			z = (T)dx::XMVectorGetZ(vec);

			return *this;
		}
#endif


		// Conversion

		template<typename T2>
		explicit operator _Vec3<T2>() const
		{
			return _Vec3<T2>((T2)x, (T2)y, (T2)z);
		}

		// Copy

		_Vec3 operator-() const
		{
			return _Vec3(-x, -y, -z);
		}

		_Vec3 operator+(const _Vec3& b) const
		{
			return _Vec3(x + b.x, y + b.y, z + b.z);
		}
		_Vec3 operator-(const _Vec3& b) const
		{
			return _Vec3(x - b.x, y - b.y, z - b.z);
		}
		_Vec3 operator*(const _Vec3& b) const
		{
			return _Vec3(x * b.x, y * b.y, z * b.z);
		}
		_Vec3 operator/(const _Vec3& b) const
		{
			return _Vec3(x / b.x, y / b.y, z / b.z);
		}

		_Vec3 operator*(const T& b) const 
		{
			return _Vec3(x * b, y * b, z * b);
		}
		_Vec3 operator/(const T& b) const 
		{
			return _Vec3(x / b, y / b, z / b);
		}

		// Assignment

		_Vec3& operator=(const _Vec3& b)
		{
			x = b.x;
			y = b.y;
			z = b.z;

			return *this;
		}

		_Vec3& operator+=(const _Vec3& b)
		{
			x += b.x;
			y += b.y;
			z += b.z;

			return *this;
		}
		_Vec3& operator-=(const _Vec3& b)
		{
			x -= b.x;
			y -= b.y;
			z -= b.z;

			return *this;
		}
		_Vec3& operator*=(const _Vec3& b)
		{
			x *= b.x;
			y *= b.y;
			z *= b.z;

			return *this;
		}
		_Vec3& operator/=(const _Vec3& b)
		{
			x /= b.x;
			y /= b.y;
			z /= b.z;

			return *this;
		}

		_Vec3& operator*=(const T& b)
		{
			x *= b;
			y *= b;
			z *= b;

			return *this;
		}
		_Vec3& operator/=(const T& b)
		{
			x /= b;
			y /= b;
			z /= b;

			return *this;
		}

		// Evaluation

		bool operator==(const _Vec3& b) const
		{
			return x == b.x && y == b.y && z == b.z;
		}
		bool operator!=(const _Vec3& b) const
		{
			return x != b.x || y != b.y || z != b.z;
		}

	};

	typedef _Vec2<int> Point;
	typedef _Vec2<float> Vec2;
	typedef _Vec2<double> Vec2d;

	typedef _Vec3<int> Point3;
	typedef _Vec3<float> Vec3;
	typedef _Vec3<double> Vec3d;

#define VC3FLOOR( v ) Point3(cs::floor(v.x), cs::floor(v.y), cs::floor(v.z))
#define VC2FLOOR( v ) Point(cs::floor(v.x), cs::floor(v.y))

}

#ifdef CSTL_VEC

using cs::Point;
using cs::Vec2;
using cs::Vec2d;

using cs::Point3;
using cs::Vec3;
using cs::Vec3d;

#endif