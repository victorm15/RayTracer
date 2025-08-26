//
// Created by Victor on 25.08.2025.
//
#ifndef CUBE_H
#define CUBE_H

#include "hittable.h"
#include "utility.h"


class cube: public hittable {
public:

    cube(const point3& cube_loc, const double half_edge_length):
    cube_loc(cube_loc), half_edge_length(half_edge_length) {}

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {




        return false;
    }



private:
    point3 cube_loc;
    double half_edge_length;




};

#endif //CUBE_H
