#pragma once

#include "Utilities/Interfaces/IHittable.h"
#include "Math/vec3.h"

namespace PathTracer
{
	class Sphere : public IHittable
	{
	public:
		Sphere() = default;
	
		Sphere(const Math::point3& center, double radius, std::shared_ptr<IMaterial> material);
	
		Math::point3 GetCenter() const;
	
		double GetRadius() const;
	
		bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& hitRecord) const override;

		bool BoundingBox(double startTime, double endTime, Physics::AABB& outputBoundingBox) const override;

		Physics::AABB BoundingBox() const override;

	private:
		Math::point3 center;

		double radius;

		std::shared_ptr<IMaterial> material;

		// temp collider
		Physics::AABB testCollider;
	};
}
