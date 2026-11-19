#include "Material.hpp"
#include "Vec3.hpp"
#include "random.hpp"
#include <cmath>

Lambertian::Lambertian(Color const& albedo)
    : albedo(albedo)
{
}
auto Lambertian::scatter(
    Ray const&       inRay,
    HitRecord const& record,
    Color&           attenuation,
    Ray&             scattered) const -> bool
{
    auto scatter_direction = record.normal + random_unit_vector();

    while (!std::isnormal(scatter_direction.length_squared())) {
        scatter_direction = record.normal + random_unit_vector();
    }

    scattered   = Ray{record.p, scatter_direction};
    attenuation = albedo;
    return true;
}
Metal::Metal(
    Color const& albedo,
    double       fuzz)
    : albedo(albedo),
      fuzz(
          std::max(
              fuzz,
              1.0))
{
}
auto Metal::scatter(
    Ray const&       inRay,
    HitRecord const& record,
    Color&           attenuation,
    Ray&             scattered) const -> bool
{
    auto reflected = reflect(inRay.direction(), record.normal);
    reflected      = unit_vector(reflected) + (fuzz * random_unit_vector());
    scattered      = Ray{record.p, reflected};
    attenuation    = albedo;
    return dot(scattered.direction(), record.normal) > 0;
}
Dielectric::Dielectric(double refraction_index)
    : refraction_index(refraction_index)
{
}

auto Dielectric::scatter(
    Ray const&       inRay,
    HitRecord const& record,
    Color&           attenuation,
    Ray&             scattered) const -> bool
{
    attenuation = Color{1.0, 1.0, 1.0};
    auto ri     = record.front_face ? (1.0 / refraction_index) : refraction_index;

    auto unit_direction = unit_vector(inRay.direction());
    auto cos_theta      = std::fmin(dot(-unit_direction, record.normal), 1.0);
    auto sin_theta      = std::sqrt(1.0 - cos_theta * cos_theta);

    auto cannot_refract = (ri * sin_theta) > 1.0;

    auto direction = [&] -> Vec3 {
        if (cannot_refract || reflectance(cos_theta, ri) > Random::get(0.0, 1.0)) {
            return reflect(unit_direction, record.normal);
        } else {
            return refract(unit_direction, record.normal, ri);
        }
    }();

    scattered = Ray{record.p, direction};
    return true;
}

auto Dielectric::reflectance(
    double cosine,
    double refraction_index) -> double
{
    auto r0 = (1.0 - refraction_index) / (1.0 + refraction_index);
    r0      = r0 * r0;
    return r0 + (1.0 - r0) * std::pow(1.0 - cosine, 5.0);
}
