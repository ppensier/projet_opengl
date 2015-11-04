#ifndef SIMPLEVIEWER_H
#define SIMPLEVIEWER_H

#include <QVector>
#include <QVector2D>
#include <QVector3D>
#include <QGLViewer/qglviewer.h>

class Viewer : public QGLViewer
{
public:
    explicit Viewer(const QVector<QVector3D>& vector, QWidget *parent = 0);
    //void setterTableau(const QVector<QVector3D> &vector);
    //QVector<QVector3D> getTableau();
    //QVector<QVector3D>& operator=(const QVector<QVector3D>& vec);
    virtual void init();

    qglviewer::Vec minCoord;
    qglviewer::Vec maxCoord;

protected:
    virtual void draw();

//    qglviewer::Vec minCoord;
//    qglviewer::Vec maxCoord;
    const QVector<QVector3D>& m_vector;
    int vertices_by_x;
    QVector<QVector3D> m_vertexSort;

private:

};

#endif // SIMPLEVIEWER_H
