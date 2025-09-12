//
// Created by Victor on 01.08.2025.
//

#ifndef HITTABLE_H
#define HITTABLE_H


#include "utility.h"
#include "aabb.h"

class material;

class hit_record {
public:
    point3 p;
    vec3 normal;
    double t;
    bool front_face;
    shared_ptr<material> mat;

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

    virtual bool hit(const ray& r, interval ray_t , hit_record& rec) const = 0;

    virtual aabb bounding_box() const = 0;



};






#endif //HITTABLE_H
