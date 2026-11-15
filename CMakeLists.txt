cmake_minimum_required(VERSION 3.15)
project(nienna LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(raytracer)

target_sources(raytracer PRIVATE
    src/main.cpp
    src/Vec3.cpp
    src/Color.cpp
    src/Ray.cpp
    src/Sphere.cpp
    src/Hittable.cpp
)

target_include_directories(raytracer PRIVATE
    include
)
