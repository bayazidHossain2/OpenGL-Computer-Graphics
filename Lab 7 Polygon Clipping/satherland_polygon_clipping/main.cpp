#include <GL/glut.h>
#include <iostream>
#include <vector>

using namespace std;

struct Point {
    float x, y;
};

void init(void ){
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glLineWidth(5.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 100, 0, 100);
}

// Clipping window coordinates
float x_min = 20, y_min = 20, x_max = 80, y_max = 80;

// Function to check if a point is inside the clip boundary
bool inside(Point p, int edge) {
    switch (edge) {
        case 0: return p.x >= x_min; // Left
        case 1: return p.x <= x_max; // Right
        case 2: return p.y >= y_min; // Bottom
        case 3: return p.y <= y_max; // Top
    }
    return true;
}

// Calculate the intersection of a line with a clipping boundary
Point intersect(Point s, Point p, int edge) {
    Point i;
    float slope;

    switch (edge) {
        case 0: // Left
            slope = (p.y - s.y) / (p.x - s.x);
            i.x = x_min;
            i.y = s.y + slope * (x_min - s.x);
            break;
        case 1: // Right
            slope = (p.y - s.y) / (p.x - s.x);
            i.x = x_max;
            i.y = s.y + slope * (x_max - s.x);
            break;
        case 2: // Bottom
            slope = (p.x - s.x) / (p.y - s.y);
            i.y = y_min;
            i.x = s.x + slope * (y_min - s.y);
            break;
        case 3: // Top
            slope = (p.x - s.x) / (p.y - s.y);
            i.y = y_max;
            i.x = s.x + slope * (y_max - s.y);
            break;
    }
    return i;
}

// Sutherland-Hodgman clipping algorithm
vector<Point> clipPolygon(vector<Point> polygon, int edge) {
    vector<Point> newPolygon;
    Point s = polygon.back(); // Start with the last point

    for (Point p : polygon) {
        if (inside(p, edge)) {
            if (inside(s, edge)) {  // in -> in
                newPolygon.push_back(p); // Both inside
            } else {
                newPolygon.push_back(intersect(s, p, edge)); // S out -> P in
                newPolygon.push_back(p);
            }
        } else if (inside(s, edge)) {
            newPolygon.push_back(intersect(s, p, edge)); // S in -> P out
        }
        s = p; // Update previous point
    }

    return newPolygon;
}

// Function to perform the complete polygon clipping
vector<Point> sutherlandHodgman(vector<Point> polygon) {
    for (int edge = 0; edge < 4; ++edge) {
        polygon = clipPolygon(polygon, edge);
    }
    return polygon;
}

// OpenGL rendering function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Original polygon vertices
//    vector<Point> polygon = { { 10, 7 }, { 30, 70 }, { 70, 2 }, { 35, 35 } };
    vector<Point> polygon = { { 15, 50}, { 50, 15}, { 70, 40 }, { 75, 10 }, {40, 5} };

    // Perform Sutherland-Hodgman clipping
    vector<Point> clippedPolygon = sutherlandHodgman(polygon);

    // Draw the clipping window
    glColor3f(1.0, 1.0, 0.0); // Yellow color for the clipping window
    glBegin(GL_LINE_LOOP);
    glVertex2f(x_min, y_min);
    glVertex2f(x_max, y_min);
    glVertex2f(x_max, y_max);
    glVertex2f(x_min, y_max);
    glEnd();

    // Draw the original polygon
    glColor3f(1.0, 0.0, 0.0); // red color for the original polygon
    glBegin(GL_LINE_LOOP);
    for (Point p : polygon) {
        glVertex2f(p.x, p.y);
    }
    glEnd();

    // Draw the clipped polygon
    glColor3f(0.0, 1.0, 0.0); // green color for the clipped polygon
    glBegin(GL_LINE_LOOP);
//    glBegin(GL_POLYGON);
    for (Point p : clippedPolygon) {
        glVertex2f(p.x, p.y);
    }
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Sutherland-Hodgman Polygon Clipping");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
