#pragma once

namespace PathTracer
{
	// Image
	static constexpr auto ASPECT_RATIO_IMAGE = 16.0 / 9.0;
	static constexpr int IMAGE_WIDTH = 400;
	static constexpr int IMAGE_HEIGHT = static_cast<int>(IMAGE_WIDTH / ASPECT_RATIO_IMAGE);
	static constexpr int SAMPLES_PER_PIXEL = 100;    // anti-aliasing
	static constexpr int MAX_DEPTH = 50;

	// Background Color
	static const Math::color BACKGROUND_COLOR_START = Math::color(1.0, 1.0, 1.0);
	static const Math::color BACKGROUND_COLOR_END   = Math::color(0.5, 0.7, 1.0);

	// World Coordinates
	//const double R = std::cos(Math::PI / 4.0);
	static const Math::point3 GROUND_SPHERE_POSITION = Math::point3( 0.0, -1000.0,  0.0);
	static const Math::point3 LEFT_SPHERE_POSITION   = Math::point3(-1.05,    0.0, -1.0);
	static const Math::point3 MIDDLE_SPHERE_POSITION = Math::point3( 0.0,     0.0, -1.0);
	static const Math::point3 RIGHT_SPHERE_POSITION  = Math::point3( 1.0,     0.0, -1.0);

	// Sphere Radius
	static constexpr double GROUND_SPHERE_RADIUS = 1000.0;
	static constexpr double NORMAL_SPHERE_RADIUS =	   0.5;
	static constexpr double HOLLOW_GLASS_RADIUS  =   -0.45;

	// Index Of Refraction for Glass Spheres
	static constexpr double INDEX_OF_REFRACTION = 1.5;

	// Sphere Albedo
	static const Math::color GROUND_SPHERE_ALBEDO = Math::color(0.8, 0.8, 0.0);
	static const Math::color LEFT_SPHERE_ALBEDO   = Math::color(0.8, 0.8, 0.8);
	static const Math::color MIDDLE_SPHERE_ALBEDO = Math::color(0.2, 0.2, 0.8);
	static const Math::color RIGHT_SPHERE_ALBEDO  = Math::color(0.8, 0.6, 0.2);

	// Metal Sphere Fuzziness
	static constexpr double LEFT_SPHERE_FUZZINESS  = 0.3;
	static constexpr double RIGHT_SPHERE_FUZZINESS = 0.0;
}