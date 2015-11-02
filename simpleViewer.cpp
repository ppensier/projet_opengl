

#include "simpleViewer.h"

#include <iostream>

using namespace std;
using namespace qglviewer;


Viewer::Viewer(const QVector<QVector3D>& vector, QWidget *parent) :
QGLViewer(parent), m_vector(vector)
{
    //std::string m_nameFile;
}

/*
void Viewer::setterTableau(const QVector<QVector3D>& vector)
{
    m_vector = vector;
    //m_vector(vector);
}
*/

//QVector<QVector3D>& operator=(const QVector<QVector3D>& vec)

void Viewer::init()
{

    minCoord.x = 0;
    minCoord.y = 0;
    minCoord.z = 0;
    maxCoord.x = 0;
    maxCoord.y = 0;
    maxCoord.z = 0;

    if (m_vector.length() != 0)
    {
        cout << m_vector[0].x() << endl;
        for ( int i = 0; i < m_vector.length(); i++ )
        {
            if (m_vector[i].x() > maxCoord.x)
                maxCoord.x = m_vector[i].x();
            if (m_vector[i].y() > maxCoord.y)
                maxCoord.y = m_vector[i].y();
            if (m_vector[i].z() > maxCoord.z)
                maxCoord.z = m_vector[i].z();
            if (m_vector[i].x() < minCoord.x)
                minCoord.x = m_vector[i].x();
            if (m_vector[i].y() < minCoord.y)
                maxCoord.y = m_vector[i].y();
            if (m_vector[i].z() < minCoord.z)
                maxCoord.z = m_vector[i].z();
        }

        setSceneBoundingBox(minCoord, maxCoord);
        glPointSize( 10.0 );
        restoreStateFromFile();
    }
}

/*
void Viewer::resizeGL(int width, int height)
{
    glViewport(0, 0, (GLint)width, (GLint)height);
}
*/

void Viewer::draw()
{

  if (m_vector.length() != 0)
  {
  drawAxis();

  /*
  glBegin(GL_LINE_LOOP);
      glColor3f(1.0f, 0.2f , 0.0f);
      glVertex3f(1.0, 1.0, 0.0);
      glVertex3f(0.0, 0.0, 0.0);
      glVertex3f(1.0, 0.0, 0.0);
  glEnd();
  */

  //glBegin(GL_LINE_LOOP);
  //    glColor3f(1.0f, 0.2f , 0.0f);
      //for (int i(0); i<m_vector.length(); i++)
      for (int i(0); i<10; i++)
      {
          cout << m_vector[i].x() << endl;
          //glVertex3f(m_vector[i].x(), m_vector[i].y(), m_vector[i].z());

      }
  //glEnd();

    }
}



