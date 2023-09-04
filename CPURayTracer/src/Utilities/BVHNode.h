#pragma once

#include "Interfaces/IHittable.h"
#include "HittableList.h"

namespace PathTracer
{
	class BVHNode : public IHittable
	{
	public:
		BVHNode() = default;

		BVHNode(const HittableList& hittableList, double startTime, double endTime);

		BVHNode(const std::vector<std::shared_ptr<IHittable>>& objects, size_t start, size_t end, double startTime, double endTime);

		bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& hitRecord) const override;

		bool BoundingBox(double startTime, double endTime, Physics::AABB& outputBoundingBox) const override;

	private:
		std::shared_ptr<IHittable> left;

		std::shared_ptr<IHittable> right;

		Physics::AABB boundingBox;
	};
}