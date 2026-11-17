#pragma once

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
