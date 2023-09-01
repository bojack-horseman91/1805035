#include "1805035_plane.h"

double plane::getIntersection(Ray ray){
    points3D normal = getNormal(a-ray.origin);
    double t = normal.dot(a - ray.origin) / normal.dot(ray.direction);
    points3D intersectinPoint=ray.origin + ray.direction * t;
    //check the intersection point is in the plane
    if(checkBounds(intersectinPoint))
        return t;
    else
        return -1;
    
}