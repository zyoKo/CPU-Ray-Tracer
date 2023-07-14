#pragma once

#include "Interfaces/IHittable.h"

#include <memory>
#include <vector>

namespace PathTracer
{
	class HittableList : public IHittable
	{
	public:
		HittableList() = default;

		HittableList(std::shared_ptr<IHittable> object);

		void Clear();

		void Add(std::shared_ptr<IHittable> object);

		bool Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;

	private:
		std::vector<std::shared_ptr<IHittable>> objects;
	};
}


