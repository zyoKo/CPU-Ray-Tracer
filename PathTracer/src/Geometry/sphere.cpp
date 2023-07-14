#include "sphere.h"

namespace PathTracer
{
    sphere::sphere(Math::point3 cen, double r)
        :   center(cen),
			radius(r)
    {}

    Math::point3 sphere::GetCenter() const
    {
        return center;
    }

    double sphere::GetRadius() const
    {
        return radius;
    }

    bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const
    {
	    Math::vec3 oc = r.origin() - center;
        auto a = r.direction().length_squared();
        auto half_b = dot(oc, r.direction());
        auto c = oc.length_squared() - radius * radius;

        auto discriminant = half_b * half_b - a * c;
        if (discriminant < 0) return false;
        auto sqrtd = sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        auto root = (-half_b - sqrtd) / a;
        if (root < t_min || t_max < root) {
            root = (-half_b + sqrtd) / a;
            if (root < t_min || t_max < root)
                return false;
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        Math::vec3 outward_normal = (rec.p - center) / radius;
        rec.set_face_normal(r, outward_normal);

        return true;
    }
}
