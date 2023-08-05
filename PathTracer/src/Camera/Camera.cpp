#include "Camera.h"

namespace PathTracer
{
	Camera::Camera(
		const Math::point3& lookFrom,
		const Math::point3& lookAt,
		const Math::vec3& viewUp,
		double fieldOfView,
		double aspectRatio,
		double aperture,
		double focusDistance)
	{
		const auto theta = Math::DegreesToRadians(fieldOfView);
		const auto h = std::tan(theta / 2.0);
		const auto viewportHeight = 2.0 * h;
		const auto viewportWidth = aspectRatio * viewportHeight;

		w = GetUnitVector(lookFrom - lookAt);
		u = GetUnitVector(Cross(viewUp, w));
		v = Cross(w, u);

		origin		= lookFrom;
		horizontal	= focusDistance * viewportWidth  * u;
		vertical	= focusDistance * viewportHeight * v;
		lowerLeftCorner = origin - horizontal / 2.0 - vertical / 2.0 - focusDistance * w;

		lensRadius = aperture / 2.0;
	}

	Ray Camera::GetRay(double s, double t) const
	{
		const Math::vec3 random = lensRadius * Math::RandomInUnitDisk();
		const Math::vec3 offset = u * random.x() + v * random.y();

		return { origin + offset, lowerLeftCorner + s * horizontal + t * vertical - origin - offset };
	}
}