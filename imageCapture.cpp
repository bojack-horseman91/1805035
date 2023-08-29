#include "imageCapture.h"
#include "GL/glut.h"

const int numberOfPixels = 768;
// points3D pointBuffer[numberOfPixels*numberOfPixels];
Ray rays[numberOfPixels * numberOfPixels];

void pointGeneration()
{
    double fovX = fovY * aspectRatio;
    double planeHeight = 2 * nearZ * tan(fovY / 2 * DEG2RAD);
    double planeWidth = 2 * nearZ * tan(fovX / 2 * DEG2RAD);
    points3D middlePoint = eye + (center-eye).normalize() * nearZ;
    points3D rightVector = (center-eye).cross(up).normalize();
    // find top right point

    

    // generate all rays from  this
    double pixelWidth = planeWidth / numberOfPixels, pixelHeight = planeHeight / numberOfPixels;
    // points3D pointsBuffer[numberOfPixels * numberOfPixels];
    for (int row = 0; row < numberOfPixels; row++)
    {
        for (int col = 0; col < numberOfPixels; col++)
        {
            // Calculate the position of the current pixel's center on the near plane
            double xOffset = (col - numberOfPixels / 2.0 + 0.5) * pixelWidth;
            double yOffset = (row - numberOfPixels / 2.0 + 0.5) * pixelHeight;
            // pointsBuffer[row * numberOfPixels + col] = middlePoint + rightVector * xOffset + up * yOffset;
            // Calculate the direction vector from the camera to the center of the current pixel
            points3D rayDirection = (middlePoint + rightVector * xOffset + up * yOffset - eye).normalize();
            // Create a ray starting from the camera position and going in the calculated direction
            rays[row * numberOfPixels + col].origin = eye;
            rays[row * numberOfPixels + col].direction = rayDirection;
            
            
            // pointBuffer[row*numberOfPixels+col]=rayDirection;
        }
    }

    std::cout << "point generation completed" << std::endl;
}

void imageProcessing()
{
    bitmap_image image(numberOfPixels, numberOfPixels);
    std::cout << eye << " " << center << " " << rays[0].origin << " " << rays[0].direction << std::endl;
    for (int row = 0; row < numberOfPixels; row++)
    {
        for (int col = 0; col < numberOfPixels; col++)
        {

            Ray ray = rays[row * numberOfPixels + col];
            glColor3d(1, 0, 0);
            glBegin(GL_POINTS);
            {
                // glVertex3d(ray.origin.x,ray.origin.y,ray.origin.z);
                glVertex3d(ray.origin.x + ray.direction.x * 10, ray.origin.y + ray.direction.y * 10, ray.origin.z + ray.direction.z * 10);
            }
            glEnd();
            double t_min_value=-1;
            rgb color=rgb();
           for(Object*obj:myObjects){
             if (obj->getIntersectionPoints(ray))
            {
               if(t_min_value==-1||t_min_value<obj->t_value)
               {
                t_min_value=obj->t_value;
                color=obj->calculated_light;
               }
                // std::cout<<row<<" "<<col<<std::endl;
            }
           }
           if(t_min_value>0){
             std::cout<<color.r*255<<" "<<color.g*255<<" "<<color.b*255<<std::endl;
             image.set_pixel(col,row, (color.r * 255), color.g * 255, color.b * 255);
           }

        }
    }
    std::cout << "almost done" << std::endl;
    image.save_image("test.bmp");
    std::cout << "done" << std::endl;
}

void captureImage()
{
    pointGeneration();
    imageProcessing();
}