#ifndef Gasket_H
#define Gasket_H

#include <QGLWidget>

class Gasket : public QGLWidget
{
    Q_OBJECT

public:
    Gasket(QWidget *parent = 0);
    ~Gasket();
    QSize minimumSizeHint() const;
    QSize sizeHint() const;

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void timerEvent(QTimerEvent *) {update();}
    void setXRotation(int angle);
    void setYRotation(int angle);

private:
    QPoint lastPos;
    int xRot;
    int yRot;
    int timerId;
    void triangle( GLfloat *a, GLfloat *b, GLfloat *c);
	void divide_triangle(GLfloat *a, GLfloat *b, GLfloat *c, int m);
	void tetrahedron(int n);

};

#endif
