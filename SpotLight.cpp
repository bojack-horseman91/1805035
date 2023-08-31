#include "SpotLight.h"
#include <GL/glut.h> // Make sure you have the appropriate OpenGL headers

SpotLight::SpotLight() : LightSource(), cutOffAngle(0.0) {}

SpotLight::SpotLight(points3D position, double falloff, double cutOffAngle, points3D lookDirection)
    : LightSource(position, falloff), cutOffAngle(cutOffAngle),lookDirection(lookDirection) {}


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

    // Draw the cone
    glutSolidCone(baseRadius, height, 20, 20); // Adjust the resolution as needed

    // Restore the matrix
    glPopMatrix();
}

void SpotLight::draw() {
    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0); // Set the spotlight color (yellow in this case)

    // Draw a cone representing the spotlight
    drawCone(sourcePosition, lookDirection, cutOffAngle * M_PI / 180.0, 10.0); // Adjust height as needed

    glPopMatrix();
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