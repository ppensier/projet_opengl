#ifndef SIMPLEVIEWER_H
#define SIMPLEVIEWER_H

#include <QMouseEvent>
#include <QVector>
#include <QVector2D>
#include <QVector3D>
#include <QThread>
#include <QGLViewer/qglviewer.h>

class Viewer : public QGLViewer
{
public:
    //explicit Viewer(const QVector<QVector3D>& vector, const QVector<QVector2D>& vector_interp, QWidget *parent = 0);
    explicit Viewer(QVector<QVector3D>& vector, QVector<QVector3D>& vector_interp, double& distMax, QWidget *parent = 0);
    virtual void init();
    virtual void draw();

    bool intervisibility(QVector3D pt1, QVector3D pt2);
    float compareAlti(QVector3D intersect, int code);
    void computeIntervisility(QVector<QVector3D> m_vec);

    void computeLineLength();

    bool computeSousTerre(QVector3D pt1);

    qglviewer::Vec minCoord;
    qglviewer::Vec maxCoord;
    qglviewer::Vec mouseClick(QMouseEvent* const event);

protected:
//    const QVector<QVector3D>& m_vector;
    QVector<QVector3D>& m_vector;
    int vertices_by_x;
    int m_nbLines;
    QVector<QVector3D> m_vertexSort;
    QVector<QVector3D>& m_coordInterp;
    QVector<QVector3D> tabColor;
    QVector<QVector3D> m_vect1;
    double& distanceTir;
    int pasX;
    int pasY;

private:
    QThread m_tabThread1;
    //QThread m_tabThread2;
    //QThread m_tabThread3;
    //QThread m_tabThread4;

signals:
    void beginThread();

};

bool intervisibility(QVector3D pt1, QVector3D pt2);


#endif // SIMPLEVIEWER_H
