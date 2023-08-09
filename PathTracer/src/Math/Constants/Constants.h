#pragma once

#include <limits>
#include <cstdlib>
#include <random>

namespace PathTracer::Math
{
	static const double INFINITY_DOUBLE = std::numeric_limits<double>::infinity();

	static constexpr double PI = 3.1415926535897932385;

	inline double DegreesToRadians(double degree) { return degree * PI / 180.0; }

	inline double RandomDouble() { return rand() / (RAND_MAX + 1.0); }

	inline double RandomDoublePrecise()
	{
		static std::uniform_real_distribution<double> distribution(0.0, 1.0);
		static std::mt19937 generator;
		return distribution(generator);
	}

	inline double RandomDoubleInRange(double min, double max) { return min + (max - min) * RandomDouble(); }

	inline double RandomDoubleInRangePrecise(double min, double max) { return min + (max - min) * RandomDoublePrecise(); }

	inline double Clamp(double x, double min, double max)
	{
		if (x < min) return min;
		if (x > max) return max;
		return x;
	}
}
