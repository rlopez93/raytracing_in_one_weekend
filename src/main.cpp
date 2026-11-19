#include "Camera.hpp"
#include "Color.hpp"
#include "HittableList.hpp"
#include "Material.hpp"
#include "Sphere.hpp"
#include "Vec3.hpp"
#include "random.hpp"
#include <memory>
#include <ranges>

int main(
    int   argc,
    char* argv[])
{
    auto world = HittableList{};

    auto ground_material = std::make_shared<Lambertian>(Color{0.5, 0.5, 0.5});
    world.add(
        std::make_shared<Sphere>(Point3{0.0, -1000.0, 0.0}, 1000.0, ground_material));

    for (auto a : std::views::iota(-11, 11)) {
        for (auto b : std::views::iota(-11, 11)) {
            auto choose_material = Random::get(0.0, 1.0);
            auto center          = Point3{
                a + 0.9 * Random::get(0.0, 1.0),
                0.2,
                b + 0.9 * Random::get(0.0, 1.0)};

            if ((center - Point3{4, 0.2, 0}).length() > 0.9) {
                auto sphere_material = std::shared_ptr<Material>{};

                if (choose_material < 0.8) {
                    auto albedo     = Color::random() * Color::random();
                    sphere_material = std::make_shared<Lambertian>(albedo);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }

                else if (choose_material < 0.95) {
                    auto albedo     = Color::random(0.5, 1.0);
                    auto fuzz       = Random::get(0.0, 0.5);
                    sphere_material = std::make_shared<Metal>(albedo, fuzz);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }

                else {
                    sphere_material = std::make_shared<Dielectric>(1.5);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<Dielectric>(1.5);
    world.add(std::make_shared<Sphere>(Point3{0.0, 1.0, 0.0}, 1.0, material1));

    auto material2 = std::make_shared<Lambertian>(Color{0.4, 0.2, 0.1});
    world.add(std::make_shared<Sphere>(Point3{-4.0, 1.0, 0.0}, 1.0, material2));

    auto material3 = std::make_shared<Metal>(Color{0.7, 0.6, 0.5}, 0.0);
    world.add(std::make_shared<Sphere>(Point3{4.0, 1.0, 0.0}, 1.0, material3));

    auto camera              = Camera{};
    camera.aspect_ratio      = 16.0 / 9.0;
    camera.image_width       = 1200;
    camera.samples_per_pixel = 10;
    camera.max_depth         = 10;

    camera.vfov     = 20.0;
    camera.lookfrom = Point3{13.0, 2.0, 3.0};
    camera.lookat   = Point3{0.0, 0.0, 0.0};
    camera.vup      = Vec3{0.0, 1.0, 0.0};

    camera.defocus_angle  = 0.6;
    camera.focus_distance = 10.0;

    camera.render(world);
}
