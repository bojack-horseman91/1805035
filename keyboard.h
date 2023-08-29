#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <GL/glut.h>
#include <cmath>
#include <vector>
#include <iostream>
#include "helper.h"
// #include "cylinder.h"
#include "globals.h"
#include "imageCapture.h"
#include "camera.h"
/* Callback handler for normal-key event */
void keyboardListener(unsigned char key, int x, int y);
/* Callback handler for special-key event */
void specialKeyListener(int key, int x,int y);

#endif