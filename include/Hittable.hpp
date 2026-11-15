#pragma once

#include "Ray.hpp"

class HitRecord
{
  public:
    Point3 p;
    Vec3   normal;
    double t;
    bool   front_face;

    auto set_face_normal(
        Ray const&  ray,
        Vec3 const& outward_normal) -> void;
};

class Hittable
{
  public:
    virtual ~Hittable() = default;

    virtual auto
    hit(Ray const& ray,
        double     t_min,
        double     t_max,
        HitRecord& record) const -> bool = 0;
};
