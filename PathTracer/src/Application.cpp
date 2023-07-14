#include <iostream>

#include "Math/Constants/Constants.h"
#include "Geometry/Sphere.h"
#include "Utilities/color.h"
#include "Geometry/Ray.h"
#include "Math/vec3.h"
#include "Utilities/HittableList.h"
#include "Camera/Camera.h"

namespace PathTracer
{
	Math::color RayColor(const Ray& ray, const Hittable& world)
    {
        HitRecord rec;

        if (world.Hit(ray, 0, INFINITY_DOUBLE, rec))
        {
            return 0.5 * (rec.normal + Math::color(1, 1, 1));
        }

        const Math::vec3 unitDirection = GetUnitVector(ray.GetDirection());
        const auto t = 0.5 * (unitDirection.y() + 1.0);
        return (1.0 - t) * Math::color(1.0, 1.0, 1.0) + t * Math::color(0.5, 0.7, 1.0);
    }
}

int main()
{
    // Image
    constexpr auto aspectRatio = 16.0 / 9.0;
    constexpr int imageWidth = 400;
    constexpr int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    constexpr int samplesPerPixel = 100;    // anti-aliasing

    // World
    PathTracer::HittableList world;
    world.Add(std::make_shared<PathTracer::Sphere>(PathTracer::Math::point3( 0.0,    0.0,   -1.0),   0.5));
    world.Add(std::make_shared<PathTracer::Sphere>(PathTracer::Math::point3( 0.0, -100.5,   -1.0), 100.0));
    world.Add(std::make_shared<PathTracer::Sphere>(PathTracer::Math::point3(-1.0,    0.0,   -1.0),   0.5));
    world.Add(std::make_shared<PathTracer::Sphere>(PathTracer::Math::point3( 1.0,    0.0,   -1.0),   0.5));

    // Camera
    PathTracer::Camera camera;

    // Render
    std::cout << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";

    for (int j = imageHeight - 1; j >= 0; --j)
    {
        std::cerr << "\rScan-lines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < imageWidth; ++i)
        {
	        PathTracer::Math::color pixelColor(0.0, 0.0, 0.0);
            for (int s = 0; s < samplesPerPixel; ++s)
            {
                const auto u = (i + PathTracer::RandomDoublePrecise()) / (imageWidth  - 1);
                const auto v = (j + PathTracer::RandomDoublePrecise()) / (imageHeight - 1);

                PathTracer::Ray ray = camera.GetRay(u, v);
                pixelColor += RayColor(ray, world);
            }

            PathTracer::WriteColor(std::cout, pixelColor, samplesPerPixel);
        }
    }

    std::cerr << "\nDone.\n";

    return 0;
}