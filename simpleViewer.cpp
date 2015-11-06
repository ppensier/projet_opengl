

#include "simpleViewer.h"

#include <iostream>

using namespace std;
using namespace qglviewer;


Viewer::Viewer(const QVector<QVector3D>& vector, const QVector<QVector2D>& vector_interp, QWidget *parent) :
QGLViewer(parent), m_vector(vector), m_coordInterp(vector_interp), vertices_by_x(4000)
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

        if (m_coordInterp.length() != 0)
        {
            cout << m_coordInterp.length() << endl;

        }
        //cout << m_coordInterp[0].x() << " " << m_coordInterp[0].y() << " " << m_coordInterp[1].x() << " " << m_coordInterp[1].y() << endl;

        //cout << m_vertexSort[0].x() << " " << m_vertexSort[1].x() << " " << m_vertexSort[2].x() << endl;
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

/*

bool Viewer::intervisibilitee(QVector3D pt1, QVector3D pt2)//prend en paramètre deux vecteurs
{
    //On appelle une fonction pour sortir les droites du rectangle
    double calculateAxis(QVector3D pt1, QVector3D pt2);


    }



}
*/

void Viewer::calculateAxis(QVector3D pt1, QVector3D pt2)
{
    double x1, x2, y1, y2;

    QVector3D p1, p2, p3;

    //on trouve d'abord  le x de la droite du 1er point
    double soustractionx1 = pt1.x()-m_vector[0].x();
    int pasX = 25;
    int resx1 = soustractionx1/pasX;

    //on calcule le x de la droite la droite du 2eme point
    double soustractionx2 = pt2.x()-m_vector[0].x();
    int resx2 = soustractionx2/pasX;

    double soustractiony1 = pt1.y()-m_vector[m_vector.length()-1].y();
    int pasY = m_vector[0].y() - m_vector[4000].y();
    int resy1 = soustractiony1/pasY;

    double soustractiony2 = pt2.y()-m_vector[m_vector.length()-1].y();
    int resy2 = soustractiony2/pasY;

    if (pt1.x() < pt2.x())
    {
        x1 = (resx1+1)*pasX;
        x2 = resx2*pasX;

        if(pt1.y() < pt2.y())
        {
            y1 = (resy1+1)*pasY;
            y2 = resy2*pasY;

            //on récupère le triangle auquel appartient le point
            p1.setX(m_vector[x1/pasX-1].x());
            p2.setX(m_vector[x1/pasX].x());
            p3.setX(m_vector[x1/pasX].x());

            p1.setY(m_vector[].y());
            p2.setY(m_vector[].y());
            p3.setY(m_vector[].y());

        }
        else
        {
            y1 = resy1*pasY;
            y2 = (resy2+1)*pasY;

        }

    }
    else
    {
        x1 = resx1*pasX;
        x2 = (resx2+1)*pasX;

        if(pt1.y() < pt2.y())
        {
            y1 = (resy1+1)*pasY;
            y2 = resy2*pasY;

        }
        else
        {
            y1 = resy1*pasY;
            y2 = (resy2+1)*pasY;

        }

    }

    cout << "les deux abscisses des deux droites sont: " << x1 << " et " << x2 << endl;
    cout << "indices: " << x1/pasX << " et " << x2/pasX << endl;
    cout << m_vector[x1/pasX].x() << " et " << m_vector[x2/pasX].x() << endl;

    //cout << "L'ordonnée minimale est: " << m_vector[m_vector.length()-1].y() << endl;
    cout << "les deux ordonnées des deux droites sont: " << y1 << " et " << y2 << endl;
    //cout << pasY << " " << soustractiony2 << "=" << pt2.y() << "-" << m_vector[m_vector.length()-1].y() << endl;

}

/*
double x1, x2, y1, y2;
//cout << coordAinterp.length() << endl;

//recherche des abscisses
int i = 0;
while (i != 4000)//on ne parcourt que la permiere ligne
{
    //premier point considéré
    if (m_vect[i].x() > coordAinterp[0].x())
    {
        //cout << "Arret: " << m_vect[i].x() << " " << coordAinterp[0].x() << endl;
        x1 = m_vect[i].x();
        x2 = m_vect[i-1].x();
        cout << "les deux abscisses limites pour le 1er point sont: "  << x1 << " et " << x2 << endl;
        break;
    }
    i++;
}

//recherche des ordonnées, donc parcours de tout le fichier
int j = 0;
while(j != m_vect.length())// on parcourt une colonne du fichier
{
    if (m_vect[j].y() < coordAinterp[0].y())
    {
            cout << "Arret sur les ordonnées!" << m_vect[j].y() << " " << coordAinterp[0].y() << endl;
            y1 = m_vect[j].y();
            y2 = m_vect[j-1].y();
            cout << "les deux ordonnees limites pour le 1er point sont: "  << y1 << " et " << y2 << endl;
            break;
    }
    j += 4000;
}


*/




