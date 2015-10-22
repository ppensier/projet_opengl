#include "simpleViewer.h"
#include "mainwindow.h"

using namespace std;

Viewer::Viewer(const QVector<QVector3D>& vector, Widget *parent) :
QGLViewer(parent), m_vector(vector)
{
    //std::string m_nameFile;
}

//Accesseurs et mutateurs de tableau dans la classe viewer
QVector<QVector3D> Viewer::getterTableau()
{
    return this->m_vector;
}

QVector<QVector3D> Viewer::setterTableau(QVector<QVector3D> vector)
{

    m_vector = vector;

    return m_vector;
}

void Viewer::initializeGL()
{
    restoreStateFromFile();
    glLineWidth(3.0);
    glPointSize(10.0);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glEnable( GL_POINT_SMOOTH );
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glPointSize( 10.0 );


/*
    double maxAbs = this->m_vector[0].x();
    double maxOrd = this->m_vector[0].y();
    double maxAlt = this->m_vector[0].z();

/*
    glClear(GL_COLOR_BUFFER_BIT);
    for ( int i = 0; i < m_vector.size(); i++ )
    {
        if (m_vector[i].x() > maxAbs)
        {
            maxAbs = m_vector[i].x();
        }
        if (m_vector[i].y() > maxOrd)
        {
            maxOrd = m_vector[i].y();
        }
        if (m_vector[i].z() > maxAlt)
        {
            maxAlt = m_vector[i].z();
        }
    }
*/

}


void Viewer::resizeGL(int width, int height)
{
    glViewport(0, 0, (GLint)width, (GLint)height);
}

void Viewer::paintGL()
{
    qglColor(Qt::white);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, m_vector.constData());
    glDrawArrays(GL_TRIANGLES, 0, m_vector.size());
    glDisableClientState(GL_VERTEX_ARRAY);

}

