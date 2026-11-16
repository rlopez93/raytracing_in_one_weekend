#include "Color.hpp"
#include "Interval.hpp"

#include <cmath>
#include <print>

void write_color(
    std::ostream& out,
    Color const&  pixel_color)
{
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    static auto const intensity = Interval{0.000, 0.999};

    auto rbyte = std::floor(256 * intensity.clamp(r));
    auto gbyte = std::floor(256 * intensity.clamp(g));
    auto bbyte = std::floor(256 * intensity.clamp(b));

    std::println(out, "{}", Color{rbyte, gbyte, bbyte});
}
