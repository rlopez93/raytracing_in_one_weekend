#include "Material.hpp"
#include "Vec3.hpp"
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
Metal::Metal(Color const& albedo)
    : albedo(albedo)
{
}
auto Metal::scatter(
    Ray const&       inRay,
    HitRecord const& record,
    Color&           attenuation,
    Ray&             scattered) const -> bool
{
    auto reflected = reflect(inRay.direction(), record.normal);
    scattered      = Ray{record.p, reflected};
    attenuation    = albedo;
    return true;
}
