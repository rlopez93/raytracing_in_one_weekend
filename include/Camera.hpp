#pragma once

#include "Color.hpp"
#include "Hittable.hpp"
#include "Ray.hpp"
#include "Vec3.hpp"
class Camera
{
  public:
    double aspect_ratio{1.0};
    int    image_width{100};
    int    samples_per_pixel{10};
    int    max_depth{10};

    double vfov{90.0};
    Point3 lookfrom{0.0, 0.0, 0.0};
    Point3 lookat{0.0, 0.0, -1.0};
    Vec3   vup{0.0, 1.0, 0.0};

    double defocus_angle  = 0.0;
    double focus_distance = 10.0;

    auto render(Hittable const& world) -> void;

  private:
    int    image_height{0};
    double pixel_samples_scale{};
    Point3 center{};
    Point3 pixel00_loc{};
    Vec3   pixel_delta_u{};
    Vec3   pixel_delta_v{};
    Vec3   u{};
    Vec3   v{};
    Vec3   w{};
    Vec3   defocus_disk_u{};
    Vec3   defocus_disk_v{};

    auto initialize() -> void;

    auto ray_color(
        Ray const&      ray,
        int             depth,
        Hittable const& world) const -> Color;

    auto get_ray(
        int i,
        int j) const -> Ray;

    auto sample_square() const -> Color;

    auto defocus_disk_sample() const -> Point3;
};
