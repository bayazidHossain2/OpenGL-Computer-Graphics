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

void BHLDA(int x1, int y1, int x2, int y2, float r=1, float g=1, float b=1){
    glColor3f(r, g, b);
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int step = max(dx,dy);
    double m = abs(dy+0.0)/dx;
    int pp, pn, pk; // pp for p-positive and pn for p-negative

    cout<<"M : "<<m<<endl;
    int x=x1,y=y1;
    glBegin(GL_POINTS);
    if(m<1){
        pp = 2*(dy-dx);// when p value is positive
        pn = 2*dy; // when p value is negative
        pk = pp + dx; //
        while(step--){
            printf("%d \t-> %d, %d \n", pk, x, y);
            glVertex2i(x, y);
            x = (x1<=x2) ? x+1 : x-1;
            y = (pk>=0)? ((y1<=y2) ? (y+1) : (y-1)) : y;
            pk = (pk>=0)? (pk+pp) : (pk+pn); // for Pnext
        }
    }else{
        pp = 2*(dx-dy);
        pn = 2*dx;
        pk = pp + dy;
        while(step--){
            printf("%d \t-> %d, %d \n", pk, x, y);
            glVertex2i(x, y);
            y = (y1<=y2) ? y+1 : y-1;
            x = (pk>=0)? ((x1<=x2) ? (x+1) : (x-1)): x;
            pk = (pk>=0)? (pk+pp) : (pk+pn);
        }
    }
    glEnd();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);


    int x1=1,y1=1,x2=70,y2=70;
    int x3=75,y3=70,x4=15,y4=10;
    int x5=5,y5=70,x6=70,y6=5;
    int x7=75,y7=10,x8=10,y8=75;
    int x9=5,y9=90,x10=20,y10=20;
    int x11=20,y11=20,x12=5,y12=90;
    BHLDA(x1, y1, x2, y2);
    BHLDA(x3, y3, x4, y4, 1,0,0);
    BHLDA(x5, y5, x6, y6, 0,1,0);
    BHLDA(x7, y7, x8, y8, 0,0,1);
    BHLDA(x9, y9, x10, y10, 0,1,1);
    BHLDA(x11, y11, x12, y12, 1, 1, 0);
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
