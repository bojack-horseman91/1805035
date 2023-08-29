#include <GL/glut.h>

void drawFloor(){
    //draw checkered infinte floor
    int i,j;
    int tileNum = 20;
    double tileWidth = 10.0;
    double tileHeight = 10.0;
    double x,y,z;
    for(i=0;i<tileNum;i++){
        for(j=0;j<tileNum;j++){
            x = i*tileWidth;
            y = j*tileHeight;
            z = 0;
            if((i+j)%2==0){
                glColor3f(0,0,0);
            }
            else{
                glColor3f(1,1,1);
            }
            glBegin(GL_QUADS);
            {
                glVertex3f(x,y,z);
                glVertex3f(x+tileWidth,y,z);
                glVertex3f(x+tileWidth,y+tileHeight,z);
                glVertex3f(x,y+tileHeight,z);
            }
            glEnd();
        }
    }

}