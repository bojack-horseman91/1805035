#ifndef READFILE_H
#define READFILE_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

// Include necessary headers for your classes
#include "LightSource.h"
#include "Spotlight.h"
#include "Object.h"
#include "globals.h"
#include "floor.h"
#include "sphere.h"
#include "Cube.h"
#include "Pyramid.h"
#include "NormalLightSource.h"

void readFile()
{
    std::ifstream inputFile("input.txt"); // Provide the correct file path

    if (!inputFile.is_open())
    {
        std::cerr << "Failed to open input file." << std::endl;
        std::exit(EXIT_FAILURE);
    }

    // double nearPlane, farPlane, fovY, aspectRatio;
    // int recursionLevel, resolution;
    double checkerboardWidth;
    // Read and parse the initial input data
    inputFile >> nearZ >> farZ >> fovY >> aspectRatio >> recursionLevel >> resolution >> checkerboardWidth;

    // Read and parse the ambient, diffuse, and reflection coefficients for the checkerboard
    double ambientChecker, diffuseChecker, reflectionChecker;
    inputFile >> ambientChecker >> diffuseChecker >> reflectionChecker;
    // Create a Floor object with the above properties
    Object *floor = new Floor(checkerboardWidth, ReflectionCoefficient(ambientChecker, diffuseChecker, 0, reflectionChecker));
    myObjects.push_back(floor);
    int numObjects;
    inputFile >> numObjects;
    std::cout << "Near Z: " << nearZ << std::endl;
    std::cout << "Far Z: " << farZ << std::endl;
    std::cout << "FOV Y: " << fovY << std::endl;
    std::cout << "Aspect Ratio: " << aspectRatio << std::endl;
    std::cout << "Recursion Level: " << recursionLevel << std::endl;
    std::cout << "Resolution: " << resolution << std::endl;
    std::cout << "Checkerboard Width: " << checkerboardWidth << std::endl;
    std::cout << "Ambient Checker: " << ambientChecker << std::endl;
    std::cout << "Diffuse Checker: " << diffuseChecker << std::endl;
    std::cout << "Reflection Checker: " << reflectionChecker << std::endl;
    std::cout << "Number of Objects: " << numObjects << std::endl;

    // Create vectors to hold objects and lights
    // std::vector<Object*> objects;
    // std::vector<LightSource*> lights;

    for (int i = 0; i < numObjects; ++i)
    {
        std::string objectType;
        inputFile >> objectType;

        if (objectType == "sphere")
        {
            points3D center;
            double radius;
            rgb color;
            double ambient, diffuse, specular, reflection;
            double shininess;

            inputFile >> center.x >> center.y >> center.z >> radius >> color.r >> color.g >> color.b >> ambient >> diffuse >> specular >> reflection >> shininess;

            Object *createdSphere = new sphere(center, radius, color, ReflectionCoefficient(ambient, diffuse, specular, reflection), shininess);
            myObjects.push_back(createdSphere);
        }
        else if (objectType == "cube")
        {
            points3D bottomPoint;
            double side;
            rgb color;
            double ambient, diffuse, specular, reflection;
            double shininess;

            inputFile >> bottomPoint.x >> bottomPoint.y >> bottomPoint.z >> side
                      >> color >> ambient >> diffuse >> specular >> reflection >> shininess;

            Object *createdCube = new Cube(bottomPoint, side, color, ReflectionCoefficient(ambient, diffuse, specular, reflection), shininess);
            myObjects.push_back(createdCube);
        }
        else if (objectType == "pyramid")
        {
            points3D lowestPoint;
            double width, height;
            rgb color;
            double ambient, diffuse, specular, reflection;
            double shininess;

            inputFile >> lowestPoint.x >> lowestPoint.y >> lowestPoint.z >> 
            width >> height >> color >> ambient >> diffuse >> specular >> reflection 
            >> shininess;

            Object *createdPyramid = new Pyramid(lowestPoint, width, height, color, ReflectionCoefficient(ambient, diffuse, specular, reflection), shininess);
            myObjects.push_back(createdPyramid); 
        }
        // Repeat for other object types...
    }

    int numNormalLights;
    inputFile >> numNormalLights;

    for (int i = 0; i < numNormalLights; ++i)
    {
        points3D position;
        double falloff;

        inputFile >> position.x >> position.y >> position.z >> falloff;
        LightSource *createdLight = new NormalLightSource(position, falloff);
        myLightSources.push_back(createdLight);
    }

    int numSpotLights;
    inputFile >> numSpotLights;

    for (int i = 0; i < numSpotLights; ++i)
    {
          points3D position, direction;
        double falloff, cutoffAngle;

        inputFile >> position.x >> position.y >> position.z >> falloff;
        inputFile >> direction.x >> direction.y >> direction.z;
        inputFile >> cutoffAngle;

        LightSource *createdLight = new SpotLight(position, falloff, cutoffAngle,direction);
        myLightSources.push_back(createdLight);
    }

    // Close the input file
    inputFile.close();
};
#endif