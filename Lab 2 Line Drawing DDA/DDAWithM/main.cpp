#include<windows.h>
#include<GL/glut.h>
#include<cmath>
#include<iostream>
using namespace std;


void init(void ){
    glClearColor(0.0, 0.0, 0, 1.0);
    //glColor3f(1, 1, 0);
    glPointSize(5.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 100, 0, 100);
}
// DDA Line Drawing Algorithm
void drawLineDDAWithM(int x1, int y1, int x2, int y2, float r=1, float g=1, float b=1) {
    glColor3f(r, g, b);
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    float m = abs((dy+0.0)/dx);
    float x_inc = 0, y_inc = 0;
    float x = x1, y = y1;
    int step = max(dx, dy);
    printf("dx : %d \t dy : %d \nm : %.3f \t step : %d\n", dx, dy, m, step);
    if(m<=1){
        x_inc = (x1<x2)?1:-1;
        y_inc = (y1<y2)?m:-m;
    }else if(m>1){
        x_inc = (x1<x2)?(1/m):(-1/m);
        y_inc = (y1<y2)?1:-1;
    }else{
        cout<<"Invalid value of m : "<<m<<endl;
    }
    glBegin(GL_POINTS);
    while(step--){
        glVertex2i(floor(x), floor(y)); // Draw the current point
        printf("(%.2f, %.2f) -> (%.0f, %.0f) \n", x,y, floor(x), floor(y));
        x += x_inc;
        y += y_inc;
    }
    glEnd(); // End drawing points
    glFlush(); // Flush the OpenGL commands
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    int x1=1,y1=1,x2=70,y2=70;
    int x3=75,y3=70,x4=15,y4=10;
    int x5=1,y5=70,x6=70,y6=1;
    int x7=75,y7=10,x8=10,y8=75;
    int x9=5,y9=90,x10=20,y10=20;
    drawLineDDAWithM(x1, y1, x2, y2);
    drawLineDDAWithM(x3, y3, x4, y4, 1,0,0);
    drawLineDDAWithM(x5, y5, x6, y6, 0,1,0);
    drawLineDDAWithM(x7, y7, x8, y8, 0,0,1);
    drawLineDDAWithM(x9, y9, x10, y10, 0,1,1);

    /*glBegin(GL_POINTS); // Begin drawing points
    glVertex2i(40,40);
    glEnd();*/

    glFlush();
}


int main(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("BH LDA");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
