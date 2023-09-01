#include "SpotLight.h"
#include <GL/glut.h> // Make sure you have the appropriate OpenGL headers

SpotLight::SpotLight() : LightSource(), cutOffAngle(0.0) {
    this->isSpotLight=true;
}

SpotLight::SpotLight(points3D position, double falloff, double cutOffAngle, points3D lookDirection)
    : LightSource(position, falloff), cutOffAngle(cutOffAngle),lookDirection(lookDirection) {
        this->isSpotLight=true;
    }


// Assuming the LightSource and SpotLight classes are defined as mentioned before

void drawCone(const points3D& apex, const points3D& direction, double angle, double height) {
    // Calculate the base radius of the cone
    double baseRadius = height * tan(angle);

    // Set up OpenGL drawing code
    glPushMatrix();
    glTranslated(apex.x, apex.y, apex.z);

    // Calculate rotation angle and axis to align the cone with the direction
    points3D axis = direction.cross(points3D(0, 1, 0)); // Assuming up vector is (0, 1, 0)
    axis.normalize();
    double rotationAngle = -acos(direction.dot(points3D(0, 1, 0)));
    glRotated(rotationAngle * 180.0 / M_PI, axis.x, axis.y, axis.z);
    glColor3d(1,1,1);
    // Draw the cone
    glutSolidCone(baseRadius, height, 40, 40); // Adjust the resolution as needed

    // Restore the matrix
    glPopMatrix();
}
// Function to rotate a vector by an angle (in degrees) around another vector
void rotateVector(points3D& axis, points3D& vector, float angle) {
    // Calculate the cross product between the axis and the vector
    points3D u;
    u.x = axis.y * vector.z - axis.z * vector.y;
    u.y = axis.z * vector.x - axis.x * vector.z;
    u.z = axis.x * vector.y - axis.y * vector.x;

    // Calculate sine and cosine of the angle
    float cosAngle = cos(angle);
    float sinAngle = sin(angle);

    // Apply the rotation formula
    vector.x = u.x * sinAngle + vector.x * cosAngle;
    vector.y = u.y * sinAngle + vector.y * cosAngle;
    vector.z = u.z * sinAngle + vector.z * cosAngle;
}



void RenderCone( points3D baseToApexLength,  points3D apexLocation, double height, double radius, int slices)
{
    points3D c = apexLocation - (baseToApexLength * height);
    points3D e0 = baseToApexLength.cross(points3D(0, 1, 0)).normalize();
    points3D e1 = baseToApexLength.cross(e0).normalize();
    float angInc = 360.0f / slices * M_PI / 180;
    slices++; // Increment slices to include the apex and base vertices
    
    std::vector<points3D> vertices(slices);
    for (int i = 0; i < slices; ++i)
    {
        float rad = angInc * i;
        points3D p = c + ((e0 * cos(rad) + e1 * sin(rad)) * radius);
        vertices[i] = p;
    }

    glBegin(GL_TRIANGLE_FAN);
    glVertex3d(apexLocation.x, apexLocation.y, apexLocation.z);
    for (const auto &vertex : vertices)
    {
        glVertex3d(vertex.x, vertex.y, vertex.z);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex3d(c.x, c.y, c.z);
    for (int i = slices - 1; i >= 0; --i)
    {
        glVertex3d(vertices[i].x, vertices[i].y, vertices[i].z);
    }
    glEnd();
}


void SpotLight::draw() {
    // double del = 2;
    // double h = 1;
    // points3D radiusVec = lookDirection.cross(points3D(0, 0, 1));
    // radiusVec.normalize();
    // points3D center = sourcePosition + lookDirection * h;
    // double circleRadius = h * std::tan(cutOffAngle * M_PI / 180.0);
    // radiusVec = radiusVec * circleRadius;
    // points3D prev = center + radiusVec;

    // glColor3f(1, 1, 1);
    // glBegin(GL_TRIANGLES);
    // for (int i = del; i < 360; i += del) {
    //     rotateVector(lookDirection, radiusVec, del);
    //     points3D newPoint = center + radiusVec;
    //     glVertex3f(sourcePosition.x, sourcePosition.y, sourcePosition.z);
    //     glVertex3f(prev.x, prev.y, prev.z);
    //     glVertex3f(newPoint.x, newPoint.y, newPoint.z);
    //     prev = newPoint;
    // }
    // glEnd();

    double angle = cutOffAngle; // Example angle in degrees
    double height = 5.0;
    double radius = height * tan(angle * M_PI / 180.0f);
    int slices = 30;
    
    RenderCone(lookDirection, sourcePosition, height, radius, slices);


}

// bool SpotLight::willIlluminate(Object *curObj, Ray toSource, double distance)
// {
//     // check the angle between the look direction and the ray is less than the cut off angle
//     if (acos(toSource.direction.dot(lookDirection)) > cutOffAngle)
//     {
//         return false;
//     }
//     //check for collisions with other objects
//     for (Object *obj : myObjects)
//     {
//         if (obj == curObj)
//             continue;
//         if (obj->getIntersectionPoints(toSource))
//         {
//             if (obj->t_value > 0 && obj->t_value < distance)
//                 return false;
//         }
//     }

//     return true;
// }