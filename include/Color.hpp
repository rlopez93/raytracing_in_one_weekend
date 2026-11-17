#pragma once

#include "Vec3.hpp"
#include <cmath>

using Color = Vec3;

inline auto linear_to_gamma(double linear_component) -> double
{
    if (linear_component > 0) {
        return std::sqrt(linear_component);
    }

    return 0;
}

void write_color(
    std::ostream& out,
    Color const&  pixel_color);
