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

    interval(double min, double max): min(min), max(max) {}


    double size() const {
        return max - min;
    }

    bool contains(double x) {
        return ((min <= x) && (x <= max));
    }

    bool surrounds(double x) {
        return ((min < x) && (x < max));
    }

    static const interval empty, universe;




};

const interval interval::empty = interval(+infinity,-infinity);
const interval interval::universe = interval(-infinity,+infinity);


#endif //INTERVAL_H
