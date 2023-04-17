#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>

struct Vertex {
  float x, y, z;
};

struct Face {
  int v1, v2, v3;
};

std::vector<Vertex> vertices;
std::vector<Face> faces;

void load_obj(const char *filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cerr << "Error opening OBJ file: " << filename << std::endl;
    exit(1);
  }

  std::string line;
  while (std::getline(file, line)) {
    if (line.substr(0, 2) == "v ") {
      std::istringstream s(line.substr(2));
      Vertex v;
      s >> v.x; s >> v.y; s >> v.z;
      vertices.push_back(v);
    } else if (line.substr(0, 2) == "f ") {
      std::istringstream s(line.substr(2));
      Face f;
      s >> f.v1; s >> f.v2; s >> f.v3;
      faces.push_back(f);
    }
  }

  file.close();
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST); 
  glEnable(GL_LIGHTING);  
  glEnable(GL_LIGHT0);     
  glEnable(GL_NORMALIZE);
  glShadeModel(GL_SMOOTH); 

  glLoadIdentity();
  gluLookAt(0, 0, 0.5, 0, 0, 0, 0, 1, 0);

  glBegin(GL_TRIANGLES);
  for (const Face &face : faces) {
    const Vertex &v1 = vertices[face.v1 - 1];
    const Vertex &v2 = vertices[face.v2 - 1];
    const Vertex &v3 = vertices[face.v3 - 1];
    const float nx = (v2.y - v1.y) * (v3.z - v1.z) - (v2.z - v1.z) * (v3.y - v1.y);
    const float ny = (v2.z - v1.z) * (v3.x - v1.x) - (v2.x - v1.x) * (v3.z - v1.z);
    const float nz = (v2.x - v1.x) * (v3.y - v1.y) - (v2.y - v1.y) * (v3.x - v1.x);
    const float len = std::sqrt(nx * nx + ny * ny + nz * nz);
    const float nnx = nx / len;
    const float nny = ny / len;
    const float nnz = nz / len;

    
glNormal3f(nnx, nny, nnz);
glVertex3f(v1.x, v1.y, v1.z);
glVertex3f(v2.x, v2.y, v2.z);
glVertex3f(v3.x, v3.y, v3.z);
}
glEnd();

glutSwapBuffers();
}

void reshape(int w, int h) {
glViewport(0, 0, w, h);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(60, (float) w / (float) h, 0.1, 100.0); 
glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char *argv[]) {
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
glutInitWindowSize(800, 600);
glutInitWindowPosition(100, 100);
glutCreateWindow("Bunny OBJ Viewer");

glutDisplayFunc(display);
glutReshapeFunc(reshape);

load_obj("bunny.obj");

glEnable(GL_CULL_FACE);
glCullFace(GL_BACK);

glutMainLoop();

return 0;
}
                                                                                                                                                                                                                          // 背面カリングを有効にする                                                                                             glEnable(GL_CULL_FACE);                                                                                                 glCullFace(GL_BACK);                                                                                                                                                                                                                            glutMainLoop();                                                                                                                                                                                                                                 return 0;                                                                                                               }
