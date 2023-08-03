#include "Lambertian.h"

#include "Utilities/Types/HitRecord.h"

namespace PathTracer
{
	Lambertian::Lambertian(const Math::color& albedo)
		:	albedo(albedo)
	{
	}

	bool Lambertian::Scatter(const Ray& rayIn, const HitRecord& hitRecord, Math::color& attenuation, Ray& scattered) const
	{
		auto scatterDirection = hitRecord.normal + Math::RandomUnitVector();

		if (scatterDirection.NearZero())
			scatterDirection = hitRecord.normal;

		scattered = Ray(hitRecord.p, scatterDirection);
		attenuation = albedo;
		return true;
	}

	const Math::color& Lambertian::GetAlbedo() const
	{
		return albedo;
	}
}
