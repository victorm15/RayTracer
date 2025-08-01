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
        auto c = sphere_loc.length_squared() + orig.length_squared() -2 * dot(sphere_loc,orig) - sphere_radius*sphere_radius;

        auto discriminant = b * b - 4 * a * c;

        // Check if ray touches sphere
        if (discriminant < 0) {return false;}

        // Update hit_record
        // if (t_min <= (-b - std::sqrt(discriminant) / (2a)) && )
        rec.t = (-b - std::sqrt(discriminant)) / (2 * a);
        // std::clog << rec.t <<"\n";
        rec.p = r.at(rec.t);
        if (rec.p.z()>=-1){std::clog << rec.p.z();}
        rec.normal = unit_vector(rec.p - sphere_loc);


        return true;


    }
private:
    point3 sphere_loc;
    double sphere_radius;



};





#endif //HITTABLE_H
