#include <math.h>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <stdio.h>

GLfloat red[] = { 0.8, 0.2, 0.2, 1.0 };
GLfloat pos[] = { 3.0, 4.0, 5.0, 1.0 };
GLdouble eyex = 10.0, eyey = 0.0, eyez = 0.0;
GLdouble povx = 0.0, povy = 0.0, povz = 0.0;
GLdouble up = 1.0;
GLdouble ax = 0.0, ay = 1.0;
GLdouble angle = 0.0;
GLuint cube;
double sx, sy;
#define SCALE 2.0 * 3.14159265358979323846
int cx, cy;
int zx, zy;
double dir = 0.0;
double ca;
static double cq[4] = {1.0,0.0,0.0,0.0};
static double tq[4];
static double rt[16];
GLdouble wheel_ratio = 0.0;
GLdouble middle = 0,left = 0,right = 0;
void qmul(double r[], const double p[], const double q[])
{
  r[0] = p[0] * q[0] - p[1] * q[1] - p[2] * q[2] - p[3] * q[3];
  r[1] = p[0] * q[1] + p[1] * q[0] + p[2] * q[3] - p[3] * q[2];
  r[2] = p[0] * q[2] - p[1] * q[3] + p[2] * q[0] + p[3] * q[1];
  r[3] = p[0] * q[3] + p[1] * q[2] - p[2] * q[1] + p[3] * q[0];
}
void qrot(double r[], double q[])
{
  double x2 = q[1] * q[1] * 2.0;
  double y2 = q[2] * q[2] * 2.0;
  double z2 = q[3] * q[3] * 2.0;
  double xy = q[1] * q[2] * 2.0;
  double yz = q[2] * q[3] * 2.0;
  double zx = q[3] * q[1] * 2.0;
  double xw = q[1] * q[0] * 2.0;
  double yw = q[2] * q[0] * 2.0;
  double zw = q[3] * q[0] * 2.0;
  
  r[ 0] = 1.0 - y2 - z2;
  r[ 1] = xy + zw;
  r[ 2] = zx - yw;
  r[ 4] = xy - zw;
  r[ 5] = 1.0 - z2 - x2;
  r[ 6] = yz + xw;
  r[ 8] = zx + yw;
  r[ 9] = yz - xw;
  r[10] = 1.0 - x2 - y2;
  r[ 3] = r[ 7] = r[11] = r[12] = r[13] = r[14] = 0.0;
  r[15] = 1.0;
}
void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  gluLookAt(eyex, eyey, eyez, povx, povy, povz, 0.0, up, 0.0);
  glLightfv(GL_LIGHT0, GL_POSITION, pos);
  glMultMatrixd(rt);
  glCallList(cube);
  glutSwapBuffers();
}
void resize(int fovh, int fovv)
{
  sx = 1.0 / (double)fovh;
  sy = 1.0 / (double)fovv;

  glViewport(0, 0, fovh, fovv);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(30.0, (double)fovh / (double)fovv, 1.0, 1000.0);
  glMatrixMode(GL_MODELVIEW);
}
void idle(void)
{
  glutPostRedisplay();
}
void mouse(int button, int state, int x, int y)
{
  cx = x;
  cy = y;
  if(button == GLUT_LEFT_BUTTON)
    {
      if(state == GLUT_DOWN)
	{
	  glutIdleFunc(idle);
	  left = 1;
	  cx = x;
	  cy = y;
	  ca = angle;
	}
      if(state ==  GLUT_UP)
	{
	  left = 0;
	  glutIdleFunc(0);
	  cq[0] = tq[0];
	  cq[1] = tq[1];
	  cq[2] = tq[2];
	  cq[3] = tq[3];
	}
    }
  if(button == GLUT_MIDDLE_BUTTON)
    {
      if(state ==  GLUT_DOWN)
	{
	  glutIdleFunc(idle);
	  middle = 1;
	}
      if(state ==  GLUT_UP)
	{
	  middle = 0;
	  glutIdleFunc(0);
	}
    }
  if(button == GLUT_RIGHT_BUTTON)
    {
      if(state == GLUT_DOWN)
	{
	  glutIdleFunc(idle);
	  right = 1;
	}
      if(state == GLUT_UP)
	{
	  glutIdleFunc(idle);
	  right = 0;
	}
    }
}
void motion(int x, int y)
{
  if(left == 1)
    {
      double drx, dry, a;
      drx = (x - cx) * sx;
      dry = (y - cy) * sy;
      a = sqrt(drx * drx + dry * dry);
      if (a != 0.0)
	{
	  double ar = a * SCALE *0.5;
	  double as = sin(ar) / a;
	  double dq[4] = { cos(ar),dry * as,drx * as,0.0};
	  qmul(tq,dq,cq);
	  qrot(rt,tq);
	}
    }
  if(right == 1)
    {
      double dhx, dhy;
      dhx = (x - cx)* sx;
      dhy = (y - cy)* sx;
      povz = povz + dhx*0.1;
      povy = povy + dhy*0.1;
    }
  if(middle == 1)
    {
      double dmy;
      dmy = (y - cy)*sy;
      wheel_ratio = wheel_ratio + dmy;
      double init_x = povx - eyex;
      double init_y = povy - eyey;
      double init_z = povz - eyez;
      eyex = eyex + init_x * wheel_ratio;
      eyey = eyey + init_y * wheel_ratio;
      eyez = eyez + init_z * wheel_ratio;
      wheel_ratio = 0;
      cy = y;
    }
}
void keyboard(unsigned char key, int x, int y)
{
  if (key == '\033') {
    exit(0);
  }
}
void init(void)
{
  glClearColor(0.2, 0.2, 0.2, 0.0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  qrot(rt,cq);
}
void scene(void)
{
  cube = glGenLists(1);
  glNewList(cube, GL_COMPILE);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
  glutSolidCube(2.0);
  glEndList();
}
int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);
  glutKeyboardFunc(keyboard);
  init();
  scene();
  glutMainLoop();
  return 0;
}
