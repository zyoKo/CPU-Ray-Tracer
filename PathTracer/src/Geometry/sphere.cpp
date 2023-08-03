#include "Sphere.h"

namespace PathTracer
{
    Sphere::Sphere(const Math::point3& center, double radius, std::shared_ptr<IMaterial> material)
        :   center(center),
			radius(radius),
			material(material)
    {}

    Math::point3 Sphere::GetCenter() const
    {
        return center;
    }

    double Sphere::GetRadius() const
    {
        return radius;
    }

    bool Sphere::Hit(const Ray& ray, double t_min, double t_max, HitRecord& hitRecord) const
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

        hitRecord.t = root;
        hitRecord.p = ray.At(hitRecord.t);
        const Math::vec3 outwardNormal = (hitRecord.p - center) / radius;
        hitRecord.SetFaceNormal(ray, outwardNormal);
        hitRecord.material = material;

        return true;
    }
}
