#include "utility.h"

#include <memory>
#include <vector>

#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "cube.h"
#include "material.h"



using std::make_shared;
using std::shared_ptr;



int main() {

    // World
    hittable_list world;

    // Materials


    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

    // for (int a = -6; a < 6; a++) {
    //     for (int b = -6; b < 6; b++) {
    //         auto choose_mat = random_double();
    //         point3 center(1.5 * a + 0.9*random_double(), 0.2, 1.5 * b + 0.9*random_double());
    //
    //         if ((center - point3(4, 0.2, 0)).length() > 0.9) {
    //             shared_ptr<material> sphere_material;
    //
    //             if (choose_mat < 0.8) {
    //                 // diffuse
    //                 auto albedo = color::random_vec() * color::random_vec();
    //                 sphere_material = make_shared<lambertian>(albedo);
    //                 world.add(make_shared<sphere>(center, 0.2, sphere_material));
    //             } else if (choose_mat < 0.95) {
    //                 // metal
    //                 auto albedo = color::random_vec(0.5, 1);
    //                 auto fuzz = random_double(0, 0.5);
    //                 sphere_material = make_shared<metal>(albedo, fuzz);
    //                 world.add(make_shared<sphere>(center, 0.2, sphere_material));
    //             } else {
    //                 // glass
    //                 sphere_material = make_shared<dielectric>(1.5);
    //                 world.add(make_shared<sphere>(center, 0.2, sphere_material));
    //             }
    //         }
    //     }
    // }

    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.05);
    world.add(make_shared<cube>(point3(4, 0.8, 0), 0.8, material3));

    camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 400;

    cam.antialiasing_samples = 50;
    cam.max_depth         = 20;

    cam.vertical_fov     = 20;
    cam.look_from = point3(13,2,3);
    cam.look_at   = point3(0,0,0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0;
    cam.focus_distance    = 10.0;



    // Render
    cam.render(world);


    return 0;
}

