#include "Ray.hpp"

Ray::Ray()
{
}

Ray::Ray(
    Point3 const& origin,
    Vec3 const&   direction)
    : origin_(origin),
      direction_(direction)
{
}

auto Ray::at(double t) const -> Point3
{
    return origin_ + t * direction_;
}

auto Ray::origin() const -> Point3 const&
{
    return origin_;
}

auto Ray::direction() const -> Point3 const&
{
    return direction_;
}
