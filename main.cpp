#include <iostream>
#include <memory>
#include <vector>

#include "color.h"
#include "vec3.h"
#include "ray.h"
#include "hittable.h"
#include "hittable_list.h"



using std::make_shared;
using std::shared_ptr;




color ray_color(const ray& r) {

    hit_record rec;


    auto sph1 =  make_shared<sphere>(vec3(0,1.2,-2),0.5);
    auto sph2 =  make_shared<sphere>(vec3(2,0,-2),0.5);
    auto sph3 = make_shared<sphere>(vec3(0,0,-2),0.5);

    hittable_list spheres;
    spheres.add(sph1);
    spheres.add(sph2);
    spheres.add(sph3);



    if (spheres.hit(r, 0, 100, rec)) {
        auto N = rec.normal;
        return 0.5*color(N.x()+1, N.y()+1, N.z()+1);
    }

    // Gradient
    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);

}



int main() {
    if (std::freopen("image.ppm", "w", stdout)) {



        // Image (px)
        auto aspect_ratio = 16.0 / 9.0;
        int image_width = 400;
        int image_height = int(image_width * 9 / 16);
        if (image_height < 1) {image_height = 1;}


        // Viewport (units)
        auto viewport_height = 2.0;
        auto viewport_width = viewport_height * (double(image_width) / image_height);

        // Camera
        auto focal_length = 1.0;
        auto camera_center = point3(0,0,0);

        // Viewport Vectors
        auto viewport_u = vec3(viewport_width,0,0);
        auto viewport_v = vec3(0,-viewport_height,0);

        // Pixel Delta Vectors
        auto pixel_delta_u = viewport_u / image_width;
        auto pixel_delta_v = viewport_v / image_height;

        // Top Left Locations
        auto viewport_top_left = camera_center - vec3(0,0,focal_length) - viewport_u/2 - viewport_v/2;
        auto pixel00_loc = viewport_top_left + 0.5 * pixel_delta_u -0.5 * pixel_delta_v;




        // Render
        std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
        for (int j = 0; j < image_height; j++) {
            std::clog << "Row: " << j << "/" << image_height-1 << "\n";
            for (int i = 0; i < image_width; i++) {
                auto pixel_loc = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
                auto ray_direction = pixel_loc - camera_center;

                ray r(camera_center,ray_direction);


                color pixel_color = ray_color(r);
                write_color(std::cout, pixel_color);
            }
        }
        std::clog << "Done\n";









        std:: fclose(stdout);
    }
    return 0;
}

