#ifndef CUBE_H
#define CUBE_H
#include "1805035_Object.h"
#include "1805035_plane.h"
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