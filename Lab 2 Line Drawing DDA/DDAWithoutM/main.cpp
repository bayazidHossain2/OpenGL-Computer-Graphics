#include<windows.h>
#include<GL/glut.h>
#include<cmath>
#include<iostream>
using namespace std;

void init(void ){
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glPointSize(5.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 100, 0, 100);
}
// DDA Line Drawing Algorithm
void drawLineDDAWithoutM(int x1, int y1, int x2, int y2) {
    glColor3f(0, 1, 0);
    int dx = x2 - x1, dy = y2 - y1;
    int steps = std::max(abs(dx), abs(dy));
    printf("dx : %d \t dy : %d \t step : %d\n", dx, dy, steps);

    float xIncrement = dx / (float) steps; // Calculate the x increment
    float yIncrement = dy / (float) steps; // Calculate the y increment

    float x = x1, y = y1;

    glBegin(GL_POINTS); // Begin drawing points
    for (int i = 0; i <= steps; i++) {
        glVertex2i(floor(x), floor(y)); // Draw the current point
        printf("(%.2f, %.2f) -> (%.0f, %.0f) \n", x,y, floor(x), floor(y));
        x += xIncrement; // Increment x
        y += yIncrement; // Increment y
    }
    glEnd(); // End drawing points
    glFlush(); // Flush the OpenGL commands
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

   // int x1=1,y1=1,x2=7,y2=7;
   // int x1=7,y1=7,x2=1,y2=1;
   // int x1=1,y1=7,x2=7,y2=1;
   // int x1=7,y1=1,x2=1,y2=7;
    int x1=5,y1=90,x2=20,y2=20;
    drawLineDDAWithoutM(x1, y1, x2, y2);

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
    glutCreateWindow("DDA Algorithm Without M");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

// (90 5) (20 20)
