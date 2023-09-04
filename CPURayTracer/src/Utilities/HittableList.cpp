#include "HittableList.h"
#include "Physics/AABB_Helper.h"

namespace PathTracer
{
	HittableList::HittableList(std::shared_ptr<IHittable> object)
	{
		Add(object);
	}

	void HittableList::Clear()
	{
		objects.clear();
	}

	void HittableList::Add(std::shared_ptr<IHittable> object)
	{
		objects.push_back(object);
	}

	bool HittableList::Hit(const Ray& ray, double tMin, double tMax, HitRecord& hitRecord) const
	{
		HitRecord tempHitRecord;
		bool hitAnything = false;
		auto closestSoFar = tMax;

		for (const auto& object : objects)
		{
			if (object->Hit(ray, tMin, closestSoFar, tempHitRecord))
			{
				hitAnything = true;
				closestSoFar = tempHitRecord.t;
				hitRecord = tempHitRecord;
			}
		}

		return hitAnything;
	}

	bool HittableList::BoundingBox(double startTime, double endTime, Physics::AABB& outputBoundingBox) const
	{
		if (objects.empty())
			return false;

		Physics::AABB tempBoundingBox;
		bool firstBox = true;

		for (const auto& object : objects)
		{
			if (!object->BoundingBox(startTime, endTime, tempBoundingBox))
				return false;

			outputBoundingBox = firstBox ? tempBoundingBox : SurroundingBox(outputBoundingBox, tempBoundingBox);

			firstBox = false;
		}

		return true;
	}

	const std::vector<std::shared_ptr<IHittable>>& HittableList::GetObjects() const
	{
		return objects;
	}

	Physics::AABB HittableList::BoundingBox() const
	{
		return testCollider;
	}
}
