#pragma once

#include "Vector.h"
#include "Line.h"

namespace cs
{

	class Plane
	{
	public:
		Plane(Vec3 origin, Vec3 normal);
		Plane(Vec3 origin, Vec3 v1, Vec3 v2);
		Plane(const Plane&);

		Plane& operator=(const Plane&);

		bool Contains(Vec3 vector) const;
		bool Contains(Line3 line) const;
		bool Parallel(Plane plane) const;
		bool Parallel(Line3 line) const;
		bool Perpendicular(Line3 line) const;

		Vec3 Intersection(Line3 line) const;

	private: 
		Vec3 m_origin;
		Vec3 m_normal;
	};

}

#ifdef CHSL_LINEAR

using cs::Plane;

#endif
