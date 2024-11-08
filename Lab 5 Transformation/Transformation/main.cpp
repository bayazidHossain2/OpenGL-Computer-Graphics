#include<iostream>
#include<windows.h>
#include<GL/glut.h>
#include<vector>
#include<math.h>
using namespace std;
vector<pair<int,int>> points;
void init(void){
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glPointSize(5.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100, 100, -100, 100);
}
void draw_poligon(float red = 1, float green=0, float blue=0){
    // Polygon Shape Drawing
    glBegin(GL_POLYGON);
    glColor3f(red, green, blue);

    for(pair<int,int> point : points){
        cout<<point.first<<' '<<point.second<<endl;
        glVertex2i(point.first, point.second);
    }
    glEnd();
    glFlush();
}
void translate(int tx, int ty){
    for(int i=0;i<points.size();i++){
        points[i].first += tx;
        points[i].second += ty;
    }
}
void scaling(float sx, float sy, int xc, int yc){
    for(int i=0;i<points.size();i++){
        points[i].first = points[i].first * sx + xc*(1-sx);
        points[i].second = points[i].second * sy + yc*(1-sy);
    }
}
void fixedpoint_rotation(double thita, int xc = 9999999, int yc = 0){
    thita = thita*3.14159/180;
    /// for center of mass
    if(xc == 9999999){
        xc = 0;
        for(pair<int,int> point : points){
            xc += point.first;
            yc += point.second;
        }
        xc /= points.size();
        yc /= points.size();
    }
    for(int i=0;i<points.size();i++){
        int x = points[i].first, y=points[i].second;
        points[i].first = xc + (x - xc) * cos(thita) - (y - yc) * sin(thita);
        points[i].second = yc + (x - xc) * sin(thita) + (y - yc) * cos(thita);
    }
}
void reflection(){
    cout<<"Enter reflection axis:\na For x axis\nb For y axis\nc For xy perpendicular axis\nd For x=y axis\n";
    char ch;
    cin>>ch;
    int xc=1,yc=1;
    switch(ch){
    case 'a':
        yc=-1;
        break;
    case 'b':
        xc=-1;
        break;
    case 'c':
        xc=-1;
        yc=-1;
        break;
    case 'd':
        for(int i=0;i<points.size();i++){
            int x = points[i].first, y=points[i].second;
            points[i].first = 1*y;
            points[i].second = 1*x;
        }
        return;
    default:
        cout<<"Invalid choice"<<endl;
    }
    for(int i=0;i<points.size();i++){
        int x = points[i].first, y=points[i].second;
        points[i].first = x*xc;
        points[i].second = y*yc;
    }
}
void shear(){
    cout<<"Enter share axis:\nX For x axis\nY For y axis\n";
    char ch;
    cin>>ch;
    cout<<"Share angle sh ";
    float sh;
    cin>>sh;
    sh = tan(sh*3.1416/180);
    for(int i=0;i<points.size();i++){
        int x = points[i].first, y=points[i].second;
        if(ch == 'X'){
            points[i].first = (x+sh*y);
        }else if(ch == 'Y'){
            points[i].second = (x*sh+y);
        }else{
            cout<<"Invalid choice"<<endl;
            break;
        }
    }
}
void display(void){
    int operation_choice;
    glClear(GL_COLOR_BUFFER_BIT);        // Clear Background Display Window
    cout<<"Enter your choice: \n 1 For Translation\n 2 For Scaling\n 3 For Rotation\n 4 For Reflection\n 5 For Sharing\n";
    cin>>operation_choice;
    int number_of_points;
    cout<<"Enter number of points : ";
    cin>>number_of_points;
    int x,y;
    for(int i=0;i<number_of_points;i++){
        cout<<"Enter the "<<i+1<<" coordinate(x,y) : ";
        cin>>x>>y;
        points.push_back({x,y});
    }
    draw_poligon();
    int xc,yc;
    switch(operation_choice){
    case 1:  /// for translation
        cout<<"Enter translation factor (tx, ty) : ";
        int tx,ty;
        cin>>tx>>ty;
        translate(tx,ty);
        break;
    case 2:
        cout<<"Enter Scaling factor (sx, sy) : ";
        float sx,sy;
        cin>>sx>>sy;
        cout<<"Enter pivot point (xc, yc) : ";
        cin>>xc>>yc;
        scaling(sx, sy,xc,yc);
        break;
    case 3:
        cout<<"Enter rotation parameter (thita in digree) : ";
        int thita;
        cin>>thita;
        cout<<"Enter pivot point (xc, yc) : ";
        cin>>xc>>yc;
        fixedpoint_rotation(thita, xc, yc);
        break;
    case 4:
        reflection();
        break;
    case 5:
        shear();
        break;
    default:
        cout<<"Invalid choice"<<endl;
    }
    draw_poligon(0,1,0);
}
int main(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Basic OpenGL Lines & Shapes");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
}
