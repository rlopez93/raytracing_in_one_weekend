#pragma once

#include <cassert>
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
