//
// Created by Victor on 31.07.2025.
//

#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {


public:

    // constructors
    ray() {}

    ray(const point3& origin, const vec3& direction):
    orig(origin), dir(direction) {}

    // accessors
    const point3& origin() const {return orig;}

    const vec3& direction() const {return dir;}


    point3 at(double t) const {
        return orig + t*dir;
    }

private:
    // attributes
    point3 orig;
    vec3 dir;

};




#endif //RAY_H
