//
// Created by Victor on 31.07.2025.
//

#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

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





#endif //VEC3_H
