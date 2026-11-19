#pragma once

#include "random.hpp"
#include <cassert>
#include <cmath>
#include <format>
#include <ostream>

class Vec3
{
  public:
    double e[3];

    Vec3();

    Vec3(
        double e0,
        double e1,
        double e2);

    auto x() const -> double;
    auto y() const -> double;
    auto z() const -> double;

    auto operator-() const -> Vec3;
    auto operator[](int i) const -> double;
    auto operator[](int i) -> double&;

    auto operator+=(Vec3 const& v) -> Vec3&;
    auto operator*=(double t) -> Vec3&;
    auto operator/=(double t) -> Vec3&;

    auto length() const -> double;
    auto length_squared() const -> double;

    static auto random() -> Vec3;
    static auto random(
        double min,
        double max) -> Vec3;
};

using Point3 = Vec3;

template <> struct std::formatter<Vec3> : std::range_formatter<double> {
    constexpr formatter()
    {
        set_separator(" ");
        set_brackets("", "");
    }

    auto format(
        Vec3 const& v,
        auto&       ctx) const
    {
        return std::range_formatter<double>::format(v.e, ctx);
    }
};

inline auto operator+(
    Vec3 const& u,
    Vec3 const& v) -> Vec3
{
    return {u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]};
}

inline auto operator-(
    Vec3 const& u,
    Vec3 const& v) -> Vec3
{
    return {u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]};
}

inline auto operator*(
    Vec3 const& u,
    Vec3 const& v) -> Vec3
{
    return {u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]};
}

inline auto operator*(
    double      t,
    Vec3 const& v) -> Vec3
{
    return {t * v.e[0], t * v.e[1], t * v.e[2]};
}

inline auto operator*(
    Vec3 const& v,
    double      t) -> Vec3
{
    return t * v;
}

inline auto operator/(
    Vec3 const& v,
    double      t) -> Vec3
{
    assert(t != 0.0);
    return (1.0 / t) * v;
}

inline auto
dot(Vec3 const& u,
    Vec3 const& v) -> double
{
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

inline auto cross(
    Vec3 const& u,
    Vec3 const& v) -> Vec3
{
    return {
        u.e[1] * v.e[2] - u.e[2] * v.e[1],
        u.e[2] * v.e[0] - u.e[0] * v.e[2],
        u.e[0] * v.e[1] - u.e[1] * v.e[0]};
}

inline auto unit_vector(Vec3 const& v) -> Vec3
{
    return v / v.length();
}

inline auto random_unit_vector() -> Vec3
{
    while (true) {
        auto p     = Vec3::random(-1.0, 1.0);
        auto lensq = p.length_squared();
        if (std::isnormal(lensq) && lensq <= 1) {
            return p / std::sqrt(lensq);
        }
    }
}

inline auto random_in_unit_disk() -> Vec3
{
    while (true) {
        auto p = Vec3{Random::get(-1.0, 1.0), Random::get(-1.0, 1.0), 0.0};
        if (p.length_squared() < 1.0) {
            return p;
        }
    }
}

inline auto random_on_hemisphere(Vec3 const& normal) -> Vec3
{
    auto on_unit_sphere = random_unit_vector();
    if (dot(on_unit_sphere, normal) > 0.0) {
        return on_unit_sphere;
    } else {
        return -on_unit_sphere;
    }
}

inline auto reflect(
    Vec3 const& v,
    Vec3 const& n) -> Vec3
{
    return v - 2 * dot(v, n) * n;
}

inline auto refract(
    Vec3 const& uv,
    Vec3 const& n,
    double      etai_over_etat) -> Vec3
{
    auto cos_theta      = std::fmin(dot(-uv, n), 1.0);
    auto r_out_perp     = etai_over_etat * (uv + cos_theta * n);
    auto r_out_parallel = -std::sqrt(std::fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}
