//
// Created by Victor on 31.07.2025.
//

#ifndef COLOR_H
#define COLOR_H

#include "utility.h"
#include "vec3.h"

using color = vec3;

void write_color(std::ostream& out, const color& pixel_color) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // translate to /256
    int rbyte = int(255.999 * r);
    int gbyte = int(255.99 * g);
    int bbyte = int(255.999 * b);

    // print color components
    out << rbyte << " " << gbyte << " " << bbyte << "\n";

}



#endif //COLOR_H
