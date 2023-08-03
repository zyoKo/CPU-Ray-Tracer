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
		double refractionRatio = hitRecord.frontFace ? (1.0 / indexOfRefraction) : indexOfRefraction;

		Math::vec3 unitDirection = Math::GetUnitVector(rayIn.GetDirection());
		Math::vec3 refracted = Math::Refraction(unitDirection, hitRecord.normal, refractionRatio);

		scattered = Ray(hitRecord.p, refracted);
		return true;
	}

	double Dielectric::GetIndexOfRefraction()
	{
		return indexOfRefraction;
	}
}
