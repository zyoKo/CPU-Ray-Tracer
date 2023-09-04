#pragma once

#include "Geometry/Ray.h"
#include "Physics/AABB.h"
#include "Utilities/Types/HitRecord.h"

namespace PathTracer
{
	class IHittable
	{
	public:
		IHittable() = default;

		virtual ~IHittable() = default;

		virtual bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& hitRecord) const = 0;

		virtual bool BoundingBox(double startTime, double endTime, Physics::AABB& outputBoundingBox) const = 0;

		virtual Physics::AABB BoundingBox() const = 0;
	};
}
