#pragma once

#include "Utilities/hittable.h"
#include "Math/vec3.h"

namespace PathTracer
{
	class sphere : public hittable
	{
	public:
		sphere() = default;
	
		sphere(Math::point3 cen, double r);
	
		Math::point3 GetCenter() const;
	
		double GetRadius() const;
	
		bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
	
	private:
		Math::point3 center;
		double radius;
	};
}
