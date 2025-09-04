//
// Created by Victor on 31.07.2025.
//

#ifndef VEC3_H
#define VEC3_H

#include "utility.h"

class vec3 {
public:
        // array of coordinates
        double e[3];

        // constructors
        vec3(): e{0,0,0} {}
        vec3(double e0, double e1, double e2): e {e0,e1,e2} {}

        // return coordinates
        double x() const { return e[0]; }

        double y() const { return e[1]; }

        double z() const { return e[2]; }

        // Generate random vectors

        static vec3 random_vec() { return vec3(random_double(),random_double(),random_double()); }
        static vec3 random_vec(double min, double max) { return vec3(random_double(min,max),
                random_double(min,max),random_double(min,max)); }

        bool near_zero() const {
                auto s = 1e-8;
                return ( (std::fabs(e[0]) < s) && (std::fabs(e[0]) < s) && (std::fabs(e[0]) < s));
        }

        // special operators
        vec3 operator-() const {return vec3(-e[0], -e[1], -e[2]); }

        double operator[](int i) const {return e[i];}

        double& operator[](int i) {return e[i];}

        vec3& operator+=(const vec3& v) {
                e[0] += v.e[0];
                e[1] += v.e[1];
                e[2] += v.e[2];
                return *this;
        }

        vec3& operator*=(const vec3& v) {
                e[0] *= v.e[0];
                e[1] *= v.e[1];
                e[2] *= v.e[2];
                return *this;
        }

        vec3& operator/=(const vec3& v) {
                e[0] /= v.e[0];
                e[1] /= v.e[1];
                e[2] /= v.e[2];
                return *this;
        }

        // length
        double length_squared() const {
                return (e[0] * e[0]) + (e[1] * e[1]) + (e[2] * e[2]);
        }

        double length() const {
                return std::sqrt(length_squared());
        }



};

// alias for points
using point3 = vec3;

// output coordinates
inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
        return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

// basic operators
inline vec3 operator+(const vec3& u, const vec3& v) {
        return vec3(u.e[0]+v.e[0],u.e[1]+v.e[1],u.e[2]+v.e[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
        return vec3(u.e[0]-v.e[0],u.e[1]-v.e[1],u.e[2]-v.e[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
        return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3& v) {
        return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vec3 operator*(const vec3& v, double t) {
        return t * v;
}

inline vec3 operator/(const vec3& v, double t) {
        return v * (1/t);
}

inline double dot(const vec3& u, const vec3& v) {
        return u.e[0]*v.e[0] + u.e[1]*v.e[1] + u.e[2]*v.e[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
        return vec3(
                u.e[1] * v.e[2] - v.e[1] * u.e[2],
                v.e[0] * u.e[2] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - v.e[0] * u.e[1]);
}

inline vec3 unit_vector(const vec3& v) {
        return v / v.length();
}
inline vec3 random_unit_vec() {
        while (true) {
                vec3 vec = vec3::random_vec(-1,1);
                auto lensq = vec.length_squared();
                if (1e-160 < lensq && lensq <= 1) {
                        return vec / sqrt(lensq);
                }
        }
}
inline vec3 random_on_hemisphere(const vec3& normal) {
        vec3 vec = random_unit_vec();
        if (dot(normal,vec)>0) return vec;
        return -vec;

}



inline vec3 reflect(const vec3& normal, const vec3& v) {
        return v - 2 * (normal * (dot(normal,v)));


}

inline vec3 refract(double eta_i_over_eta_r, const vec3& normal, const vec3& v) {
        double cos_theta = std::fmin(dot(-v,normal),1);
        vec3 R_perpendicular = eta_i_over_eta_r * (v + v.length() * cos_theta * normal);
        vec3 R_parallel = - std::sqrt(std::fabs(1 - R_perpendicular.length_squared())) * normal;
        return R_perpendicular + R_parallel;


}



#endif //VEC3_H
