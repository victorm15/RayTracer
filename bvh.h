//
// Created by Victor on 06.09.2025.
//


#ifndef BVH_H
#define BVH_H
#include "hittable.h"
#include "hittable_list.h"
#include "utility.h"

class bvh_node: public hittable {

public:

    bvh_node(hittable_list list): bvh_node(list.objects) {

    }

    bvh_node(std::vector<shared_ptr<hittable>>& objects) {




        int axis = random_int(0,2);

        if (axis == 0) quicksort_by_x(objects);
        if (axis == 1) quicksort_by_y(objects);
        if (axis == 2) quicksort_by_z(objects);

        const size_t mid = (objects.end() - objects.begin()) / 2;

        std::vector<shared_ptr<hittable>> v1 = objects;
        std::vector<shared_ptr<hittable>> v2 = objects;

        v1.erase(v1.begin() + mid, v1.end());
        v2.erase(v2.begin(), v2.begin() + mid);
        v1.shrink_to_fit();
        v2.shrink_to_fit();

        if (v1.size() == 1) left = v1[0];
        else left = make_shared<bvh_node>(v1);
        if (v2.size() == 1) right = v2[0];
        else right = make_shared<bvh_node>(v2);

        bbox = aabb(left->bounding_box(), right->bounding_box());



    }

    bool hit(const ray &r, interval ray_t, hit_record &rec) const override {
        if (!bbox.hit(r, ray_t)) return false;

        bool hit_left = left ? left->hit(r, ray_t, rec) : false;
        bool hit_right = right ? right->hit(r, hit_left ? interval(ray_t.min,rec.t) : ray_t, rec) : false;

        return hit_left || hit_right;


    }

    aabb bounding_box() const override {
        return bbox;
    }

    static void quicksort_by_x(std::vector<shared_ptr<hittable>>& objects) {
        if (objects.size() <= 1) return;

        if (objects.size() == 2) {
            if (objects[1]->bounding_box().x.min >= objects[0]->bounding_box().x.min) return;
            std::swap(objects[0],objects[1]);
            return;
        }

        int i = -1;
        int j = 0;
        int pivot = objects.size()-1;

        while (j != pivot) {

            if (objects[j]->bounding_box().x.min < objects[pivot]->bounding_box().x.min) {
                i ++;
                std::swap(objects[i],objects[j]);
            }

            j ++;

        }
        i ++;
        std::swap(objects[i],objects[pivot]);

        std::vector<shared_ptr<hittable>> v1 = objects;
        std::vector<shared_ptr<hittable>> v2 = objects;

        v1.erase(v1.begin() + i, v1.end());
        v2.erase(v2.begin(), v2.begin() + i + 1);

        v1.shrink_to_fit();
        v2.shrink_to_fit();

        quicksort_by_x(v1);
        quicksort_by_x(v2);

        v1.push_back(objects[i]);

        v1.insert(v1.end(), v2.begin(), v2.end());

        objects = v1;

    }

    static void quicksort_by_y(std::vector<shared_ptr<hittable>>& objects) {
        if (objects.size() <= 1) return;

        if (objects.size() == 2) {
            if (objects[1]->bounding_box().y.min >= objects[0]->bounding_box().y.min) return;
            std::swap(objects[0],objects[1]);
            return;
        }

        int i = -1;
        int j = 0;
        int pivot = objects.size()-1;

        while (j != pivot) {

            if (objects[j]->bounding_box().y.min < objects[pivot]->bounding_box().y.min) {
                i ++;
                std::swap(objects[i],objects[j]);
            }

            j ++;

        }
        i ++;
        std::swap(objects[i],objects[pivot]);

        std::vector<shared_ptr<hittable>> v1 = objects;
        std::vector<shared_ptr<hittable>> v2 = objects;

        v1.erase(v1.begin() + i, v1.end());
        v2.erase(v2.begin(), v2.begin() + i + 1);

        v1.shrink_to_fit();
        v2.shrink_to_fit();

        quicksort_by_y(v1);
        quicksort_by_y(v2);

        v1.push_back(objects[i]);

        v1.insert(v1.end(), v2.begin(), v2.end());

        objects = v1;

    }

    static void quicksort_by_z(std::vector<shared_ptr<hittable>>& objects) {
        if (objects.size() <= 1) return;

        if (objects.size() == 2) {
            if (objects[1]->bounding_box().z.min >= objects[0]->bounding_box().z.min) return;
            std::swap(objects[0],objects[1]);
            return;
        }

        int i = -1;
        int j = 0;
        int pivot = objects.size()-1;

        while (j != pivot) {

            if (objects[j]->bounding_box().z.min < objects[pivot]->bounding_box().z.min) {
                i ++;
                std::swap(objects[i],objects[j]);
            }

            j ++;

        }
        i ++;
        std::swap(objects[i],objects[pivot]);

        std::vector<shared_ptr<hittable>> v1 = objects;
        std::vector<shared_ptr<hittable>> v2 = objects;

        v1.erase(v1.begin() + i, v1.end());
        v2.erase(v2.begin(), v2.begin() + i + 1);

        v1.shrink_to_fit();
        v2.shrink_to_fit();

        quicksort_by_z(v1);
        quicksort_by_z(v2);

        v1.push_back(objects[i]);

        v1.insert(v1.end(), v2.begin(), v2.end());

        objects = v1;

    }




private:
    shared_ptr<hittable> left, right;
    aabb bbox;

};








#endif //BVH_H
