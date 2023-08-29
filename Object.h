#ifndef OBJECT_H
#define OBJECT_H
#include "rgb.h"
#include "reflectionCoefficient.h"
#include "Ray.h"
#include "helper.h"
#include "LightSource.h"

class Object{
    // private :
    
    public:
    rgb calculated_light;
    rgb color;
    double t_value;
    ReflectionCoefficient reflectionCoefficient;
    int shininess;
    points3D intersectionPoint;
    Object();
    Object(rgb color, ReflectionCoefficient reflectionCoefficient, int shininess);
    virtual bool getIntersectionPoints(Ray ray)=0;
    void getAmbientColor();
    void getDiffuseAndSpecularColor(points3D normal, points3D intersectionPoint,points3D reflectedRay);
    rgb getCalculatedLight(){
        return calculated_light;
    }
    virtual void draw() = 0;

};

#endif