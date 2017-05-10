/*
Used DanielParmerHelloQt as reference
*/
#include <stdlib.h>
#include <GL/glut.h>
#include <QtGui>
#include <QtOpenGL>
#include <math.h>
#include "Gasket.h"

static int n = 0;

Gasket::Gasket(QWidget *parent) :
		QGLWidget(parent) {
    xRot = 0;
    yRot = 0;
    timerId = startTimer(1000);
}

Gasket::~Gasket() {

}

QSize Gasket::minimumSizeHint() const
 {
     return QSize(250, 100);
 }

 QSize Gasket::sizeHint() const
 {
     return QSize(300, 300);
 }

//Initialize the GL settings
void Gasket::initializeGL() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glPointSize(2.0);
	glLineWidth(4.0);
	glEnable (GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_CULL_FACE);
    glEnable(GL_MULTISAMPLE);
	glDepthFunc (GL_LEQUAL);
    glEnable(GL_COLOR_MATERIAL);

     GLfloat mat_specular[] = { 0.0, 1.0, 0.0, 1.0 };
    GLfloat light_position[] = { 10.0, 0.0, 0.0, 0.0 };
    GLfloat light_ambient[] = { 0.0, 10.0, 10.0, 1.0};

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glLightfv(GL_LIGHT2, GL_POSITION, light_position);
     glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

     glEnable(GL_LIGHT2);
     glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);


}
void Gasket::resizeGL( int w, int h )
{
    //algorithm to keep scene "square" (preserve aspect ratio)
    //even if screen is streached
    if(w>h)
        glViewport((w-h)/2, 0, h, h);
    else
        glViewport(0, (h-w)/2, w, w);

    //setup the projection and switch to model view for transformations
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //implicit call to paintGL after resized
}

void Gasket::triangle( GLfloat *a, GLfloat *b, GLfloat *c)
/* display one triangle  */
{
      //glColor3f(1, 1, 0);
      glVertex3fv(a); 
      //glColor3f(0, 1, 1);
      glVertex3fv(b);
        //glColor3f(1, 0, 1);
      glVertex3fv(c);
}
void Gasket::divide_triangle(GLfloat *a, GLfloat *b, GLfloat *c, int m)
{
/* triangle subdivision using vertex numbers */
    GLfloat v0[3], v1[3], v2[3];
    int j;
    if(m>0)
     {
        for(j=0; j<3; j++) v0[j]=(a[j]+b[j])/2;
        for(j=0; j<3; j++) v1[j]=(a[j]+c[j])/2;
        for(j=0; j<3; j++) v2[j]=(b[j]+c[j])/2;
        glColor3f(1, 0, 0);
        divide_triangle(a, v0, v1, m-1);
        glColor3f(0.35, 0.35, 0.67);
        divide_triangle(c, v1, v2, m-1);
        glColor3f(0.85, 0.85, 0.1);
        divide_triangle(b, v2, v0, m-1);
    }
    else(triangle(a,b,c));
 /* draw triangle at end of recursion */
}

void Gasket::tetrahedron( int m)
{
    GLfloat v[3][3]={{-1.0, -0.5,-1.0},
          {1.0, -0.5,-1.0}, {0.0, 1.0,-1.0}};
    //glColor3f(1.0,1.0,0.0);
    divide_triangle(v[0], v[1], v[2], m);
    //glColor3f(0.0,1.0,1.0);
    divide_triangle(v[3], v[2], v[1], m);
    //glColor3f(1.0,0.0,1.0);
    divide_triangle(v[0], v[3], v[1], m);
    //glColor3f(0.0,0.0,0.0);
    divide_triangle(v[0], v[2], v[3], m);
}

//Paints the GL scene
void Gasket::paintGL() {

    glClear (GL_COLOR_BUFFER_BIT);
	glClear (GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_SMOOTH);

     glLoadIdentity();
         glTranslatef(0.0, 0.0, 0.0);
         glRotatef(xRot/16 , 1.0, 0.0, 0.0);
         glRotatef(yRot/16 , 0.0, 1.0, 0.0);
    if(n==6) {
       n=0;

    }
	glBegin(GL_TRIANGLES);
          tetrahedron(n++);
    glEnd();
    glFlush();

}

void Gasket::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}
void Gasket::mouseMoveEvent(QMouseEvent *event)
 {
     int dx = event->x() - lastPos.x();
     int dy = event->y() - lastPos.y();

         setXRotation(xRot + 8*dy);
         setYRotation(yRot + 8*dx);

     lastPos = event->pos();
 }
static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}
void Gasket::setXRotation(int angle)
 {
     qNormalizeAngle(angle);
     if (angle != xRot) {
         xRot = angle;
         updateGL();
     }
 }

 void Gasket::setYRotation(int angle)
 {
     qNormalizeAngle(angle);
     if (angle != yRot) {
         yRot = angle;
         updateGL();
     }
 }

