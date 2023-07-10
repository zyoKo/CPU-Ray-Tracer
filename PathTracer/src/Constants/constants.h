#pragma once

#include <limits>

const double INFINITY_DOUBLE = std::numeric_limits<double>::infinity();
constexpr double PI = 3.1415926535897932385;

inline double degrees_to_radians(double degree)
{
	return degree * PI / 180.0;
}