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
    rgb testc[4]={red,green,blue,yellow};
    for(int i=0;i<4;i++){
        rgb c=testc[i];
        glColor3f(c.r,c.g,c.b);
        faces[i].draw();
    }
     glPointSize(50);
    // glBegin(GL_POINTS);{
    //     glColor3d(color.r,color.g,color.b);
        
    //     glVertex3d(pyramidVertices[4].x, pyramidVertices[4].y, pyramidVertices[4].z);
    // }
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
    double zMid = lowerLeft.z + width / 2.0;

    // 4 Base vertices
    pyramidVertices[0] = points3D(lowerLeft.x, lowerLeft.y, lowerLeft.z);
    pyramidVertices[1] = points3D(lowerLeft.x + width, lowerLeft.y, lowerLeft.z);
    pyramidVertices[2] = points3D(lowerLeft.x + width, lowerLeft.y , lowerLeft.z+width);
    pyramidVertices[3] = points3D(lowerLeft.x, lowerLeft.y , lowerLeft.z+width);

    // Top vertex
    pyramidVertices[4] = points3D(xMid, lowerLeft.y+height, zMid );
    faces[0] = triangle(pyramidVertices[0], pyramidVertices[1], pyramidVertices[4]);
    faces[1] = triangle(pyramidVertices[1], pyramidVertices[2], pyramidVertices[4]);
    faces[2] = triangle(pyramidVertices[2], pyramidVertices[3], pyramidVertices[4]);
    faces[3] = triangle(pyramidVertices[3], pyramidVertices[0], pyramidVertices[4]);

    // for(int i=0;i<4;i++){
    //     faces[i].print();
    // }
}


bool Pyramid::getIntersectionPoints(Ray ray){
    //TODO
    double t_min=-1;
    triangle min_face;
    for(int i=0;i<4;i++){
        // double t = faces[i].intersectionPointusingBarycentricEquation(ray);
        double t=faces[i].rayIntersection(ray,intersectionPoint);
        // std::cout<<t<<" "<<std::endl;
        if(t>0&&(t_min>t||t_min==-1)){
            t_min = t;
            min_face = faces[i];
        }
            
    }
    if(t_min>0){
        t_value=t_min;
        // std::cout<<"ok"<<std::endl;
        intersectionPoint = ray.origin + ray.direction*t_min;
        normalAtIntersectionPoint = min_face.getNormal(intersectionPoint);
        reflectedRay=ray.direction-normalAtIntersectionPoint*(ray.direction.dot(normalAtIntersectionPoint))*2;
        // color=rgb(1,1,0);
        return true;
    }
    else
    {
        return false;
    }
   
}