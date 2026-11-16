#include "Color.hpp"
#include "Hittable.hpp"
#include "HittableList.hpp"
#include "Ray.hpp"
#include "Sphere.hpp"
#include "Vec3.hpp"

#include <cmath>
#include <cstdio>
#include <iostream>
#include <limits>
#include <memory>
#include <print>
#include <ranges>

auto hit_sphere(
    Point3 const& center,
    double        radius,
    Ray const&    ray) -> double
{
    auto const& C = center;
    auto const& Q = ray.origin();
    auto const& d = ray.direction();

    auto const& C_minus_Q = C - Q;

    auto a = d.length_squared();
    auto h = dot(d, C_minus_Q);
    auto c = C_minus_Q.length_squared() - (radius * radius);

    auto discriminant = h * h - a * c;

    if (discriminant < 0) {
        return -1.0;
    } else {
        return (h - std::sqrt(discriminant)) / a;
    }
}

auto ray_color(
    Ray const&      ray,
    Hittable const& world) -> Color
{
    HitRecord record;
    if (world
            .hit(ray, Interval(0.0, std::numeric_limits<double>::infinity()), record)) {
        return 0.5 * (record.normal + Color{1.0, 1.0, 1.0});
    }

    auto unit_direction = unit_vector(ray.direction());
    auto l              = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - l) * Color{1.0, 1.0, 1.0} + l * Color{0.5, 0.7, 1.0};
}

auto ray_color(Ray const& ray) -> Color
{
    auto t = hit_sphere({0.0, 0.0, -1.0}, 0.5, ray);

    if (t > 0.0) {
        auto N = unit_vector(ray.at(t) - Vec3{0.0, 0.0, -1.0});
        return 0.5 * Color{N.x() + 1, N.y() + 1, N.z() + 1};
    }

    auto unit_direction = unit_vector(ray.direction());
    auto l              = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - l) * Color{1.0, 1.0, 1.0} + l * Color{0.5, 0.7, 1.0};
}

int main(
    int   argc,
    char* argv[])
{
    auto aspect_ratio = 16.0 / 9.0;
    auto image_width  = 400;

    auto image_height = std::max(1, static_cast<int>(image_width / aspect_ratio));

    auto world = HittableList{};

    world.add(std::make_shared<Sphere>(Point3{0.0, 0.0, -1.0}, 0.5));
    world.add(std::make_shared<Sphere>(Point3{0.0, -100.5, -1.0}, 100.0));

    auto focal_length    = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width =
        viewport_height * (static_cast<double>(image_width) / image_height);
    auto camera_center = Point3{0.0, 0.0, 0.0};

    auto viewport_u = Vec3{viewport_width, 0.0, 0.0};
    auto viewport_v = Vec3{0.0, -viewport_height, 0.0};

    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    auto viewport_upper_left = camera_center - Vec3{0.0, 0.0, focal_length}
                             - viewport_u / 2.0 - viewport_v / 2.0;

    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    std::print("P3\n{} {}\n255\n", image_width, image_height);

    for (auto h : std::views::iota(0, image_height)) {
        for (auto w : std::views::iota(0, image_width)) {

            auto pixel_center = pixel00_loc + (w * pixel_delta_u) + (h * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            auto ray           = Ray{camera_center, ray_direction};
            auto pixel_color   = ray_color(ray, world);

            write_color(std::cout, pixel_color);
        }
    }
}
