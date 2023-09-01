#include <windows.h> // for MS Windows
#include <GL/glut.h> // GLUT, include glu.h and gl.h
#include <cmath>
#include <vector>
#include <iostream>
#include "1805035_globals.h"
#include "1805035_keyboard.h"
// #include "1805035_octahedron.h"
#include "1805035_sphere.h"
#include "1805035_Ray.h"
#include "1805035_Pyramid.h"
#include "1805035_NormalLightSource.h"
#include "1805035_floor.h"
#include "1805035_Cube.h"
// #include "1805035_globals.h"
#include "1805035_readFile.h"
// #include "1805035_imageCapture.h"
// #include "1805035_cylinder.h"

/* Initialize OpenGL Graphics */
void initGL()
{
    // Set "clearing" or background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
    glEnable(GL_DEPTH_TEST);              // Enable depth testing for z-culling
    sphereScale = 0.0f;
}

/* Draw axes: X in Red, Y in Green and Z in Blue */
void drawAxes()
{
    glLineWidth(3);
    glBegin(GL_LINES);
    glColor3f(1, 0, 0); // Red
    // X axis
    glVertex3f(0, 0, 0);
    glVertex3f(30, 0, 0);

    glColor3f(0, 1, 0); // Green
    // Y axis
    glVertex3f(0, 0, 0);
    glVertex3f(0, 30, 0);

    glColor3f(0, 0, 1); // Blue
    // Z axis
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 30);
    glEnd();
}
const int numberOfPixels = 768;
// points3D pointBuffer[numberOfPixels*numberOfPixels];
// Ray rays[numberOfPixels * numberOfPixels];
// void pointGeneration()
// {
//     double fovX = fovY * aspectRatio;
//     double planeHeight = 2 * nearZ * tan(fovY / 2 * DEG2RAD);
//     double planeWidth = 2 * nearZ * tan(fovX / 2 * DEG2RAD);
//     points3D middlePoint = eye + (center-eye).normalize() * nearZ;
//     points3D rightVector = (center-eye).cross(up).normalize();
//     // find top right point
//     std::cout<<middlePoint<<"--"<<rightVector<<"--"<<eye<<"--"<<center<<std::endl;
    

//     // generate all rays from  this
//     double pixelWidth = planeWidth / numberOfPixels, pixelHeight = planeHeight / numberOfPixels;
//     // points3D pointsBuffer[numberOfPixels * numberOfPixels];
//     for (int row = 0; row < numberOfPixels; row++)
//     {
//         for (int col = 0; col < numberOfPixels; col++)
//         {
//             // Calculate the position of the current pixel's center on the near plane
//             double xOffset = (col - numberOfPixels / 2.0 + 0.5) * pixelWidth;
//             double yOffset = (row - numberOfPixels / 2.0 + 0.5) * pixelHeight;
//             // pointsBuffer[row * numberOfPixels + col] = middlePoint + rightVector * xOffset + up * yOffset;
//             // Calculate the direction vector from the camera to the center of the current pixel
//             points3D rayDirection = (middlePoint + rightVector * xOffset + up * yOffset - eye).normalize();
//             // Create a ray starting from the camera position and going in the calculated direction
//             rays[row * numberOfPixels + col].origin = eye;
//             rays[row * numberOfPixels + col].direction = rayDirection;
            
            
//             // pointBuffer[row*numberOfPixels+col]=rayDirection;
//         }
//     }

//     std::cout << "point generation completed" << std::endl;
// }

/*  Handler for window-repaint event. Call back when the window first appears and
    whenever the window needs to be re-painted. */
void display()
{
    // glClear(GL_COLOR_BUFFER_BIT);            // Clear the color buffer (background)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW); // To operate on Model-View matrix
    glLoadIdentity();           // Reset the model-view matrix

    // default arguments of gluLookAt
    // gluLookAt(0,0,0, 0,0,-100, 0,1,0);

    // control viewing (or camera)
    
    gluLookAt(eye.x, eye.y, eye.z,
              center.x, center.y, center.z,
              up.x, up.y, up.z);

    drawAxes();
    
    /*
        height = 2*nearDistance*tan(fovY/2) and
        width = 2*nearDistance*tan(fovX/2); where fovX and fovY are in angles and fovX =
        aspecRatio*fovY. Also, the middle point of that screen is midpoint = cameraPosition+(l
        vector)*nearDistance
    */
//    std::cout<<myObject->shininess<<std::endl;
     for(Object* obj:myObjects)
     {
         obj->draw();
     }
    for(LightSource* lightSource:myLightSources)
    {
        lightSource->draw();
    }

    glutSwapBuffers(); // Render now
}

/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshapeListener(GLsizei width, GLsizei height)
{ // GLsizei for non-negative integer
    // Compute aspect ratio of the new window
    if (height == 0)
        height = 1; // To prevent divide by 0
    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    // Set the viewport to cover the new window
    glViewport(0, 0, width, height);

    // Set the aspect ratio of the clipping area to match the viewport
    glMatrixMode(GL_PROJECTION); // To operate on the Projection matrix
    glLoadIdentity();            // Reset the projection matrix
    /*if (width >= height) {
        // aspect >= 1, set the height from -1 to 1, with larger width
        gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
    } else {
        // aspect < 1, set the width to -1 to 1, with larger height
        gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
    }*/
    // Enable perspective projection with fovy, aspect, zNear and zFar
    gluPerspective(fovY, aspectRatio, nearZ, farZ);
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char **argv)
{
    
    // pointGeneration();
    // for(int i=0; i < a. size(); i++)
    //     std::cout << a.at(i) << ' ';
    // myObjects.push_back(new sphere());
    // myObjects.push_back(new Pyramid(points3D(-40.0 ,0.0 ,5.0),30,40,rgb(1,0,0),ReflectionCoefficient(0.4 ,0.1, 0.0, 0.4),20));
    // myObjects.push_back(new sphere(points3D(-20,0,-20),15,rgb(0,0,1),ReflectionCoefficient(0.2, 0.3, 0.1, 0.3),20));
    // Object *floorObject =new Floor(50,rgb(1,1,1),ReflectionCoefficient(0.1, 0.3, 0, 0.6),10);
    // floorObject->isFloor=true;
    // myObjects.push_back(floorObject);
    // myObjects.push_back(new Cube(points3D(0,10,0),10,rgb(0,1,0),ReflectionCoefficient(0.15 ,0.1 ,0.4 ,0.45),20));
    // myLightSources.push_back(new NormalLightSource(points3D(-2,50,3),0.0000002));
    // myLightSources.push_back(new NormalLightSource(points3D(10,3,3),0.000002));
    readFile();
    // myObjects;
    // myLightSources;
    glutInit(&argc, argv);                                    // Initialize GLUT
    glutInitWindowSize(640, 640);                             // Set the window's initial width & height
    glutInitWindowPosition(50, 50);                           // Position the window's initial top-left corner
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB); // Depth, Double buffer, RGB color
    glutCreateWindow("OpenGL 3D Drawing");                    // Create a window with the given title
    glutDisplayFunc(display);                                 // Register display callback handler for window re-paint
    glutReshapeFunc(reshapeListener);                         // Register callback handler for window re-shape
    glutKeyboardFunc(keyboardListener);                       // Register callback handler for normal-key event
    glutSpecialFunc(specialKeyListener);                      // Register callback handler for special-key event
    initGL();    
                                               // Our own OpenGL initialization
    glutMainLoop();                                           // Enter the event-processing loop
    return 0;
}
