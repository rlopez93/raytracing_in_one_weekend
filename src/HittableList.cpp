#include "HittableList.hpp"
#include "Hittable.hpp"

HittableList::HittableList()
{
}

HittableList::HittableList(std::shared_ptr<Hittable> object)
{
    add(object);
}

auto HittableList::clear() -> void
{
    objects.clear();
}

auto HittableList::add(std::shared_ptr<Hittable> object) -> void
{
    objects.push_back(object);
}

auto HittableList::hit(
    Ray const& ray,
    Interval   ray_t,
    HitRecord& record) const -> bool
{
    auto temp_record    = HitRecord{};
    auto hit_anything   = false;
    auto closest_so_far = ray_t.max_;

    for (auto const& object : objects) {
        if (object->hit(ray, Interval(ray_t.min_, closest_so_far), temp_record)) {
            hit_anything   = true;
            closest_so_far = temp_record.t;
            record         = temp_record;
        }
    }
    return hit_anything;
}
