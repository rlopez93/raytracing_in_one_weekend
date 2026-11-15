#pragma once

#include "Vec3.hpp"

class Ray
{
  public:
    Ray();

    Ray(Point3 const& origin,
        Vec3 const&   direction);

    auto origin() const -> Point3 const&;
    auto direction() const -> Point3 const&;

    auto at(double t) const -> Point3;

  private:
    Point3 origin_;
    Vec3   direction_;
};
