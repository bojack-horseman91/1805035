#include "Pyramid.h"
#include <GL/glut.h>
#include "globals.h"

Pyramid::Pyramid(){
    this->lowerLeft = points3D(0,0,0);
    this->width = 10;
    this->height = 10;
   
}

Pyramid::Pyramid(points3D lowerLeft, double width, double height, rgb color, ReflectionCoefficient reflectionCoefficient, int shininess)\
    :Object(color, reflectionCoefficient, shininess)
{
    this->lowerLeft = lowerLeft;
    this->width = width;
    this->height = height;
    
}
void Pyramid::draw(){

    calculatePyramidVertices();

    // Draw base
    drawBase(pyramidVertices[0], pyramidVertices[1], pyramidVertices[2], pyramidVertices[3]);
    //draw 4 faces
    drawTriangle(pyramidVertices[0], pyramidVertices[1], pyramidVertices[4]);
    drawTriangle(pyramidVertices[1], pyramidVertices[2], pyramidVertices[4]);
    drawTriangle(pyramidVertices[2], pyramidVertices[3], pyramidVertices[4]);
    drawTriangle(pyramidVertices[3], pyramidVertices[0], pyramidVertices[4]);
     glPointSize(50);
    glBegin(GL_POINTS);{
      
        glColor3f(1,0,0);
        glVertex3d(pyramidVertices[4].x, pyramidVertices[4].y, pyramidVertices[4].z);
    }
    glEnd();
    
}

void Pyramid::drawBase(points3D a, points3D b, points3D c, points3D d) {
    glBegin(GL_QUADS);
    {
        glVertex3d(a.x, a.y, a.z);
        glVertex3d(b.x, b.y, b.z);
        glVertex3d(c.x, c.y, c.z);
        glVertex3d(d.x, d.y, d.z);
    }
    glEnd();
}

void Pyramid::drawTriangle(points3D a, points3D b, points3D c) {
    glBegin(GL_TRIANGLES);
    {
        glVertex3d(a.x, a.y, a.z);
        glVertex3d(b.x, b.y, b.z);
        glVertex3d(c.x, c.y, c.z);
    }
    glEnd();
}

void Pyramid::calculatePyramidVertices() {
    double xMid = lowerLeft.x + width / 2.0;
    double yMid = lowerLeft.y + width / 2.0;

    // 4 Base vertices
    pyramidVertices[0] = points3D(lowerLeft.x, lowerLeft.y, lowerLeft.z);
    pyramidVertices[1] = points3D(lowerLeft.x + width, lowerLeft.y, lowerLeft.z);
    pyramidVertices[2] = points3D(lowerLeft.x + width, lowerLeft.y +width, lowerLeft.z);
    pyramidVertices[3] = points3D(lowerLeft.x, lowerLeft.y+width , lowerLeft.z);

    // Top vertex
    pyramidVertices[4] = points3D(xMid, yMid, lowerLeft.z+height );


}


bool Pyramid::getIntersectionPoints(Ray ray){
    //TODO
    return false;
}