#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Model {
  vector<GLfloat> vertices;  
  vector<GLfloat> normals;   
  vector<GLuint> indices;    
};


Model loadObj(const char* filename) {
  Model model;

  ifstream ifs(filename);
  if (!ifs) {
    cerr << "Error: Cannot open file " << filename << endl;
    exit(1);
  }

  vector<GLfloat> vertices;
  vector<GLfloat> normals;
  vector<GLuint> indices;

  string line;
  while (getline(ifs, line)) {
    if (line[0] == 'v' && line[1] == ' ') {
      GLfloat x, y, z;
      sscanf(line.c_str(), "v %f %f %f", &x, &y, &z);
      vertices.push_back(x);
      vertices.push_back(y);
      vertices.push_back(z);
    } else if (line[0] == 'v' && line[1] == 'n') {
      GLfloat nx, ny, nz;
      sscanf(line.c_str(), "vn %f %f %f", &nx, &ny, &nz);
      normals.push_back(nx);
      normals.push_back(ny);
      normals.push_back(nz);
    } else if (line[0] == 'f' && line[1] == ' ') {
      GLuint v1, v2, v3, n1, n2, n3;
      sscanf(line.c_str(), "f %u//%u %u//%u %u//%u", &v1, &n1, &v2, &n2, &v3, &n3);
      indices.push_back(v1 - 1);
      indices.push_back(v2 - 1);
      indices.push_back(v3 - 1);
    }
  }

  model.vertices = vertices;
  model.normals = normals;
  model.indices = indices;

  return model;
}


void drawModel(const Model& model) {
  glBegin(GL_TRIANGLES);

  for (int i = 0; i < model.indices.size(); i++) {
    GLuint index = model.indices[i];
    GLuint normalIndex = 3 * index;


    glNormal3f(model.normals[normalIndex], model.normals[normalIndex + 1], model.normals[normalIndex + 2]);


    GLuint vertexIndex = 3 * index;
    glVertex3f(model.vertices[vertexIndex], model.vertices[vertexIndex + 1], model.vertices[vertexIndex + 2]);
  }

  glEnd();
}

void setupLighting() {
  GLfloat ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat position[] = { 0.0f, 0.0f, 1.0f, 0.0f };

glShadeModel(GL_SMOOTH);
glEnable(GL_LIGHTING);
glEnable(GL_LIGHT0);
glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
glLightfv(GL_LIGHT0, GL_POSITION, position);
}


void display() {
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);


Model model = loadObj("model.obj");
drawModel(model);

glutSwapBuffers();
}


void init() {
glClearColor(0.0, 0.0, 0.0, 0.0);
glEnable(GL_DEPTH_TEST);
setupLighting();
}


void reshape(int w, int h) {
glViewport(0, 0, w, h);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(45.0, (double)w / h, 0.1, 100.0);
glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
glutInitWindowSize(640, 480);
glutCreateWindow("bunny 5-2");
glutDisplayFunc(display);
glutReshapeFunc(reshape);
init();
glutMainLoop();
return 0;
}
