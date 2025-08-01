#include <iostream>

#include "color.h"
#include "vec3.h"
#include "ray.h"
#include "hittable.h"

double hit_sphere(const vec3& sphere_loc, const double& sphere_radius, const ray& r) {

    auto dir = r.direction();
    auto orig = r.origin();

    auto a = dir.length_squared();
    auto b = dot((2 * dir),(orig-sphere_loc));
    auto c = sphere_loc.length_squared() + orig.length_squared() -2 * dot(sphere_loc,orig)-sphere_radius*sphere_radius;

    auto discriminant = b * b - 4 * a * c;

    // Check if ray touches sphere
    if (discriminant < 0) {return -1;}

    // Return value of t for which ray touches sphere
    else {
        return (-b - std::sqrt(discriminant) / (a));
    }



}




color ray_color(const ray& r, const point3& sphere_loc, const double& sphere_radius) {

    hit_record rec;
    sphere sph1(sphere_loc,sphere_radius);

    if (sph1.hit(r, 0, 100, rec)) {
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
        auto pixel_delta_u = viewport_width / image_width;
        auto pixel_delta_v = viewport_height / image_height;

        // Top Left Locations
        auto viewport_top_left = camera_center + vec3(-viewport_width / 2, viewport_height / 2, -focal_length);
        auto pixel00_loc = viewport_top_left + vec3(0.5 * pixel_delta_u, -0.5 * pixel_delta_v, 0);

        // Sphere
        auto sphere_loc = vec3(0,0,-1);
        auto sphere_radius = 0.5;


        // Render
        std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
        for (int j = 0; j < image_height; j++) {
            // std::clog << "Row: " << j << "/255\n";
            for (int i = 0; i < image_width; i++) {
                auto pixel_loc = pixel00_loc + vec3(i * pixel_delta_u, -j * pixel_delta_v, 0);
                auto ray_direction = pixel_loc - camera_center;

                ray r(camera_center,ray_direction);


                color pixel_color = ray_color(r, sphere_loc, sphere_radius);
                write_color(std::cout, pixel_color);
            }
        }
        std::clog << "Done\n";









        std:: fclose(stdout);
    }
    return 0;
}

