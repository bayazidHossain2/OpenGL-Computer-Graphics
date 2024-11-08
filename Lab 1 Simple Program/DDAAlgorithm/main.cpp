#include<GL/glut.h>
#include<cmath>
#include<iostream>
using namespace std;

void init( ){
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glPointSize(5.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 40, 0, 40);
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
    for (int i = 0; i < steps; i++) {
        glVertex2i(floor(x), floor(y)); // Draw the current point
        printf("(%.2f, %.2f) -> (%.0f, %.0f) \n", x,y, floor(x), floor(y));
        x += xIncrement; // Increment x
        y += yIncrement; // Increment y
    }
    glEnd(); // End drawing points
}

// DDA Line Drawing Algorithm
void drawLineDDAWithM(int x1, int y1, int x2, int y2) {
    glColor3f(1, 1, 0);
    int dx = x2 - x1;
    int dy = y2 - y1;
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
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    int x1=2,y1=2,x2=15,y2=8;
    int dist = 8;
    drawLineDDAWithoutM(x1, y1, x2, y2);
    drawLineDDAWithM(x1+dist, y1, x2+dist, y2);
    glFlush();
}

int main(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("DDA Algorithm Without M(Green) & with M(Yello)");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
