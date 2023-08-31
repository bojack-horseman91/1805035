#ifndef PYRAMID_H
#define PYRAMID_H
#include "Object.h"
#include "points3D.h"
#include "Ray.h"
#include <GL/glut.h>
#include "globals.h"
#include "triangle.h"
#include "plane.h"
class Pyramid :public Object
{
    public:
    points3D lowerLeft;
    double width, height;
    plane base;
    rgb color;
    triangle faces[4];
    ReflectionCoefficient reflectionCoefficient;
    int shininess;
    Pyramid();
    Pyramid(points3D lowerLeft, double width, double height, rgb color, ReflectionCoefficient reflectionCoefficient, int shininess);
    void draw();
    bool getIntersectionPoints(Ray ray);
    private:
    points3D  pyramidVertices[5];
    void calculatePyramidVertices();
    void drawTriangle(points3D a, points3D b, points3D c);
    void drawBase(points3D a, points3D b, points3D c, points3D d);

};
#endif
