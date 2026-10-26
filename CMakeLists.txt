cmake_minimum_required(VERSION 3.31)
project(RayTracer)

set(CMAKE_CXX_STANDARD 20)

add_executable(RayTracer
        src/main.cpp
        src/core/vec3.h
        src/core/color.h
        src/core/ray.h
        src/core/interval.h
        src/core/utility.h
        src/geometry/hittable.h
        src/geometry/hittable_list.h
        src/geometry/sphere.h
        src/geometry/cube.h
        src/materials/material.h
        src/acceleration/aabb.h
        src/acceleration/bvh.h
        src/render/camera.h
)

target_include_directories(RayTracer PRIVATE src)
