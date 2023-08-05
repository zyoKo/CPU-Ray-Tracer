#pragma once

namespace PathTracer
{
	const Math::point3 LOOK_FROM = { 13.0, 2.0, 3.0 };

	const Math::point3 LOOK_AT = { 0.0, 0.0, 0.0 };

	const Math::point3 VIEW_UP = { 0.0, 1.0, 0.0 };

	constexpr double FIELD_OF_VIEW = 40.0;

	constexpr double ASPECT_RATIO = 16.0 / 9.0;

	constexpr double APERTURE = 0.1;

	constexpr double FOCUS_DISTANCE = 10.0; //(LOOK_FROM - LOOK_AT).GetLength();
}