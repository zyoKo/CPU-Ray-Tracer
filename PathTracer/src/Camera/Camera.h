#pragma once

#include "Geometry/ray.h"
#include "Constants/Constants.h"

namespace PathTracer
{
	class Camera
	{
	public:
		Camera()
		{
			origin = Math::point3(0, 0, 0);
			horizontal = Math::vec3(PathTracer::VIEWPORT_WIDTH, 0, 0);
			vertical = Math::vec3(0, PathTracer::VIEWPORT_HEIGHT, 0);
			lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - Math::vec3(0, 0, PathTracer::FOCAL_LENGTH);
		}

		ray GetRay(double u, double v) const
		{
			return ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
		}

	private:
		Math::point3 origin;
		Math::point3 lowerLeftCorner;
		Math::vec3 horizontal;
		Math::vec3 vertical;
	};
}
