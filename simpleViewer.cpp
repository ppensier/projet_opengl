

#include "simpleViewer.h"

#include <iostream>

using namespace std;
using namespace qglviewer;


Viewer::Viewer(const QVector<QVector3D>& vector, QWidget *parent) :
QGLViewer(parent), m_vector(vector), vertices_by_x(4000)
{

}

void Viewer::init()
{

    minCoord.x = INFINITY;
    minCoord.y = INFINITY;
    minCoord.z = INFINITY;
    maxCoord.x = 0;
    maxCoord.y = 0;
    maxCoord.z = 0;

    if (m_vector.length() != 0)
    {
        for ( int i = 0; i<m_vector.length(); ++i)
        {
            if (m_vector[i].x() > maxCoord.x)
                maxCoord.x = m_vector[i].x();
            if (m_vector[i].x() < minCoord.x)
                minCoord.x = m_vector[i].x();
            if (m_vector[i].y() > maxCoord.y)
                maxCoord.y = m_vector[i].y();
            if (m_vector[i].y() < minCoord.y)
                minCoord.y = m_vector[i].y();
            if (m_vector[i].z() > maxCoord.z)
                maxCoord.z = m_vector[i].z();
            if (m_vector[i].z() < minCoord.z)
                minCoord.z = m_vector[i].z();

        }

        //redimensionner les spinbox

        //on trie les points
        for (int i(0); i<m_vector.length()-vertices_by_x-1; i++)
        {
            //premier triangle
            m_vertexSort.push_back(m_vector[i]);
            m_vertexSort.push_back(m_vector[i+vertices_by_x]);
            m_vertexSort.push_back(m_vector[i+1]);

            //deuxième triangle
            m_vertexSort.push_back(m_vector[i+1]);
            m_vertexSort.push_back(m_vector[i+vertices_by_x]);
            m_vertexSort.push_back(m_vector[i+1+vertices_by_x]);

        }

        cout << m_vertexSort[0].x() << " " << m_vertexSort[1].x() << " " << m_vertexSort[2].x() << endl;
        //cout << "min : " << minCoord.x << " " << minCoord.y << " " << minCoord.z << endl;

        //cout << m_vector[2].x() << " " << m_vector[2+vertices_by_x].x() << endl;

        //cout << "min en x: " << minCoord.x << endl;
        //cout << "max en x: " << maxCoord.x << endl;

        setSceneBoundingBox(minCoord, maxCoord);
        showEntireScene();
        //restoreStateFromFile();
    }
}


void Viewer::draw()
{

  drawAxis();

  if (m_vector.length() != 0)
  {

    drawAxis();

    glClear(GL_COLOR_BUFFER_BIT); // clear screen
    glLineWidth(1);

//  glBegin(GL_LINE_LOOP);
//      glColor3f(1.0f, 0.2f , 0.0f);
//      glVertex3f(m_vector[1].x(),m_vector[1].y(),m_vector[1].z());
//      glVertex3f(m_vector[10].x(),m_vector[10].y(),m_vector[10].z());
//      glVertex3f(m_vector[20].x(),m_vector[20].y(),m_vector[20].z());
//      glVertex3f(1.0, 1.0, 0.0);
//      glVertex3f(0.0, 0.0, 0.0);
//      glVertex3f(1.0, 0.0, 0.0);
//  glEnd();

/*
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 0.2f , 0.0f);
      for (int i(0); i<m_vector.length(); i++)
      {
          glVertex3d(m_vector[i].x(), m_vector[i].y(), m_vector[i].z());
      }
    glEnd();
*/

  //cout << minCoord.x << minCoord.y << minCoord.z << endl;

  //glBegin(GL_TRIANGLES);
/*
    glColor3f(1.0f, 1.0f , 1.0f);
      for (int i(0); i<m_vector.length()-vertices_by_x-1; i++)
      {
          glBegin(GL_LINE_LOOP);
          //glColor3f(1.0f, 0.2f , 0.0f);
          //Premier triangle
              glVertex3d(m_vector[i].x(), m_vector[i].y(), m_vector[i].z()); //premier point
              glVertex3d(m_vector[i+vertices_by_x].x(), m_vector[i+vertices_by_x].y(), m_vector[i+vertices_by_x].z());//deuxième point
              glVertex3d(m_vector[i+1].x(), m_vector[i+1].y(), m_vector[i+1].z());//troisième point
          glEnd();
*/
          //Deuxième triangle
          /*
          glBegin(GL_LINE_LOOP);
              glVertex3f(m_vector[i+1].x(), m_vector[i+1].y(), m_vector[i+1].z());//3eme point du deuxième triangle
              glVertex3f(m_vector[i+vertices_by_x].x(), m_vector[i+vertices_by_x].y(), m_vector[i+vertices_by_x].z());//2eme point du premier triangle
              glVertex3f(m_vector[i+1+vertices_by_x].x(), m_vector[i+1+vertices_by_x].y(), m_vector[i+1+vertices_by_x].z());
          glEnd();

           }
          */

    //on affiche le tableau trié avec glDrawArrays
    qglColor(Qt::white);
    glEnableClientState(GL_VERTEX_ARRAY);//on indique à la carte graphique que l'on va travailler avec des vertex array
        glVertexPointer(3, GL_FLOAT, 0, m_vertexSort.constData());//on envoie le tableau de données à la carte graphique
        glDrawArrays(GL_LINE_LOOP, 0, m_vertexSort.size());//dessine les primitives
    glDisableClientState(GL_VERTEX_ARRAY);




  }
}


