#ifndef SPHERE_H
#define SPHERE_H

#include <vector>
#include "globals.h"
#include "helper.h"
#include <cmath>
#include "reflectionCoefficient.h"
#include "Object.h"
#include "Ray.h"

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
