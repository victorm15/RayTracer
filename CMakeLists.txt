cmake_minimum_required(VERSION 3.31)
project(RayTracer)

set(CMAKE_CXX_STANDARD 20)

add_executable(RayTracer main.cpp
        vec3.h
        color.h
        ray.h
        hittable.h
        hittable_list.h
        interval.h
        utility.h
        sphere.h
        camera.h
        cube.h
        material.h
        aabb.h
        bvh.h
)
