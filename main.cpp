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
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;

    cam.render(world);


    return 0;
}

