#pragma once

namespace PathTracer
{
	// Image
	constexpr auto ASPECT_RATIO_IMAGE = 16.0 / 9.0;
	constexpr int IMAGE_WIDTH = 900;
	constexpr int IMAGE_HEIGHT = static_cast<int>(IMAGE_WIDTH / ASPECT_RATIO_IMAGE);
	constexpr int SAMPLES_PER_PIXEL = 100;    // anti-aliasing
	constexpr int MAX_DEPTH = 50;

	// World Coordinates
	const Math::point3 GROUND_SPHERE_POSITION = Math::point3( 0.0, -100.5, -1.0);
	const Math::point3 LEFT_SPHERE_POSITION   = Math::point3(-1.0,    0.0, -1.0);
	const Math::point3 MIDDLE_SPHERE_POSITION = Math::point3( 0.0,    0.0, -1.0);
	const Math::point3 RIGHT_SPHERE_POSITION  = Math::point3( 1.0,    0.0, -1.0);

	// Sphere Radius
	constexpr double GROUND_SPHERE_RADIUS = 100.0;
	constexpr double NORMAL_SPHERE_RADIUS = 0.5;
	constexpr double HOLLOW_GLASS_RADIUS = -0.4;

	// Background Color
	const Math::color BACKGROUND_COLOR_START = Math::color(1.0, 1.0, 1.0);
	const Math::color BACKGROUND_COLOR_END   = Math::color(0.5, 0.7, 1.0);

	// Sphere Albedo
	const Math::color GROUND_SPHERE_ALBEDO = Math::color(0.8, 0.8, 0.0);
	const Math::color LEFT_SPHERE_ALBEDO   = Math::color(0.8, 0.8, 0.8);
	const Math::color MIDDLE_SPHERE_ALBEDO = Math::color(0.7, 0.3, 0.3);
	const Math::color RIGHT_SPHERE_ALBEDO  = Math::color(0.8, 0.6, 0.2);

	// Metal Sphere Fuzziness
	constexpr double LEFT_SPHERE_FUZZINESS  = 0.3;
	constexpr double RIGHT_SPHERE_FUZZINESS = 1.0;
}