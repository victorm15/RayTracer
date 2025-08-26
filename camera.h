//
// Created by Victor on 23.08.2025.
//

#ifndef CAMERA_H
#define CAMERA_H
#include <iostream>

#include "hittable.h"
#include "utility.h"


#include "color.h"



class ray;
class hittable;

class camera {
public:

    double aspect_ratio = 1.0;
    int image_width = 100;
    bool antialising = true;
    int antialiasing_samples = 1;
    int max_depth = 10;



    void render(const hittable& world) {
        initalize();

        if (std::freopen("image.ppm", "w", stdout)) {
            // Render
            std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
            for (int j = 0; j < image_height; j++) {
                std::clog << "Row: " << j << "/" << image_height-1 << "\n";
                for (int i = 0; i < image_width; i++) {
                    auto pixel_loc = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);

                    color pixel_color;
                    if (antialising) {
                        color sum = color(0,0,0);

                        for (int i = 0; i < antialiasing_samples; i++) {

                            auto ray_target = pixel_loc + random_double(-1,1) * pixel_delta_u/2 +
                                random_double(-1,1) * pixel_delta_v/2;

                            auto ray_direction = ray_target - camera_center;

                            ray r(camera_center,ray_direction);
                            sum += ray_color(r,world, max_depth);
                        }

                        pixel_color = sum / antialiasing_samples;
                    }
                    else {
                        auto ray_direction = pixel_loc - camera_center;
                        ray r(camera_center,ray_direction);
                        pixel_color = ray_color(r,world, max_depth);
                    }

                    write_color(std::cout, pixel_color);
                }
            }
            std::clog << "Done\n";

            std:: fclose(stdout);

        }






    }


private:


    int image_height;
    point3 camera_center;

    vec3 pixel_delta_u;
    vec3 pixel_delta_v;

    vec3 pixel00_loc;


    void initalize() {

        // Image (px)
        image_height = int(image_width / aspect_ratio);
        if (image_height < 1) {image_height = 1;}

        // Viewport (units)
        auto viewport_height = 2.0;
        auto viewport_width = viewport_height * (double(image_width) / image_height);

        // Camera
        auto focal_length = 1.0;
        camera_center = point3(0,0,0);

        // Viewport Vectors
        auto viewport_u = vec3(viewport_width,0,0);
        auto viewport_v = vec3(0,-viewport_height,0);

        // Pixel Delta Vectors
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // Top Left Locations
        auto viewport_top_left = camera_center - vec3(0,0,focal_length) - viewport_u/2 - viewport_v/2;
        pixel00_loc = viewport_top_left + 0.5 * pixel_delta_u -0.5 * pixel_delta_v;


    }

    color ray_color(const ray& r, const hittable& world, int depth) const {

        hit_record rec;

        // Check if ray intersects with hittable objects
        if (depth <= 0) return color(0,0,0);
        if (world.hit(r, interval(0.001,infinity), rec)) {
            auto normal = rec.normal;
            vec3 direction = normal + random_unit_vec();

            ray bounced_ray(rec.p,direction);
            // return 0.5*color(normal.x()+1, normal.y()+1, normal.z()+1);
            return 0.5 * ray_color(bounced_ray,world, depth-1);

        }

        // Create gradient
        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5*(unit_direction.y() + 1.0);
        return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);

    }

};

#endif //CAMERA_H
