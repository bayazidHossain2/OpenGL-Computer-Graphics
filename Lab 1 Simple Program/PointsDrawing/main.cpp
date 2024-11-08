// Lab-01, Date:15/05/2024, Topic: Lines & Basic Shapes Drawing Using OpenGL
#include<windows.h>
#include<GL/glut.h>

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);    // Set Background Display Window Color
    glMatrixMode(GL_PROJECTION);         // Set Projection Parameters
    gluOrtho2D(0.0, 10.0, 0.0, 10.0);    // Set Orthogonal reference Frame's/ Graphs Limit (X axis & Y axis)
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);        // Clear Background Display Window

    glBegin(GL_POINT);
        glColor3f(1.0, 1.0, 0.0);

        glVertex2d(5, 5);
    glEnd();

    // Line Drawing
    glBegin(GL_LINES);

        glColor3f(1.0, 0.0, 0.0);        // Set Drawing Color (RGB)

        glVertex2i(2, 8);                // Vertex or Points Coordinates
        glVertex2i(3, 6);

        glVertex2i(2, 7);                // Vertex or Points Coordinates
        glVertex2i(4, 8);

        glVertex2i(4, 8);                // Vertex or Points Coordinates
        glVertex2i(3, 6);
/*
        glVertex2i(4, 5);                // Vertex or Points Coordinates
        glVertex2i(8, 9);  */

    glEnd();                             // Ending & Saving Coordinates in Refresh Buffer

    glFlush();                           // Process all OpenGL Functions and Force Execution to Display
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);                      // Initalise GLUT
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);  // Set Display Mode

    glutInitWindowPosition(100, 100);                // Set Window Showing Position
    glutInitWindowSize(500, 500);                    // Set Window Size
    glutCreateWindow("Basic OpenGL Lines & Shapes"); // Set the Name of the Display Window

    init();                   // Execute Initialization Procedure
    glutDisplayFunc(display); // Send Graphics to Display Window *
    glutMainLoop();           // Display Everything and Wait

}
