#pragma once

#include "IMaterial.h"

namespace PathTracer
{
	class Dielectric : public IMaterial
	{
	public:
		Dielectric(double indexofRefraction);

		bool Scatter(const Ray& rayIn, const HitRecord& hitRecord, Math::color& attenuation, Ray& scattered) const override;

		double GetIndexOfRefraction();

	private:
		double indexOfRefraction;
	};
}