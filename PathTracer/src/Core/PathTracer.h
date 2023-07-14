#pragma once

#include "Utilities/HittableList.h"
#include "Camera/Camera.h"

namespace PathTracer
{
	class PathTracer
	{
	public:
		PathTracer() = default;

		void Init();

		void Run();

	private:
		HittableList world;

		Camera camera;
	};
}
