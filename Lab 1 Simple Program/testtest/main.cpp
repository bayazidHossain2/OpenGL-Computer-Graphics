#include <GL/glut.h>
#include <windows.h>
#include <stdio.h>
#include<iostream>

using namespace std;
float x1, x2, y1, y2;
void init(void) {

    glClearColor(1.0, 1.0, 0, 0.0);
    gluOrtho2D(-100, 100, -100, 100);

}
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(2.0);

    glBegin(GL_POINTS);
        glColor3f(1.0, 0.0, 0.0);
        float dx = (x2 - x1);
        float dy = (y2 - y1);
        float m = (float)dy / dx;
        m = abs(m);
        int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
        if (m <= 1) {
            if (dx > 0 && dy > 0) {
                float x = x1, y = y1;
                for (int i = 0; i <= steps; i++) {

                    glVertex2i(x, y);
                    x += 1;
                    y += m;
                }
            } else if (dx < 0 && dy < 0) {
                float x = x2, y = y2;
                for (int i = 0; i <= steps; i++) {

                    glVertex2i(x, y);
                    x -= 1;
                    y -= m;
                }
            } else if (dx > 0 && dy < 0) {
                float x = x1, y = y2;
                for (int i = 0; i <= steps; i++) {

                    glVertex2i(x, y);
                    x += 1;
                    y -= m;
                }
            } else if (dx < 0 && dy > 0) {
                float x = x2, y = y1;
                for (int i = 0; i <= steps; i++) {

                    glVertex2i(x, y);
                    x -= 1;
                    y += m;
                }
            }

        } else {
            if (dx > 0 && dy > 0) {
                float x = x1, y = y1;
                for (int i = 0; i <= steps; i++) {

                    glVertex2i(x, y);
                    x += 1 / m;
                    y += 1;
                }
            } else if (dx < 0 && dy < 0) {
                float x = x1, y = y1;
                for (int i = 0; i <= steps; i++) {

                    glVertex2i(x, y);
                    x -= 1 / m;
                    y -= 1;
                }
            } else if (dx > 0 && dy < 0) {
                float x = x1, y = y1;
                for (int i = 0; i <= steps; i++) {

                    glVertex2i(x, y);
                    x += 1 / m;
                    y -= 1;
                }
            } else if (dx < 0 && dy > 0) {
                float x = x1, y = y1;
                for (int i = 0; i <= steps; i++) {

                    glVertex2i(x, y);
                    x -= 1 / m;
                    y += 1;
                }
            }
        }
    glEnd();

    glFlush();
}

int main(int argc, char* argv[]) {


    cout << "Enter x1 = ";
    cin >> x1;
    cout << "Enter y1 = ";
    cin >> y1;
    cout << "Enter x2 = ";
    cin >> x2;
    cout << "Enter y2 = ";
    cin >> y2;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);

    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("DDA Line Drawing Algorithm with M");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
}
