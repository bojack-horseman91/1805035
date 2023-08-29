#ifndef GLOBALS_H
#define GLOBALS_H

#include "helper.h"
#include "Object.h"
#include "LightSource.h"
#include <vector>

extern double triangleScale;
extern const float DEG2RAD;
extern  float sphereScale;
extern int subdivision;
extern rgb yellow, pink, cyan, red, green, blue, white, black, grey;
extern points3D eye, center, up;
extern bool isAxes, isCube, isPyramid;
extern double nearZ , farZ, fovY, aspectRatio;
extern const double PI;
extern std::vector<Object*>myObjects;
extern std::vector<LightSource*>myLightSources;
// extern  const int numberOfPixels;
#endif  // GLOBALS_H
