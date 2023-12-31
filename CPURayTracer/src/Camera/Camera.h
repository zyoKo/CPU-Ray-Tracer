#pragma once

#include "Geometry/Ray.h"

class Ray;

namespace PathTracer
{
	class Camera
	{
	public:
		Camera(
			const Math::point3& lookFrom,
			const Math::point3& lookAt,
			const Math::vec3& viewUp,
			double fieldOfView,
			double aspectRatio,
			double aperture,
			double focusDistance,
			double captureStart,
			double captureEnd);

		Ray GetRay(double s, double t) const;

	private:
		Math::point3 origin;

		Math::point3 lowerLeftCorner;

		Math::vec3 horizontal;

		Math::vec3 vertical;

		Math::vec3 u, v, w;

		double lensRadius;

		double captureStart, captureEnd;	// shutter open/close times
	};
}
