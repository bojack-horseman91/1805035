#include "plane.h"

double plane::getIntersection(Ray ray){
    points3D normal = getNormal(ray.origin);
    double t = normal.dot(a - ray.origin) / normal.dot(ray.direction);
    points3D intersectinPoint=ray.origin + ray.direction * t;
    //check the intersection point is in the plane
    if(intersectinPoint.x>=a.x && intersectinPoint.x<=b.x && intersectinPoint.y>=a.y && intersectinPoint.y<=c.y && intersectinPoint.z>=a.z && intersectinPoint.z<=d.z)
        return t;
    else
        return -1;
    
}