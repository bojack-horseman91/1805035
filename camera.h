#ifndef CAMERA_H
#define CAMERA_H
#include "globals.h"
#include <cmath>


void moveCameraRight();
void moveCameraLeft();
void moveCameraForward();
void moveCameraBackward();
void moveCameraUp();
void moveCameraDown();
void rotateCameraUp();
void rotateCameraDown();
void rotateCameraLeft();
void rotateCameraRight();
void tiltCameraClockwise();
void tiltCameraCounterClockwise();
void spinObjectClockwise();
void spinObjectCounterClockwise();
void moveUpWithoutReferenceChange();
void moveDownWithoutReferenceChange();
#endif