#include "NormalLightSource.h"
#include "sphere.h"

void NormalLightSource::draw(){
    sphere s=sphere(sourcePosition,1,rgb(1,1,1),ReflectionCoefficient(),0);
    s.draw();
}