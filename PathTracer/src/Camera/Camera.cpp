#include "Camera.h"
#include "Constants/Constants.h"

namespace PathTracer
{
	Camera::Camera(
		const Math::point3& lookFrom,
		const Math::point3& lookAt,
		const Math::vec3& viewUp,
		double fieldOfView,
		double aspectRatio)
	{
		const auto theta = Math::DegreesToRadians(fieldOfView);
		const auto h = std::tan(theta / 2.0);
		const auto viewportHeight = 2.0 * h;
		const auto viewportWidth = aspectRatio * viewportHeight;

		const auto w = GetUnitVector(lookFrom - lookAt);
		const auto u = GetUnitVector(Cross(viewUp, w));
		const auto v = Cross(w, u);

		origin		= lookFrom;
		horizontal	= viewportWidth  * u;
		vertical	= viewportHeight * v;
		lowerLeftCorner = origin - horizontal / 2.0 - vertical / 2.0 - w;
	}

	Ray Camera::GetRay(double s, double t) const
	{
		return { origin, lowerLeftCorner + s * horizontal + t * vertical - origin };
	}
}