#pragma once

#include "Utilities/hittable.h"
#include "Math/vec3.h"

class sphere : public hittable
{
public:
	sphere() = default;

	sphere(point3 cen, double r);

	point3 GetCenter() const;

	double GetRadius() const;

	bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

private:
	point3 center;
	double radius;
};