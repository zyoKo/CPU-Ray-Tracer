#pragma once

#include "Geometry/Ray.h"
#include "Math/vec3.h"

namespace PathTracer
{
	struct HitRecord
	{
		Math::point3 p;

		Math::vec3 normal;

		double t;

		bool front_face;

		inline void SetFaceNormal(const Ray& r, const Math::vec3& outward_normal);
	};

	inline void HitRecord::SetFaceNormal(const Ray& r, const Math::vec3& outward_normal)
	{
		front_face = Dot(r.GetDirection(), outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	}

	class Hittable
	{
	public:
		Hittable() = default;

		virtual ~Hittable() = default;

		virtual bool Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const = 0;
	};
}
