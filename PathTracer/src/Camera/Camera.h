#pragma once

#include "Geometry/Ray.h"

class Ray;

namespace PathTracer
{
	class Camera
	{
	public:
		Camera();

		Ray GetRay(double u, double v) const;

	private:
		Math::point3 origin;

		Math::point3 lowerLeftCorner;

		Math::vec3 horizontal;

		Math::vec3 vertical;
	};
}
