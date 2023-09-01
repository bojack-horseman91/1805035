#include <GL/glut.h>
#include "1805035_floor.h"
#include "bitmap_image.hpp"
#include "1805035_globals.h"
// #include <SOIL.h>

// GLuint loadTexture(const char *texturePath)
// {
//     GLuint textureID;
//     glGenTextures(1, &textureID);
//     glBindTexture(GL_TEXTURE_2D, textureID);

//     int width, height;
//     unsigned char *image = SOIL_load_image(texturePath, &width, &height, 0, SOIL_LOAD_RGB);

//     if (image)
//     {
//         glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
//         glGenerateMipmap(GL_TEXTURE_2D);

//         SOIL_free_image_data(image);
//     }
//     else
//     {
//         // Handle texture loading error
//         std::cerr << "Error loading texture: " << SOIL_last_result() << std::endl;
//     }

//     glBindTexture(GL_TEXTURE_2D, 0);
//     return textureID;
// }

// // Load your black and white textures
// GLuint textureBlack = loadTexture("black_texture.png");
// GLuint textureWhite = loadTexture("white_texture.png");
// glEnable(GL_TEXTURE_2D);

// // Set texture parameters (you may need to adjust these based on your image size)
// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// bitmap_image texture("texture_b.bmp");
// rgb blackTexture
bitmap_image blackTexture("texture_b.bmp");
bitmap_image whiteTexture("texture_w.bmp");
void Floor::draw()
{
    // std::cout<<"drawing floor"<<std::endl;
    int size = 1000;
    ;
    // draw checkered infinte floor
    int numSquaresX = static_cast<int>(size / checkerSize);
    int numSquaresY = static_cast<int>(size / checkerSize);

    for (int i = 0; i < numSquaresX; ++i)
    {
        for (int j = 0; j < numSquaresY; ++j)
        {
            double x = 0 - size / 2.0 + i * checkerSize;
            double y = 0 - size / 2.0 + j * checkerSize;

            if ((i + j) % 2 == 0)
            {
                glColor3f(0.0f, 0.0f, 0.0f); // Black
            }
            else if(!TEXTUREMODE)
            {
                glColor3f(1.0f, 1.0f, 1.0f); // White
            }
            else{
                //black
                glColor3d(0,0,0);
            }
            // if ((i + j) % 2 == 0)
            // {
            //     glBindTexture(GL_TEXTURE_2D, textureBlack);
            // }
            // else
            // {
            //     glBindTexture(GL_TEXTURE_2D, textureWhite);
            // }

            glBegin(GL_QUADS);
            glVertex3d(x, y, -6);
            glVertex3d(x + checkerSize, y, -6);
            glVertex3d(x + checkerSize, y + checkerSize, -6);
            glVertex3d(x, y + checkerSize, -6);
            glEnd();
            // glBegin(GL_QUADS);
            // {
            //     glTexCoord2d(0.0, 0.0);
            //     glVertex3d(x, y, -6);
            //     glTexCoord2d(1.0, 0.0);
            //     glVertex3d(x + checkerSize, y, -6);
            //     glTexCoord2d(1.0, 1.0);
            //     glVertex3d(x + checkerSize, y + checkerSize, -6);
            //     glTexCoord2d(0.0, 1.0);
            //     glVertex3d(x, y + checkerSize, -6);
            // }
            // glEnd();
            // Unbind the texture
            // glBindTexture(GL_TEXTURE_2D, 0);
        }
    }
}
bool Floor::getIntersectionPoints(Ray ray)
{
    points3D normal = points3D(0, 0, 1);
    // color=rgb(1,1,1);
    t_value = -(ray.origin.dot(normal) + 6) / ray.direction.dot(normal);
    if (t_value > 0)
    {
        intersectionPoint = ray.origin + ray.direction * t_value;
        // if(normal.dot(intersectionPoint)<0){
        //     normal = -normal;
        // }
        // color at that intersection point
        int size = 1000;
        int squareX = static_cast<int>((intersectionPoint.x - size / 2) / checkerSize);
        int squareY = static_cast<int>((intersectionPoint.y - size / 2) / checkerSize);
        // bitmap_image texture("black_texture.bmp");
        // convert this to 50*50 rgb
        // std::cout<<texture.width()<<" "<<texture.height()<<std::endl;
        // map checker texture height and width to 50*50
        // check if intersection point.x <-size/2 or >size/2 and same for y
        if (intersectionPoint.x < -size / 2 || intersectionPoint.x > size / 2 || intersectionPoint.y < -size / 2 || intersectionPoint.y > size / 2)
        {
            // error
            //  std::cout<<"error"<<intersectionPoint.x<<" "<<intersectionPoint.y<<std::endl;
            return false;
        }

        if(TEXTUREMODE)
        {

            bitmap_image texture;
            if ((squareX + squareY) % 2 == 0)
            {
                texture = blackTexture;
            }
            else
            {
                texture = whiteTexture;
            }
            int row = (int)(intersectionPoint.x + size / 2) / checkerSize;
            int col = (int)(intersectionPoint.y + size / 2) / checkerSize;

            double x = (intersectionPoint.x + size / 2) - checkerSize * row;
            double y = (intersectionPoint.y + size / 2) - checkerSize * col;
            double tile_width = checkerSize;
            if (x / tile_width > 1)
            {
                // error
                //  std::cout<<"error"<<x/tile_width<<std::endl;
                return false;
            }
            if (y / tile_width > 1)
            {
                // error
                //  std::cout<<"error"<<y/tile_width<<std::endl;
                return false;
            }

            int tex_x = (int)((texture.width() - 1) * x / tile_width);
            int tex_y = (int)((texture.height() - 1) * y / tile_width);

            if (tex_x > texture.width() - 1)
            {
                // error
                std::cout << "error" << tex_x << std::endl;
                return false;
            }
            if (tex_y > texture.height() - 1)
            {
                // error
                std::cout << "error" << tex_y << std::endl;
                return false;
            }
            unsigned char red, green, blue;
            texture.get_pixel(tex_x, tex_y, red, green, blue);

            color = rgb(red / 255.0, green / 255.0, blue / 255.0); // Normalize color values to [0, 1]
        }
        else{
              if ((squareX + squareY) % 2 == 0)
            {
                color=rgb(0,0,0);
            }
            else
            {
                // texture = whiteTexture;
                color=rgb(1,1,1);
            }
        }
        normalAtIntersectionPoint = normal;
        reflectedRay = ray.direction - normalAtIntersectionPoint * (ray.direction.dot(normalAtIntersectionPoint)) * 2;
        // texture.clear();
        return true;
    }
    return false;
}