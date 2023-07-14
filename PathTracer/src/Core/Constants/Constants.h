#pragma once

namespace PathTracer
{
    // Image
    constexpr auto ASPECT_RATIO_IMAGE = 16.0 / 9.0;

    constexpr int IMAGE_WIDTH = 400;

	constexpr int IMAGE_HEIGHT = static_cast<int>(IMAGE_WIDTH / ASPECT_RATIO_IMAGE);

	constexpr int SAMPLES_PER_PIXEL = 100;    // anti-aliasing
}