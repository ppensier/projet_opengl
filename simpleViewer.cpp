#include "plan.h"
#include "droite.h"

#include "simpleViewer.h"

#include <iostream>

using namespace std;
using namespace qglviewer;

/*
Viewer::Viewer(const QVector<QVector3D>& vector, const QVector<QVector2D>& vector_interp, QWidget *parent) :
QGLViewer(parent), m_vector(vector), m_coordInterp(vector_interp), vertices_by_x(4000)
{

}
*/

Viewer::Viewer(QVector<QVector3D>& vector, const QVector<QVector2D>& vector_interp, QWidget *parent) :
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

        double minimumX = m_vector[0].x();
        double minimumY = m_vector[m_vector.length()-1].y();

        for ( int i = 0; i<m_vector.length(); ++i)
        {
            //on norme les coordonnées du MNT
            m_vector[i].setX(m_vector[i].x() - minimumX);
            m_vector[i].setY(m_vector[i].y() - minimumY);

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

            //cout << m_vector[i].x() << endl;
            //cout << m_vector[i].x() - m_vector[0].x() << endl;

        }

        //definition du pas en y
        double pasY = m_vector[0].y() - m_vector[4000].y();

        cout << "le pas en Y est: " << pasY << endl;
        cout << "m_vector(x1): " << m_vector[5].x() << endl;
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

        const qglviewer::Camera* const camera = this->camera();

        const Vec& vectPos(float(1),float(0),float(0));
        //vectPos.setValue(0,0,0);

        //camera->setPosition(const Vec& target	);

        //m_texture_location = bindTexture(":/texture_sand_zoom.jpg");

        //QVector<Qvector2D> m_textures;
        QVector2D coordonnees;



    }
}

void Viewer::draw()
{

  drawAxis();

//  glBegin(GL_LINE_LOOP);
//      glColor3f(1.0f, 0.2f , 0.0f);
//      glVertex3f(m_vector[1].x(),m_vector[1].y(),m_vector[1].z());
//      glVertex3f(m_vector[10].x(),m_vector[10].y(),m_vector[10].z());
//      glVertex3f(m_vector[20].x(),m_vector[20].y(),m_vector[20].z());
//      glVertex3f(0.0, 0.0, 1.0);
//      glVertex3f(0.0, 0.0, 0.0);
//      glVertex3f(1.0, 0.0, 0.0);
//  glEnd();



  if (m_vector.length() != 0)
  {

    drawAxis();


    //glBindTexture(GL_TEXTURE_2D, m_texture_location);

    glClear(GL_COLOR_BUFFER_BIT); // clear screen
    glLineWidth(1);

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
    glEnableClientState (GL_COLOR_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, m_vertexSort.constData());//on envoie le tableau de données à la carte graphique
        glDrawArrays(GL_LINE_LOOP, 0, m_vertexSort.size());//dessine les primitives
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

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

bool Viewer::intervisibility(QVector3D pt1, QVector3D pt2)
{

    //premiere chose à faire: vérifier que les points ne sont pas sous terre


    int pasX = 25;
    int pasY = 25;

    double x1 = 0;
    double x2 = 0;
    double y1 = 0;
    double y2 = 0;

    droite d(pt1, pt2);//on construit la droite passant par les deux points

    d.afficherDroite();

    calculateAxis(pt1, pt2, x1, x2, y1, y2);

    cout << "les deux abscisses des deux droites sont: " << x1 << " et " << x2 << endl;
    cout << "les deux ordonnées des deux droites sont: " << y1 << " et " << y2  << endl;

    QVector3D vectNabs(1,0,0);
    QVector3D vectNord(0,1,0);
    QVector3D vectOblique(-0.5,-0.5,0);

    //parcours de toutes les abscisses
    for (int i(x1); i<=x2; i+=pasX)
    {
        //cout << "premiere ligne" << endl;

        plan p(QVector3D(i, y1, 0), vectNabs);

        //on récupère les coordonnées de l'intersection de la droite et du plan
        QVector3D intersect = d.calculIntersection(p);

        cout << "les coordonnées de l'intersection sont: " << intersect.x() << " et " << intersect.y() << endl;

        float altiPoint = compareAlti(intersect,0);

        cout << "toto1" << endl;
        cout << "l'altitude du point d'intersection est: " << altiPoint << " " << intersect.z() << endl;

        if (altiPoint > intersect.z())
            return false;
//            cout << "toto" << endl;
    }

    //Parcours des ordonnées
    for (int i(y1); i<=y2; i+=pasY)
    {
        plan p(QVector3D(x1, i, 0), vectNord);

        QVector3D intersect = d.calculIntersection(p);

        float altiPoint = compareAlti(intersect,1);

        cout << "toto2" << endl;
        cout << "l'altitude du point d'intersection est: " << altiPoint << " " << intersect.z() << endl;

        if (altiPoint > intersect.z())
            return false;
            //cout << "toto" << endl;
    }

    //Parcours des droites obliques
    for (int i(y1); i<=y2; i+=pasY)
    {
        plan p(QVector3D(x1, i, 0), vectOblique);

        QVector3D intersect = d.calculIntersection(p);

        float altiPoint = compareAlti(intersect,2);//code 2 pour les droites obliques

        if (altiPoint > intersect.z())
            return false;
            //cout << "toto" << endl;

    }

}


float Viewer::compareAlti(QVector3D intersect, int code)
{

    QVector3D pt1Cherche;
    QVector3D pt2Cherche;

    float altiPoint;
    //cout << "indice de l'abscisse: " << intersect.x()/25 << endl;

    //on récupère les deux points qui entourent le point d'intersection
    int resY = intersect.y()/25;
    int resX = intersect.x()/25;

    switch (code)
    {
        case 0: {//on teste les droites verticales

        int valeurSup = (resY+1)*25;
        int valeurInf = resY*25;

        for (int j(0); j<=m_vector.length(); j += 4000)
        {
            if (m_vector[j].y() == valeurSup)
            {
                pt1Cherche.setX(float(intersect.x()));
                pt1Cherche.setY(float(valeurSup));
                pt1Cherche.setZ(m_vector[j].z());

                pt2Cherche.setX(float(intersect.x()));
                pt2Cherche.setY(float(valeurInf));
                pt2Cherche.setZ(m_vector[j+4000].z());

            }
        }

        //cout << "les cooordonnées du premier point sont: " << pt1Cherche.x() << " " << pt1Cherche.y() << " " << pt1Cherche.z() << endl;
        //cout << "les cooordonnées du deuxieme point sont: " << pt2Cherche.x() << " " << pt2Cherche.y() << " " << pt2Cherche.z() << endl;

        //puis on calcule les coordonnées de l'altitude du point situé sur la droite
        droite di(pt1Cherche, pt2Cherche);

        float lambdaDroite = (intersect.y() - di.b2)/di.a2;

        altiPoint = ((di.a3)*lambdaDroite) + di.b3;

        }

        case 1: {//on teste les droites horizontales

            int valeurSup = (resX+1)*25;
            int valeurInf = resX*25;

            for (int j(0); j<=4000; j++)
            {
                if (m_vector[j].x() == valeurInf)
                {
                    pt1Cherche.setX(float(valeurInf));
                    pt1Cherche.setY(float(intersect.y()));
                    pt1Cherche.setZ(m_vector[j].z());

                    pt2Cherche.setX(float(valeurSup));
                    pt2Cherche.setY(float(intersect.y()));
                    pt2Cherche.setZ(m_vector[j+1].z());

                }
            }

            droite di(pt1Cherche, pt2Cherche);

            float lambdaDroite = (intersect.x() - di.b1)/di.a1;

            altiPoint = ((di.a3)*lambdaDroite) + di.b3;

        }

        case 2: {

            int valeurSup = (resX+1)*25;
            int valeurInf = resX*25;

            for (int j(0); j<=4000; j++)
            {
                if (m_vector[j].x() == valeurSup)

                {

                    pt1Cherche.setX(valeurSup);
                    pt1Cherche.setY(m_vector[j].y());//on choisit le y du point en question
                    pt1Cherche.setZ(m_vector[j].z());

                    pt2Cherche.setX(valeurInf);
                    pt2Cherche.setY(m_vector[j+4000].y());
                    pt2Cherche.setZ(m_vector[j+4000-1].y());

                }
            }

            droite di(pt1Cherche, pt2Cherche);

            float lambdaDroite = (intersect.x() - di.b1)/di.a1;

            altiPoint = ((di.a3)*lambdaDroite) + di.b3;

        }

    }


    return altiPoint;

}

