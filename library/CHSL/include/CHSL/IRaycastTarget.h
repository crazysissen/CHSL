#pragma once

#include "Line.h"

namespace cs
{

	class IRaycastTarget
	{
	public:
		virtual bool Raycast(const Line3& line, float& out) const = 0;
	};

}