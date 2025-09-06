//
// Created by Victor on 18.08.2025.
//
#include "utility.h"
#ifndef SPHERE_H
#define SPHERE_H

using std::shared_ptr;

class sphere: public hittable {
public:


    // Constructor
    sphere(const point3& sphere_loc, double sphere_radius, shared_ptr<material> mat):
    sphere_loc(sphere_loc), sphere_radius(std::fmax(0,sphere_radius)), mat(mat) {
        vec3 rvec = vec3(sphere_radius, sphere_radius, sphere_radius);
        bbox = aabb(sphere_loc - rvec, sphere_loc + rvec);
    }

    // Hit function


    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {



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
        if (ray_t.surrounds(t)) {
            rec.t = t;
            rec.p = r.at(rec.t);
            rec.normal = unit_vector(rec.p - sphere_loc);
            rec.set_face_normal(r);
            rec.mat = mat;
            return true;
        }
        if (ray_t.max <= t) {
            return false;
        }
        t = (-b + std::sqrt(discriminant)) / (2 * a);
        if (ray_t.surrounds(t)) {
            rec.t = t;
            rec.p = r.at(rec.t);
            rec.normal = unit_vector(rec.p - sphere_loc);
            rec.set_face_normal(r);
            rec.mat = mat;
            return true;
        }
        return false;

    }
    aabb bounding_box() const override {
        return bbox;
    }

private:
    point3 sphere_loc;
    double sphere_radius;
    shared_ptr<material> mat;
    aabb bbox;



};



#endif //SPHERE_H
