#include <stdio.h>
#include <GL/glut.h>


#define ARRAY_MAX 10000000

float vertex[ARRAY_MAX];
int lines[ARRAY_MAX];
int vertexDataSize=0, lineDataSize=0;
GLfloat pos[] = { 150.0,150.0,150.0, 1.0 };
void display()
{
  glClearColor(0,0,0,1);
  glClear(GL_COLOR_BUFFER_BIT);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3,GL_FLOAT,0,vertex);
  glPointSize(3);
  glBegin(GL_POINTS);
  {
    for(int i=0;i<vertexDataSize;i++)
      glArrayElement(i);
  }
  glEnd();

  glColor3f(0.6,0.35,0);
  glBegin(GL_TRIANGLES);
  {
    for(int i=0;i<lineDataSize;i++){
      glArrayElement(lines[i*3]);
      glArrayElement(lines[i*3+1]);
      glArrayElement(lines[i*3+2]);
    }
  }
  glEnd();

  glColor3f(1.0,0.75,0);
  glBegin(GL_LINES);
  {
    for(int i=0;i<lineDataSize;i++){
      glArrayElement(lines[i*3]);
      glArrayElement(lines[i*3+1]);

      glArrayElement(lines[i*3+1]);      
      glArrayElement(lines[i*3+2]);

      glArrayElement(lines[i*3+2]);
      glArrayElement(lines[i*3]);
    }
  }
  glEnd();
  glFlush();
}


void InitialProc()
{
  FILE *fpVData, *fpFData, *fpVNData;
  fpVData = fopen("vData.txt","r");
  fpFData = fopen("fData.txt", "r");
  fpVNData = fopen("vnData.txt","r");
  if((fpVData==NULL)||(fpFData==NULL)||(fpVNData==NULL))
    {
    printf("file error!!\n");
    return;
    }

  while (fscanf(fpVData,"%f, %f, %f",&vertex[vertexDataSize*3],&vertex[vertexDataSize*3+1],&vertex[vertexDataSize*3+2])!=EOF)
    vertexDataSize+=1;

  while(fscanf(fpFData,"%d, %d, %d",&lines[lineDataSize*3],&lines[lineDataSize*3+1],&lines[lineDataSize*3+2])!=EOF)
    lineDataSize+=1;
  glLightfv(GL_LIGHT0, GL_POSITION, pos);
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glFrontFace(GL_CW);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
}

int main(int argc, char **argv)
{
  InitialProc();

  glutInit(&argc, argv);
  glutInitWindowPosition(50,100);
  glutInitWindowSize(500,500);
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);

  glutCreateWindow("bunny");

  glRotatef(30,1.0,0,0);
  glRotatef(30,0,1.0,0);
  glScalef(10.0,10.0,10.0);

  glutDisplayFunc(display);

  glutMainLoop();

  return 0;
}
