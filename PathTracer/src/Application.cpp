#include <iostream>

#include "Constants/Constants.h"
#include "Geometry/sphere.h"
#include "Utilities/color.h"
#include "Geometry/ray.h"
#include "Math/vec3.h"
#include "Utilities/hittable_list.h"
#include "Camera/Camera.h"

namespace PathTracer
{
	Math::color RayColor(const ray& r, const hittable& world)
    {
        hit_record rec;
        if (world.hit(r, 0, INFINITY_DOUBLE, rec))
        {
            return 0.5 * (rec.normal + Math::color(1, 1, 1));
        }

        const Math::vec3 unit_direction = unit_vector(r.direction());
        const auto t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - t) * Math::color(1.0, 1.0, 1.0) + t * Math::color(0.5, 0.7, 1.0);
    }
}

int main()
{
    // Image
    constexpr auto aspect_ratio = 16.0 / 9.0;
    constexpr int image_width = 400;
    constexpr int image_height = static_cast<int>(image_width / aspect_ratio);
    constexpr int samplesPerPixel = 100;

    // World
    PathTracer::hittable_list world;
    world.add(std::make_shared<PathTracer::sphere>(PathTracer::Math::point3(0, 0, -1), 0.5));
    world.add(std::make_shared<PathTracer::sphere>(PathTracer::Math::point3(0, -100.5, -1), 100));
    world.add(std::make_shared<PathTracer::sphere>(PathTracer::Math::point3(-1, 0, -1), 0.5));
    world.add(std::make_shared<PathTracer::sphere>(PathTracer::Math::point3(1, 0, -1), 0.5));

    // Camera
    PathTracer::Camera camera;

    // Render
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j)
    {
        std::cerr << "\rScan-lines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i)
        {
	        PathTracer::Math::color pixelColor(0.0, 0.0, 0.0);
            for (int s = 0; s < samplesPerPixel; ++s)
            {
                const auto u = (i + RandomDoublePrecise()) / (image_width - 1);
                const auto v = (j + RandomDoublePrecise()) / (image_height - 1);

                ray r = camera.GetRay(u, v);
                pixelColor += RayColor(r, world);
            }

            PathTracer::WriteColor(std::cout, pixelColor, samplesPerPixel);
        }
    }

    std::cerr << "\nDone.\n";

    return 0;
}