#include <GL/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 0.0); // 赤色を選択

    // 三角形を描画
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.2, -0.2);
    glVertex2f(0.0, 0.2);
    glVertex2f(0.2, -0.2);
    glEnd();

    glColor3f(0.75, 0.51, 0.45);
    // 四角形を描画
    glBegin(GL_QUADS);
    glVertex2f(-0.6, 0.2);
    glVertex2f(-0.6, -0.2);
    glVertex2f(-0.4, -0.2);
    glVertex2f(-0.4, 0.2);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("赤い三角形と四角形");

    glClearColor(0.0, 0.0, 0.0, 1.0);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
