#include "Sphere.h"

namespace PathTracer
{
    Sphere::Sphere(const Math::point3& center, double radius, std::shared_ptr<IMaterial> material)
        :   center(center),
			radius(radius),
			material(material)
    {
    }

    Math::point3 Sphere::GetCenter() const
    {
        return center;
    }

    double Sphere::GetRadius() const
    {
        return radius;
    }

    bool Sphere::Hit(const Ray& ray, double tMin, double tMax, HitRecord& hitRecord) const
    {
	    const Math::vec3 oc = ray.GetOrigin() - center;
        const auto a = ray.GetDirection().LengthSquared();
        const auto half_b = Dot(oc, ray.GetDirection());
        const auto c = oc.LengthSquared() - radius * radius;

        const auto discriminant = std::pow(half_b, 2) - a * c;
        if (discriminant < 0) return false;
        const auto sqrt_discriminant = sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        auto root = (-half_b - sqrt_discriminant) / a;
        if (root < tMin || tMax < root) {
            root = (-half_b + sqrt_discriminant) / a;
            if (root < tMin || tMax < root)
                return false;
        }

        hitRecord.t = root;
        hitRecord.p = ray.At(hitRecord.t);
        const auto outwardNormal = (hitRecord.p - center) / radius;
        hitRecord.SetFaceNormal(ray, outwardNormal);
        hitRecord.material = material;

        return true;
    }

    bool Sphere::BoundingBox(double startTime, double endTime, Physics::AABB& outputBoundingBox) const
    {
        outputBoundingBox = Physics::AABB(
            center - Math::vec3(radius, radius, radius),
            center + Math::vec3(radius, radius, radius));

        return true;
    }

    Physics::AABB Sphere::BoundingBox() const
    {
        return testCollider;
    }
}
