#pragma once

#include <cmath>
#include <iostream>

#include "Constants/Constants.h"

namespace PathTracer::Math
{
	class vec3
	{
	public:
		vec3()
			:	e{ 0.0, 0.0, 0.0 }
		{}

		vec3(double e0, double e1, double e2)
			:	e{ e0, e1, e2 }
		{}

		vec3(double value)
			:	e{ value, value, value }
		{}

		double x() const { return e[0]; }
		double y() const { return e[1]; }
		double z() const { return e[2]; }

		vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
		double operator[](int i) const { return e[i]; }
		double& operator[](int i) { return e[i]; }

		vec3& operator+=(const vec3& v)
		{
			e[0] += v.e[0];
			e[1] += v.e[1];
			e[2] += v.e[2];
			return *this;
		}

		vec3& operator*=(const double t)
		{
			e[0] *= t;
			e[1] *= t;
			e[2] *= t;
			return *this;
		}

		vec3& operator/=(const double t) { return *this *= 1 / t; }

		double GetLength() const { return sqrt(LengthSquared()); }
		double LengthSquared() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }

		static vec3 Random() { return {RandomDoublePrecise(),RandomDoublePrecise(), RandomDoublePrecise()}; }
		static vec3 Random(double min, double max)
		{
			return {	RandomDoubleInRangePrecise(min, max),
						RandomDoubleInRangePrecise(min, max),
						RandomDoubleInRangePrecise(min, max)};
		}

		bool NearZero() const
		{
			// Return true if vector is close to zero in all dimensions
			constexpr auto s = 1e-8;
			return (std::fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
		}

		friend std::ostream& operator<<(std::ostream& out, const vec3& v);
		friend vec3 operator+(const vec3& u, const vec3& v);
		friend vec3 operator-(const vec3& u, const vec3& v);
		friend vec3 operator*(const vec3& u, const vec3& v);
		friend vec3 operator*(double t, const vec3& v);
		friend vec3 operator*(const vec3& v, double t);
		friend vec3 operator/(vec3 v, double t);
		friend double Dot(const vec3& u, const vec3& v);
		friend vec3 Cross(const vec3& u, const vec3& v);
		friend vec3 GetUnitVector(vec3 v);

	private:
		double e[3];
	};

	// Type aliases for vec3
	using point3 = vec3;   // 3D point
	using color = vec3;    // RGB color

	// vec3 Utility Functions

	inline std::ostream& operator<<(std::ostream& out, const vec3& v) { return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2]; }

	inline vec3 operator+(const vec3& u, const vec3& v) { return { u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2] }; }

	inline vec3 operator-(const vec3& u, const vec3& v) { return { u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2] }; }

	inline vec3 operator*(const vec3& u, const vec3& v) { return {u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]}; }

	inline vec3 operator*(double t, const vec3& v) { return {t * v.e[0], t * v.e[1], t * v.e[2]}; }

	inline vec3 operator*(const vec3& v, double t) { return t * v; }

	inline vec3 operator/(vec3 v, double t) { return (1 / t) * v; }

	inline double Dot(const vec3& u, const vec3& v)
	{
		return u.e[0] * v.e[0]
			 + u.e[1] * v.e[1]
			 + u.e[2] * v.e[2];
	}

	inline vec3 Cross(const vec3& u, const vec3& v)
	{
		return {
			u.e[1] * v.e[2] - u.e[2] * v.e[1],
			u.e[2] * v.e[0] - u.e[0] * v.e[2],
			u.e[0] * v.e[1] - u.e[1] * v.e[0]
		};
	}

	inline vec3 GetUnitVector(vec3 v) { return v / v.GetLength(); }

	inline vec3 RandomInUnitSphere()
	{
		while(true)
		{
			auto p = vec3::Random(-1.0, 1.0);
			if (p.LengthSquared() >= 1.0)
				continue;
			return p;
		}
	}

	inline vec3 RandomUnitVector()
	{
		return GetUnitVector(RandomInUnitSphere());
	}

	inline vec3 RandomInHemisphere(const vec3& normal)
	{
		const vec3 inUnitSphere = RandomInUnitSphere();

		if (Dot(inUnitSphere, normal) > 0.0)	// In the same hemisphere as the normal
			return inUnitSphere;
		else
			return -inUnitSphere;
	}

	inline vec3 Reflection(const vec3& v, const vec3& n)
	{
		return v - 2 * Dot(v, n) * n;	// 9.4
	}

	inline vec3 Refraction(const vec3& uv, const vec3& n, double etaiOverEtat)
	{
		const auto cosTheta = std::fmin(Dot(-uv, n), 1.0);
		const vec3 rayOutPerpendicular = etaiOverEtat * (uv + cosTheta * n);
		const vec3 rayOutParallel = -std::sqrt(std::fabs(1.0 - rayOutPerpendicular.LengthSquared())) * n;
		return rayOutPerpendicular + rayOutParallel;
	}
}
