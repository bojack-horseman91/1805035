#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H
#include "1805035_points3D.h"
#include "1805035_Ray.h"
#include "1805035_helper.h"
// #include "1805035_globals.h"
#include "1805035_Object.h"
class LightSource{
    public:
    points3D sourcePosition;
    double fallOff;
    bool isSpotLight=false;
    LightSource();
    LightSource(points3D position,double falloff);
    virtual void draw()=0;
    // virtual bool willIlluminate(Object*currentObject,Ray toSource,double distance)=0;
};

#endif