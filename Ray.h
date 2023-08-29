#ifndef RAY_H
#define RAY_H
#include "points3D.h"
#include <iostream>
#include <fstream>
class Ray{
    public:
    points3D origin;
    points3D direction;
    Ray(points3D origin, points3D direction);
    Ray();
    //input stream
    friend std::istream& operator>>(std::istream& in, Ray& ray);
    //output stream
    friend std::ostream& operator<<(std::ostream& out, Ray& ray);

};
#endif