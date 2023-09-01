#include "NormalLightSource.h"
#include "sphere.h"

void NormalLightSource::draw(){
    sphere s=sphere(sourcePosition,40,rgb(1,1,1),ReflectionCoefficient(),0);
    s.draw();
}

// bool NormalLightSource::willIlluminate(Object *curObj, Ray toSource, double distance)
// {
//     //check for collisions with other objects
//     for (Object *obj : myObjects)
//     {
//         if (obj == curObj)
//             continue;
//         if (obj->getIntersectionPoints(toSource))
//         {
//             if (obj->t_value > 0 && obj->t_value < distance)
//                 return false;
//         }
//     }

//     return true;
// }