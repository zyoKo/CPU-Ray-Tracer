#pragma once

#include "Interface/IMaterial.h"

namespace PathTracer
{
	class Dielectric : public IMaterial
	{
	public:
		Dielectric(double indexofRefraction);

		bool Scatter(const Ray& rayIn, const HitRecord& hitRecord, Math::color& attenuation, Ray& scattered) const override;

		double GetIndexOfRefraction();

	private:
		static double ReflectanceSchlick(double cosine, double refractionRatio);

		double indexOfRefraction;
	};
}