#include <GL/glut.h>
#include "floor.h"

void Floor::draw(){
    // std::cout<<"drawing floor"<<std::endl;
    int size=500;
    int checkerSize=50;
    //draw checkered infinte floor
   int numSquaresX = static_cast<int>(size / checkerSize);
    int numSquaresY = static_cast<int>(size / checkerSize);

    for (int i = 0; i < numSquaresX; ++i) {
        for (int j = 0; j < numSquaresY; ++j) {
            double x = 0- size / 2.0 + i * checkerSize;
            double y = 0 - size / 2.0 + j * checkerSize;

            if ((i + j) % 2 == 0) {
                glColor3f(0.0f, 0.0f, 0.0f); // Black
            } else {
                glColor3f(1.0f, 1.0f, 1.0f); // White
            }

            glBegin(GL_QUADS);
            glVertex3d(x, y,-6);
            glVertex3d(x + checkerSize,y,-6);
            glVertex3d(x + checkerSize, y + checkerSize,-6);
            glVertex3d(x, y+ checkerSize,-6);
            glEnd();
        }
    }

}
bool Floor::getIntersectionPoints(Ray ray){
    points3D normal=points3D(0,0,1);
    // color=rgb(1,1,1);
    t_value=-(ray.origin.dot(normal)+6)/ray.direction.dot(normal);
    if(t_value>0){
        intersectionPoint = ray.origin + ray.direction*t_value;
        if(normal.dot(intersectionPoint)<0){
            normal = -normal;
        }
        //color at that intersection point
        int size=500;
        int squareX=static_cast<int>((intersectionPoint.x-size/2)/50);
        int squareY=static_cast<int>((intersectionPoint.y-size/2)/50);
        if((squareX+squareY)%2==0){
            color=rgb(0,0,0);
        }
        else{
            color=rgb(1,1,1);
        }

        normalAtIntersectionPoint=normal;
        reflectedRay=ray.direction-normalAtIntersectionPoint*(ray.direction.dot(normalAtIntersectionPoint))*2;
        return true;
    }
    return false;
}