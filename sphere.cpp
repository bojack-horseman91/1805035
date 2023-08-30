
#include "sphere.h"
#include <GL/glut.h>
#include <cmath>
// std::vector<points3D> makeFace(){
//     int pointsPerRow = (int)pow(2, subdivision) + 1;
//      std::vector<points3D> unitPoistiveX = buildUnitPositiveXCircle(subdivision, 0,pointsPerRow);
//    // 4 vertices of a quad
//             // v1--v3
//             // | / |
//             // v2--v4
//     //make two loops which will iterate through each rows and make
//     //a quad pair i.e. two points3D from current row and two points3D from
//     //the next row
//     std::vector<points3D>quadPoints;
//     for (int row=0;row < pointsPerRow-1; row++){
//         for(int column=0;column<pointsPerRow-1;column++){
//             int firstRowIndex=row*pointsPerRow+column;
//             int secondRowIndex=(row+1)*pointsPerRow+column;
//                 quadPoints.push_back(unitPoistiveX[secondRowIndex+1]);
//                 quadPoints.push_back(unitPoistiveX[firstRowIndex+1]);
//                 quadPoints.push_back(unitPoistiveX[secondRowIndex]);
//                 quadPoints.push_back(unitPoistiveX[firstRowIndex]);

//         }
//     }
//   return quadPoints;

// }

// void drawSphereSegments(rgb color){
//     std::vector<points3D>a=makeFace();
//         glPointSize(10);
//         glPushMatrix();
//         glTranslated(1-sphereScale,0,0);
//         glScaled(sphereScale,sphereScale,sphereScale);
//         glBegin(GL_QUAD_STRIP);
//         glColor3f(color.r,color.g,color.b);
//         for(int i=0;i<a.size();i++){

//             glVertex3f(a[i].x,a[i].y,a[i].z);

//         }
//         glEnd();

//         glPopMatrix();

// }
// void drawSphere(){

//     //X face
//     glPushMatrix();
//     drawSphereSegments(red);
//     glRotated(180,0,0,1);
//     drawSphereSegments(red);
//     glPopMatrix();

//     //Y FACE
//     glPushMatrix();
//     glRotated(90,0,0,1);
//     drawSphereSegments(green);
//     glRotated(180,0,0,1);
//     drawSphereSegments(green);
//     glPopMatrix();

//     //Z FACE
//     glPushMatrix();
//     glRotated(90,0,1,0);
//     drawSphereSegments(blue);
//     glRotated(180,0,0,1);
//     drawSphereSegments(blue);
//     glPopMatrix();
// }

void sphere::draw()
{
    points3D points[stacks + 1][segments + 1];
    double height, _radius;

    /* generating points: segments = segments in plane; stacks = segments in hemisphere */
    for (int i = 0; i <= stacks; i++)
    {
        height = radius * sin(((double)i / (double)stacks) * (PI / 2));
        _radius = radius * cos(((double)i / (double)stacks) * (PI / 2));

        for (int j = 0; j <= segments; j++)
        {
            points[i][j] = points3D(_radius * cos(((double)j / (double)segments) * 2 * PI), _radius * sin(((double)j / (double)segments) * 2 * PI), height);
        }
        // std::cout<<height<<" "<<_radius<<std::endl;
    }

    /* drawing quads using generated points */
    glColor3f(color.r, color.g, color.b);

    for (int i = 0; i < stacks; i++)
    {
        for (int j = 0; j < segments; j++)
        {
            glBegin(GL_QUADS);
            {
                /* upper hemisphere */
                glVertex3f((center + points[i][j]).x, (center + points[i][j]).y, (center + points[i][j]).z);
                glVertex3f((center + points[i][j + 1]).x, (center + points[i][j + 1]).y, (center + points[i][j + 1]).z);
                glVertex3f((center + points[i + 1][j + 1]).x, (center + points[i + 1][j + 1]).y, (center + points[i + 1][j + 1]).z);
                glVertex3f((center + points[i + 1][j]).x, (center + points[i + 1][j]).y, (center + points[i + 1][j]).z);

                /* lower hemisphere */
                glVertex3f((center + points[i][j]).x, (center + points[i][j]).y, (center - points[i][j]).z);
                glVertex3f((center + points[i][j + 1]).x, (center + points[i][j + 1]).y, (center - points[i][j + 1]).z);
                glVertex3f((center + points[i + 1][j + 1]).x, (center + points[i + 1][j + 1]).y, (center - points[i + 1][j + 1]).z);
                glVertex3f((center + points[i + 1][j]).x, (center + points[i + 1][j]).y, (center - points[i + 1][j]).z);
            }
            glEnd();
        }
    }
}

sphere::sphere()
{
    radius = 1;
    center = points3D(0, 0, nearZ);
}

bool sphere::getIntersectionPoints(Ray ray)
{

    // double tp=ray.direction.dot(center-ray.origin);
    // if(tp<0){
    //     return false;
    // }
    // points3D p=ray.origin+ray.direction*tp;
    // double d=(p-center).length();
    // if(d>radius){
    //     return false;
    // }
    // double th=sqrt(radius*radius-d*d);
    // double t1=tp-th;
    // double t2=tp+th;
    // if(t1<0 && t2<0){
    //     return false;
    // }
    // else if(t1<0 && t2>0){
    //     intersectionPoint=(ray.origin+ray.direction*t2);
    //     t_value=t2;
    //     // return true;
    // }
    // else if(t1>0 && t2<0){
    //     intersectionPoint=(ray.origin+ray.direction*t1);
    //     t_value=t1;
    //     // return true;
    // }
    // else{
    //     double tmin=std::min(t1,t2);
    //     intersectionPoint=(ray.origin+ray.direction*tmin);
    //     t_value=tmin;
    //     // return true;
    // }

    points3D oc = ray.origin - center;
    double a = ray.direction.dot(ray.direction);
    double b = 2.0 * oc.dot(ray.direction);
    double c = oc.dot(oc) - radius * radius;
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
    {
        return false; // No intersection
    }

    // Calculate the two possible intersection points
    double t1 = (-b - std::sqrt(discriminant)) / (2.0 * a);
    double t2 = (-b + std::sqrt(discriminant)) / (2.0 * a);

    if (t1 > 0 || t2 > 0)
    {
        t_value = (t1 > 0) ? t1 : t2; // Choose the positive intersection point
        points3D newRay = ray.origin + ray.direction * t_value;
        intersectionPoint = newRay;
        normalAtIntersectionPoint = (intersectionPoint - center).normalize();
        reflectedRay = newRay - normalAtIntersectionPoint * (newRay.dot(normalAtIntersectionPoint)) * 2;
        return true;
    }

    return false;

    // calculated_light=rgb(0,0,0);
    // getAmbientColor();
    // getDiffuseAndSpecularColor();
    // std::cout<<calculated_light.r<<" "<<calculated_light.g<<" "<<calculated_light.b<<std::endl;
    return true;
}

sphere::sphere(points3D center, float radius, rgb color, ReflectionCoefficient reflectionCoefficient, int shininess) : Object(color, reflectionCoefficient, shininess)
{
    this->center = center;
    this->radius = radius;
}