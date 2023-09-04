#pragma once

#include "Geometry/Ray.h"
#include "Math/vec3.h"

namespace PathTracer::Physics
{
	class AABB
	{
	public:
		AABB() = default;

		AABB(const Math::point3& minimum, const Math::point3& maximum);

		Math::point3 GetMinimum() const;

		Math::point3 GetMaximum() const;

		bool Hit(const Ray& ray, double tMin, double tMax) const;

		bool HitOptimized(const Ray& ray, double tMin, double tMax) const;

	private:
		Math::point3 minimum;

		Math::point3 maximum;
	};
}
