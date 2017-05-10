
#ifndef AMCarrier_H
#define AMCarrier_H

#include <QGLWidget>

class AMCarrier : public QGLWidget
{
    Q_OBJECT

public:
    AMCarrier(QWidget *parent = 0);
    ~AMCarrier();
    QSize minimumSizeHint() const;
    QSize sizeHint() const;

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

public slots:
    void setAmplitude(int amplitude);
    void setFrequency(int frequency);

private:
    int amplitude;
    int frequency;
};

#endif
