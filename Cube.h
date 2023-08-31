#ifndef CUBE_H
#define CUBE_H
#include "Object.h"
#include "plane.h"
class Cube : public Object
{
public:
    points3D bottomLowerLeft;
    plane planes[6];
    double side;
    // Cube();
    Cube(points3D bottomLowerLeft, double side, rgb color, ReflectionCoefficient reflectionCoefficient, int shininess);
    void draw();
    bool getIntersectionPoints(Ray ray);
    void planePointsCalulation();
};
#endif