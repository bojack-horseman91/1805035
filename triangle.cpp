#include "matrix.h"
#include "points3D.h"
#include "ray.h"
#include "triangle.h"
double triangle::intersectionPointusingBarycentricEquation(Ray ray) {
    points3D A=this->a,  B=this->b,C=this->c;
    points3D intersectionPoint; // The point of intersection

    Matrix AB(1, 3, {{B.x - A.x, B.y - A.y, B.z - A.z}});
    Matrix AC(1, 3, {{C.x - A.x, C.y - A.y, C.z - A.z}});
    Matrix rayDir(1, 3, {{ray.direction.x, ray.direction.y, ray.direction.z}});
    Matrix AO(1, 3, {{ray.origin.x - A.x, ray.origin.y - A.y, ray.origin.z - A.z}});

    Matrix M(3, 3, {
        {AB.get(0, 0), AC.get(0, 0), -rayDir.get(0, 0)},
        {AB.get(0, 1), AC.get(0, 1), -rayDir.get(0, 1)},
        {AB.get(0, 2), AC.get(0, 2), -rayDir.get(0, 2)}
    });

    Matrix invM = M.inverse();

    Matrix barycentricCoords = AO * invM.transpose();

    double u = barycentricCoords.get(0, 0);
    double v = barycentricCoords.get(0, 1);
    double t=barycentricCoords.get(0, 2);
    // std::cout<<t<<" "<<u<<" "<<v<<std::endl;
    // Check if the intersection point is inside the triangle
    if (u >= 0 && v >= 0 && u + v < 1) {
        // std::cout<<1-u-v<<std::endl;
        return t;
    }

    return -1;
}

double triangle::intersectionPoint(Ray ray) {
    points3D A=this->a,  B=this->b,C=this->c;
    points3D intersectionPoint; // The point of intersection

    points3D AB = B - A;
    points3D AC = C - A;
    points3D normal = AB.cross(AC);
    //checks the ray intersect the plane 
    double t = -1 * (normal.dot(ray.origin)) / (normal.dot(ray.direction));
    std::cout<<t<<std::endl;
    //check the intersection point is in the triangle
    

    


    if (t < 0)
        return -1;
    return t;
    // points3D AO = ray.origin - A;
    // double t = -1 * (normal.dot(AO)) / (normal.dot(ray.direction));
    // std::cout<<t<<std::endl;
    // if (t < 0)
    //     return -1;
    // intersectionPoint = ray.origin + ray.direction * t;
    // points3D AP = intersectionPoint - A;
    // points3D BP = intersectionPoint - B;
    // points3D CP = intersectionPoint - C;
    // points3D normalAB = AB.cross(AP);
    // points3D normalBC = BP.cross(AC);
    // points3D normalCA = CP.cross(AC*-1);
    // std::cout<<"returning "<<intersectionPoint<<" "<<t<<std::endl;
    // if (normal.dot(normalAB) >= 0 && normal.dot(normalBC) >= 0 && normal.dot(normalCA) >= 0) {
        
    //     return t;
    // }
    // return -1;

}






double triangle::rayIntersection(Ray ray, points3D intersectionPoint)  {
    points3D e1 = b - a;
    points3D e2 = c - a;
    points3D h = ray.direction.cross(e2);
    double a_det = e1.dot(h);

    if (std::abs(a_det) < 1e-6) {
        return -1; // Ray is parallel to the triangle
    }

    double f = 1.0 / a_det;
    points3D s = ray.origin - a;
    double u = f * s.dot(h);

    if (u < 0.0 || u > 1.0) {
        return -1; // Intersection point is outside triangle's plane
    }

    points3D q = s.cross(e1);
    double v = f * ray.direction.dot(q);

    if (v < 0.0 || u + v > 1.0) {
        return -1; // Intersection point is outside triangle's plane
    }

    double t = f * e2.dot(q);

    if (t > 1e-6) {
        intersectionPoint = ray.origin + ray.direction * t;
        return t;
    }

    return -1; // Intersection point is behind the ray's origin
}