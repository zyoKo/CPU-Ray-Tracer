#pragma once

#include "Geometry/ray.h"
#include "Math/vec3.h"

namespace PathTracer
{
	struct hit_record
	{
		Math::point3 p;
		Math::vec3 normal;
		double t;
		bool front_face;

		inline void set_face_normal(const ray& r, const Math::vec3& outward_normal);
	};

	inline void hit_record::set_face_normal(const ray& r, const Math::vec3& outward_normal)
	{
		front_face = dot(r.direction(), outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	}

	class hittable
	{
	public:
		hittable() = default;

		virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
	};
}
