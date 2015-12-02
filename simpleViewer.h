#ifndef SIMPLEVIEWER_H
#define SIMPLEVIEWER_H

#include <QMouseEvent>
#include <QVector>
#include <QVector2D>
#include <QVector3D>
#include <QThread>
#include <QGLViewer/qglviewer.h>

//#include "minitab.h"

//class MiniTab;

class Viewer : public QGLViewer
{
    Q_OBJECT
public:
    Viewer();
    Viewer(QVector<QVector3D>& vertexSort, QWidget *parent);
    explicit Viewer(QVector<QVector3D>& vertexSort, QVector<QVector3D>& tabColor, QVector<QVector3D>& vector_interp, qglviewer::Vec& Min, qglviewer::Vec& Max, QVector<QVector3D>& vector1, QWidget *parent=0);

    virtual void init();
    virtual void draw();
    virtual ~Viewer();

    void mousePressEvent(QMouseEvent* const event);
/*
    //explicit Viewer(const QVector<QVector3D>& vector, const QVector<QVector2D>& vector_interp, QWidget *parent = 0);
    explicit Viewer(QVector<QVector3D>& vector, QVector<QVector3D>& vector_interp, double& distMax, int vertices_by_x, QWidget *parent = 0);
    virtual ~Viewer();

    bool intervisibility(QVector3D pt1, QVector3D pt2);
    float compareAlti(QVector3D intersect, int code);
    void computeIntervisility(QVector<QVector3D> m_vec);

    void computeLineLength();

    bool computeSousTerre(QVector3D pt1);

    qglviewer::Vec minCoord;
    qglviewer::Vec maxCoord;
*/

//protected:
    qglviewer::Vec& minCoord;
    qglviewer::Vec& maxCoord;
    QVector<QVector3D>& m_tabColor;
    QVector<QVector3D>& m_vertexSort;
    QVector<QVector3D>& m_coordInterp;
    QVector<QVector3D>& m_vect1;//vecteur à un seul point


    qglviewer::Vec pointMin;
    qglviewer::Vec pointMax;

    QVector3D pointClique;

private:
    bool m_selectMode;

signals:
    void coordAinterpModif(QVector3D);

public slots:
    void activateSelection();
    void setMode(bool visu);

//    const QVector<QVector3D>& m_vector;
/*
    QVector<QVector3D>& m_vector;
    int vertices_by_x;
    int m_nbLines;
    QVector<QVector3D> m_vertexSort;

    QVector<QVector3D> tabColor;

    double& distanceTir;
    int pasX;
    int pasY;

    MiniTab* tab1;
    MiniTab* tab2;
    MiniTab* tab3;
    MiniTab* tab4;


private:
    QThread m_thread1;
    QThread m_thread2;
    QThread m_thread3;
    QThread m_thread4;

signals:
    void beginThread1();
    void beginThread2();
    void beginThread3();
    void beginThread4();
*/

};

//bool intervisibility(QVector3D pt1, QVector3D pt2);


#endif // SIMPLEVIEWER_H
