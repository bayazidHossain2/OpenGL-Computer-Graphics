#include <GL/glut.h>
#include <iostream>
using namespace std;

void init(void ){
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glLineWidth(5.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 100, 0, 100);
}

const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000
float x_min = 20, y_min = 20, x_max = 80, y_max = 80;
int computeCode(float x, float y) {
    int code = 0;
    if (x < x_min)
        code |= LEFT;
    else if (x > x_max)
        code |= RIGHT;
    if (y < y_min)
        code |= BOTTOM;
    else if (y > y_max)
        code |= TOP;
    return code;
}
void cohenSutherlandClip(float x0, float y0, float x1, float y1) {
    int code0 = computeCode(x0, y0);
    int code1 = computeCode(x1, y1);
    bool accept = false;

    while (true) {
        if ((code0 == 0) && (code1 == 0)) {
            accept = true;
            break;
        } else if (code0 & code1) {
            break;
        } else {
            int code_out;
            float x, y;
            code_out = (code0 != 0) ? code0 : code1;
            if (code_out & TOP) {
//                x = x0 + (x1 - x0) * (y_max - y0) / (y1 - y0);
                x = x0 + (x0 - x1) * (y_max - y0) / (y0 - y1);
                y = y_max;
            } else if (code_out & BOTTOM) {
                x = x0 + (x0 - x1) * (y_min - y0) / (y0 - y1);
                y = y_min;
            } else if (code_out & RIGHT) {
                y = y0 + (y0 - y1) * (x_max - x0) / (x0 - x1);
                x = x_max;
            } else if (code_out & LEFT) {
                y = y0 + (y0 - y1) * (x_min - x0) / (x0 - x1);
                x = x_min;
            }
            if (code_out == code0) {
                x0 = x;
                y0 = y;
                code0 = computeCode(x0, y0);
            } else {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1);
            }
        }
    }
    if (accept) {
        glColor3f(0.0, 1.0, 0.0);
        glBegin(GL_LINES);
        glVertex2f(x0, y0);
        glVertex2f(x1, y1);
        glEnd();
        glFlush();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);


    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x_min, y_min);
    glVertex2f(x_max, y_min);
    glVertex2f(x_max, y_max);
    glVertex2f(x_min, y_max);
    glEnd();
    glFlush();

    cout<<"Enter number of line : ";
    int lines =0;
    cin>>lines;
    while(lines--){
        cout<<"Enter first coordinate of line (x0, y0) : ";
        int x0, y0;
        cin>>x0>>y0;
        cout<<"Enter send coordinate of line (x1, y1) : ";
        int x1, y1;
        cin>>x1>>y1;
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x0, y0);
        glEnd();
        cohenSutherlandClip(x0,y0, x1,y1);
    }

}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Cohen-Sutherland Line Clipping");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

/*
4
2 2
40 40
40 20
20 52
40 70
95 66
25 5
55 50

*/
