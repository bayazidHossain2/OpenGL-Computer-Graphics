// Lab-01, Date:15/05/2024, Topic: Lines & Basic Shapes Drawing Using OpenGL
#include<windows.h>
#include<GL/glut.h>
#include<cmath>
#include<iostream>

// Function to initialize the OpenGL environment
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set background color to black
    glColor3f(1.0, 1.0, 1.0);         // Set the drawing color to white
    glPointSize(8.0);                 // Set the point size
    glMatrixMode(GL_PROJECTION);      // Set the projection mode
    glLoadIdentity();                 // Load the identity matrix
    gluOrtho2D(0, 40, 0, 40);       // Set the coordinate system
}

// DDA Line Drawing Algorithm
void drawLineDDA(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = std::max(abs(dx), abs(dy)); // Calculate the number of steps

    float xIncrement = dx / (float) steps; // Calculate the x increment
    float yIncrement = dy / (float) steps; // Calculate the y increment

    float x = x1;
    float y = y1;

    glBegin(GL_POINTS); // Begin drawing points
    for (int i = 0; i <= steps; i++) {
        glVertex2i(round(x), round(y)); // Draw the current point
        x += xIncrement; // Increment x
        y += yIncrement; // Increment y
    }
    glEnd(); // End drawing points
    glFlush(); // Flush the OpenGL commands
}

void drawline(int x0, int y0, int x1, int y1)
{
    int dx, dy, p, x, y;
    dx=x1-x0;
    dy=y1-y0;
    x=x0;
    y=y0;
    p=2*dy-dx;
    while(x<x1)
    {
        if(p>=0)
        {
            glBegin(GL_POINTS);
            glVertex2i(x, y);
            glEnd();
           // putpixel(x,y,7);
            y=y+1;
            p=p+2*dy-2*dx;
        }
        else
        {
            glBegin(GL_POINTS);
            glVertex2i(x, y);
            glEnd();
          //  putpixel(x,y,7);
            p=p+2*dy;
            x=x+1;
        }
    }
    glFlush(); // Flush the OpenGL commands
}
/*
        glBegin(GL_POINTS);
        glVertex2i(x1, y1);
        glEnd();
*/

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Clear the screen

    // Draw a line using the DDA algorithm
   // drawLineDDA(10, 10, 30, 25);
    drawline(10, 12, 20, 27);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Set display mode
    glutInitWindowSize(500, 500); // Set window size
    glutInitWindowPosition(100, 100); // Set window position
    glutCreateWindow("DDA Line Drawing Algorithm"); // Create window with title

    init(); // Initialize the OpenGL environment
    glutDisplayFunc(display); // Set the display callback function
    glutMainLoop(); // Enter the GLUT event processing loop

    return 0;
}
