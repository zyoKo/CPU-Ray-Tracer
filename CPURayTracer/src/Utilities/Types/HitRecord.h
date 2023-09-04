#pragma once

#include "Math/vec3.h"

namespace PathTracer
{
	class IMaterial;

	struct HitRecord
	{
		Math::point3 p;

		Math::vec3 normal;

		std::shared_ptr<IMaterial> material;

		double t;

		bool frontFace;

		inline void SetFaceNormal(const Ray& ray, const Math::vec3& outwardNormal);
	};

	inline void HitRecord::SetFaceNormal(const Ray& ray, const Math::vec3& outwardNormal)
	{
		frontFace = Dot(ray.GetDirection(), outwardNormal) < 0.0;
		normal = frontFace ? outwardNormal : -outwardNormal;
	}
}
