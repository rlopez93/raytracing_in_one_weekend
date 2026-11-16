#pragma once

#include "Hittable.hpp"

#include <memory>
#include <vector>

class HittableList : public Hittable
{
  public:
    std::vector<std::shared_ptr<Hittable>> objects;

    HittableList();
    HittableList(std::shared_ptr<Hittable> object);

    auto clear() -> void;
    auto add(std::shared_ptr<Hittable> object) -> void;

    auto
    hit(Ray const& ray,
        Interval   ray_t,
        HitRecord& record) const -> bool override;
};
