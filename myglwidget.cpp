#include "myglwidget.h"
#include "triangle.h"
#include "mainwindow.h"

#include <cmath>
#include <QVector>
#include <QFileDialog>
#include <fstream>
#include <iostream>
#include <string>
#include <QIcon>
#include <limits>
#include <typeinfo>

using namespace std;



GL_Widget::GL_Widget(QWidget *parent) :
QGLWidget(parent)
{
    //std::string m_nameFile;
}

//Accesseurs et setteurs noms fichiers
std::string GL_Widget::getterNomFile() const
{
    return this->m_nameFile;
}

std::string GL_Widget::setterNomFile(std::string nom)
{
    m_nameFile = nom;
}

QVector<QVector3D> GL_Widget::getterTableau()
{
    return this->m_vector;
}

QVector<QVector3D> GL_Widget::setterTableau(QVector<QVector3D> vector)
{

    m_vector = vector;




    return m_vector;
}

void GL_Widget::initializeGL()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glEnable( GL_POINT_SMOOTH );
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glPointSize( 10.0 );
}

void GL_Widget::resizeGL(int width, int height)
{
    glViewport(0, 0, (GLint)width, (GLint)height);
}

void GL_Widget::paintGL()
{

    //glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
    //glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

//    double maxAbs = m_vector[0].x();
//    double maxOrd = m_vector[0].y();
//    double maxAlt = m_vector[0].z();

    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glBegin( GL_POINTS );
        glColor3f(1.0,1.0,1.0);
        /*
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

void GL_Widget::initiali
        }

        for ( int i = 0; i < m_vector.size(); i++)
        {

            glVertex3f(((float)m_vector[i].x())/(float)maxAbs,((float)m_vector[i].y())/(float)maxOrd,((float)m_vector[i].z())/(float)maxAlt);

        }
        */
        glEnd();

    // Previous code
/*    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glBegin(GL_POINTS);
        glColor3f(1.0,1.0,1.0);
        glVertex3f((float)1000/(float)2000, -0.5, 0.0);
        glVertex3f(0.0f, 0.0f, 0.0f);
    glEnd();
*/
}


QVector3D GL_Widget::readGL(){

    cout << m_nameFile << endl;

    //cout << m_vector[0] << endl;

    return m_vector[0];
}


