#include "Color.hpp"
#include "Vec3.hpp"
#include <cstdio>
#include <iostream>
#include <print>
#include <ranges>

int main(
    int   argc,
    char* argv[])
{

    auto image_width  = 256;
    auto image_height = 256;
    std::print("P3\n{} {}\n255\n", image_width, image_height);

    for (auto h : std::views::iota(0, image_height)) {
        for (auto w : std::views::iota(0, image_width)) {
            auto r = static_cast<double>(w) / (image_width - 1);
            auto g = static_cast<double>(h) / (image_height - 1);
            auto b = 0.0;

            write_color(std::cout, Color{r, g, b});
        }
    }
}
