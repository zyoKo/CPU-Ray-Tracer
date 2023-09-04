#pragma once

#include "AABB.h"

namespace PathTracer::Physics
{
	inline AABB SurroundingBox(AABB& firstBox, AABB& secondBox)
	{
		Math::point3 smallBox(
			std::fmin(firstBox.GetMinimum().x(), secondBox.GetMinimum().x()),
			std::fmin(firstBox.GetMinimum().y(), secondBox.GetMinimum().y()),
			std::fmin(firstBox.GetMinimum().z(), secondBox.GetMinimum().z()));

		Math::point3 bigBox(
			std::fmax(firstBox.GetMaximum().x(), secondBox.GetMaximum().x()),
			std::fmax(firstBox.GetMaximum().y(), secondBox.GetMaximum().y()),
			std::fmax(firstBox.GetMaximum().z(), secondBox.GetMaximum().z()));

		return { smallBox, bigBox };
	}
}
