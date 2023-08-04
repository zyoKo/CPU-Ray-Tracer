#include "PathTracer.h"

#include <iostream>
#include <memory>

#include "Constants/Constants.h"
#include "Geometry/Sphere.h"
#include "Material/IMaterial.h"
#include "Math/vec3.h"
#include "Math/Constants/Constants.h"
#include "Utilities/color.h"

namespace PathTracer
{
	void PathTracer::Init()
	{
        materialGround       = std::make_shared<Lambertian>(GROUND_SPHERE_ALBEDO);
        materialMiddleSphere = std::make_shared<Lambertian>(MIDDLE_SPHERE_ALBEDO);
        materialLeftSphere   = std::make_shared<Metal>(LEFT_SPHERE_ALBEDO,  LEFT_SPHERE_FUZZINESS);
        materialRightSphere  = std::make_shared<Metal>(RIGHT_SPHERE_ALBEDO, RIGHT_SPHERE_FUZZINESS);
        materialDielectric   = std::make_shared<Dielectric>(1.5);

		world.Add(std::make_shared<Sphere>(GROUND_SPHERE_POSITION,  GROUND_SPHERE_RADIUS, materialGround));
		world.Add(std::make_shared<Sphere>(LEFT_SPHERE_POSITION,   -NORMAL_SPHERE_RADIUS, materialDielectric));  // Left Sphere
		world.Add(std::make_shared<Sphere>(MIDDLE_SPHERE_POSITION,  HOLLOW_GLASS_RADIUS,  materialDielectric));  // Middle Sphere
		world.Add(std::make_shared<Sphere>(RIGHT_SPHERE_POSITION,   NORMAL_SPHERE_RADIUS, materialRightSphere)); // Right Sphere
	}

	void PathTracer::Run() const
	{
        // Render
        std::cout << "P3\n" << IMAGE_WIDTH << " " << IMAGE_HEIGHT << "\n255\n";

        for (int j = IMAGE_HEIGHT - 1; j >= 0; --j)
        {
            std::cerr << "\rScan-lines remaining: " << j << ' ' << std::flush;
            for (int i = 0; i < IMAGE_WIDTH; ++i)
            {
                Math::color pixelColor(0.0, 0.0, 0.0);
                for (int s = 0; s < SAMPLES_PER_PIXEL; ++s)
                {
                    const auto u = (i + Math::RandomDoublePrecise()) / (IMAGE_WIDTH  - 1);
                    const auto v = (j + Math::RandomDoublePrecise()) / (IMAGE_HEIGHT - 1);

                    Ray ray = camera.GetRay(u, v);
                    pixelColor += RayColor(ray, world, MAX_DEPTH);
                }

                WriteColor(std::cout, pixelColor, SAMPLES_PER_PIXEL);
            }
        }

        std::cerr << "\nDone.\n";
	}

    // Private/Helper Functions
    Math::color PathTracer::RayColor(const Ray& ray, const IHittable& world, int depth)
    {
        HitRecord hitRecord;

        // If exceeded the ray bounce limit, no more light gathered!
        if (depth <= 0)
            return { 0.0, 0.0, 0.0 };

        if (world.Hit(ray, 0.001, Math::INFINITY_DOUBLE, hitRecord))
        {
            //const Math::point3 target = hitRecord.p + hitRecord.normal + Math::RandomUnitVector();      // True Lambertian Reflection
            //const Math::point3 target = hitRecord.p + hitRecord.normal + Math::RandomInUnitSphere();    // Rejection Method
            //const Math::point3 target = hitRecord.p + hitRecord.normal + RandomInHemisphere(hitRecord.normal); // Old-Style Diffuse Method
            
            //return 0.5 * RayColor(Ray(hitRecord.p, target - hitRecord.p), world, depth - 1);

            Ray scattered;
            Math::color attenuation;

            if (hitRecord.material->Scatter(ray, hitRecord, attenuation, scattered))
				return attenuation * RayColor(scattered, world, depth - 1);

            return { 0.0, 0.0, 0.0 };
        }

        const Math::vec3 unitDirection = GetUnitVector(ray.GetDirection());
        const auto t = 0.5 * (unitDirection.y() + 1.0);
        return (1.0 - t) * BACKGROUND_COLOR_START + t * BACKGROUND_COLOR_END;
    }
}
