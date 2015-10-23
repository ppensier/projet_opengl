#include <QGLViewer/qglviewer.h>
#include "mainwindow.h"

class Viewer : public QGLViewer
{
public:
    explicit Viewer(const QVector<QVector3D>& vector, QWidget *parent = 0);
    //void setterTableau(const QVector<QVector3D> &vector);
    //QVector<QVector3D> getTableau();

    //test ajout attribut
    double maxAbs;
    double maxOrd;
    double maxAlt;

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    //virtual QString helpString() const;

private:
    const QVector<QVector3D>& m_vector;

};
