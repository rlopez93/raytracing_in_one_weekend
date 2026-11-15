#include "Hittable.hpp"

auto HitRecord::set_face_normal(
    Ray const&  ray,
    Vec3 const& outward_normal) -> void
{
    front_face = dot(ray.direction(), outward_normal) < 0.0;
    normal     = front_face ? outward_normal : -outward_normal;
}
