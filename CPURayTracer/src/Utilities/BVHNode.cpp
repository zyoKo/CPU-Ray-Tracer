#include "BVHNode.h"
#include <algorithm>

#include "BVH_Helper.h"

namespace PathTracer
{
	BVHNode::BVHNode(const HittableList& hittableList, double startTime, double endTime)
		:	BVHNode(hittableList.GetObjects(), 0, hittableList.GetObjects().size(), startTime, endTime)
	{
	}

	BVHNode::BVHNode(const std::vector<std::shared_ptr<IHittable>>& objects, size_t start, size_t end, double startTime, double endTime)
	{
		auto tempObjects = objects;

		int axis = Math::RandomInt(0, 2);
		auto comparator = 
			  (axis == 0) ? BoundingBoxComparator(tempObjects[0], tempObjects[1], Math::AXIS::X)
			: (axis == 1) ? BoundingBoxComparator(tempObjects[0], tempObjects[1], Math::AXIS::Y)
			              : BoundingBoxComparator(tempObjects[0], tempObjects[1], Math::AXIS::Z);
	}

	bool BVHNode::Hit(const Ray& ray, double tMin, double tMax, HitRecord& hitRecord) const
	{
		if (!boundingBox.Hit(ray, tMin, tMax))
			return false;

		const bool hitLeft = left->Hit(ray, tMin, tMax, hitRecord);
		const bool hitRight = right->Hit(ray, tMin, hitLeft ? hitRecord.t : tMax, hitRecord);

		return hitLeft || hitRight;
	}

	bool BVHNode::BoundingBox(double startTime, double endTime, Physics::AABB& outputBoundingBox) const
	{
		outputBoundingBox = boundingBox;

		return true;
	}
}
