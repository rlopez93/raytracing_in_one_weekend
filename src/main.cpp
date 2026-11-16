#include "Camera.hpp"
#include "HittableList.hpp"
#include "Sphere.hpp"
#include "Vec3.hpp"

int main(
    int   argc,
    char* argv[])
{
    auto world = HittableList{};

    world.add(std::make_shared<Sphere>(Point3{0.0, 0.0, -1.0}, 0.5));
    world.add(std::make_shared<Sphere>(Point3{0.0, -100.5, -1.0}, 100.0));

    auto camera              = Camera{};
    camera.aspect_ratio      = 16.0 / 9.0;
    camera.image_width       = 400;
    camera.samples_per_pixel = 100;

    camera.render(world);
}
