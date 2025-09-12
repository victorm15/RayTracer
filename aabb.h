//
// Created by Victor on 06.09.2025.
//



#ifndef AABB_H
#define AABB_H

#include "utility.h"



class aabb {
public:
    interval x,y,z;

    aabb() {}

    aabb(const interval& x, const interval& y, const interval& z): x(x), y(y), z(z) {}

    aabb(const point3& a, const point3& b) {
        x = interval(a.x(),b.x());
        y = interval(a.y(),b.y());
        z = interval(a.z(),b.z());

    }

    aabb(const aabb& a, const aabb& b) {
        x = interval(a.x,b.x);
        y = interval(a.y,b.y);
        z  = interval(a.z,b.z);
    }

    bool hit(const ray&r, interval ray_t) const {

        vec3 dir = r.direction();

        vec3 orig = r.origin();

        if (((dir.x() != 0) || x.contains(orig.x())) &&
            ((dir.y() != 0) || y.contains(orig.y())) &&
            ((dir.z() != 0) || z.contains(orig.z()))) {

            interval t_x = (dir.x() == 0) ? ray_t : interval((x.min - orig.x()) / dir.x(),
                (x.max - orig.x()) / dir.x());

            interval t_y = (dir.y() == 0) ? ray_t : interval((y.min - orig.y()) / dir.y(),
                (y.max - orig.y()) / dir.y());

            interval t_z = (dir.z() == 0) ? ray_t : interval((z.min - orig.z()) / dir.z(),
                (z.max - orig.z()) / dir.z());


            interval intersection;


            if (interval::intersects(t_x,t_y,intersection)) {

                t_x = intersection;

                if (interval::intersects(t_x,t_z,intersection)) {

                    intersection.min = std::fmax(1e-9, intersection.min);
                    intersection.max = std::fmin(ray_t.max,intersection.max);

                    if (intersection.min > intersection.max) return false;

                    return true;
                }
            }
            }
        return false;
    }


    int larget_axis() {
        if ((x.max - x.min) > (y.max - y.min)) {
            if ((x.max - x.min) > (z.max - z.min)) {
                return 0;
            }
            return 2;
        }
        if ((y.max - y.min) > (z.max - z.min)) return 1;
        return 2;
    }





    static const aabb empty, universe;

};

const aabb aabb::empty = aabb(interval::empty, interval::empty, interval::empty);
const aabb aabb::universe = aabb(interval::universe, interval::universe, interval::universe);





#endif //AABB_H
