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

		const bool cannotRefract = refractionRatio * sinTheta > 1.0;
		Math::vec3 rayDirection;	// either reflection or refraction

		if (cannotRefract || ReflectanceSchlick(cosTheta, refractionRatio) > Math::RandomDoublePrecise())
			rayDirection = Reflection(unitDirection, hitRecord.normal);
		else
			rayDirection = Refraction(unitDirection, hitRecord.normal, refractionRatio);

		scattered = Ray(hitRecord.p, rayDirection, rayIn.GetTime());

		return true;
	}

	double Dielectric::GetIndexOfRefraction()
	{
		return indexOfRefraction;
	}

	double Dielectric::ReflectanceSchlick(double cosine, double refractionRatio)
	{
		// Schlick's Approximation
		auto r0 = (1 - refractionRatio) / (1 + refractionRatio);
		r0 = std::pow(r0, 2);
		return r0 + (1 - r0) * std::pow(1 - cosine, 5);
	}
}
