/*
Used DanielParmerHelloQt as reference
*/
#include <QtGui>
#include <QtOpenGL>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include "AMCarrier.h"

AMCarrier::AMCarrier(QWidget *parent) :
		QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
 {
	amplitude = 1;
	frequency = 1;
}

AMCarrier::~AMCarrier() {

}

QSize AMCarrier::minimumSizeHint() const
 {
     return QSize(250, 150);
 }

 QSize AMCarrier::sizeHint() const
 {
     return QSize(300, 300);
 }
void AMCarrier::setAmplitude(int amplitudeNew) {
	if(amplitudeNew != amplitude) {
		amplitude = amplitudeNew;
		updateGL();
	}
}

void AMCarrier::setFrequency(int frequencyNew) {
	if(frequencyNew != frequency) {
			frequency = frequencyNew;
			updateGL();
		} 
}
 
//Initialize the GL settings
void AMCarrier::initializeGL() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glPointSize(2.0);
	glLineWidth(2.0);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5.0, 5.0, -5.0, 5.0,-1.0,1.0);

    	glMatrixMode(GL_MODELVIEW);

    	glLoadIdentity();
	glEnable (GL_DEPTH_TEST);
	glDepthFunc (GL_LEQUAL);
	glViewport(0, 200, 0, 200);

}

//Set up the viewport based on the screen dimentions
//Function is called implicitly by initializeGL and when screen is resized
void AMCarrier::resizeGL(int w, int h) {
	if (w > h)
		glViewport((w - h) / 2, 0, h, h);
	else
		glViewport(0, (h - w) / 2, w, w);

}

//Paints the GL scene
void AMCarrier::paintGL() {
	glClear (GL_COLOR_BUFFER_BIT);
	glClear (GL_DEPTH_BUFFER_BIT);
	
		glColor3f(1.0,0.0,0.0);
		glBegin(GL_LINE_STRIP);
        	for(GLfloat x = -5; x < 5; x=x+0.001)     // draw the plot
			glVertex2f(x, amplitude*cos(2*3.14159 * frequency*x)); 
		glEnd();
	
	glFlush();          // send all output to display 

}


 
