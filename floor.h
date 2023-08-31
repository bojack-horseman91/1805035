#ifndef FLOOR_H
#define FLOOR_H
#include "Object.h"
class Floor:public Object{
    public:
    int checkerSize;
    Floor(int checkerSize,ReflectionCoefficient reflectionCoefficient):Object(rgb(0,0,0),reflectionCoefficient,0){
        this->checkerSize = checkerSize;
        this->isFloor = true;
    }
    void draw();
    bool getIntersectionPoints(Ray ray);
};
#endif