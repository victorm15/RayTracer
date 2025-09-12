//
// Created by Victor on 25.08.2025.
//
#ifndef CUBE_H
#define CUBE_H

#include "hittable.h"
#include "utility.h"

using std::shared_ptr;


class cube: public hittable {
public:

    cube(const point3& cube_loc, const double half_edge_length, shared_ptr<material> mat):
    x(interval(cube_loc.x() - half_edge_length,cube_loc.x() + half_edge_length)),
    y(interval(cube_loc.y() - half_edge_length,cube_loc.y() + half_edge_length)),
    z(interval(cube_loc.z() - half_edge_length,cube_loc.z() + half_edge_length)),
    mat(mat) {
        vec3 rvec = vec3(half_edge_length,half_edge_length,half_edge_length);
        bbox = aabb(cube_loc + rvec, cube_loc - rvec);
    }


    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
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

                    intersection.min = std::fmax(ray_t.min, intersection.min);
                    intersection.max = std::fmin(ray_t.max,intersection.max);
                    if (intersection.min > intersection.max) return false;

                    const bool origin_inside = x.contains(r.origin().x()) &&
                        y.contains(r.origin().y()) &&
                            z.contains(r.origin().z());



                    rec.t = origin_inside ? intersection.max : intersection.min;
                    rec.p = r.at(rec.t);
                    rec.mat = mat;

                    if (x.min - 1e-6 <= rec.p.x() && rec.p.x() <= x.min + 1e-6) rec.normal = vec3(-1,0,0);
                    else if (x.max - 1e-6 <= rec.p.x() && rec.p.x() <= x.max + 1e-6) rec.normal = vec3(1,0,0);

                    else if (y.min - 1e-6 <= rec.p.y() && rec.p.y() <= y.min + 1e-6) rec.normal = vec3(0,-1,0);
                    else if (y.max - 1e-6 <= rec.p.y() && rec.p.y() <= y.max + 1e-6) rec.normal = vec3(0,1,0);

                    else if (z.min - 1e-6 <= rec.p.z() && rec.p.z() <= z.min + 1e-6) rec.normal = vec3(0,0,-1);
                    else if (z.max - 1e-6 <= rec.p.z() && rec.p.z() <= z.max + 1e-6) rec.normal = vec3(0,0,1);

                    rec.set_face_normal(r);


                    // std::clog << rec.p << rec.normal << "\n";

                    return true;
                }
            }


        }


        return false;
    }

    aabb bounding_box() const override {
        return bbox;
    }




private:
    interval x, y, z;
    shared_ptr<material> mat;
    aabb bbox;




};

#endif //CUBE_H
