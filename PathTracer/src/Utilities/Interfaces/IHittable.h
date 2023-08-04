#pragma once

#include "Geometry/Ray.h"
#include "Utilities/Types/HitRecord.h"

namespace PathTracer
{
	class IHittable
	{
	public:
		IHittable() = default;

		virtual ~IHittable() = default;

		virtual bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& hitRecord) const = 0;
	};
}
