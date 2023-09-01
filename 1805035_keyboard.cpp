#include "1805035_keyboard.h"



/* Callback handler for normal-key event */
void keyboardListener(unsigned char key, int x, int y) {
    float v = 0.1;
    switch (key) {

    //
    // case '.':
    //     triangleScale=std::min(triangleScale+.1,1.0);
    //     sphereScale=std::max(1-triangleScale,0.0);
    // break;
    // case ',':
    //     triangleScale=std::max(triangleScale-0.1,0.0);
    //     sphereScale=std::min(1-triangleScale,1.0);
    // break;
     case ' ': // Spacebar key
            TEXTUREMODE = !TEXTUREMODE; // Toggle the texture mode
            break;
    case 'a':
        spinObjectClockwise();
        break;
    case 'd':
        spinObjectCounterClockwise();
        break;
    // Control eye (location of the eye)
    // control eye.x

    case '0':
        captureImage();
        break;
    case '1':
        // eye.x += v;
        rotateCameraLeft();
        break;
    case '2':
        // eye.x -= v;
        rotateCameraRight();
        break;
    // control eye.y
    case '3':
        // eye.y += v;
        rotateCameraUp();
        break;
    case '4':
        // eye.y -= v;
        rotateCameraDown();
        break;
    // control eye.z
    case '5':
        // eye.z += v;
        tiltCameraClockwise();
        break;
    case '6':
        // eye.z -= v;
        tiltCameraCounterClockwise();
        break;
    case 'w':
    moveUpWithoutReferenceChange();
    break;
    case 's':
    moveDownWithoutReferenceChange();
    break;
    // // Control center (location where the eye is looking at)
    // // control center.x
    // case 'q':
    //     center.x += v;
    //     break;
    // case 'w':
    //     center.x -= v;
    //     break;
    // // control center.y
    // case 'e':
    //     center.y += v;
    //     break;
    // case 'r':
    //     center.y -= v;
    //     break;
    // // control center.z
    // case 't':
    //     center.z += v;
    //     break;
    // case 'y':
    //     center.z -= v;
    //     break;

    // // Control what is shown
    // case 'a':
    //     isAxes = !isAxes;   // show/hide Axes if 'a' is pressed
    //     break;
    // case 'c':
    //     isCube = !isCube;   // show/hide Cube if 'c' is pressed
    //     break;
    // case 'p':
    //     isPyramid = !isPyramid; // show/hide Pyramid if 'p' is pressed
    //     break;
    // //move left
    // case 'z':
    //     test();
    //     break;
    // Control exit
    // case 27:    // ESC key
    //     exit(0);    // Exit window
    //     break;
    }
    glutPostRedisplay();    // Post a paint request to activate display()
}

/* Callback handler for special-key event */
void specialKeyListener(int key, int x,int y) {
    // double v = 0.25;
    // double lx = center.x - eye.x;
    // double lz = center.z - eye.z;
    // double s;
    switch (key) {
    case GLUT_KEY_PAGE_DOWN:
    moveCameraDown();
    break;
    case GLUT_KEY_PAGE_UP:
    moveCameraUp();
    break;
    case GLUT_KEY_LEFT:
        moveCameraLeft();
        // eye.x += v * (up.y*lz);
        // eye.z += v * (-lx*up.y);
        // s = sqrt(eye.x*eye.x + eye.z*eye.z) / (4 * sqrt(2));
        // eye.x /= s;
        // eye.z /= s;
        break;
    case GLUT_KEY_RIGHT:
        // eye.x += v * (-up.y*lz);
        // eye.z += v * (lx*up.y);
        // s = sqrt(eye.x*eye.x + eye.z*eye.z) / (4 * sqrt(2));
        // eye.x /= s;
        // eye.z /= s;
        moveCameraRight();
        break;
    case GLUT_KEY_UP:
        moveCameraForward();
        // eye.y += v;
        break;
    case GLUT_KEY_DOWN:
        // eye.y -= v;
        moveCameraBackward();
        break;
    
    default:
        return;
    }
    glutPostRedisplay();    // Post a paint request to activate display()
}