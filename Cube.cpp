#include "Cube.h"

void Cube::draw()
{
    rgb colors[6]={rgb(1,0,0),rgb(0,1,0),rgb(0,0,1),rgb(1,1,0),rgb(1,0,1),rgb(0,1,1)};
    for (int i = 0; i < 6; i++)
    {
        // glColor3d(color.r, color.g, color.b);
        glColor3d(colors[i].r, colors[i].g, colors[i].b);
        planes[i].draw();
    }
}
Cube::Cube(points3D bottomLowerLeft, double side, rgb color, ReflectionCoefficient reflectionCoefficient, int shininess)
:Object(color, reflectionCoefficient, shininess){
    this->bottomLowerLeft = bottomLowerLeft;
    this->side = side;
    planePointsCalulation();

}
bool Cube::getIntersectionPoints(Ray ray)
{
    double t_minvalue = -1;
    for (int i = 0; i < 6; i++)
    {
        double t =planes[i].getIntersection(ray);
        if (t > 0)
        {
            if (t_minvalue == -1||t < t_minvalue)
            {
                t_minvalue = t;
            }
        }
        if(t_minvalue>0){
            intersectionPoint = ray.origin + ray.direction * t_minvalue;
            normalAtIntersectionPoint = planes[i].getNormal(ray.origin);
            reflectedRay = ray.direction - normalAtIntersectionPoint * (ray.direction.dot(normalAtIntersectionPoint)) * 2;
            t_value = t_minvalue;
            return true;
        }
    }
    return false;
}

void Cube::planePointsCalulation(){
   // Calculate the points for each plane based on the bottomLowerLeft corner and side length
    
    // Plane 1: Bottom face
    points3D a = bottomLowerLeft;
    points3D b = bottomLowerLeft + points3D(side, 0, 0);
    points3D c = bottomLowerLeft + points3D(side, 0, side);
    points3D d = bottomLowerLeft + points3D(0, 0, side);
    planes[0] = plane(a, b, c, d);

    // Plane 2: Top face
    points3D e = bottomLowerLeft + points3D(0, side, 0);
    points3D f = bottomLowerLeft + points3D(side, side, 0);
    points3D g = bottomLowerLeft + points3D(side, side, side);
    points3D h = bottomLowerLeft + points3D(0, side, side);
    
    planes[1] = plane(e, f, g, h);

    // Repeat for the remaining four faces
    //PLANE 3: LEFT FACE
    
    planes[2] = plane(a, d, h, e);

    //PLANE 4: RIGHT FACE
    // glColor3d(0, 1, 0);
    planes[3] = plane(b, c, g, f);
    // glColor3d(1, 0, 0);
    //PLANE 5: FRONT FACE
    // glColor3d(1, 0, 1);
    planes[4] = plane(a, b, f, e);
    
    //PLANE 6: BACK FACE
    // glColor3d(1, 1, 0);
    planes[5] = plane(d, c, g, h);




}