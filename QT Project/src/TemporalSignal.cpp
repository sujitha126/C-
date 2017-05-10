/*
Used DanielParmerHelloQt as reference
*/
#include <QtGui>
#include <QtOpenGL>
#include <GL/glu.h>
#include <GL/glut.h>
#include<list>
#include <math.h>
#include "TemporalSignal.h"
using std::list;

TemporalSignal::TemporalSignal(QWidget *parent) :
		QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
 {

}

TemporalSignal::~TemporalSignal() {

}

QSize TemporalSignal::minimumSizeHint() const
 {
     return QSize(250, 150);
 }

 QSize TemporalSignal::sizeHint() const
 {
     return QSize(300, 300);
 }
 
void TemporalSignal::renderTemporalSignal(list<int> values,int maxValue,int numberOfSamples) {
    sampleValues = values;
    ymax = maxValue+10;
    xmax = sqrt(maxValue)+5;
    updateGL();

}

//Initialize the GL settings
void TemporalSignal::initializeGL() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glPointSize(2.0);
	glLineWidth(2.0);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    glOrtho(0, 10, 0, 40,-2.0,2.0);

    	glMatrixMode(GL_MODELVIEW);

    	glLoadIdentity();
	glEnable (GL_DEPTH_TEST);
	glDepthFunc (GL_LEQUAL);
	glViewport(0, 200, 0, 200);

}

//Set up the viewport based on the screen dimentions
//Function is called implicitly by initializeGL and when screen is resized
void TemporalSignal::resizeGL(int w, int h) {
	if (w > h)
		glViewport((w - h) / 2, 0, h, h);
	else
		glViewport(0, (h - w) / 2, w, w);

}

//Paints the GL scene
void TemporalSignal::paintGL() {
    double p,q;
	glClear (GL_COLOR_BUFFER_BIT);
	glClear (GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, xmax, 0, ymax,-2.0,2.0);
    glMatrixMode(GL_MODELVIEW);
		glColor3f(1.0,0.0,0.0);
        glBegin(GL_LINE_STRIP);
        for (std::list<int>::iterator it = sampleValues.begin(); it != sampleValues.end(); it++) {
            q = abs(*it);
            p = sqrt(q);
            glVertex2f(p,q);
         }
        glEnd();
	
	glFlush();          // send all output to display 

}


 
