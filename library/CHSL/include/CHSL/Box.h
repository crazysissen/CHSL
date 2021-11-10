#pragma once

#include "IRaycastTarget.h"

namespace cs
{

	class Box : public IRaycastTarget
	{
	public:
		Box(Vec3 center, Vec3 xV, Vec3 yV, Vec3 zV);
		Box(Vec3 center, float width, float height, float depth, float rX = 0, float rY = 0, float rZ = 0);
		
		bool Raycast(const Line3& line, float& out) const override;
		bool Intersection(const Line3& line, Vec3& out) const;

	private:
		Vec3 m_center;
		Vec3 m_x;
		Vec3 m_y;
		Vec3 m_z;
	};

}
