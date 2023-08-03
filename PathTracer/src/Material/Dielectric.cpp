#include "Dielectric.h"

#include "Utilities/Types/HitRecord.h"

namespace PathTracer
{
	Dielectric::Dielectric(double indexOfRefraction)
		:	indexOfRefraction(indexOfRefraction)
	{
	}

	bool Dielectric::Scatter(const Ray& rayIn, const HitRecord& hitRecord, Math::color& attenuation, Ray& scattered) const
	{
		attenuation = Math::color(1.0, 1.0, 1.0);
		const double refractionRatio = hitRecord.frontFace ? (1.0 / indexOfRefraction) : indexOfRefraction;

		const Math::vec3 unitDirection = Math::GetUnitVector(rayIn.GetDirection());
		const double cosTheta = std::fmin(Math::Dot(-unitDirection, hitRecord.normal), 1.0);
		const double sinTheta = std::sqrt(1.0 - cosTheta * cosTheta);

		const bool canRefract = !(refractionRatio * sinTheta > 1.0);
		Math::vec3 rayDirection;	// either reflection or refraction

		if (canRefract)
			rayDirection = Refraction(unitDirection, hitRecord.normal, refractionRatio);
		else
			rayDirection = Reflection(unitDirection, hitRecord.normal);

		scattered = Ray(hitRecord.p, rayDirection);

		return true;
	}

	double Dielectric::GetIndexOfRefraction()
	{
		return indexOfRefraction;
	}
}
