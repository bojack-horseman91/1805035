#ifndef OBJECT_H
#define OBJECT_H
#include "1805035_rgb.h"
#include "1805035_reflectionCoefficient.h"
#include "1805035_Ray.h"
#include "1805035_helper.h"
#include "1805035_LightSource.h"

class Object{
    // private :
    
    public:
    rgb calculated_light;
    rgb color;
    bool  isFloor=false;
    double t_value;
    ReflectionCoefficient reflectionCoefficient;
    int shininess;
    points3D intersectionPoint;
    points3D normalAtIntersectionPoint,reflectedRay;
    Object();
    Object(rgb color, ReflectionCoefficient reflectionCoefficient, int shininess);
    virtual bool getIntersectionPoints(Ray ray)=0;
    rgb getAmbientColor();
    rgb getDiffuseAndSpecularColor();
    rgb getCalculatedLight(){
        return calculated_light;
    }
    virtual void draw() = 0;
    bool willIlluminate(Ray ray,double distance);

};

#endif