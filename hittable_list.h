//
// Created by Victor on 17.08.2025.
//

#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"
#include "utility.h"

#include <vector>

#include "cube.h"
#include "sphere.h"
#include "aabb.h"

class hittable_list: public hittable {
public:

    // Vector of hittable objects
    std::vector<shared_ptr<hittable>> objects;

    // Constructors
    hittable_list() {}
    hittable_list(shared_ptr<hittable> object) {add(object);}

    // Clear and add to vector
    void clear() {objects.clear();}
    void add(shared_ptr<hittable> object) {
        objects.push_back(object);
        bbox = aabb(bbox,object->bounding_box());
    }

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {

        bool hit_anything = false;
        hit_record temp_rec;
        double closest_t = ray_t.max;

        for (const auto& object : objects) {
            if (object->hit(r, ray_t, temp_rec)) {
                hit_anything = true;
                if (temp_rec.t < closest_t) {
                    rec = temp_rec;
                    closest_t = rec.t;
                }
            }

        }


        return hit_anything;



    }

    aabb bounding_box() const override {return bbox;}
private:
    aabb bbox;
};









#endif //HITTABLE_LIST_H
