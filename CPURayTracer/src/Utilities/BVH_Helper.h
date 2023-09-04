#pragma once

#include "BVHNode.h"

namespace PathTracer
{
	inline bool BoundingBoxComparator(const std::shared_ptr<IHittable>& firstBox, const std::shared_ptr<IHittable>& secondBox, Math::AXIS axis)
	{
		Physics::AABB box1;
		Physics::AABB box2;

		if (!firstBox->BoundingBox(0.0, 0.0, box1) || !secondBox->BoundingBox(0.0, 0.0, box2))
			std::cerr << "No bounding box in BVHNode Constructor.\n";

		return box1.GetMinimum()[static_cast<int>(axis)] < box2.GetMinimum()[static_cast<int>(axis)];
	}
}