#pragma once

#include "Math/vec3.h"

class ray
{
public:
	ray() = default;

	ray(const PathTracer::Math::point3& origin, const PathTracer::Math::vec3& direction)
		:	orig(origin), dir(direction)
	{}

	PathTracer::Math::point3 origin() const { return orig; }
	PathTracer::Math::vec3 direction() const { return dir; }

	PathTracer::Math::point3 at(double t) const {
		return orig + t * dir;
	}

private:
	PathTracer::Math::point3 orig;
	PathTracer::Math::vec3 dir;
};