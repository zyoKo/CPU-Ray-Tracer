#include "PathTracer.h"

#include <iostream>
#include <memory>

#include "Camera/Constants/Constants.h"
#include "Constants/Constants.h"
#include "Geometry/Sphere.h"
#include "Material/Interface/IMaterial.h"
#include "Math/vec3.h"
#include "Math/Constants/Constants.h"
#include "Utilities/Color.h"
#include "Geometry/MovingSphere.h"

namespace PathTracer
{
    PathTracer::PathTracer()
	    :   camera(LOOK_FROM, LOOK_AT, VIEW_UP, FIELD_OF_VIEW, ASPECT_RATIO, APERTURE, FOCUS_DISTANCE, CAPTURE_START, CAPTURE_END)
    {
	    
    }

	void PathTracer::Init()
	{
        auto materialGround = std::make_shared<Lambertian>(GROUND_SPHERE_ALBEDO);
		world.Add(std::make_shared<Sphere>(GROUND_SPHERE_POSITION, GROUND_SPHERE_RADIUS, materialGround));

        for (int x = -11; x < 11; ++x)
        {
	        for (int y = -11; y < 11; ++y)
	        {
                const auto chooseMat = Math::RandomDoublePrecise();
                Math::point3 center(x + 0.9 * Math::RandomDoublePrecise(), 0.2, y + 0.9 * Math::RandomDoublePrecise());

                if ((center - Math::point3(4, 0.2, 0)).GetLength() > 0.9)
                {
                    std::shared_ptr<IMaterial> sphereMaterial;

                    if (chooseMat < 0.8)    // diffuse
                    {
                        auto albedo = Math::color::Random() * Math::color::Random();
                        sphereMaterial = std::make_shared<Lambertian>(albedo);
                        auto center2 = center + Math::vec3(0.0, Math::RandomDoubleInRangePrecise(0, 0.5), 0.0);
                        world.Add(std::make_shared<MovingSphere>(center, center2, CAPTURE_START, CAPTURE_END, 0.2, sphereMaterial));
                    }
                    else if (chooseMat < 0.95) 
                    {
                        // metal
                        auto albedo = Math::color::Random(0.5, 1);
                        auto fuzz = Math::RandomDoubleInRangePrecise(0, 0.5);
                        sphereMaterial = std::make_shared<Metal>(albedo, fuzz);
                        world.Add(std::make_shared<Sphere>(center, 0.2, sphereMaterial));
                    }
                    else 
                    {
                        // glass
                        sphereMaterial = std::make_shared<Dielectric>(1.5);
                        world.Add(std::make_shared<Sphere>(center, 0.2, sphereMaterial));
                    }
                }
	        }
        }

        auto material1 = std::make_shared<Dielectric>(1.5);
        world.Add(std::make_shared<Sphere>(Math::point3(0, 1, 0), 1.0, material1));

        auto material2 = std::make_shared<Lambertian>(Math::color(0.4, 0.2, 0.1));
        world.Add(std::make_shared<Sphere>(Math::point3(-4, 1, 0), 1.0, material2));

        auto material3 = std::make_shared<Metal>(Math::color(0.7, 0.6, 0.5), 0.0);
        world.Add(std::make_shared<Sphere>(Math::point3(4, 1, 0), 1.0, material3));
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
            // TODO: Apply different Diffuse Methods and test results with them
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

