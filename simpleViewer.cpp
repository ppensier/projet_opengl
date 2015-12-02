#include "plan.h"
#include "droite.h"

#include "simpleViewer.h"
#include "minitab.h"

#include <iostream>

using namespace std;
using namespace qglviewer;

Viewer::Viewer(QVector<QVector3D>& vertexSort, QVector<QVector3D>& tabColor, QVector<QVector3D>& vector_interp, qglviewer::Vec& Min, qglviewer::Vec& Max, QVector<QVector3D>& vector1, QWidget *parent) :
QGLViewer(parent), m_vertexSort(vertexSort), m_tabColor(tabColor), minCoord(Min), maxCoord(Max), m_coordInterp(vector_interp), m_vect1(vector1)
{

}

void Viewer::init()
{

    //redimensionnement de la fenêtre
    if (m_vertexSort.length() != 0)
    {
        setSceneBoundingBox(minCoord, maxCoord);
        showEntireScene();

    }

    //méthode de la camra quand l'utilisateur rentre un point
    if (m_coordInterp.length() != 0)
    {
        qglviewer::Camera* const cam = this->camera();
        Vec positionCam(qreal(m_coordInterp[0].x()),qreal(m_coordInterp[0].y()),qreal(m_coordInterp[0].z()));
        cam->setPosition(positionCam);

        if (m_coordInterp.length() == 2)
        {

            Vec direction(qreal(m_coordInterp[1].x()-m_coordInterp[0].x()),qreal(m_coordInterp[1].y()-m_coordInterp[0].y()),qreal(m_coordInterp[1].z()-m_coordInterp[0].z()));
            cam->setViewDirection(direction);
        }

    }
}

void Viewer::draw()
{

  if (m_vertexSort.length() != 0)//si le viewer a récupéré le vecteur du MNT
  {

    glClear(GL_COLOR_BUFFER_BIT); // clear screen

    if (m_coordInterp.length() != 0)
    {

        if (m_coordInterp.length() >= 2 && m_vect1.length() == 0)
        {
            glLineWidth(1.0);
            glPointSize(5.0);
            glColor3f(1.0f, 0.0f, 0.0f);
            glBegin(GL_LINES);
            if (m_coordInterp.length() == 2)
            {
                glVertex3f(m_coordInterp[0].x(), m_coordInterp[0].y(), m_coordInterp[0].z());
                glVertex3f(m_coordInterp[1].x(), m_coordInterp[1].y(), m_coordInterp[1].z());
            }
            else
            {
                glVertex3f(m_coordInterp[0].x(), m_coordInterp[0].y(), m_coordInterp[0].z());
                glVertex3f(m_coordInterp[2].x(), m_coordInterp[2].y(), m_coordInterp[2].z());
            }
            glEnd();

            glBegin(GL_POINTS);
            if (m_coordInterp.length() == 2)
            {
                glVertex3f(m_coordInterp[0].x(), m_coordInterp[0].y(), m_coordInterp[0].z());
                glColor3f(1.0f, 0.0f, 0.0f);
                glVertex3f(m_coordInterp[1].x(), m_coordInterp[1].y(), m_coordInterp[1].z());
            }
            else
            {
                glVertex3f(m_coordInterp[0].x(), m_coordInterp[0].y(), m_coordInterp[0].z());
                glColor3f(1.0f, 0.0f, 0.0f);
                glVertex3f(m_coordInterp[2].x(), m_coordInterp[2].y(), m_coordInterp[2].z());
            }
            glEnd();

        }
        else//un seul point
        {
            glPointSize(10.0);
            glColor3f(0.0f, 0.0f, 1.0f);
            glBegin(GL_POINTS);
                glVertex3f(m_coordInterp[0].x(), m_coordInterp[0].y(), m_coordInterp[0].z());
            glEnd();

            glColor3f(1.0f, 0.0f, 0.0f);
            if (m_vect1.length() != 0)
            {
                for (int i(0); i<m_vect1.length(); i++)
                {
                    glBegin(GL_LINES);
                        glLineWidth(0.01);
                        glVertex3f(m_coordInterp[0].x(), m_coordInterp[0].y(), m_coordInterp[0].z());
                        glVertex3f(m_vect1[i].x(), m_vect1[i].y(), m_vect1[i].z());
                    glEnd();
                }
            }
        }
     }

   //Affichage du MNT
   glLineWidth(1.0);
   glEnableClientState(GL_VERTEX_ARRAY);//on indique à la carte graphique que l'on va travailler avec des vertex array
   glEnableClientState (GL_COLOR_ARRAY);
       glVertexPointer(3, GL_FLOAT, 0, m_vertexSort.constData());//on envoie le tableau de données à la carte graphique
       glColorPointer(3, GL_FLOAT, 0, m_tabColor.constData());
       glDrawArrays(GL_TRIANGLES, 0, m_vertexSort.size());//dessine les primitives
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);

}
}

void Viewer:: activateSelection()
{

    m_selectMode = true;
}

void Viewer:: setMode(bool visu){

    m_selectMode = visu;
}

void Viewer::mousePressEvent(QMouseEvent* const event)
 {
     qglviewer::Vec position_terrain;

     if(m_selectMode){
         qglviewer::Camera* const camera = this->camera();
         QPoint position_mouse;
         position_mouse.setX(event->x());
         position_mouse.setY(event->y());

         //cout << "Coorodonnées écran x : " << position_mouse.x() << ", y : " << position_mouse.y() << endl;
         bool found;
         position_terrain = camera->pointUnderPixel(position_mouse, found);

         if (found)
         {
             //cout << "coordonnées terrain: " << position_terrain.x << ", " << position_terrain.y << ", " << position_terrain.z << endl;
             pointClique.setX(float(position_terrain.x));
             pointClique.setY(float(position_terrain.y));
             pointClique.setZ(float(position_terrain.z));

             emit coordAinterpModif(pointClique);//signal pour changer les coordonnées des spinbox
         }
         else
         {
             cout << "la postion cherchée n'existe pas" << endl;
         }
     }
     else
     {
         QGLViewer::mousePressEvent(event);
     }
     m_selectMode=false;
     //return position_terrain;
 }

Viewer::~Viewer()
{

    //m_thread1.quit();
    //m_thread1.wait();
    //m_thread2.quit();
    //m_thread2.wait();
    //m_thread3.quit();
    //m_thread3.wait();
    //m_thread4.quit();
    //m_thread4.wait();

}


