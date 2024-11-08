#include<windows.h>
#include<GL/glut.h>
#include<cmath>
#include<iostream>
using namespace std;


void init(void ){
    glClearColor(0.0, 0.0, 0.0, 1.0);
    //glColor3f(1, 1, 0);
    glPointSize(5.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-50, 50, -50, 50);
}

void CircleDraw(int radius, float r=1, float g=1, float b=1){
    glColor3f(r, g, b);
    int pk=1-radius;
    int x=0,y=radius;
    glBegin(GL_POINTS);
    while(x<=y){
        printf("%d \t-> %d, %d \n", pk, x, y);
        glVertex2i(x, y);
        glVertex2i(y, x); /// first
        glVertex2i(-1*x, y);
        glVertex2i(-1*y, x); /// second
        glVertex2i(-1*y, -1*x);
        glVertex2i(-1*x, -1*y); /// third
        glVertex2i(x, -1*y);
        glVertex2i(y, -1*x); /// fourth
        x++;
        y = (pk<0)? y : y-1;
        pk = (pk<0)? pk+2*x+1 : pk+2*x-2*y+1; // for Pnext
    }
    glEnd();
}

int rad = 10;
// Timer callback function
void clearScreenAfterTimeout(int value) {
    // Call for redisplay to clear the screen
    glutPostRedisplay();
    rad++;
    if(rad>40){
        rad=10;
    }
    // Set another timer to repeat if needed (comment out if you want it to run only once)
    glutTimerFunc(100, clearScreenAfterTimeout, 0);  // Uncomment if you want to clear every 3 seconds
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    CircleDraw(rad);

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

    // Set up the timer function to clear the screen after 3 seconds
    glutTimerFunc(3000, clearScreenAfterTimeout, 0);

    glutMainLoop();

    return 0;
}
