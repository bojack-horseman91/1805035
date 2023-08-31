#ifndef NORMAL_LIGHT_SOURCE_H
#define NORMAL_LIGHT_SOURCE_H
#include "LightSource.h"

class NormalLightSource:public LightSource{
    public:
    void draw();
    NormalLightSource();
    NormalLightSource(points3D position,double falloff):LightSource(position,falloff){};
    // bool willIlluminate(Object*currentObject,Ray toSource,double distance);
};
#endif