#ifndef SPHERE_H
#define SPHERE_H

#include <vector>
#include "1805035_globals.h"
#include "1805035_helper.h"
#include <cmath>
#include "1805035_reflectionCoefficient.h"
#include "1805035_Object.h"
#include "1805035_Ray.h"

class sphere : public Object
{
public:
    points3D center;
    float radius;
    int stacks=100, segments=100;
    ReflectionCoefficient reflectionCoefficient;
    sphere();
    sphere(points3D center, float radius, rgb color, ReflectionCoefficient reflectionCoefficient, int shininess);
    void draw ();
    bool getIntersectionPoints(Ray ray);
};

#endif
