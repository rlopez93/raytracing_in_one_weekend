#include "Color.hpp"

#include <cmath>
#include <print>

void write_color(
    std::ostream& out,
    Color const&  pixel_color)
{
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    auto rbyte = std::floor(255.999 * r);
    auto gbyte = std::floor(255.999 * g);
    auto bbyte = std::floor(255.999 * b);

    std::println(out, "{}", Color{rbyte, gbyte, bbyte});
}
