#include "Camera.hpp"
#include "Color.hpp"
#include "Material.hpp"
#include "Vec3.hpp"

#include "random.hpp"

#include <iostream>
#include <numbers>
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
                pixel_color += ray_color(ray, max_depth, world);
            }

            write_color(std::cout, pixel_color * pixel_samples_scale);
        }
    }
}

auto Camera::initialize() -> void
{
    image_height        = std::max(1, static_cast<int>(image_width / aspect_ratio));
    pixel_samples_scale = 1.0 / samples_per_pixel;
    center              = lookfrom;

    auto theta           = std::numbers::pi * vfov / 180.0;
    auto h               = std::tan(theta / 2.0);
    auto viewport_height = 2.0 * h * focus_distance;
    auto viewport_width =
        viewport_height * (static_cast<double>(image_width) / image_height);

    w = unit_vector(lookfrom - lookat);
    u = unit_vector(cross(vup, w));
    v = cross(w, u);

    auto viewport_u = viewport_width * u;
    auto viewport_v = viewport_height * -v;

    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    auto viewport_upper_left =
        center - (focus_distance * w) - viewport_u / 2.0 - viewport_v / 2.0;

    pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    auto defocus_radius =
        focus_distance * std::tan((defocus_angle / 2.0) * std::numbers::pi / 180.0);
    defocus_disk_u = u * defocus_radius;
    defocus_disk_v = v * defocus_radius;
}

auto Camera::ray_color(
    Ray const&      ray,
    int             depth,
    Hittable const& world) const -> Color
{
    if (depth <= 0) {
        return {0.0, 0.0, 0.0};
    }
    constexpr auto infinity = std::numeric_limits<double>::infinity();
    auto           record   = HitRecord{};

    if (world.hit(ray, Interval{0.001, infinity}, record)) {
        auto scattered   = Ray{};
        auto attenuation = Color{};

        if (record.material->scatter(ray, record, attenuation, scattered)) {
            return attenuation * ray_color(scattered, depth - 1, world);
        }

        return {0.0, 0.0, 0.0};
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

    auto ray_origin    = (defocus_angle <= 0) ? center : defocus_disk_sample();
    auto ray_direction = pixel_sample - ray_origin;

    return {ray_origin, ray_direction};
}
auto Camera::sample_square() const -> Color
{
    return {Random::get(-0.5, 0.5), Random::get(-0.5, 0.5), 0.0};
}
auto Camera::defocus_disk_sample() const -> Point3
{
    auto p = random_in_unit_disk();
    return center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
}
