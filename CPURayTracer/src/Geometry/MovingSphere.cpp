#include "MovingSphere.h"
#include "Physics/AABB_Helper.h"

namespace PathTracer
{
	MovingSphere::MovingSphere(
		Math::point3 center0, Math::point3 center1, 
		double timeAtCenter0, double timeAtCenter1,
		double radius, 
		std::shared_ptr<IMaterial> material)
		:	center0(center0), center1(center1), timeAtCenter0(timeAtCenter0), timeAtCenter1(timeAtCenter1), radius(radius), material(material)
	{}

	bool MovingSphere::Hit(const Ray& ray, double tMin, double tMax, HitRecord& hitRecord) const
	{
        const Math::vec3 oc = ray.GetOrigin() - GetPositionAtTime(ray.GetTime());
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
        const auto outwardNormal = (hitRecord.p - GetPositionAtTime(ray.GetTime())) / radius;
        hitRecord.SetFaceNormal(ray, outwardNormal);
        hitRecord.material = material;

        return true;
	}

	bool MovingSphere::BoundingBox(double startTime, double endTime, Physics::AABB& outputBoundingBox) const
	{
        Physics::AABB initialLocationBox(
            GetPositionAtTime(startTime) - Math::vec3(radius, radius, radius),
            GetPositionAtTime(startTime) + Math::vec3(radius, radius, radius));

        Physics::AABB finalLocationBox(
            GetPositionAtTime(endTime) - Math::vec3(radius, radius, radius),
            GetPositionAtTime(endTime) + Math::vec3(radius, radius, radius));

        outputBoundingBox = SurroundingBox(initialLocationBox, finalLocationBox);

        return true;
	}

	Math::point3 MovingSphere::GetPositionAtTime(double time) const
	{
        return center0 + (time - timeAtCenter0) / (timeAtCenter1 - timeAtCenter0) * (center1 - center0);
	}

	Physics::AABB MovingSphere::BoundingBox() const
	{
        return testCollider;
	}
}
