#include "globals.h"
#include <cmath>
#include "sphere.h"

double triangleScale = 1.0,testRef = 0.0;
const float DEG2RAD = acos(-1) / 180.0f;
float sphereScale = 1.0f;
int subdivision = 3;
rgb yellow(1.0, 1.0, 0.0);
rgb pink(1,0,1),cyan(0,1,1),red(1,0,0),green(0,1,0),blue(0,0,1),white(1,1,1),black(0,0,0),grey(0.5,0.5,0.5);
// Global variables
points3D eye(0,0,0);
points3D center(1,-10,0);
points3D up(0,0,1);
double nearZ = 1.0, farZ = 1000.0, fovY = 80.0, aspectRatio = 1.0;
const double PI = acos(-1);
int recursionLevel, resolution;
bool isAxes = true, isCube = false, isPyramid = false;
std::vector<Object*>myObjects=std::vector<Object*>();
std::vector<LightSource*>myLightSources=std::vector<LightSource*>();

