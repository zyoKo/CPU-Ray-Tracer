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

	bool HittableList::Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const
	{
		HitRecord tempHitRecord;
		bool hitAnything = false;
		auto closestSoFar = t_max;

		for (const auto& object : objects)
		{
			if (object->Hit(r, t_min, closestSoFar, tempHitRecord))
			{
				hitAnything = true;
				closestSoFar = tempHitRecord.t;
				rec = tempHitRecord;
			}
		}

		return hitAnything;
	}
}
