//
// Created by Victor on 31.07.2025.
//

#ifndef COLOR_H
#define COLOR_H

#include "interval.h"
#include "utility.h"
#include "vec3.h"

using color = vec3;

inline double linear_to_gamma(double linear_component) {
    if (linear_component > 0) {
        return std::sqrt(linear_component);
    }
    return 0;
}

void write_color(std::ostream& out, const color& pixel_color) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);

    // translate to /256
    static const interval intensity(0.000, 0.999);
    int rbyte = int(256 * intensity.clamp(r));
    int gbyte = int(256 * intensity.clamp(g));
    int bbyte = int(256 * intensity.clamp(b));

    // print color components
    out << rbyte << " " << gbyte << " " << bbyte << "\n";

}

void write_row(std::ostream& out, const std::vector<color>& row) {
    for (auto& px : row) write_color(out, px);

}



#endif //COLOR_H
