#pragma once

#include "Utilities/HittableList.h"
#include "Camera/Camera.h"
#include "Material/Lambertian.h"
#include "Material/Metal.h"

namespace PathTracer
{
	class PathTracer
	{
	public:
		PathTracer() = default;

		void Init();

		void Run() const;

	private:
		static Math::color RayColor(const Ray& ray, const IHittable& world, int depth);

		HittableList world;

		Camera camera;

		std::shared_ptr<Lambertian> materialGround;

		std::shared_ptr<Lambertian> materialMiddleSphere;

		std::shared_ptr<Metal> materialLeftSphere;

		std::shared_ptr<Metal> materialRightSphere;
	};
}
