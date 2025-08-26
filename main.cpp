#include "utility.h"

#include <memory>
#include <vector>

#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"



using std::make_shared;
using std::shared_ptr;



int main() {

    // World
    hittable_list world;
    world.add(make_shared<sphere>(vec3(0,0,-1),0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

    // Camera settings
    camera cam;
    cam.image_width = 400;
    cam.aspect_ratio = 16.0 / 9.0;
    cam.antialising = true;
    cam.antialiasing_samples = 100;
    cam.max_depth = 10;

    // Render
    cam.render(world);


    return 0;
}

/*
Let's make cubes as hittable objects, take a center point, and if the distance between a point and the center
(x,y,z) is where x,y,z <= 1, then it falls within the cube
i.e. instead of the distance being within a number it is the x,y,z components of the distance vector that must
fall within the range
reflection of rays must also change where it is a perfect reflection (\theta_i = \theta_r)
*/