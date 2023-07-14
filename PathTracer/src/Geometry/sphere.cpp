#include "Sphere.h"

namespace PathTracer
{
    Sphere::Sphere(const Math::point3& center, double radius)
        :   center(center),
			radius(radius)
    {}

    Math::point3 Sphere::GetCenter() const
    {
        return center;
    }

    double Sphere::GetRadius() const
    {
        return radius;
    }

    bool Sphere::Hit(const Ray& ray, double t_min, double t_max, HitRecord& rec) const
    {
	    Math::vec3 oc = ray.GetOrigin() - center;
        auto a = ray.GetDirection().LengthSquared();
        auto half_b = Dot(oc, ray.GetDirection());
        auto c = oc.LengthSquared() - radius * radius;

        const auto discriminant = std::pow(half_b, 2) - a * c;
        if (discriminant < 0) return false;
        auto sqrt_discriminant = sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        auto root = (-half_b - sqrt_discriminant) / a;
        if (root < t_min || t_max < root) {
            root = (-half_b + sqrt_discriminant) / a;
            if (root < t_min || t_max < root)
                return false;
        }

        rec.t = root;
        rec.p = ray.At(rec.t);
        const Math::vec3 outwardNormal = (rec.p - center) / radius;
        rec.SetFaceNormal(ray, outwardNormal);

        return true;
    }
}
