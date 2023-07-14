#pragma once

#include "Geometry/Ray.h"
#include "Constants/Constants.h"

namespace PathTracer
{
	class Camera
	{
	public:
		Camera()
		{
			origin = Math::point3(0, 0, 0);
			horizontal = Math::vec3(VIEWPORT_WIDTH, 0, 0);
			vertical = Math::vec3(0, VIEWPORT_HEIGHT, 0);
			lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - Math::vec3(0, 0, FOCAL_LENGTH);
		}

		Ray GetRay(double u, double v) const
		{
			return Ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
		}

	private:
		Math::point3 origin;
		Math::point3 lowerLeftCorner;
		Math::vec3 horizontal;
		Math::vec3 vertical;
	};
}
