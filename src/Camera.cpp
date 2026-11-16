#include "Camera.hpp"
#include "Color.hpp"
#include "Vec3.hpp"

#include "random.hpp"
using Random = ilqvya::Random;

#include <iostream>
#include <print>
#include <ranges>

auto Camera::render(Hittable const& world) -> void
{
    initialize();

    std::print("P3\n{} {}\n255\n", image_width, image_height);

    for (auto h : std::views::iota(0, image_height)) {
        for (auto w : std::views::iota(0, image_width)) {

            auto pixel_color = Color{0.0, 0.0, 0.0};

            for (auto sample : std::views::iota(0, samples_per_pixel)) {
                auto ray = get_ray(w, h);
                pixel_color += ray_color(ray, world);
            }

            write_color(std::cout, pixel_color * pixel_samples_scale);
        }
    }
}

auto Camera::initialize() -> void
{
    image_height = std::max(1, static_cast<int>(image_width / aspect_ratio));

    pixel_samples_scale = 1.0 / samples_per_pixel;

    center = Point3{0.0, 0.0, 0.0};

    auto focal_length    = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width =
        viewport_height * (static_cast<double>(image_width) / image_height);
    auto viewport_u = Vec3{viewport_width, 0.0, 0.0};
    auto viewport_v = Vec3{0.0, -viewport_height, 0.0};

    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    auto viewport_upper_left =
        center - Vec3{0.0, 0.0, focal_length} - viewport_u / 2.0 - viewport_v / 2.0;

    pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
}

auto Camera::ray_color(
    Ray const&      ray,
    Hittable const& world) const -> Color
{
    constexpr auto infinity = std::numeric_limits<double>::infinity();
    auto           record   = HitRecord{};

    if (world.hit(ray, Interval{0.0, infinity}, record)) {
        return 0.5 * (record.normal + Color{1.0, 1.0, 1.0});
    }

    auto unit_direction = unit_vector(ray.direction());
    auto t              = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * Color{1.0, 1.0, 1.0} + t * Color{0.5, 0.7, 1.0};
}
auto Camera::get_ray(
    int i,
    int j) const -> Ray
{
    auto offset       = sample_square();
    auto pixel_sample = pixel00_loc + ((i + offset.x()) * pixel_delta_u)
                      + ((j + offset.y()) * pixel_delta_v);

    return {center, pixel_sample - center};
}
auto Camera::sample_square() const -> Color
{
    return {Random::get(-0.5, 0.5), Random::get(-0.5, 0.5), 0.0};
}
