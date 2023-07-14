#pragma once

#include "Utilities/Interfaces/IHittable.h"
#include "Math/vec3.h"

namespace PathTracer
{
	class Sphere : public IHittable
	{
	public:
		Sphere() = default;
	
		Sphere(const Math::point3& center, double radius);
	
		Math::point3 GetCenter() const;
	
		double GetRadius() const;
	
		bool Hit(const Ray& ray, double t_min, double t_max, HitRecord& rec) const override;
	
	private:
		Math::point3 center;

		double radius;
	};
}
