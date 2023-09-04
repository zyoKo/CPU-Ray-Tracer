#pragma once

#include "Math/vec3.h"
#include "Math/Constants/Constants.h"

namespace PathTracer
{
	inline void WriteColor(std::ostream& out, const Math::color& pixelColor, int samplesPerPixel)
	{
		auto r = pixelColor.x();
		auto g = pixelColor.y();
		auto b = pixelColor.z();

		// Divide the color by the number of samples
		const auto scale = 1.0 / samplesPerPixel;
		r = std::sqrt(scale * r);
		g = std::sqrt(scale * g);
		b = std::sqrt(scale * b);

		// Write the translated [0, 255] value of each color component
		out << static_cast<int>(255.999 * Math::Clamp(r, 0.0, 0.999)) << ' '
			<< static_cast<int>(255.999 * Math::Clamp(g, 0.0, 0.999)) << ' '
			<< static_cast<int>(255.999 * Math::Clamp(b, 0.0, 0.999)) << '\n';
	}
}
