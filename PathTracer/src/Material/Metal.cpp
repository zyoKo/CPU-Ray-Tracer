#include "Metal.h"

#include "Utilities/Types/HitRecord.h"

namespace PathTracer
{
	Metal::Metal(const Math::color& albedo, double fuzziness)
		:	albedo(albedo),
			fuzziness(fuzziness < 1.0 ? fuzziness : 1.0)
	{
	}

	bool Metal::Scatter(const Ray& rayIn, const HitRecord& hitRecord, Math::color& attenuation, Ray& scattered) const
	{
		Math::vec3 reflected = Reflection(GetUnitVector(rayIn.GetDirection()), hitRecord.normal);
		scattered = Ray(hitRecord.p, reflected + fuzziness * Math::RandomInUnitSphere());
		attenuation = albedo;
		return Dot(scattered.GetDirection(), hitRecord.normal) > 0.0;
	}
}
