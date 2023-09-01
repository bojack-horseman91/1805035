#include "1805035_imageCapture.h"
#include "GL/glut.h"


// Ray **rays;
// Rays std::vector<std::vector<Ray>> rays;

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
    // shift object point a little bit epsilon to avoid self intersection towards normal
    double epsilon = 0.0001;
    selectedobj->intersectionPoint = selectedobj->intersectionPoint + selectedobj->normalAtIntersectionPoint.normalize() * epsilon;

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

void pointGeneration()
{
    //     rays = new Ray *[resolution];
    //     for (int i = 0; i < resolution; ++i)
    //     {
    //         rays[i] = new Ray[resolution];
    //     }

    //sanity check size of rays array is correct
    // std::cout << "size of rays array is " << sizeof(rays)/sizeof(rays[0]) << std::endl;
    // std::cout << "size of rays array is " <<  << std::endl;
    std::cout<<resolution<<std::endl;
     bitmap_image image(resolution, resolution);

    std::cout << "point generation started" << std::endl;
    double fovX = fovY * aspectRatio;
    double planeHeight = 2 * nearZ * tan(fovY / 2 * DEG2RAD);
    double planeWidth = 2 * nearZ * tan(fovX / 2 * DEG2RAD);
    points3D middlePoint = eye + (center - eye).normalize() * nearZ;
    points3D rightVector = (center - eye).cross(up).normalize();
    points3D topLeft = middlePoint + up * (planeHeight / 2) - rightVector * (planeWidth / 2);
    // find top right point

    // generate all rays from  this
    double pixelWidth = planeWidth / resolution, pixelHeight = planeHeight / resolution;
    // points3D pointsBuffer[resolution * resolution];
    std::cout<<resolution<<std::endl;
    for (int row = 0; row < resolution; row++)
    {
        for (int col = 0; col < resolution; col++)
        {
            points3D rayDirection = topLeft + rightVector * (col * pixelWidth) - up * (row * pixelHeight);
            // Create a ray starting from the camera position and going in the calculated direction
            // rays[row][col].origin = eye;
            Ray ray = Ray(eye, (rayDirection - eye).normalize());

             rgb color = rayTracing(ray, 0);

            //  std::cout<<color.r*255<<" "<<color.g*255<<" "<<color.b*255<<std::endl;
            image.set_pixel(col, row, std::min(color.r * 255.0,255.0), std::min(color.g * 255,255.0), std::min(color.b * 255,255.0));
        }
        if (row % 100 == 0)
            std::cout << "rendering done: " << row << " " << (row / resolution) * 100.00 << "%" << std::endl;
    }
    std::cout << "almost done" << std::endl;
    image.save_image("test.bmp");
    std::cout << "done" << std::endl;
    std::cout << "point generation completed" << std::endl;
}

// void imageProcessing()
// {
   
//     std::cout << eye << " " << center << " " << rays[0][0].origin << " " << rays[0][0].direction << std::endl;
//     for (int row = 0; row < resolution; row++)
//     {
//         for (int col = 0; col < resolution; col++)
//         {

//             Ray ray = rays[row][col];
//             // double t_min_value = -1;
//             // rgb color = rgb();
//             // for (Object *obj : myObjects)
//             // {
//             //     if (obj->getIntersectionPoints(ray))
//             //     {
//             //         if (t_min_value == -1 || t_min_value < obj->t_value)
//             //         {
//             //             t_min_value = obj->t_value;
//             //             color = obj->calculated_light;
//             //         }
//             //         // std::cout<<row<<" "<<col<<std::endl;
//             //     }
//             // }
           
// }

void captureImage()
{
    // rays = new Ray *[resolution];
    // for (int i = 0; i < resolution; ++i)
    // {
    //     rays[i] = new Ray[resolution];
    // }
    pointGeneration();
    // imageProcessing();
    //delete rays
    // for (int i = 0; i < resolution; ++i)
    // {
    //     delete[] rays[i];
    // }

    // delete[] rays;
}
