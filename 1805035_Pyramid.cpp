#include "1805035_Pyramid.h"
#include <GL/glut.h>
#include "1805035_globals.h"

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
    // drawBase(pyramidVertices[0], pyramidVertices[1], pyramidVertices[2], pyramidVertices[3]);
    base.draw();
    //draw 4 faces

    // rgb testc[4]={red,green,blue,yellow};
    for(int i=0;i<4;i++){
        // rgb c=testc[i];
        // glColor3f(c.r,c.g,c.b);
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
    double yMid = lowerLeft.y + width / 2.0;

    // 4 Base vertices
    pyramidVertices[0] = points3D(lowerLeft.x, lowerLeft.y, lowerLeft.z);
    pyramidVertices[1] = points3D(lowerLeft.x + width, lowerLeft.y, lowerLeft.z);
    pyramidVertices[2] = points3D(lowerLeft.x + width, lowerLeft.y +width, lowerLeft.z);
    pyramidVertices[3] = points3D(lowerLeft.x, lowerLeft.y+width , lowerLeft.z);

    // Top vertex
    pyramidVertices[4] = points3D(xMid,  yMid,lowerLeft.z + height);
    faces[0] = triangle(pyramidVertices[0], pyramidVertices[1], pyramidVertices[4]);
    faces[1] = triangle(pyramidVertices[1], pyramidVertices[2], pyramidVertices[4]);
    faces[2] = triangle(pyramidVertices[2], pyramidVertices[3], pyramidVertices[4]);
    faces[3] = triangle(pyramidVertices[3], pyramidVertices[0], pyramidVertices[4]);
    base = plane(pyramidVertices[0], pyramidVertices[1], pyramidVertices[2], pyramidVertices[3]);
    // for(int i=0;i<4;i++){
    //     faces[i].print();
    // }
}


bool Pyramid::getIntersectionPoints(Ray ray){
    //TODO
    double t_min=-1;
    triangle min_face;
    bool isBase=false;
    for(int i=0;i<4;i++){
        // double t = faces[i].intersectionPointusingBarycentricEquation(ray);
        double t=faces[i].rayIntersection(ray,intersectionPoint);
        // std::cout<<t<<" "<<std::endl;
        if(t>0&&(t_min>t||t_min==-1)){
            t_min = t;
            min_face = faces[i];
        }
            
    }
    double t=base.getIntersection(ray);
    if(t>0&&(t_min>t||t_min==-1)){
        t_min = t;
        isBase=true;
    }
    if(t_min>0){
        t_value=t_min;
        // std::cout<<"ok"<<std::endl;
        
        intersectionPoint = ray.origin + ray.direction*t_min;
        if(isBase){
            normalAtIntersectionPoint = base.getNormal(ray.direction);
        }
        else{
            normalAtIntersectionPoint = min_face.getNormal(ray.direction);
        }
        intersectionPoint = intersectionPoint + normalAtIntersectionPoint * 0.0001;
        // normalAtIntersectionPoint = min_face.getNormal(intersectionPoint);
        reflectedRay=ray.direction-normalAtIntersectionPoint*(ray.direction.dot(normalAtIntersectionPoint))*2;
        // reflectedRay=reflectedRay*-1;
        // color=rgb(1,1,0);
        return true;
    }
    else
    {
        return false;
    }
   
}