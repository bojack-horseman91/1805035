#include "imageCapture.h"
#include "GL/glut.h"

const int numberOfPixels = 768;
// Ray **rays;
Ray rays[numberOfPixels][numberOfPixels];
void pointGeneration()
{
//     rays = new Ray *[numberOfPixels];
//     for (int i = 0; i < numberOfPixels; ++i)
//     {
//         rays[i] = new Ray[numberOfPixels];
//     }
    double fovX = fovY * aspectRatio;
    double planeHeight = 2 * nearZ * tan(fovY / 2 * DEG2RAD);
    double planeWidth = 2 * nearZ * tan(fovX / 2 * DEG2RAD);
    points3D middlePoint = eye + (center - eye).normalize() * nearZ;
    points3D rightVector = (center - eye).cross(up).normalize();
    points3D topLeft = middlePoint + up * (planeHeight / 2) - rightVector * (planeWidth / 2);
    // find top right point

    // generate all rays from  this
    double pixelWidth = planeWidth / numberOfPixels, pixelHeight = planeHeight / numberOfPixels;
    // points3D pointsBuffer[numberOfPixels * numberOfPixels];
    for (int row = 0; row < numberOfPixels; row++)
    {
        for (int col = 0; col < numberOfPixels; col++)
        {
            points3D rayDirection = topLeft + rightVector * (col * pixelWidth) - up * (row * pixelHeight);
            // Create a ray starting from the camera position and going in the calculated direction
            // rays[row][col].origin = eye;
            rays[row][col] = Ray(eye, (rayDirection - eye).normalize());

            // pointBuffer[row*numberOfPixels+col]=rayDirection;
        }
    }

    std::cout << "point generation completed" << std::endl;
}
rgb rayTracing(Ray ray, int levelOfDepth)
{
    if (levelOfDepth == 3)
        return black;
    double t_min_value = -1;
    Object *selectedobj = nullptr;
    // rgb color = rgb();
    for (Object *obj : myObjects)
    {
        if (obj->getIntersectionPoints(ray))
        {
            // std::cout<<obj->t_value<<std::endl;
            if (obj->t_value > 0 && (t_min_value > obj->t_value || t_min_value == -1))
            {
                t_min_value = obj->t_value;
                // color = obj->calculated_light;
                selectedobj = obj;
                // std::cout<<t_min_value<<std::endl;
            }
            // std::cout<<row<<" "<<col<<std::endl;
        }
    }
    if (t_min_value <= 0)
        return black;
    Ray reflected = Ray(selectedobj->intersectionPoint, selectedobj->reflectedRay.normalize());
    rgb color = selectedobj->getAmbientColor();
    color = color + selectedobj->getDiffuseAndSpecularColor();
    color = color + rayTracing(reflected, levelOfDepth + 1) * selectedobj->reflectionCoefficient.reflection;
    // std::cout<<"color is :"<<color.r<<" "<<color.g<<" "<<color.b<<std::endl;
    // return selectedobj->color;
    // if(selectedobj->isFloor){
    //     std::cout<<selectedobj->color.r<<" "<<selectedobj->color.g<<" "<<selectedobj->color.b<<std::endl;
    // }
    return color;
}

void imageProcessing()
{
    bitmap_image image(numberOfPixels, numberOfPixels);
    std::cout << eye << " " << center << " " << rays[0][0].origin << " " << rays[0][0].direction << std::endl;
    for (int row = 0; row < numberOfPixels; row++)
    {
        for (int col = 0; col < numberOfPixels; col++)
        {

            Ray ray = rays[row][col];
            // double t_min_value = -1;
            // rgb color = rgb();
            // for (Object *obj : myObjects)
            // {
            //     if (obj->getIntersectionPoints(ray))
            //     {
            //         if (t_min_value == -1 || t_min_value < obj->t_value)
            //         {
            //             t_min_value = obj->t_value;
            //             color = obj->calculated_light;
            //         }
            //         // std::cout<<row<<" "<<col<<std::endl;
            //     }
            // }
            rgb color = rayTracing(ray, 0);

            //  std::cout<<color.r*255<<" "<<color.g*255<<" "<<color.b*255<<std::endl;
            image.set_pixel(col, row, (color.r * 255), color.g * 255, color.b * 255);
        }
        if (row % 100 == 0)
            std::cout << "rendering done: " << row << " " << row / numberOfPixels * 100.00 << "%" << std::endl;
    }
    std::cout << "almost done" << std::endl;
    image.save_image("test.bmp");
    std::cout << "done" << std::endl;
}

void captureImage()
{
    pointGeneration();
    imageProcessing();
    // delete[] rays;
}
