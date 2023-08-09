#pragma once

#include "Math/vec3.h"

namespace PathTracer
{
	class Ray
	{
	public:
		Ray() = default;

		Ray(const Math::point3& origin, const Math::vec3& direction, double time);

		const Math::point3& GetOrigin() const;

		const Math::vec3& GetDirection() const;

		double GetTime() const;

		Math::point3 At(double t) const;

	private:
		Math::point3 origin;

		Math::vec3 direction;

		double time;
	};
}