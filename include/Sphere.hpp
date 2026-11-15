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
        double     t_min,
        double     t_max,
        HitRecord& record) const -> bool override;

  private:
    Point3 center_;
    double radius_;
};
