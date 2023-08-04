#include "HittableList.h"

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
}
