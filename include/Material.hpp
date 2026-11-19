#pragma once

#include "Color.hpp"
#include "Hittable.hpp"
#include "Ray.hpp"

class Material
{
  public:
    virtual ~Material() = default;

    virtual auto scatter(
        Ray const&       inRay,
        HitRecord const& record,
        Color&           attenuation,
        Ray&             scattered) const -> bool
    {
        return false;
    }
};

class Lambertian : public Material
{
  public:
    Lambertian(Color const& albedo);

    auto scatter(
        Ray const&       inRay,
        HitRecord const& record,
        Color&           attenuation,
        Ray&             scattered) const -> bool override;

  private:
    Color albedo;
};

class Metal : public Material
{
  public:
    Metal(
        Color const& albedo,
        double       fuzz);

    auto scatter(
        Ray const&       inRay,
        HitRecord const& record,
        Color&           attenuation,
        Ray&             scattered) const -> bool override;

  private:
    Color  albedo;
    double fuzz;
};

class Dielectric : public Material
{
  public:
    Dielectric(double refraction_index);

    auto scatter(
        Ray const&       inRay,
        HitRecord const& record,
        Color&           attenuation,
        Ray&             scattered) const -> bool override;

  private:
    double refraction_index;

    static auto reflectance(
        double cosine,
        double refraction_index) -> double;
};
