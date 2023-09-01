#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "1805035_points3D.h"
#include <GL/glut.h>
#include "1805035_Ray.h"
class triangle
{
public:
    points3D a, b, c;
    triangle(points3D a, points3D b, points3D c)
    {
        this->a = a;
        this->b = b;
        this->c = c;
        points3D edge1 = b - a;
        points3D edge2 = c - a;
        points3D normal = edge1.cross(edge2).normalize();

        // Check if the normal points inward
        if (normal.dot(a - points3D(0, 0, 0)) > 0)
        {
            // Swap vertices b and c to reverse winding order
            std::swap(b, c);
        }
    }
    triangle()
    {
        this->a = points3D(0, 1, 0);
        this->b = points3D(1, 0, 0);
        this->c = points3D(0, 0, 1);
    }
    void draw()
    {
        glBegin(GL_TRIANGLES);
        {
            glVertex3d(a.x, a.y, a.z);
            glVertex3d(b.x, b.y, b.z);
            glVertex3d(c.x, c.y, c.z);
        }
        glEnd();
    }
    points3D getNormal(points3D intersectionPoint)
    {
        points3D edge1 = b - a;
        points3D edge2 = c - a;

        points3D normal = edge1.cross(edge2).normalize();

        // Check the direction of the normal vector with respect to the ray's direction
        if (normal.dot(intersectionPoint - a) < 0)
        {
            // If the normal points inward, reverse the direction
            normal = -normal;
        }

        return normal;
    }
    points3D getMidPoint()
    {
        points3D midPoint = (a + b + c) / 3;
        return midPoint;
    }
    double intersectionPointusingBarycentricEquation(Ray ray);
    void print()
    {
        std::cout << "triange:a" << a << " b:" << b << " c:" << c << std::endl;
    }
    double intersectionPoint(Ray ray);
    double rayIntersection(Ray ray, points3D intersectionPoint);
};
#endif