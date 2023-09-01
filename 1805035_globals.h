#ifndef GLOBALS_H
#define GLOBALS_H

#include "1805035_helper.h"
#include "1805035_Object.h"
#include "1805035_LightSource.h"
#include <vector>

extern double triangleScale;
extern const float DEG2RAD;
extern  float sphereScale;
extern int subdivision;
extern rgb yellow, pink, cyan, red, green, blue, white, black, grey;
extern points3D eye, center, up;
extern bool isAxes, isCube, isPyramid;
extern double nearZ , farZ, fovY, aspectRatio;
extern int recursionLevel, resolution;
extern const double PI;
extern bool TEXTUREMODE;
// Object* currentObject;
extern std::vector<Object*>myObjects;
extern std::vector<LightSource*>myLightSources;
#endif  // GLOBALS_H
