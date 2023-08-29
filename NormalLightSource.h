#include "LightSource.h"

class NormalLightSource:public LightSource{
    public:
    void draw();
    NormalLightSource();
    NormalLightSource(points3D position,double falloff):LightSource(position,falloff){};
};