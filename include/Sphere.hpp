#pragma once

#include "Hittable.hpp"
#include "Vec3.hpp"
#include <memory>

class Sphere : public Hittable
{
  public:
    Sphere(
        Point3 const&             center,
        double                    radius,
        std::shared_ptr<Material> material);

    auto
    hit(Ray const& ray,
        Interval   ray_t,
        HitRecord& record) const -> bool override;

  private:
    Point3                    center_;
    double                    radius_;
    std::shared_ptr<Material> material_;
};
