#include "LightSource.h"


LightSource::LightSource(){
    sourcePosition=points3D();
    fallOff=0;

}

LightSource::LightSource(points3D position,double falloff){
    sourcePosition=position;
    this->fallOff=fallOff;
}