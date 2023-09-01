#ifndef PYRAMID_H
#define PYRAMID_H
#include "1805035_Object.h"
#include "1805035_points3D.h"
#include "1805035_Ray.h"
#include <GL/glut.h>
#include "1805035_globals.h"
#include "1805035_triangle.h"
#include "1805035_plane.h"
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
