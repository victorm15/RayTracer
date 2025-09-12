#include "utility.h"

#include <memory>
#include <vector>
#include <chrono>
#include <iomanip>


#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "cube.h"
#include "material.h"
#include "bvh.h"



using std::make_shared;
using std::shared_ptr;


int main() {
    auto start = std::chrono::high_resolution_clock::now();
    hittable_list world;


    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            double choose_mat = random_double();
            double choose_shape = random_double();
            point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> random_material;
                if (choose_shape < 0.75) {
                    if (choose_mat < 0.8) {
                        // diffuse
                        auto albedo = color::random_vec() * color::random_vec();
                        random_material = make_shared<lambertian>(albedo);
                        world.add(make_shared<sphere>(center, 0.2, random_material));
                    } else if (choose_mat < 0.95) {
                        // metal
                        auto albedo = color::random_vec(0.5, 1);
                        auto fuzz = random_double(0, 0.5);
                        random_material = make_shared<metal>(albedo, fuzz);
                        world.add(make_shared<sphere>(center, 0.2, random_material));
                    } else {
                        // glass
                        random_material = make_shared<dielectric>(1.5);
                        world.add(make_shared<sphere>(center, 0.2, random_material));
                    }
                }
                else {
                    if (choose_mat < 0.8) {
                        // diffuse
                        auto albedo = color::random_vec() * color::random_vec();
                        random_material = make_shared<lambertian>(albedo);
                        world.add(make_shared<cube>(center + vec3(0,-0.04,0), 0.16, random_material));
                    } else if (choose_mat < 0.95) {
                        // metal
                        auto albedo = color::random_vec(0.5, 1);
                        auto fuzz = random_double(0, 0.5);
                        random_material = make_shared<metal>(albedo, fuzz);
                        world.add(make_shared<cube>(center + vec3(0,-0.04,0), 0.16, random_material));
                    } else {
                        // glass
                        random_material = make_shared<dielectric>(1.5);
                        world.add(make_shared<cube>(center + vec3(0,-0.04,0), 0.16, random_material));
                    }

                }





            }
        }
    }

    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));



    auto material1 = make_shared<dielectric>(1.5);
    auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.05);


    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));


    world.add(make_shared<cube>(point3(4, 0.7, 0), 0.7, material3));


    camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 1200;

    cam.antialiasing_samples = 500;
    cam.max_depth         = 50;

    cam.vertical_fov     = 20;
    cam.look_from = point3(13,2,3);
    cam.look_at   = point3(0,0,0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0.6;
    cam.focus_distance    = 10;
    bool bounding_box = true;







    world = bounding_box ? hittable_list(make_shared<bvh_node>(world)) : world;
    cam.render(world);



    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> ms = stop - start;

    double seconds = ms.count() / 1000.0;

    std::clog << std::fixed << std::setprecision(1)
              << "Finished in " << seconds << "s\n";


    return 0;
}









