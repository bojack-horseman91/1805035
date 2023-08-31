#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H
#include "points3D.h"
#include "Ray.h"
#include "helper.h"
// #include "globals.h"
// #include "Object.h"
class LightSource{
    public:
    points3D sourcePosition;
    double fallOff;
    LightSource();
    LightSource(points3D position,double falloff);
    virtual void draw()=0;
    // virtual bool willIlluminate(Object*currentObject,Ray toSource,double distance)=0;
};

#endif