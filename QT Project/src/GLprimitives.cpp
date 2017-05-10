
#include <QtGui>
#include <QtOpenGL>
#include<GL/glu.h>
#include <math.h>
#include "GLprimitives.h"
#ifndef GL_MULTISAMPLE
 #define GL_MULTISAMPLE  0x809D
 #endif


GLprimitives::GLprimitives(QWidget *parent) :
		QGLWidget(parent) {

}

GLprimitives::~GLprimitives() {

}

QSize GLprimitives::minimumSizeHint() const
 {
     return QSize(250, 150);
 }

 QSize GLprimitives::sizeHint() const
 {
     return QSize(300, 300);
 }
//Initialize the GL settings
void GLprimitives::initializeGL() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glPointSize(2.0);
	glLineWidth(4.0);
	glEnable (GL_DEPTH_TEST);
	glDepthFunc (GL_LEQUAL);
    glEnable(GL_MULTISAMPLE);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

//Set up the viewport based on the screen dimentions
//Function is called implicitly by initializeGL and when screen is resized
void GLprimitives::resizeGL(int w, int h) {
	//algorithm to keep scene "square" (preserve aspect ratio)
	//even if screen is streached
    /*if (w > h)
		glViewport((w - h) / 2, 0, h, h);
	else
        glViewport(0, (h - w) / 2, w, w);*/
    glViewport(0, 0, w, h);

	//setup the projection and switch to model view for transformations
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
    gluPerspective(15.0f,(float)w/h,0.1f,100.0f);

	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
    gluLookAt(0, 0, 10,  //Camera position
                      0, 0, 0,  //look at position
                      0, 1, 1); //Camera "up" vector

	//implicit call to paintGL after resized
}

void GLprimitives::drawCube() {

    //Front of the Cube		//Cube
        glPushMatrix();
        //glTranslatef(0.2f,0.2f,-7.0f);
        glTranslatef(1.2f, 1.0f, -7.0f);
        glScalef(0.5f,0.5f,0.5f);
        glRotatef(45,0.1,0.0,0.0);
        glRotatef(35,0.0,1.0,0.0);

    glBegin(GL_QUADS);
    glColor3f(0.0f, 1.0f, 0.0f);     // Green
          glVertex3f( 1.0f, 1.0f, -1.0f);
          glVertex3f(-1.0f, 1.0f, -1.0f);
          glVertex3f(-1.0f, 1.0f,  1.0f);
          glVertex3f( 1.0f, 1.0f,  1.0f);

          // Bottom face (y = -1.0f)
          glColor3f(1.0f, 0.5f, 0.0f);     // Orange
          glVertex3f( 1.0f, -1.0f,  1.0f);
          glVertex3f(-1.0f, -1.0f,  1.0f);
          glVertex3f(-1.0f, -1.0f, -1.0f);
          glVertex3f( 1.0f, -1.0f, -1.0f);

          // Front face  (z = 1.0f)
          glColor3f(1.0f, 0.0f, 0.0f);     // Red
          glVertex3f( 1.0f,  1.0f, 1.0f);
          glVertex3f(-1.0f,  1.0f, 1.0f);
          glVertex3f(-1.0f, -1.0f, 1.0f);
          glVertex3f( 1.0f, -1.0f, 1.0f);

          // Back face (z = -1.0f)
          glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
          glVertex3f( 1.0f, -1.0f, -1.0f);
          glVertex3f(-1.0f, -1.0f, -1.0f);
          glVertex3f(-1.0f,  1.0f, -1.0f);
          glVertex3f( 1.0f,  1.0f, -1.0f);

          // Left face (x = -1.0f)
          glColor3f(0.0f, 0.0f, 1.0f);     // Blue
          glVertex3f(-1.0f,  1.0f,  1.0f);
          glVertex3f(-1.0f,  1.0f, -1.0f);
          glVertex3f(-1.0f, -1.0f, -1.0f);
          glVertex3f(-1.0f, -1.0f,  1.0f);

          // Right face (x = 1.0f)
          glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
          glVertex3f(1.0f,  1.0f, -1.0f);
          glVertex3f(1.0f,  1.0f,  1.0f);
          glVertex3f(1.0f, -1.0f,  1.0f);
          glVertex3f(1.0f, -1.0f, -1.0f);

          glEnd();
         glPopMatrix();
}
//Paints the GL scene
void GLprimitives::paintGL() {
	glClear (GL_COLOR_BUFFER_BIT);
	glClear (GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glTranslatef(0.0f,0.0f,0.0f);
    glRotatef(0,0.0,1.0,0.0);
	glBegin (GL_POINTS);
	glColor3f(0.0, 1.0, 0.0);
    glVertex3f(-1.0f,-1.0f,1.0f);
    glVertex3f(-1.0f,1.0f,1.0f);
    glVertex3f(1.0f,-1.0f,1.0f);
    glVertex3f(1.0f,1.0f,1.0f);
	glEnd();
    glPopMatrix();

    // Lines
    glPushMatrix();
    glTranslatef(0.0f,-0.2f,0.0f);
    glRotatef(0,1.0,0.0,0.0);
    glBegin (GL_LINES);
	glColor3f(1.0, 0.5, 0.0);
    glVertex3f(-1.0, 0.0,1.0f);
    glVertex3f(1.0, 0.0,1.0f);
    glEnd();
    glPopMatrix();

    // Triangles
    glPushMatrix();
    glTranslatef(-0.3f,0.0f,0.0f);
    glScalef(1.5f,1.5f,1.5f);
    glRotatef(45,1.0,0.0,0.0);
     glBegin (GL_TRIANGLES);
         glColor3f(0.0, 0.0, 1.0);
         glVertex2f(-0.6, 0.6);
         glVertex2f(-0.6, 0);
         glVertex2f(0, 0.6);
         glEnd();
    glPopMatrix();

    // Quad
    glPushMatrix();
      glTranslatef(-0.15f,0.65f,0.0f);
      glScalef(1.5f,1.5f,1.5f);
      glRotatef(45.0,0.0,0.0,1.0);
      glTranslatef(0.25f,0.55f,0.0f);
         //Draw a quad
         glBegin (GL_QUADS);
         glColor3f(1.0, 1.0, 0.0);
         glVertex2f(-0.8, -0.5);
         glVertex2f(-0.8, -0.6);
         glVertex2f(0, -0.6);
         glVertex2f(0, -0.5);
         glEnd();
     glPopMatrix();

     // Polygon
     glPushMatrix();
     glTranslatef(1.2f,-0.6f,0.0f);
     glRotatef(-45.0,0.0,0.0,1.0);
         glBegin (GL_POLYGON);//Polygon
         glColor3f(0.8, 0.7, 0.2);
         glVertex3f(-0.6, -0.6,1.0);
         glVertex3f(-0.6, -0.2,1.0);
         glVertex3f(-0.3, 0.0,1.0);
         glVertex3f(0.0, -0.2,1.0);
         glVertex3f(0.0, -0.6,1.0);
         glEnd();
     glPopMatrix();

     glPushMatrix();
     glTranslatef(0.0f,-0.2f,0.0f);
     glScalef(1.5f,1.5f,1.5f);
     glRotatef(60.0,0.0,0.0,1.0);
         glBegin (GL_LINE_LOOP);// LINE LOOP
         glColor3f(0.0, 1.0, 1.0);
         glVertex2f(-0.7,0.5);
         glVertex2f(-0.7,0.15);
         glVertex2f(-0.5,0.15);
         glVertex2f(-0.5,0.5);
         glEnd();
     glPopMatrix();

     glPushMatrix();
     glTranslatef(-0.3f,-0.5f,0.0f);
     glScalef(0.8,0.8,0.8);
     glRotatef(40.0,0.0,0.0,1.0);
         glBegin (GL_LINE_STRIP);	//Line Strip
         glColor3f(0.3, 0.85, 0.6);
         glVertex2f(-0.6,-0.6);
         glVertex2f(-0.6,-0.2);
         glVertex2f(0.6,-0.2);
         glVertex2f(0.6,-0.6);

         glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f,0.0f,0.0f);
    glRotatef(15.0,0.0,0.0,1.0);
         glBegin (GL_TRIANGLE_STRIP);	// TRIANGLE STRIP
         glColor3f(0.4,0.5, 0.1);
         glVertex2f(-0.25,-0.8);
         glVertex2f(-0.5,-0.9);
         glVertex2f(-0.15,-0.9);
         glVertex2f(0,-0.9);
         glVertex2f(-0.5,-1);
         glEnd();
    glPopMatrix();

    drawCube();
	glFlush();
}

