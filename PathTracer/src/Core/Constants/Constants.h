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
	constexpr Math::point3 GROUND_SPHERE_POSITION = Math::point3( 0.0, -100.5, -1.0);
	constexpr Math::point3 LEFT_SPHERE_POSITION   = Math::point3(-1.0,    0.0, -1.0);
	constexpr Math::point3 CENTER_SPHERE_POSITION = Math::point3( 0.0,    0.0, -1.0);
	constexpr Math::point3 RIGHT_SPHERE_POSITION  = Math::point3( 1.0,    0.0, -1.0);

	// Sphere Radius
	constexpr double GROUND_SPHERE_RADIUS = 100.0;
	constexpr double NORMAL_SPHERE_RADIUS = 0.5;

	// Sphere Albedo
	constexpr Math::color GROUND_SPHERE_ALBEDO = Math::color(0.8, 0.8, 0.0);
	constexpr Math::color LEFT_SPHERE_ALBEDO = Math::color(0.7, 0.3, 0.3);
	constexpr Math::color CENTER_SPHERE_ALBEDO = Math::color(0.8, 0.8, 0.8);
	constexpr Math::color RIGHT_SPHERE_ALBEDO = Math::color(0.8, 0.6, 0.2);

	// Metal Sphere Fuzziness
	constexpr double LEFT_SPHERE_FUZZINESS = 0.3;
	constexpr double RIGHT_SPHERE_FUZZINESS = 1.0;
}