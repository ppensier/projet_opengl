#include "simpleViewer.h"
#include "mainwindow.h"

using namespace std;

Viewer::Viewer(const QVector<QVector3D>& vector, QWidget *parent) :
QGLViewer(parent), m_vector(vector)
{
    //std::string m_nameFile;
}

//Accesseurs et mutateurs de tableau dans la classe viewer
QVector<QVector3D> Viewer::getTableau()
{
    return this->m_vector;
}

/*
void Viewer::setterTableau(const QVector<QVector3D>& vector)
{

    m_vector = vector;

}*/

void Viewer::init()
{
    double maxAbs(0);
    double maxOrd(0);
    double maxAlt(0);

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

    glPointSize( 10.0 );
    restoreStateFromFile();
/*Previous initializeGL
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
*/

    //int sizeTable = m_vector.size();

//    QVector<QVector3D> testVector;
//
//    testVector = this->getTableau();

//    double maxAbs = testVector[0].x();
//    double maxOrd = this->m_vector[0].y();
//    double maxAlt = this->m_vector[0].z();

}

/*
void Viewer::resizeGL(int width, int height)
{
    glViewport(0, 0, (GLint)width, (GLint)height);
}
*/

void Viewer::draw()
{

  glBegin(GL_LINE_LOOP);
      glColor3f(1.0f, 0.2f , 0.0f);
      glVertex3f(1.0, 1.0, 0.0);
      glVertex3f(0.0, 0.0, 0.0);
      glVertex3f(1.0, 0.0, 0.0);
  glEnd();

    /*
  glBegin(GL_LINE);
  for (int i(0); i<m_vector.size(); i++)
  {
      glColor3f(0.0f, 0.0f, 0.0f);
      glVertex3f(m_vector[i].x(), m_vector[i].y(), m_vector[i].z());

  }
  glEnd();
*/
}



