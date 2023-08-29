#ifndef REFLECTIONCOEFFICIENT_H
#define REFLECTIONCOEFFICIENT_H
#include<iostream>
#include<fstream>


class ReflectionCoefficient{
   
    public:
         double ambient, diffuse, specular, reflection;
         ReflectionCoefficient();
        ReflectionCoefficient(double ambient, double diffuse, double specular, double reflection);
        //input stream
        friend std::istream& operator>>(std::istream& in, ReflectionCoefficient& reflectionCoefficient);
        //output stream
        friend std::ostream& operator<<(std::ostream& out, ReflectionCoefficient& reflectionCoefficient);
};

#endif