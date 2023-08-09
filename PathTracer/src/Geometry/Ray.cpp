#include "Ray.h"

namespace PathTracer
{
	Ray::Ray(const Math::point3& origin, const Math::vec3& direction, double time)
		:	origin(origin),
			direction(direction),
			time(time)
	{}

	const Math::point3& Ray::GetOrigin() const { return origin; }

	const Math::vec3& Ray::GetDirection() const { return direction; }

	double Ray::GetTime() const { return time; }

	Math::point3 Ray::At(double t) const { return origin + t * direction; }
}