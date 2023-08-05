#pragma once

#include "Interface/IMaterial.h"

namespace PathTracer
{
	class Metal : public IMaterial
	{
	public:
		Metal(const Math::color& albedo, double fuzziness);

		bool Scatter(const Ray& rayIn, const HitRecord& hitRecord, Math::color& attenuation, Ray& scattered) const override;

	public:
		Math::color albedo;

		double fuzziness;
	};
}
