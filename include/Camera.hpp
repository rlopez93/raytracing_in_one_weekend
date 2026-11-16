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

    auto render(Hittable const& world) -> void;

  private:
    int    image_height{0};
    double pixel_samples_scale{};
    Point3 center{};
    Point3 pixel00_loc{};
    Vec3   pixel_delta_u{};
    Vec3   pixel_delta_v{};

    auto initialize() -> void;

    auto ray_color(
        Ray const&      ray,
        Hittable const& world) const -> Color;

    auto get_ray(
        int i,
        int j) const -> Ray;

    auto sample_square() const -> Color;
};
