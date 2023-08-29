#include "reflectionCoefficient.h"

ReflectionCoefficient::ReflectionCoefficient(double ambient, double diffuse, double specular, double reflection){
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->reflection = reflection;
}
ReflectionCoefficient::ReflectionCoefficient(){
    //0.04 0.03 0.03 0.9
    this->ambient = 0.04;
    this->diffuse = 0.03;
    this->specular = 0.03;
    this->reflection = 0.9;
}
//input stream
std::istream& operator>>(std::istream& in, ReflectionCoefficient& reflectionCoefficient){
    in >> reflectionCoefficient.ambient >> reflectionCoefficient.diffuse >> reflectionCoefficient.specular >> reflectionCoefficient.reflection;
    return in;
}
//output stream
std::ostream& operator<<(std::ostream& out, ReflectionCoefficient& reflectionCoefficient){
    out << reflectionCoefficient.ambient << " " << reflectionCoefficient.diffuse << " " << reflectionCoefficient.specular << " " << reflectionCoefficient.reflection;
    return out;
}
