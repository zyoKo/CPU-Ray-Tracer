#pragma once

#include "Utilities/Interfaces/IHittable.h"

namespace PathTracer
{
	class MovingSphere : public IHittable
	{
	public:
		MovingSphere(Math::point3 center0, Math::point3 center1, double timeAtCenter0, double timeAtCenter1, double radius, std::shared_ptr<IMaterial> material);

		bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& hitRecord) const override;

		bool BoundingBox(double startTime, double endTime, Physics::AABB& outputBoundingBox) const override;

		Math::point3 GetPositionAtTime(double time) const;

		Physics::AABB BoundingBox() const override;

	private:
		Math::point3 center0, center1;

		double timeAtCenter0, timeAtCenter1;

		double radius;

		std::shared_ptr<IMaterial> material;

		Physics::AABB testCollider;
	};
}