#include "AABB.h"

namespace PathTracer::Physics
{
	AABB::AABB(const Math::point3& minimum, const Math::point3& maximum)
		:	minimum(minimum),
			maximum(maximum)
	{
	}

	Math::point3 AABB::GetMinimum() const
	{
		return minimum;
	}

	Math::point3 AABB::GetMaximum() const
	{
		return maximum;
	}

	bool AABB::Hit(const Ray& ray, double tMin, double tMax) const
	{
		for (int i = 0; i < 3; ++i)
		{
			const auto t0 = std::fmin((minimum[i] - ray.GetOrigin()[i]) / ray.GetDirection()[i], 
											(maximum[i] - ray.GetOrigin()[i]) / ray.GetDirection()[i]);

			const auto t1 = std::fmax((minimum[i] - ray.GetOrigin()[i]) / ray.GetDirection()[i],
											(maximum[i] - ray.GetOrigin()[i]) / ray.GetDirection()[i]);

			tMin = std::fmax(t0, tMin);
			tMax = std::fmin(t1, tMax);

			if (tMax <= tMin)
				return false;
		}

		return true;
	}

	bool AABB::HitOptimized(const Ray& ray, double tMin, double tMax) const
	{
		for (int i = 0; i < 3; ++i)
		{
			const auto inverseDirection = 1.0f / ray.GetDirection()[i];

			auto t0 = (minimum[i] - ray.GetOrigin()[i]) * inverseDirection;
			auto t1 = (maximum[i] - ray.GetOrigin()[i]) * inverseDirection;

			if (inverseDirection < 0.0f)
				std::swap(t0, t1);
			
			tMin = t0 > tMin ? t0 : tMin;
			tMax = t1 < tMax ? t1 : tMax;

			if (tMax <= tMin)
				return false;
		}

		return true;
	}
}
