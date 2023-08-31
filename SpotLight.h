#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H
#include "LightSource.h"

class SpotLight:public LightSource{
    public:
    double cutOffAngle;
    points3D lookDirection;
    SpotLight();
    SpotLight(points3D position,double falloff,double cutOffAngle,points3D lookDirection);
    void draw();
    // bool willIlluminate(Object*currentObject,Ray toSource,double distance);


};
#endif