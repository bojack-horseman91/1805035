#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <GL/glut.h>
#include <cmath>
#include <vector>
#include <iostream>
#include "1805035_helper.h"
// #include "1805035_cylinder.h"
#include "1805035_globals.h"
#include "1805035_imageCapture.h"
#include "1805035_camera.h"
/* Callback handler for normal-key event */
void keyboardListener(unsigned char key, int x, int y);
/* Callback handler for special-key event */
void specialKeyListener(int key, int x,int y);

#endif