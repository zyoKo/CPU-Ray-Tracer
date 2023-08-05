#pragma once

namespace PathTracer
{
	const Math::point3 LOOK_FROM = { -2.0, 2.0, 1.0 };

	const Math::point3 LOOK_AT = { 0.0, 0.0, -1.0 };

	const Math::point3 VIEW_UP = { 0.0, 1.0, 0.0 };

	constexpr double FIELD_OF_VIEW = 50.0;

	constexpr double ASPECT_RATIO = 16.0 / 9.0;

	constexpr double APERTURE = 1.0;

	const double FOCUS_DISTANCE = (LOOK_FROM - LOOK_AT).GetLength();
}