#pragma once

#include "Math/vec3.h"

void WriteColor(std::ostream &out, color pixel_color, int samplesPerPixel)
{
	auto r = pixel_color.x();
	auto g = pixel_color.y();
	auto b = pixel_color.z();

	// Divide the color by the number of samples
	const auto scale = 1.0 / samplesPerPixel;
	r *= scale;
	g *= scale;
	b *= scale;

	// Write the translated [0, 255] value of each color component.
	out << static_cast<int>(255.999 * clamp(r, 0.0, 0.999)) << ' '
		<< static_cast<int>(255.999 * clamp(g, 0.0, 0.999)) << ' '
		<< static_cast<int>(255.999 * clamp(b, 0.0, 0.999)) << '\n';
}