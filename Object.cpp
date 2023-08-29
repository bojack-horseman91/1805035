#include "Object.h"
#include "Ray.h"
#include "rgb.h"
#include "reflectionCoefficient.h"
#include "helper.h"
#include "globals.h"

Object::Object()
{
    this->color = rgb(1, 1, 1);
    this->reflectionCoefficient = ReflectionCoefficient();
    this->shininess = 30;
    calculated_light = rgb();
    t_value = -1;
}

Object::Object(rgb color, ReflectionCoefficient reflectionCoefficient, int shininess)
{
    this->color = color;
    this->reflectionCoefficient = reflectionCoefficient;
    this->shininess = shininess;
    calculated_light = rgb();
    t_value = -1;
}
void Object::getAmbientColor()
{

    // calculated_light = 
}

void Object::getDiffuseAndSpecularColor(points3D normal, points3D intersectionPoint, points3D reflectedRay)
{
    double lambert = 0;
    double phong = 0;
    const double epsilon = 0.001; // Define your desired epsilon value
       // Calculate ambient light
    rgb ambient = color * reflectionCoefficient.ambient;
    for (LightSource *lightSource : myLightSources)
    {
        points3D toSource = (lightSource->sourcePosition - intersectionPoint);
        points3D newPoint=intersectionPoint+toSource.normalize()*epsilon;
        for(Object*obj:myObjects){
            if(obj->getIntersectionPoints(Ray(newPoint,toSource.normalize()))){
                continue;
            }
        }
        double d = toSource.length();
        double scalingFactor = exp(-(d * d * lightSource->fallOff));
        toSource = toSource.normalize();
        
        double cur_lambert = std::max(toSource.dot(normal) * reflectionCoefficient.diffuse , 0.0)*scalingFactor;
        lambert += cur_lambert;

        double cur_phong = pow(std::max(reflectedRay.dot(toSource), 0.0), shininess) * scalingFactor*reflectionCoefficient.specular;
        phong += cur_phong;
    }
    
 
    
    // Add diffuse and specular contributions
     calculated_light = ambient+ rgb(1,1,1) * (lambert + phong);
    
    // You can use 'calculated_light' for shading or rendering.


}

rgb recursiveReflection(Ray ray,)
