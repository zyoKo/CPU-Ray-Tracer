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

		virtual bool Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const = 0;
	};
}
