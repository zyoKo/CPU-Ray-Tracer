#include "PathTracer.h"

#include <iostream>
#include <memory>

#include "Constants/Constants.h"
#include "Geometry/Sphere.h"
#include "Math/vec3.h"
#include "Math/Constants/Constants.h"
#include "Utilities/color.h"

namespace PathTracer
{
    // TODO: Find a better place for this function
    Math::color RayColor(const Ray& ray, const IHittable& world)
    {
        HitRecord hitRecord;

        if (world.Hit(ray, 0, Math::INFINITY_DOUBLE, hitRecord))
        {
            return 0.5 * (hitRecord.normal + Math::color(1.0));
        }

        const Math::vec3 unitDirection = GetUnitVector(ray.GetDirection());
        const auto t = 0.5 * (unitDirection.y() + 1.0);
        return (1.0 - t) * Math::color(1.0, 1.0, 1.0) + t * Math::color(0.5, 0.7, 1.0);
    }

	void PathTracer::Init()
	{
		world.Add(std::make_shared<Sphere>(Math::point3( 0.0,    0.0, -1.0),   0.5));
		world.Add(std::make_shared<Sphere>(Math::point3( 0.0, -100.5, -1.0), 100.0));
		world.Add(std::make_shared<Sphere>(Math::point3(-1.0,    0.0, -1.0),   0.5));
		world.Add(std::make_shared<Sphere>(Math::point3( 1.0,    0.0, -1.0),   0.5));
	}

	void PathTracer::Run()
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
                    pixelColor += RayColor(ray, world);
                }

                WriteColor(std::cout, pixelColor, SAMPLES_PER_PIXEL);
            }
        }

        std::cerr << "\nDone.\n";
	}
}
