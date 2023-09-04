#pragma once

#include "Geometry/Ray.h"
#include "Utilities/color.h"

namespace PathTracer
{
	struct HitRecord;

	class IMaterial
	{
	public:
		virtual bool Scatter(const Ray& rayIn, const HitRecord& hitRecord, Math::color& attenuation, Ray& scattered) const = 0;
	};
}
