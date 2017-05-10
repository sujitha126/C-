
#ifndef GLprimitives_H
#define GLprimitives_H

#include <QGLWidget>

class GLprimitives : public QGLWidget
{
    Q_OBJECT

public:
    GLprimitives(QWidget *parent = 0);
    ~GLprimitives();
    QSize minimumSizeHint() const;
    QSize sizeHint() const;

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
private:
    void drawCube();
};

#endif
