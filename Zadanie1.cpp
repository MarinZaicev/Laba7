#include <GL/glut.h>  
#include <cmath>       


const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int RECURSION_DEPTH = 4;


void drawKochCurve(float x1, float y1, float x2, float y2, int depth) {
    if (depth == 0) {
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        return;
    }


    float dx = x2 - x1;
    float dy = y2 - y1;


    float xA = x1 + dx / 3;
    float yA = y1 + dy / 3;
    float xB = x1 + 2 * dx / 3;
    float yB = y1 + 2 * dy / 3;

    float xC = (x1 + x2) / 2 - dy * sqrt(3) / 6;
    float yC = (y1 + y2) / 2 + dx * sqrt(3) / 6;


    drawKochCurve(x1, y1, xA, yA, depth - 1);
    drawKochCurve(xA, yA, xC, yC, depth - 1);
    drawKochCurve(xC, yC, xB, yB, depth - 1);
    drawKochCurve(xB, yB, x2, y2, depth - 1);
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_LINES);

    drawKochCurve(-0.8f, -0.2f, 0.8f, -0.2f, RECURSION_DEPTH);
    glEnd();

    glutSwapBuffers();
}


void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Koch Curve");


    init();
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
