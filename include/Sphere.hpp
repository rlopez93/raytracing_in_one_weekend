#pragma once

#include "Hittable.hpp"
#include "Vec3.hpp"

class Sphere : public Hittable
{
  public:
    Sphere(
        Point3 const& center,
        double        radius);

    auto
    hit(Ray const& ray,
        Interval   ray_t,
        HitRecord& record) const -> bool override;

  private:
    Point3 center_;
    double radius_;
};
