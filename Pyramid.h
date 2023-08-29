#ifndef PYRAMID_H
#define PYRAMID_H
#include "Object.h"
class Pyramid :public Object
{
    public:
    points3D lowerLeft;
    double width, height;
    rgb color;
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
