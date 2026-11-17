#include "Vec3.hpp"
#include "random.hpp"
#include <cmath>

Vec3::Vec3()
    : e{0,
        0,
        0}
{
}

Vec3::Vec3(
    double e0,
    double e1,
    double e2)
    : e{e0,
        e1,
        e2}
{
}

auto Vec3::x() const -> double
{
    return e[0];
}

auto Vec3::y() const -> double
{
    return e[1];
}

auto Vec3::z() const -> double
{
    return e[2];
}

auto Vec3::operator-() const -> Vec3
{
    return {-e[0], -e[1], -e[2]};
}

auto Vec3::operator[](int i) const -> double
{
    return e[i];
}

auto Vec3::operator[](int i) -> double&
{
    return e[i];
}

auto Vec3::operator+=(Vec3 const& v) -> Vec3&
{
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
}
auto Vec3::operator*=(double t) -> Vec3&
{
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}

auto Vec3::operator/=(double t) -> Vec3&
{
    assert(t != 0.0);
    return *this *= (1.0 / t);
}

auto Vec3::length() const -> double
{
    return std::sqrt(length_squared());
}

auto Vec3::length_squared() const -> double
{
    return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
}

auto Vec3::random() -> Vec3
{
    return {Random::get(0.0, 1.0), Random::get(0.0, 1.0), Random::get(0.0, 1.0)};
}
auto Vec3::random(
    double min,
    double max) -> Vec3
{
    return {Random::get(min, max), Random::get(min, max), Random::get(min, max)};
}
