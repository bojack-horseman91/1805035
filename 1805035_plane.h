#ifndef PLANE_H
#define PLANE_H

#include "1805035_points3D.h"
#include "1805035_Ray.h"
#include <GL/glut.h>
class plane
{
public:
    points3D a, b, c, d;
    points3D getNormal(points3D intersectionPoint)
    {
        points3D edge1 = b - a;
        points3D edge2 = c - a;
        points3D normal = edge1.cross(edge2).normalize();
        if (normal.dot(intersectionPoint - a) < 0)
            normal = -normal;
        return normal;
    }
    plane(points3D a, points3D b, points3D c, points3D d)
    {
        this->a = a;
        this->b = b;
        this->c = c;
        this->d = d;
        // Assuming you have points a, b, c, and d defined

        // Ensure a has the smallest x, y, and z coordinates
        points3D smallestPoint(std::min(a.x, std::min(b.x, std::min(c.x, d.x))),
                               std::min(a.y, std::min(b.y, std::min(c.y, d.y))),
                               std::min(a.z, std::min(b.z, std::min(c.z, d.z))));

        // Ensure b has the highest x coordinate
        points3D highestXPoint(std::max(a.x, std::max(b.x, std::max(c.x, d.x))),
                               std::max(a.y, std::max(b.y, std::max(c.y, d.y))),
                               std::max(a.z, std::max(b.z, std::max(c.z, d.z))));

        // Ensure c has the highest y coordinate
        points3D highestYPoint(std::max(a.x, std::max(b.x, std::max(c.x, d.x))),
                               std::max(a.y, std::max(b.y, std::max(c.y, d.y))),
                               std::max(a.z, std::max(b.z, std::max(c.z, d.z))));

        // Ensure d has the highest z coordinate
        points3D highestZPoint(std::max(a.x, std::max(b.x, std::max(c.x, d.x))),
                               std::max(a.y, std::max(b.y, std::max(c.y, d.y))),
                               std::max(a.z, std::max(b.z, std::max(c.z, d.z))));

        // Now you have the points with the desired properties
        a = smallestPoint;
        b = highestXPoint;
        c = highestYPoint;
        d = highestZPoint;
    }
    plane()
    {
        this->a = points3D(0, 0, 0);
        this->b = points3D(1, 0, 0);
        this->c = points3D(0, 1, 0);
        this->d = points3D(0, 0, 1);
    }
    void draw()
    {
        glBegin(GL_QUADS);
        {
            glVertex3d(a.x, a.y, a.z);
            glVertex3d(b.x, b.y, b.z);
            glVertex3d(c.x, c.y, c.z);
            glVertex3d(d.x, d.y, d.z);
        }
        glEnd();
    }
    double getIntersection(Ray ray);
    // points3D getNormal()
    // {
    //     points3D edge1 = b - a;
    //     points3D edge2 = c - a;
    //     points3D normal = edge1.cross(edge2).normalize();
    //     return normal;
    // }
    
    points3D smallestPointOn_particularAxis(points3D axis){
        points3D smallestPoint;
        //make dot product of axis with a,b,c,d return the smallest
        double min=axis.dot(a);
        smallestPoint=a;
        if(axis.dot(b)<min){
            min=axis.dot(b);
            smallestPoint=b;
        }
        if(axis.dot(c)<min){
            min=axis.dot(c);
            smallestPoint=c;
        }
        if(axis.dot(d)<min){
            min=axis.dot(d);
            smallestPoint=d;
        }

        return smallestPoint;
    }

    points3D highestPointOn_particularAxis(points3D axis){
        points3D highestPoint;
        //make dot product of axis with a,b,c,d return the highest
        double max=axis.dot(a);
        highestPoint=a;
        if(axis.dot(b)>max){
            max=axis.dot(b);
            highestPoint=b;
        }
        if(axis.dot(c)>max){
            max=axis.dot(c);
            highestPoint=c;
        }
        if(axis.dot(d)>max){
            max=axis.dot(d);
            highestPoint=d;
        }

        return highestPoint;
    }

    bool checkBounds(points3D intersectionPoint){ 
        //check for each axis if the intersectionPoint is within
        //the bounds of the plane that is a,b,c,d
        //if it is then return true else false
        points3D xAxis=points3D(1,0,0);
        points3D yAxis=points3D(0,1,0);
        points3D zAxis=points3D(0,0,1);
        points3D xAxisSmallestPoint=smallestPointOn_particularAxis(xAxis);
        points3D xAxisHighestPoint=highestPointOn_particularAxis(xAxis);
        points3D yAxisSmallestPoint=smallestPointOn_particularAxis(yAxis);
        points3D yAxisHighestPoint=highestPointOn_particularAxis(yAxis);
        points3D zAxisSmallestPoint=smallestPointOn_particularAxis(zAxis);
        points3D zAxisHighestPoint=highestPointOn_particularAxis(zAxis);
        if(intersectionPoint.x>=xAxisSmallestPoint.x && intersectionPoint.x<=xAxisHighestPoint.x && intersectionPoint.y>=yAxisSmallestPoint.y && intersectionPoint.y<=yAxisHighestPoint.y && intersectionPoint.z>=zAxisSmallestPoint.z && intersectionPoint.z<=zAxisHighestPoint.z)
            return true;
        else
            return false;
    }
};

#endif