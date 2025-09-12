//
// Created by Victor on 18.08.2025.
//

#ifndef INTERVAL_H
#define INTERVAL_H
#include "utility.h"


class interval {
public:

    // Min and max values
    double min;

    double max;

    // Constructors
    interval(): min(-infinity), max(+infinity) {}

    interval(double a, double b) {
        double min = std::fmin(a,b);
        double max = std::fmax(a,b);

        this->min = min;
        this->max = max;

    }

    interval(const interval& a, const interval& b) {

        this->min = std::fmin(a.min,b.min);
        this->max = std::fmax(a.max,b.max);

    }

    double size() const {
        return max - min;
    }

    bool contains(double x) const {
        return ((min <= x) && (x <= max));
    }

    bool surrounds(double x) const {
        return ((min < x) && (x < max));
    }

    double clamp(double x) const {
        if (x < min)  return min;
        if (x > max)  return max;
        return x;
    }

    static const interval empty, universe;

    static bool intersects(const interval a, const interval b, interval& intersection) {
        if (b.contains(a.min)) {
            if (b.contains(a.max)) {
                intersection = a;
                return true;
            }
            intersection = interval(a.min,b.max);
            return true;
        }
        if (b.contains(a.max)) {
            intersection = interval(b.min, a.max);
            return true;
        }
        if (a.contains(b.min)) {
            intersection = b;
            return true;
        }

        return false;

    }




};

const interval interval::empty = interval(+infinity,-infinity);
const interval interval::universe = interval(-infinity,+infinity);

inline std::ostream& operator<<(std::ostream& out, const interval& r) {
    return out << "Min: " << r.min << " Max: " << r.max;
}

#endif //INTERVAL_H
