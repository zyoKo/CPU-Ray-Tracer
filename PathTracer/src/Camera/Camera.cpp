#include "Camera.h"
#include "Constants/Constants.h"

namespace PathTracer
{
	Camera::Camera()
	{
		origin = Math::point3(0, 0, 0);

		horizontal = Math::vec3(VIEWPORT_WIDTH, 0, 0);

		vertical = Math::vec3(0, VIEWPORT_HEIGHT, 0);

		lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - Math::vec3(0, 0, FOCAL_LENGTH);
	}

	Ray Camera::GetRay(double u, double v) const
	{
		return Ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
	}
}