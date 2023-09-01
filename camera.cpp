#include "camera.h"

double cameraScaleFactor = 0.8;
double rotationTheta = 0.09;

void moveWithoutReferenceChange(int direction) {
    // 
    eye+=up*cameraScaleFactor*direction;
    // up=(center-eye).cross(rightVector).normalize(); 
}
void moveUpWithoutReferenceChange() {
    moveWithoutReferenceChange(1);
}

void moveDownWithoutReferenceChange() {
    moveWithoutReferenceChange(-1);
}

void moveCamera(const points3D& direction) {
    eye += direction.scaled(cameraScaleFactor);
    center += direction.scaled(cameraScaleFactor);
}
void  moveCameraUp() {
    moveCamera(up);
}
void moveCameraDown() {
    moveCamera(up*-1);
}
void moveCameraRight() {
    points3D viewVector = center - eye;
    points3D unitVector = up.cross(viewVector).normalize();
    moveCamera(unitVector);
}

void moveCameraLeft() {
    points3D viewVector = center - eye;
    points3D unitVector = up.cross(viewVector).normalize();
    moveCamera((unitVector*-1));
}

void moveCameraForward() {
    points3D viewVector = center - eye;
    moveCamera(viewVector.normalize());
}

void moveCameraBackward() {
    points3D viewVector = center - eye;
    moveCamera(viewVector.normalize()*-1);
}

void rotateCamera(int direction, points3D axis) {
    double cosTheta = cos(rotationTheta);
    double sinTheta = sin(rotationTheta);

    points3D viewVector = center - eye;
    points3D rightVector = up.cross(viewVector).normalize();

    points3D rotatedViewVector = viewVector * cosTheta + axis*(sinTheta * viewVector.length());
    points3D newCenter = eye + rotatedViewVector ;

    center = newCenter;
    up = (rotatedViewVector.cross(rightVector)).normalize();
    center.print(1);
    axis.print(2);
}
void tiltCamera(int direction) {
    double cosTheta = cos(rotationTheta);
    double sinTheta = sin(rotationTheta);

    points3D viewVector = center - eye;
    points3D rightVector = viewVector.cross(up).normalize();

    points3D rotatedViewVector = up * cosTheta + rightVector*(sinTheta );
    up= rotatedViewVector.normalize();
}
void tiltCameraClockwise() {
    double theta = rotationTheta;
    points3D viewVector = center - eye;
    points3D rightVector = up.cross(viewVector).normalize();
    points3D rotatedUpVector = up * cos(theta) + rightVector * sin(theta);
    up = rotatedUpVector.normalize();

}
void tiltCameraCounterClockwise() {
    double theta = rotationTheta;
    points3D viewVector = center - eye;
    points3D rightVector = up.cross(viewVector).normalize();
    points3D rotatedUpVector = up * cos(theta) - rightVector * sin(theta);
    up = rotatedUpVector.normalize();

}
void spinObjectClockwise(){
  double theta = rotationTheta;
    points3D viewVector =  eye-center;
    points3D rightVector = up.cross(viewVector).normalize();
    points3D rotatedVector = viewVector * cos(theta) + rightVector * sin(theta)*viewVector.length();
    eye = center+rotatedVector;
    up = rotatedVector.cross(rightVector).normalize();
}
void spinObjectCounterClockwise(){
     double theta = rotationTheta;
    points3D viewVector =  eye-center;
    points3D rightVector = viewVector.cross(up).normalize();
    points3D rotatedVector = viewVector * cos(theta) + rightVector * sin(theta)*viewVector.length();
    eye = center+rotatedVector;
    up = rightVector.cross(rotatedVector).normalize();
}

void rotateCameraRightLeftWrapper(int direction) {
     // based on direction get right vector
     points3D rightVector;
    if(direction == 1) {
       rightVector = up.cross(center - eye).normalize();
    } else if(direction == -1) {
       rightVector = (center - eye).cross(up).normalize();
    }
    
    rotateCamera(direction, rightVector);
}

void rotateCameraRight() {
    rotateCameraRightLeftWrapper(1);
}

void rotateCameraLeft() {
    rotateCameraRightLeftWrapper(-1);
}

void rotateCameraUpDownWrapper(int direction) {
    points3D rightVector;
    points3D axis;
    points3D viewVector = center - eye;
   if(direction == 1) {
       rightVector = up.cross(center - eye).normalize();
        axis=rightVector.cross(viewVector).normalize();
    } else if(direction == -1) {
       rightVector = up.cross(center - eye).normalize();
        axis=viewVector.cross(rightVector).normalize();
    }
    rotateCamera(direction, axis);
}

void rotateCameraUp() {
    rotateCameraUpDownWrapper(1);
}

void rotateCameraDown() {
    rotateCameraUpDownWrapper(-1);
}

// void tiltCameraClockwise() {
//     points3D viewVector = center - eye;
//     points3D rightVector = up.cross(viewVector).normalize();
//     points3D newUp = viewVector.cross(rightVector).normalize();
//     up = newUp;
// }
