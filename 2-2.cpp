#include <GL/glut.h>

void init() {
    glEnable(GL_LIGHTING); 
    glEnable(GL_LIGHT0);   

    GLfloat light_ambient[] = {0.2, 0.2, 0.2, 1.0}; 
    GLfloat light_diffuse[] = {0.8, 0.8, 0.8, 1.0}; 
    GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0}; 
    GLfloat light_position[] = {0.0, 1.0, 1.0, 0.0}; 

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_COLOR_MATERIAL); //color

    glEnable(GL_DEPTH_TEST); 
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(0.0, 0.0, 5.0, // camera
              0.0, 0.0, 0.0, // lookat
              0.0, 1.0, 0.0); // up

    glColor3f(1.0, 0.6, 0.2); // teapotcolor
    glutSolidTeapot(1.0); // size of teapot

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("teapot 2-2");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;
}
