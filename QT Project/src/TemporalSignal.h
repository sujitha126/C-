
#ifndef TemporalSignal_H
#define TemporalSignal_H

#include <QGLWidget>
#include<list>
using std::list;

class TemporalSignal : public QGLWidget
{
    Q_OBJECT

public:
    TemporalSignal(QWidget *parent = 0);
    ~TemporalSignal();
    QSize minimumSizeHint() const;
    QSize sizeHint() const;

public slots:
    void renderTemporalSignal(list<int> values, int maxValue, int numberOfSamples);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

private:
    list<int> sampleValues;
    GLdouble xmax;
    GLdouble ymax;

};

#endif
