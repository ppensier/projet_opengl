#include "plan.h"
#include "droite.h"

#include "simpleViewer.h"

#include <iostream>

using namespace std;
using namespace qglviewer;

Viewer::Viewer(QVector<QVector3D>& vector, QVector<QVector3D>& vector_interp, QWidget *parent) :
QGLViewer(parent), m_vector(vector), m_coordInterp(vector_interp), tabColor(m_vector.length())
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

        computeLineLength();
        double pasY = m_vector[0].y() - m_vector[vertices_by_x].y();
        double pasX = m_vector[1].x() - m_vector[0].x();
        cout << "le pas en x est de: " << pasX << ", le pas en y est de: " << pasY << endl;
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

        }

        //on trie les points
        for (int i(0); i<m_vector.length()-vertices_by_x; i++)
        {
            //premier triangle
            m_vertexSort.push_back(m_vector[i]);
            m_vertexSort.push_back(m_vector[i+vertices_by_x]);
            m_vertexSort.push_back(m_vector[i+1]);

            //si l'on atteint la fin de la ligne, on revient en arrière

            if ((i+1)%vertices_by_x == vertices_by_x-1 && (i+1) != m_vector.length()-vertices_by_x) //i+1 est au bout de la ligne
            {
                //cout << ligne << endl;
                //cout << "vous êtes à la ligne: " << ligne << endl;
                for (int j = i+1+vertices_by_x; j > i + 1; j--)
                {
                    m_vertexSort.push_back(m_vector[j]);
                }
                i++;
            }

            //deuxième triangle
//            m_vertexSort.push_back(m_vector[i+1]);
//            m_vertexSort.push_back(m_vector[i+vertices_by_x]);
//            m_vertexSort.push_back(m_vector[i+1+vertices_by_x]);

        }

        //tableau de couleurs
        tabColor.clear();
        tabColor.resize(m_vertexSort.length());
        for ( int i = 0; i<m_vertexSort.length(); ++i)
        {
            tabColor[i].setX(0);
            tabColor[i].setY((m_vertexSort[i].z()-minCoord.z) / (maxCoord.z -minCoord.z));
            tabColor[i].setZ(0);
        }

        if (m_coordInterp.length() != 0)
        {
            cout << "INTERPOLATION: " << m_coordInterp.length() << endl;
        }

        //cout << m_coordInterp[0].x() << " " << m_coordInterp[0].y() << " " << m_coordInterp[1].x() << " " << m_coordInterp[1].y() << endl;

        //cout << m_vertexSort[0].x() << " " << m_vertexSort[1].x() << " " << m_vertexSort[2].x() << endl;
        //cout << "min : " << minCoord.x << " " << minCoord.y << " " << minCoord.z << endl;

        //cout << m_vector[2].x() << " " << m_vector[2+vertices_by_x].x() << endl;

        //cout << "min en x: " << minCoord.x << endl;
        //cout << "max en x: " << maxCoord.x << endl;

        setSceneBoundingBox(minCoord, maxCoord);
        showEntireScene();      

        const qglviewer::Camera* const camera = this->camera();

        const Vec vectPos(0,0,0);

        //if (m_coordInterp.length() != 0)
            //camera->setPosition(m_coordInterp[0]);

    }
}


void Viewer::computeLineLength()
{
    const unsigned long NOT_COMPUTED = 0;
    unsigned long lineLength_prec = NOT_COMPUTED;
    vertices_by_x = 1;
    m_nbLines = 1;

    // at each loop, m_lineLenght takes 1 if "m_vertices[i].y == m_vertices[i+1].y".
    // m_lineLenght begin at 1.
    for(unsigned long i = 0 ; i < m_vector.size()-1; ++i, ++vertices_by_x)
    {
          // when "m_vertices[i].y != m_vertices[i+1].y", we compare m_lineLenght and lineLenght_prec
          // to see if they have the same number of points.
          if (m_vector[i].y() != m_vector[i+1].y())
          {
              if(vertices_by_x != lineLength_prec)
                  cout << "Lines " << i << " and " << i+1 << " don't have the same length.";

             lineLength_prec = vertices_by_x;
             vertices_by_x = 0;
             ++m_nbLines;
          }
    }

    vertices_by_x = lineLength_prec;
    cout << "la longueur d'une ligne est de : " << vertices_by_x << endl;
    cout << "il y a : " << m_nbLines << " lignes" << endl;
}


void Viewer::draw()
{

  drawAxis();
//  glLineWidth(100.0);
//  glBegin(GL_LINES);
//      glColor3f(1.0f, 0.0f, 0.0f);
//      glVertex3f(0,0,0);
//      glVertex3f(1,1,1);
//  glEnd();

  if (m_vector.length() != 0)
  {

      drawAxis();

//    glColor3f(1.0f, 0.0f , 0.0f);
//    glLineWidth(50.0);
//    glBegin(GL_LINE);
//        glVertex3f(m_vector[0].x(), m_vector[0].y(), m_vector[0].z());
//        glVertex3f(m_vector[1].x(), m_vector[1].y(), m_vector[1].z());

//    glEnd();

//    glBegin(GL_POINT);
//    glPointSize(50);
//    glColor3f(1.0f, 0.0f , 0.0f);
//        glVertex3f(m_vector[1].x(), m_vector[1].y(), m_vector[1].z());
//    glEnd();

    glClear(GL_COLOR_BUFFER_BIT); // clear screen
    //glLineWidth(1);

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
    glLineWidth(1.0);
    glEnableClientState(GL_VERTEX_ARRAY);//on indique à la carte graphique que l'on va travailler avec des vertex array
    glEnableClientState (GL_COLOR_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, m_vertexSort.constData());//on envoie le tableau de données à la carte graphique
        glColorPointer(3, GL_FLOAT, 0, tabColor.constData());
        glDrawArrays(GL_LINE_STRIP, 0, m_vertexSort.size());//dessine les primitives
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    if (m_coordInterp.length() != 0)
    {
    glLineWidth(1.0);
    glPointSize(5.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
        //glVertex3d(m_vector[0].x(), m_vector[0].y(), m_vector[0].z());
        //glVertex3d(m_vector[m_vector.length()-1].x(), m_vector[m_vector.length()-1].y(), m_vector[m_vector.length()-1].z());
        glVertex3f(m_coordInterp[0].x(), m_coordInterp[0].y(), m_coordInterp[0].z());
        glVertex3f(m_coordInterp[1].x(), m_coordInterp[1].y(), m_coordInterp[1].z());
    glEnd();

    glBegin(GL_POINTS);
        glVertex3f(m_coordInterp[0].x(), m_coordInterp[0].y(), m_coordInterp[0].z());
        glVertex3f(m_coordInterp[1].x(), m_coordInterp[1].y(), m_coordInterp[1].z());
    glEnd();

    }

//    if (m_coordInterp.length() != 0)
//    {
//        //cout << "DRAW INTERPOLATION: " << m_coordInterp.length() << endl;
//        glBegin(GL_LINE);
//            glLineWidth(50.0);
//            glColor3f(1.0f, 0.0f, 0.0f);
//            glVertex3f(m_coordInterp[0].x(), m_coordInterp[0].y(), m_coordInterp[0].z());
//            glVertex3f(m_coordInterp[1].x(), m_coordInterp[1].y(), m_coordInterp[1].z());
//        glEnd();

    //}

  }
}

bool Viewer::intervisibility(QVector3D pt1, QVector3D pt2)
{

    double x1 = 0;
    double x2 = 0;
    double y1 = 0;
    double y2 = 0;

    droite d(pt1, pt2);//on construit la droite passant par les deux points

    d.afficherDroite();

    calculateAxis(pt1, pt2, x1, x2, y1, y2);

    cout << "les deux abscisses des deux droites sont: " << x1 << " et " << x2 << endl;
    cout << "les deux ordonnées des deux droites sont: " << y1 << " et " << y2  << endl;

    //premiere chose à faire: vérifier que les points ne sont pas sous terre
    if (computeSousTerre(pt1))
    {
        cout << "le premier point n'est pas sous terre" << endl;
    }
    else
    {
        cout << "le premier point est sous terre" << endl;
        return false;
    }

    if (computeSousTerre(pt2))
    {
        cout << "le deuxieme point n'est pas sous terre" << endl;
    }
    else
    {
        cout << "le deuxieme point est sous terre" << endl;
        return false;
    }


    QVector3D vectNabs(1,0,0);
    QVector3D vectNord(0,1,0);
    QVector3D vectOblique(1,-1,0);

    //PARCOURS DES ABSCISSES (= les droites verticales)
    //cout << "pasX: " << 25 << endl;

    for (int i(x1); i<=x2; i+=25)
    {
        plan p(QVector3D(i, y1, 0), vectNabs);

        if (d.position(p) == 2)//i.e la droite appartient au plan
        {
            //on cherche si l'altitude d'un point sur la droite est supérieure à l'altitude d'un des deux points
            //la droite a pour coordonnées x1
            for (int j(y1/25); j<=y2/25; j+=vertices_by_x)
            {
                if (m_vector[j].z() > pt1.z() || m_vector[j].z() > pt2.z())
                {
                    cout << " Arrêt droite appartient au plan " << endl;
                    return false;
                }

            }

        }

        //droite parallèle au plan verticaux
        else if(d.position(p) == 1 && ((int)pt1.x()%25) != 0)//si la droite est parallèle aux plans et n'est pas un plan vertical
        {
            //on bascule sur les verifications des ordonnées
            for (int j(y1); j<=y2; j+=25)
            {
                plan p(QVector3D(x1, j, 0), vectNord);

                QVector3D intersect = d.calculIntersection(p);

                //cout << "test2" << endl;
                float altiPoint = compareAlti(intersect,1);

                if (altiPoint > intersect.z())
                {
                    cout << "arrêt droite parallèle" << endl;
                    return false;
                }

            }

        }

        else
        {
            QVector3D intersect = d.calculIntersection(p);
            float altiPoint = compareAlti(intersect,0);
            //cout << altiPoint << " " << intersect.z() << endl;
            if (altiPoint > intersect.z())
            {
                cout << "pas de visibilité sur le parcours des abscisses!" << endl;
                return false;
            }
        }

//        else//droite en configuration normale
//        {
            //on récupère les coordonnées de l'intersection de la droite et du plan
            //QVector3D intersect = d.calculIntersection(p);

            //cout << "les coordonnées de l'intersection sont: " << intersect.x() << " et " << intersect.y() << endl;

            //cout << "test1" << endl;
            //float altiPoint = compareAlti(intersect,0);

            //cout << "toto1" << endl;
            //cout << "l'altitude du point d'intersection est: " << altiPoint << " " << intersect.z() << endl;

            //cout << altiPoint << " " << intersect.z() << endl;
            //if (altiPoint > intersect.z())
            //{
            //    cout << "parcours des abscisses!" << endl;
            //    return false;
            //}
//        }

    }

  //PARCOURS DES ORDONNEES (=les droites horizontales)
    //cout << "Parcours des ordonnées" << endl;

    for (int i(y1); i<=y2; i+=25)
    {
        plan p(QVector3D(x1, i, 0), vectNord);
        QVector3D intersect = d.calculIntersection(p);
        //cout << y1 << " " << y2 << " " << "pasY: " << 25 << "pasX: " << 25 << endl;
        float altiPoint = compareAlti(intersect,1);
        //cout << altiPoint << " " << intersect.z() << endl;
        if (altiPoint > intersect.z())
        {
            cout << "pas de visibilité sur le parcours des ordonnées!" << endl;
            return false;
        }

    }

    cout << "fin du parcours des ordonnées" << endl;

//        if (d.position(p) == 2)//i.e la droite appartient au plan
//        {
//            for (int j(x1/pasX); j<=x2/pasX; j++)
//            {
//                if (m_vector[j].z() > pt1.z() || m_vector[j].z() > pt2.z())
//                {
//                    return false;
//                }
//
//            }
//
//        }

//        else if (d.position(p) == 1 && ((int)pt1.y()%pasY) != 0)//si la droite est parallèle et n'est pas un multiple de 25
//        {
//
//            //on bascule sur les verifications des abscisses
//            for (int j(x1); j<=x2; j+=pasX)
//            {
//                plan p(QVector3D(x1, j, 0), vectNord);
//
//                QVector3D intersect = d.calculIntersection(p);
//
//                //cout << "test2" << endl;
//                float altiPoint = compareAlti(intersect,1);
//
//                //cout << "toto2" << endl;
//                //cout << "l'altitude du point d'intersection est: " << altiPoint << " " << intersect.z() << endl;
//
//                if (altiPoint > intersect.z())
//                    return false;
//
//            }
//
//        }

//        else
//        {

//            QVector3D intersect = d.calculIntersection(p);
//
//            cout << "test2" << endl;
//            float altiPoint = compareAlti(intersect,1);
//
//            if (altiPoint > intersect.z())
//                return false;
//        }

//    }

    //PARCOURS DES DROITES OBLIQUES
    cout << "limites du plan: " << x1 << " " << x2 << " " << y1 << " " << y2 << endl;
    for (int i(y1); i<=y2; i+=25)
    {
        plan p(QVector3D(x1, i, 0), vectOblique);
        //cout << x1 << " " << i << endl;
        //p.afficherPlan();
        QVector3D intersect = d.calculIntersection(p);
        //if ((x1 <= intersect.x() <= x2) && (y1 <= intersect.y() <= y2))
        //cout << "coordonnées de l'INTERSECTION: " << intersect.x() << " " << intersect.y() << " " << intersect.z() << endl;
        if (x1 <= intersect.x() && intersect.x() <= x2 && y1 <= intersect.y() && intersect.y() <= y2)
        {
            //cout << "coordonnées de l'INTERSECTION: " << intersect.x() << " " << intersect.y() << " " << intersect.z() << endl;
            //cout << "les coordonnées de l'intersection sont: " << intersect.x() << " et " << intersect.y() << endl;

            float altiPoint = compareAlti(intersect,2);//code 2 pour les droites obliques
            //cout << "l'altitude du point d'intersection est: " << altiPoint << " " << intersect.z() << endl;
            //    cout << "toto " << altiPoint << " " << intersect.z() << endl;
            if (altiPoint > intersect.z())
            {
                cout << "pas de visibilité sur le parcours des droites obliques!" << endl;
                return false;
            }

        }
    }
    cout << "fin de parcours des droites obliques" << endl;

}

//cette fonction retourne l'altitude du point de la droite correspond à l'intersection
float Viewer::compareAlti(QVector3D intersect, int code)
{

    QVector3D pt1Cherche;
    QVector3D pt2Cherche;

    float altiPoint;
    //cout << "indice de l'abscisse: " << intersect.x()/25 << endl;

    //on récupère les deux points qui entourent le point d'intersection
    int resY = intersect.y()/25;
    int resX = intersect.x()/25;

    //switch (code)
    //{
        //case 0: {//on teste les droites verticales
        if (code == 0)
        {

            int valeurSupX = (resX+1)*25;
            int valeurInfX = resX*25;
            int valeurSupY = (resY+1)*25;
            int valeurInfY = resY*25;

            //for (int j(0); j<=m_vector.length(); j += vertices_by_x)
            for (int j(0); j<=m_vector.length(); j += 1)
            {
                if (m_vector[j].y() == valeurSupY && m_vector[j].x() == intersect.x())
                {

                    //cout << "intersection: " << intersect.x() << " " << valeurSupY << " indice: " << j << endl;
                    //cout << m_vector[j].x() << " " << valeurSupY << " " << m_vector[j].z() << endl;

                    pt1Cherche.setX(float(intersect.x()));
                    pt1Cherche.setY(float(valeurSupY));
                    pt1Cherche.setZ(m_vector[j].z());

                    pt2Cherche.setX(float(intersect.x()));
                    pt2Cherche.setY(float(valeurInfY));
                    pt2Cherche.setZ(m_vector[j+vertices_by_x].z());
                    break;
                }
            }

            //cout << "teste les droites verticales" << endl;
            //cout << "le premier point cherché est: " << pt1Cherche.x() << " " << pt1Cherche.y() << " " << pt1Cherche.z() << endl;
            //cout << "le deuxieme point cherché est: " << pt2Cherche.x() << " " << pt2Cherche.y() << " " << pt2Cherche.z() << endl;

            //puis on calcule les coordonnées de l'altitude du point situé sur la droite
            droite di(pt1Cherche, pt2Cherche);

            float lambdaDroite = (intersect.y() - di.b2)/di.a2;

            altiPoint = ((di.a3)*lambdaDroite) + di.b3;

        }

        //case 1: {//on teste les droites horizontales
        else if (code == 1)
        {

            //cout << "ne doit pas rentrer ici!" << endl;

            int valeurSup = (resX+1)*25;
            int valeurInf = resX*25;

            cout << intersect.y() << " " << m_vector[9503].y() << endl;

            for (int j(0); j<=m_vector.length(); j++)
            {
                if (m_vector[j].x() == valeurInf && m_vector[j].y() == 100)
                {
                    //cout << "intersection: " << intersect.x() << " " << valeurSup << " indice: " << j << endl;
                    //cout << m_vector[j].x() << " " << m_vector[j].y() << " " << m_vector[j].z() << endl;

                    pt1Cherche.setX(float(valeurInf));
                    pt1Cherche.setY(float(intersect.y()));
                    pt1Cherche.setZ(m_vector[j].z());

                    pt2Cherche.setX(float(valeurSup));
                    pt2Cherche.setY(float(intersect.y()));
                    pt2Cherche.setZ(m_vector[j+1].z());
                    break;
                }
            }

            //cout << "teste les droites horizontales" << endl;
            //cout << "coordonnées de l'intersection: " << intersect.x() << " " << intersect.y() << endl;
            //cout << "le premier point cherché est: " << pt1Cherche.x() << " " << pt1Cherche.y() << " " << pt1Cherche.z() << endl;
            //cout << "le deuxieme point cherché est: " << pt2Cherche.x() << " " << pt2Cherche.y() << " " << pt2Cherche.z() << endl;

            droite di(pt1Cherche, pt2Cherche);

            float lambdaDroite = (intersect.x() - di.b1)/di.a1;

            altiPoint = ((di.a3)*lambdaDroite) + di.b3;

        }

        //case 2: {//teste les droites obliques
        else if (code == 2)
        {
            int valeurSupX = (resX+1)*25;
            int valeurInfX = resX*25;
            int valeurSupY = (resY+1)*25;
            int valeurInfY = resY*25;

            for (int j(0); j<m_vector.length(); j++)
            {
                if (m_vector[j].x() == valeurSupX && m_vector[j].y() == valeurSupY)

                {

                    //cout << "intersection: " << intersect.x() << " " << valeurSup << " indice: " << j << endl;
                    //cout << m_vector[j].x() << " " << m_vector[j].y() << " " << m_vector[j].z() << endl;

                    pt1Cherche.setX(valeurSupX);
                    pt1Cherche.setY(valeurSupY);//on choisit le y du point en question
                    pt1Cherche.setZ(m_vector[j].z());

                    pt2Cherche.setX(valeurInfX);
                    pt2Cherche.setY(valeurInfY);
                    pt2Cherche.setZ(m_vector[j+vertices_by_x-1].z());
                    break;

                }
            }

            //cout << "teste les droites obliques" << endl;
            //cout << "le premier point cherché est: " << pt1Cherche.x() << " " << pt1Cherche.y() << " " << pt1Cherche.z() << endl;
            //cout << "le deuxieme point cherché est: " << pt2Cherche.x() << " " << pt2Cherche.y() << " " << pt2Cherche.z() << endl;

            droite di(pt1Cherche, pt2Cherche);

            float lambdaDroite = (intersect.x() - di.b1)/di.a1;

            altiPoint = ((di.a3)*lambdaDroite) + di.b3;

        }

    //}

    return altiPoint;

}



bool Viewer::computeSousTerre(QVector3D pt1)
{
    QVector3D pt1Cherche;
    QVector3D pt2Cherche;
    QVector3D pt3Cherche;
    QVector3D pt4Cherche;


    int resY = pt1.y()/25;
    int resX = pt1.x()/25;

    int valeurSupX = (resX+1)*25;
    int valeurInfX = resX*25;
    int valeurSupY = (resY+1)*25;
    int valeurInfY = resY*25;

    for (int i(0); i<=m_vector.length(); i++)
    {
        if (m_vector[i].y() == valeurSupY && m_vector[i].x() == valeurInfX)
        {
            pt1Cherche.setX(float(valeurInfX));
            pt1Cherche.setY(float(valeurSupY));
            pt1Cherche.setZ(m_vector[i].z());

            pt2Cherche.setX(float(valeurSupX));
            pt2Cherche.setY(float(valeurSupY));
            pt2Cherche.setZ(m_vector[i+1].z());

            pt3Cherche.setX(float(valeurInfX));
            pt3Cherche.setY(float(valeurInfY));
            pt3Cherche.setZ(m_vector[i+vertices_by_x].z());

            pt4Cherche.setX(float(valeurSupX));
            pt4Cherche.setY(float(valeurInfY));
            pt4Cherche.setZ(m_vector[i+vertices_by_x+1].z());
            break;
        }
    }

    //cout << resX << " " << resY << " " << pasX << " " << pasY << endl;
    //cout << "valeurs sup: " << valeurInfX << " " << valeurSupX << " " << valeurInfY << " " << valeurSupY << endl;
    //cout << "le premier cherché est: " << pt1Cherche.x() << " " << pt1Cherche.y() << " " << pt1Cherche.z() << endl;
    //cout << "le deuxième cherché est: " << pt2Cherche.x() << " " << pt2Cherche.y() << " " << pt2Cherche.z() << endl;
    //cout << "le troisieme cherché est: " << pt3Cherche.x() << " " << pt3Cherche.y() << " " << pt3Cherche.z() << endl;
    //cout << "le quatrieme cherché est: " << pt4Cherche.x() << " " << pt4Cherche.y() << " " << pt4Cherche.z() << endl;

    //float distance[4] = {pt1.distanceToPoint(pt1Cherche), pt1.distanceToPoint(pt2Cherche), pt1.distanceToPoint(pt3Cherche), pt1.distanceToPoint(pt4Cherche)};

    float distance1 = pt1.distanceToPoint(pt1Cherche);
    float distance2 = pt1.distanceToPoint(pt4Cherche);

    double alti;

    if (distance1 < distance2)
    {
        plan p(pt1Cherche, pt2Cherche, pt3Cherche);
        p.afficherPlan();
        alti = (-(p.a*pt1.x())-(p.b*pt1.y())-p.d)/p.c;
        cout << alti << endl;
    }
    else
    {
        plan p(pt4Cherche, pt2Cherche, pt3Cherche);
        p.afficherPlan();
        alti = (-(p.a*pt1.x())-(p.b*pt1.y())-p.d)/p.c;
        cout << alti << endl;
    }

    cout << "DIFFERENCE: " << alti << " " << pt1.z() << endl;

    if (pt1.z()>alti)//le point est au dessus de la surface
        return true;
    else
        return false;

}
