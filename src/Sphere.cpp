#include "Sphere.hpp"
#include <cmath>

Sphere::Sphere(
    Point3 const& center,
    double        radius)
    : center_{center},
      radius_{std::fmax(
          0,
          radius)}
{
}

auto Sphere::hit(
    Ray const& ray,
    double     t_min,
    double     t_max,
    HitRecord& record) const -> bool
{
    auto const& C = center_;
    auto const& Q = ray.origin();
    auto const& d = ray.direction();

    auto const& C_minus_Q = C - Q;

    auto a = d.length_squared();
    auto h = dot(d, C_minus_Q);
    auto c = C_minus_Q.length_squared() - (radius_ * radius_);

    auto discriminant = h * h - a * c;

    if (discriminant < 0) {
        return false;
    }

    auto sqrtd = std::sqrt(discriminant);

    auto root = (h - sqrtd) / a;

    if (root <= t_min || t_max <= root) {
        root = (h + sqrtd) / a;
        if (root <= t_min || t_max <= root) {
            return false;
        }
    }

    record.t            = root;
    record.p            = ray.at(record.t);
    auto outward_normal = (record.p - center_) / radius_;
    record.set_face_normal(ray, outward_normal);

    return true;
}
