#pragma once

#include "Math/vec3.h"

namespace PathTracer
{
	class Ray
	{
	public:
		Ray() = default;

		Ray(const Math::point3& origin, const Math::vec3& direction)
			: orig(origin), dir(direction)
		{}

		Math::point3 GetOrigin() const { return orig; }
		Math::vec3 GetDirection() const { return dir; }

		PathTracer::Math::point3 at(double t) const {
			return orig + t * dir;
		}

	private:
		Math::point3 orig;
		Math::vec3 dir;
	};
}