#pragma once

#include "Utilities/Hittable.h"
#include "Math/vec3.h"

namespace PathTracer
{
	class Sphere : public Hittable
	{
	public:
		Sphere() = default;
	
		Sphere(Math::point3 cen, double r);
	
		Math::point3 GetCenter() const;
	
		double GetRadius() const;
	
		bool Hit(const Ray& ray, double t_min, double t_max, HitRecord& rec) const override;
	
	private:
		Math::point3 center;

		double radius;
	};
}
