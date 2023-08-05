#pragma once

#include "Utilities/HittableList.h"
#include "Camera/Camera.h"
#include "Material/Dielectric.h"
#include "Material/Lambertian.h"
#include "Material/Metal.h"

namespace PathTracer
{
	class PathTracer
	{
	public:
		PathTracer();

		void Init();

		void Run() const;

	private:
		static Math::color RayColor(const Ray& ray, const IHittable& world, int depth);

		HittableList world;

		Camera camera;
	};
}
