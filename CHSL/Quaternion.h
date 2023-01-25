#pragma once

/* CHSL

	|	Quaternion
	|
	|	- Quaternion implementation.

*/









namespace cs
{

	class Quaternion sealed
	{
	public:
		Quaternion();
		Quaternion(float x, float y, float z, float w);
		Quaternion(const Quaternion&);
		~Quaternion() = default;

		Quaternion operator*(const Quaternion&);
		Quaternion operator+(const Quaternion&);

	private:
		// Either:
		// 4D Vector
		// 3D imaginary vector + real component
		// 3 imaginary components + real component

		union
		{
			struct
			{
				// Imaginary components
				union
				{
					cs::Vec3 m_imaginary;

					struct
					{
						float m_x;
						float m_y;
						float m_z;
					};
				};

				// Real component
				float m_w;
			};

			cs::Vec4 m_vector;
		};
	};

}

