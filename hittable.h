//
// Created by Victor on 01.08.2025.
//

#ifndef HITTABLE_H
#define HITTABLE_H


#include "ray.h"

class hit_record {
public:
    point3 p;
    vec3 normal;
    double t;
    bool front_face;

    void set_face_normal(const ray& r) {
        if (dot(normal,r.direction()) > 0) {
            front_face = false;
            normal = - normal;
        }
        else {
            front_face = true;
        }
    }
};


class hittable {
public:

    virtual ~hittable() = default;

    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;



};

class sphere: public hittable {
public:



    sphere(const point3& sphere_loc, double sphere_radius):
    sphere_loc(sphere_loc), sphere_radius(std::fmax(0,sphere_radius)) {}

    bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override {


        auto dir = r.direction();
        auto orig = r.origin();

        auto a = dir.length_squared();
        auto b = dot((2 * dir),(orig - sphere_loc));
        auto c = sphere_loc.length_squared() + orig.length_squared() - (2 * dot(sphere_loc,orig)) - (sphere_radius*sphere_radius);

        auto discriminant = b * b - 4 * a * c;

        // Check if ray touches sphere
        if (discriminant < 0) {
            return false;
        }
        auto t = (-b - std::sqrt(discriminant)) / (2 * a);
        if (t_min <= t && t <= t_max) {
            rec.t = t;
            rec.p = r.at(rec.t);
            rec.normal = unit_vector(rec.p - sphere_loc);
            rec.set_face_normal(r);
            return true;
        }
        if (t_max <= t) {
            return false;
        }
        t = (-b + std::sqrt(discriminant)) / (2 * a);
        if (t_min <= t && t <= t_max) {
            rec.t = t;
            rec.p = r.at(rec.t);
            rec.normal = unit_vector(rec.p - sphere_loc);
            rec.set_face_normal(r);
            return true;
        }
        return false;

    }
private:
    point3 sphere_loc;
    double sphere_radius;



};





#endif //HITTABLE_H
