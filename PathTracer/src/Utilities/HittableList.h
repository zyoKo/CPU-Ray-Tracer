#pragma once

#include "Hittable.h"

#include <memory>
#include <vector>

namespace PathTracer
{
	class HittableList : public Hittable
	{
	public:
		HittableList() = default;

		HittableList(std::shared_ptr<Hittable> object);

		void Clear();

		void Add(std::shared_ptr<Hittable> object);

		bool Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;

	private:
		std::vector<std::shared_ptr<Hittable>> objects;
	};
}


