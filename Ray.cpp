#include "Ray.h"

Ray::Ray(points3D origin, points3D direction){
    this->origin = origin;
    this->direction = direction;
}
Ray::Ray(){
    this->origin = points3D();
    this->direction = points3D();
}
//input stream
std::istream& operator>>(std::istream& in, Ray& ray){
    in >> ray.origin >> ray.direction;
    return in;
}
//output stream
std::ostream& operator<<(std::ostream& out, Ray& ray){
    out << ray.origin << " " << ray.direction;
    return out;
}
