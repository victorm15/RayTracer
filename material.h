//
// Created by Victor on 26.08.2025.
//

#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"
#include "utility.h"


class material {
public:
    virtual ~material() = default;

    virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const {
        return false;
    }
};

class lambertian: public material {
public:

    lambertian(const color& albedo): albedo(albedo) {}

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
        auto normal = rec.normal;
        vec3 scatter_direction = normal + random_unit_vec();
        // vec3 scatter_direction = random_on_hemisphere(normal);

        if (scatter_direction.near_zero()) scatter_direction = normal;

        scattered = ray(rec.p,scatter_direction);
        attenuation = albedo;

        return true;

    }

private:
    color albedo;

};

class metal: public material {
public:
    metal(const color& albedo): albedo(albedo), fuzz(0) {}
    metal(const color& albedo, const double fuzz): albedo(albedo), fuzz(fuzz) {}

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {



        auto scatter_direction = reflect(rec.normal, r_in.direction());

        scattered = ray(rec.p, unit_vector(scatter_direction) + (fuzz * random_unit_vec()));
        attenuation = albedo;
        return (dot(rec.normal,scattered.direction())>0);
    }


private:
    color albedo;
    double fuzz;
};


class dielectric: public material {
public:
    dielectric(const double refractive_index): refractive_index(refractive_index) {}

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
        attenuation = color(1.0,1.0,1.0);

        double ri = rec.front_face ? 1/refractive_index : refractive_index;

        auto cos_theta = std::fmin(dot(rec.normal,-unit_vector(r_in.direction())),1.0);
        auto sin_theta = std::sqrt(std::fabs(1 - cos_theta * cos_theta));

        vec3 scatter_direction = (((ri * sin_theta) > 1) || reflectance(cos_theta, refractive_index) > random_double())  ?
        reflect(rec.normal, r_in.direction()) :
        refract(ri, rec.normal, unit_vector(r_in.direction()));

        // vec3 scatter_direction = refract(ri, rec.normal, unit_vector(r_in.direction()));

        scattered = ray(rec.p, scatter_direction);





        return true;

        // || reflectance(cos_theta, refractive_index) > random_double()
    }




private:
    double refractive_index;

    static double reflectance(double cosine, double refractive_index) {
        auto r0 = (1 - refractive_index) / (1 + refractive_index);
        r0 = r0 * r0;
        return r0 + ((1 - r0) * std::pow((1-cosine),5));

    }


};





#endif //MATERIAL_H
