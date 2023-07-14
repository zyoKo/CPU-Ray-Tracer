#include "Ray.h"

namespace PathTracer
{
	Ray::Ray(const Math::point3& origin, const Math::vec3& direction)
		:	origin(origin),
			direction(direction)
	{}

	const Math::point3& Ray::GetOrigin() const { return origin; }

	const Math::vec3& Ray::GetDirection() const { return direction; }

	Math::point3 Ray::At(double t) const { return origin + t * direction; }
}