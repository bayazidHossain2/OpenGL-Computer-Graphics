#include<windows.h>
#include<GL/glut.h>
#include<cmath>
#include<iostream>
using namespace std;


void init(void ){
    glClearColor(1.0, 1.0, 1.0, 1.0);
    //glColor3f(1, 1, 0);
    glPointSize(5.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 100, 0, 100);
}

void CircleDraw(int radius,int f=0, int g=0, float red=1, float green=1, float blue=0){
    glColor3f(red, green, blue);
    int pk=1-radius;
    int x=0,y=radius;
    glBegin(GL_POINTS);
    while(x<=y){
        printf("%d \t-> %d, %d \n", pk, x, y);
        glVertex2i(x+f, y+g);
        glVertex2i(y+f, x+g); /// first
        glVertex2i(-1*x+f, y+g);
        glVertex2i(-1*y+f, x+g); /// second
        glVertex2i(-1*y+f, -1*x+g);
        glVertex2i(-1*x+f, -1*y+g); /// third
        glVertex2i(x+f, -1*y+g);
        glVertex2i(y+f, -1*x+g); /// fourth
        x++;
        y = (pk<0)? y : y-1;
        pk = (pk<0)? pk+2*x+1 : pk+2*x-2*y+1; // for Pnext
    }
    glEnd();
}

int rad = 30;
int g=50, f=50;

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    CircleDraw(rad, g, f);
    glFlush();
}


int main(int argc, char* argv[]){
    /*cout<<"Enter the Circle Radius: ";
    cin>>rad;
    cout<<"Enter the center coordinate of Radius: ";
    cin>>g>>f;*/

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
