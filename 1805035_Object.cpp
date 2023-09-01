#include "1805035_Object.h"
#include "1805035_Ray.h"
#include "1805035_rgb.h"
#include "1805035_reflectionCoefficient.h"
#include "1805035_helper.h"
#include "1805035_globals.h"
#include "1805035_SpotLight.h"

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
rgb Object::getAmbientColor()
{

    return color * reflectionCoefficient.ambient;
}
bool Object::willIlluminate(Ray toSource, double distance)
{
     //check for collisions with other objects
    for (Object *obj : myObjects)
    {
        if (obj->getIntersectionPoints(toSource))
        {
            if (obj->t_value > 0 && obj->t_value < distance)
                return false;
        }
    }

    return true;
}

rgb Object::getDiffuseAndSpecularColor(){
    points3D normal=normalAtIntersectionPoint;
    points3D reflectedRay=this->reflectedRay.normalize();
    // reflectedRay=reflectedRay*-1;
    double lambert = 0;
    double phong = 0;
    const double epsilon = 0.00000001; // Define your desired epsilon value
       // Calculate ambient light
    
    for (LightSource *lightSource : myLightSources)
    {
        points3D toSource = (lightSource->sourcePosition - intersectionPoint);
        points3D newPoint=intersectionPoint+toSource.normalize()*epsilon;
       
        // if(!lightSource->willIlluminate(this,Ray(newPoint,toSource.normalize()),toSource.length()))
        // {
        //     continue;
        // }
        if(lightSource->isSpotLight){
            SpotLight* spotLight=(SpotLight*)lightSource;
            if (acos(toSource.normalize().dot(spotLight->lookDirection.normalize())) > (spotLight->cutOffAngle*DEG2RAD))
                {
                    continue;
                }
        }

        if(!willIlluminate(Ray(newPoint,toSource.normalize()),toSource.length()))
        {
            // lambert+=0.2;
            continue;
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
     return  color*(lambert )+ color * (this->isFloor?0:1) * phong;
    
    // You can use 'calculated_light' for shading or rendering.


}


