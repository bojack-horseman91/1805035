#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <vector>
#include <cmath>
#include "points3D.h"
class rgb {
public:
    double r, g, b;
    rgb(double r, double g, double b);
    rgb();
    //multiplication operator
    rgb operator*(const double &p);
    rgb operator+(const rgb &p);
};






std::vector<points3D> buildUnitPositiveXCircle(int subdivision, int start, int end);

#endif  // HELPER_H
