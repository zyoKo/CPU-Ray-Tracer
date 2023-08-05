#pragma once

#include "Interface/IMaterial.h"

namespace PathTracer
{
	class Lambertian : public IMaterial
	{
	public:
		Lambertian(const Math::color& albedo);

		bool Scatter(const Ray& rayIn, const HitRecord& hitRecord, Math::color& attenuation, Ray& scattered) const override;

		const Math::color& GetAlbedo() const;

	private:
		Math::color albedo;
	};
}