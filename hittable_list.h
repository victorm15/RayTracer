//
// Created by Victor on 17.08.2025.
//

#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <memory>
#include <vector>

using std::make_shared;
using std::shared_ptr;
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
    }

    bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override {

        bool hit_anything = false;
        hit_record temp_rec;
        double closest_t = t_max;

        for (const auto& object : objects) {
            if (object->hit(r, t_min, t_max, temp_rec)) {
                hit_anything = true;
                if (temp_rec.t < closest_t) {
                    rec = temp_rec;
                    closest_t = rec.t;
                }
            }

        }


        return hit_anything;



    }


};









#endif //HITTABLE_LIST_H
