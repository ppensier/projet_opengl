#include "mnt.h"
#include "qmutex.h"

using namespace std;


MNT::MNT(QVector<QVector3D>& vector, QVector<QVector3D>& vector_interp, double& distMax, int vertices):
m_vector(vector), m_coordInterp(vector_interp), distanceTir(distMax),vertices_by_x(vertices)
{

}

void MNT::computeLineLength()
{
    const unsigned long NOT_COMPUTED = 0;
    unsigned long lineLength_prec = NOT_COMPUTED;
    vertices_by_x = 1;
    m_nbLines = 1;

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
}

void MNT::computeExtremes()
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
        int pasY = m_vector[0].y() - m_vector[vertices_by_x].y();
        int pasX = m_vector[1].x() - m_vector[0].x();
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
    }

}

//fonction de trie des points, pour dessiner le MNT
void MNT::trierPoints()
{
    for (int i(0); i<m_vector.length()-vertices_by_x; i++)
    {
        //premier triangle
        m_vertexSort.push_back(m_vector[i]);
        m_vertexSort.push_back(m_vector[i+vertices_by_x]);
        m_vertexSort.push_back(m_vector[i+1]);

        //si l'on atteint la fin de la ligne, on revient en arrière

        if ((i+1)%vertices_by_x == vertices_by_x-1 && (i+1) != m_vector.length()-vertices_by_x) //i+1 est au bout de la ligne
        {
            for (int j = i+1+vertices_by_x; j > i + 1; j--)
            {
                if ((j-1)!=(i+1))
                {
                    m_vertexSort.push_back(m_vector[j]);
                    m_vertexSort.push_back(m_vector[j-vertices_by_x]);
                    m_vertexSort.push_back(m_vector[j-1]);
                }
            }
            i++;//on passe à ligne suivante
        }
    }
}

void MNT::computeColorTable()
{

    //tableau de couleurs
    m_tabColor.clear();
    m_tabColor.resize(m_vertexSort.length());
    for ( int i = 0; i<m_vertexSort.length(); ++i)
    {

        if(m_vertexSort[i].z()<=1300)
                   {
                   m_tabColor[i].setX(((m_vertexSort[i].z()-318) / (1300 -318))*0.);
                   m_tabColor[i].setY(((m_vertexSort[i].z()-318) / (1300 -318))*0.4);
                   m_tabColor[i].setZ(((m_vertexSort[i].z()-318) / (1300 -318))*0.6);
                   }



           if(m_vertexSort[i].z()<2286 && m_vertexSort[i].z()>1300)
                   {
                   m_tabColor[i].setX(((m_vertexSort[i].z()-1300) / (2286 -1300))*0.2798);
                   m_tabColor[i].setY(((m_vertexSort[i].z()-1300) / (2286 -1300))*0.4815);
                   m_tabColor[i].setZ(((m_vertexSort[i].z()-1300) / (2286 -1300))*0.2387);
                   }


           if(m_vertexSort[i].z()<3300 && m_vertexSort[i].z()>=2286)
                   {
                   m_tabColor[i].setX(((m_vertexSort[i].z()-2286) / (3300 -2286))*0.3333);
                   m_tabColor[i].setY(((m_vertexSort[i].z()-2286) / (3300 -2286))*0.3333);
                   m_tabColor[i].setZ(((m_vertexSort[i].z()-2286) / (3300 -2286))*0.3333);
                   }

    }
}


//Fonction pour déterminer si le(s) point(s) sont sont terre ou non
bool MNT::computeSousTerre(QVector3D pt1)
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

    for (int i(0); i<=m_vector.length()-1; i++)
    {
        if (m_vector[i].y() == valeurSupY && m_vector[i].x() == valeurInfX)
        {

            //cout << "TEST: " << float(valeurInfX) << " " << float(valeurSupY) << " " << endl;
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


    float distance1 = pt1.distanceToPoint(pt1Cherche);
    float distance2 = pt1.distanceToPoint(pt4Cherche);

    float alti;

    if (distance1 < distance2)
    {
        plan p(pt1Cherche, pt2Cherche, pt3Cherche);
        alti = (-(p.a*pt1.x())-(p.b*pt1.y())-p.d)/p.c;
        //cout << "alti:" << alti << " " << p.c << endl;
    }
    else
    {
        plan p(pt4Cherche, pt2Cherche, pt3Cherche);
        alti = (-(p.a*pt1.x())-(p.b*pt1.y())-p.d)/p.c;
        //cout << "alti:" << alti << " " << p.c << endl;
    }

    if (pt1.z() >= alti)//le point est au dessus de la surface
        return true;
    else
        return false;


}


//cette fonction retourne l'altitude du point de la droite correspond à l'intersection
float MNT::compareAlti(QVector3D intersect, int code)
{

    QVector3D pt1Cherche;
    QVector3D pt2Cherche;

    float altiPoint;
    //cout << "indice de l'abscisse: " << intersect.x()/25 << endl;

    //on récupère les deux points qui entourent le point d'intersection
    int resY = intersect.y()/25;
    int resX = intersect.x()/25;
        if (code == 0)
        {

            int valeurSupY = (resY+1)*25;
            int valeurInfY = resY*25;

            for (int j(0); j<=m_vector.length()-vertices_by_x-1; j += 1)
            {
                if (m_vector[j].y() == valeurSupY && m_vector[j].x() == intersect.x())
                {


                    pt1Cherche.setX(float(intersect.x()));
                    pt1Cherche.setY(float(valeurSupY));
                    pt1Cherche.setZ(m_vector[j].z());

                    pt2Cherche.setX(float(intersect.x()));
                    pt2Cherche.setY(float(valeurInfY));
                    pt2Cherche.setZ(m_vector[j+vertices_by_x].z());
                    break;
                }
            }


            //puis on calcule les coordonnées de l'altitude du point situé sur la droite
            droite di(pt1Cherche, pt2Cherche);

            float lambdaDroite = (intersect.y() - di.b2)/di.a2;

            altiPoint = ((di.a3)*lambdaDroite) + di.b3;

        }

        else if (code == 1)
        {


            int valeurSupX = (resX+1)*25;
            int valeurInfX = resX*25;

            for (int j(0); j<=m_vector.length()-1; j++)
            {
                if (m_vector[j].x() == valeurInfX && m_vector[j].y() == intersect.y())
                {

                    pt1Cherche.setX(float(valeurInfX));
                    pt1Cherche.setY(float(intersect.y()));
                    pt1Cherche.setZ(m_vector[j].z());

                    pt2Cherche.setX(float(valeurSupX));
                    pt2Cherche.setY(float(intersect.y()));
                    pt2Cherche.setZ(m_vector[j+1].z());
                    break;
                }
            }

            droite di(pt1Cherche, pt2Cherche);

            float lambdaDroite = (intersect.x() - di.b1)/di.a1;

            altiPoint = ((di.a3)*lambdaDroite) + di.b3;

        }

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

                    pt1Cherche.setX(valeurSupX);
                    pt1Cherche.setY(valeurSupY);//on choisit le y du point en question
                    pt1Cherche.setZ(m_vector[j].z());

                    pt2Cherche.setX(valeurInfX);
                    pt2Cherche.setY(valeurInfY);
                    pt2Cherche.setZ(m_vector[j+vertices_by_x-1].z());
                    break;

                }
            }

            droite di(pt1Cherche, pt2Cherche);

            float lambdaDroite = (intersect.x() - di.b1)/di.a1;

            altiPoint = ((di.a3)*lambdaDroite) + di.b3;

        }

    return altiPoint;
}


//Fonction de calcul de l'intervisibilité pour deux points
bool MNT::intervisibility(QVector3D pt1, QVector3D pt2)
{

    bool result = true;

    double x1 = 0;
    double x2 = 0;
    double y1 = 0;
    double y2 = 0;

    droite d(pt1, pt2);//on construit la droite passant par les deux points

    calculateAxis(pt1, pt2, x1, x2, y1, y2);



    //premiere chose à faire: vérifier que les points ne sont pas sous terre

    if (computeSousTerre(pt1))
    {
        //cout << "le premier point n'est pas sous terre" << endl;
    }
    else
    {
        //cout << "le premier point est sous terre" << endl;
        result = false;
    }

    if (computeSousTerre(pt2))
    {
        //cout << "le deuxieme point n'est pas sous terre" << endl;
    }
    else
    {
        //cout << "le deuxieme point est sous terre" << endl;
        result = false;
    }

    //cout << "fin du calcul sous terre" << endl;

    QVector3D vectNabs(1,0,0);
    QVector3D vectNord(0,1,0);
    QVector3D vectOblique(1,-1,0);


    //PARCOURS DES ABSCISSES (= les droites verticales)
    for (int i(x1); i<=x2; i+=25)
    {
        plan p(QVector3D(i, y1, 0), vectNabs);

        if (d.position(p) == 2)//i.e la droite appartient au plan
        {
            //cout << "la droite considérée appartient au plan!" << endl;
            //on cherche si l'altitude d'un point sur la droite est supérieure à l'altitude d'un des deux points
            int indice = (i/25)+m_vector.length()-(((y1/25)+1)*vertices_by_x);
            //cout << ((y1/25)+1)*vertices_by_x << endl;
            //cout << m_vector.length() << endl;
            //cout << i/25 << endl;
            //cout << "result: " << (i/25)+m_vector.length()-(((y1/25)+1)*vertices_by_x) << endl;
            //cout << indice << " " <<m_vector[indice].y() << " " << y1 << endl;
            while (indice >= y1)
            {
                //cout << "indice: " << indice << " altitude: " << m_vector[indice].z() << endl;
                if (m_vector[indice].z() > pt1.z() || m_vector[indice].z() > pt2.z())
                {
                    //cout << " Arrêt droite appartient au plan " << m_vector[indice].y() << endl;
                    result = false;
                    //return false;
                }
                indice-=vertices_by_x;
            }
            break;
        }

        //droite parallèle au plan verticaux
        else if(d.position(p) == 1 && ((int)pt1.x()%25) != 0)//si la droite est parallèle aux plans et n'est pas un plan vertical
        {
            //on bascule sur les verifications des ordonnées
            d.afficherDroite();
            for (int i(y1); i<=y2; i+=25)
            {
                plan p(QVector3D(x1, i, 0), vectNord);
                //p.afficherPlan();
                QVector3D intersect = d.calculIntersection(p);
                float altiPoint = compareAlti(intersect,1);
                //cout << altiPoint << endl;
                //cout << intersect.y() << " " << altiPoint << " " << intersect.z() << endl;
                if (altiPoint > intersect.z())
                {
                    //cout << "pas de visibilité sur le parcours des ordonnées!" << endl;
                    result = false;
                    //return false;
                }
            }
            break;
        }

        else
        {
            QVector3D intersect = d.calculIntersection(p);
            float altiPoint = compareAlti(intersect,0);
            //cout <<  "ALTI: " << altiPoint << " " << intersect.z() << endl;
            if (altiPoint > intersect.z())
            {
                //cout << "pas de visibilité sur le parcours des abscisses!" << endl;
                result = false;
                //return false;
            }
        }

    }
    //cout << "Fin de parcours des abscisses" << endl;


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
            //cout << "pas de visibilité sur le parcours des ordonnées!" << endl;
            result = false;
            //return false;
        }
    }


    //PARCOURS DES DROITES OBLIQUES
    //cout << "limites du plan: " << x1 << " " << x2 << " " << y1 << " " << y2 << endl;

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
                //cout << "pas de visibilité sur le parcours des droites obliques!" << endl;
                result = false;
                //return false;
            }
        }
    }

    //cout << "fin de parcours des droites obliques" << endl;
    return result;
}

//Fonction de généralisation du calcul d'intervisibilité sur un vecteur
void MNT::computeIntervisility(const QVector<QVector3D>& m_vec)
{
    for (int i(0); i<m_vec.length()-vertices_by_x-1; i++)
    {
        float distance = m_coordInterp[0].distanceToPoint(m_vec[i]);

        //cout << distance << endl;
        //if (distance <= distanceTir)
        if (distance <= distanceTir && intervisibility(m_coordInterp[0],m_vec[i]))
        {
            //cout << "ajout de point" << endl;
            m_vect1.append(m_vec[i]);
            //cout << m_vec[i].x() << " " << m_vec[i].y() << " " << m_vec[i].z() << endl;
        }
    }

    cout << "SIZE: " << m_vect1.length() << endl;
}


bool MNT::verifHorizontal(QVector3D pt1, QVector3D pt2, double x1, double x2, double y1, double y2, bool* resultatGlobal)
{

    QMutex mutex;

bool result = true;
cout << x1 << " " << x2 << endl;
QVector3D vectNabs(1,0,0);
QVector3D vectNord(0,1,0);
QVector3D vectOblique(1,-1,0);

droite d(pt1, pt2);//on construit la droite passant par les deux points

//PARCOURS DES ABSCISSES (= les droites verticales)
for (int i(x1); i<=x2; i+=25)
{
    if (*resultatGlobal == false)
        break;

    plan p(QVector3D(i, y1, 0), vectNabs);

    if (d.position(p) == 2)//i.e la droite appartient au plan
    {
        //cout << "la droite considérée appartient au plan!" << endl;
        //on cherche si l'altitude d'un point sur la droite est supérieure à l'altitude d'un des deux points
        //la droite a pour coordonnées x1
        int indice = (i/25)+(m_vector.length()-((y1/25)+1)*vertices_by_x);
        //cout << indice << " " <<m_vector[indice].y() << " " << y1 << endl;
        while (m_vector[indice].y() >= y1)
        {
            //cout << "indice: " << indice << " altitude: " << m_vector[indice].z() << endl;
            if (m_vector[indice].z() > pt1.z() || m_vector[indice].z() > pt2.z())
            {
                cout << " Arrêt droite appartient au plan " << m_vector[indice].y() << endl;
                result = false;
                mutex.lock();
                *resultatGlobal = false;
                mutex.unlock();
                return false;
            }
            indice-=vertices_by_x;
        }
        break;
    }

    //droite parallèle au plan verticaux
    else if(d.position(p) == 1 && ((int)pt1.x()%25) != 0)//si la droite est parallèle aux plans et n'est pas un plan vertical
    {
        //cout << "la droite considérée est parallèle au plan " << y1 << " " << y2 << endl;
        //on bascule sur les verifications des ordonnées
        d.afficherDroite();
        for (int i(y1); i<=y2; i+=25)
        {
            if (*resultatGlobal == false)
                break;

            plan p(QVector3D(x1, i, 0), vectNord);
            //p.afficherPlan();
            QVector3D intersect = d.calculIntersection(p);
            //cout << "INTERSECTION: " << " " << intersect.x() << " " << intersect.y() << " " << intersect.z() << endl;
            //cout << y1 << " " << y2 << " " << "pasY: " << 25 << "pasX: " << 25 << endl;
            float altiPoint = compareAlti(intersect,1);
            //cout << altiPoint << endl;
            //cout << intersect.y() << " " << altiPoint << " " << intersect.z() << endl;
            if (altiPoint > intersect.z())
            {
                //cout << "pas de visibilité sur le parcours des ordonnées!" << endl;
                result = false;
                mutex.lock();
                *resultatGlobal = false;
                mutex.unlock();
                return false;
            }
        }
        break;
    }

    else
    {
        QVector3D intersect = d.calculIntersection(p);
        float altiPoint = compareAlti(intersect,0);
        //cout <<  "ALTI: " << altiPoint << " " << intersect.z() << endl;
        if (altiPoint > intersect.z())
        {
            //cout << "pas de visibilité sur le parcours des abscisses!" << endl;
            result = false;
            mutex.lock();
            *resultatGlobal = false;
            mutex.unlock();
            return false;
        }
    }

}

}

bool MNT::verifVertical(QVector3D pt1, QVector3D pt2, double x1, double x2, double y1, double y2, bool* resultatGlobal)
{

    QMutex mutex;

    bool result = true;
    cout << x1 << " " << x2 << endl;
    QVector3D vectNabs(1,0,0);
    QVector3D vectNord(0,1,0);
    QVector3D vectOblique(1,-1,0);

    droite d(pt1, pt2);//on construit la droite passant par les deux points

//PARCOURS DES ORDONNEES (=les droites horizontales)
for (int i(y1); i<=y2; i+=25)
{
    if (*resultatGlobal == false)
        break;

    plan p(QVector3D(x1, i, 0), vectNord);
    QVector3D intersect = d.calculIntersection(p);
    //cout << y1 << " " << y2 << " " << "pasY: " << 25 << "pasX: " << 25 << endl;
    float altiPoint = compareAlti(intersect,1);
    //cout << altiPoint << " " << intersect.z() << endl;
    if (altiPoint > intersect.z())
    {
        //cout << "pas de visibilité sur le parcours des ordonnées!" << endl;
        result = false;
        mutex.lock();
        *resultatGlobal = false;
        mutex.unlock();
        //return false;
    }
}
}

bool MNT::verifOblique(QVector3D pt1, QVector3D pt2, double x1, double x2, double y1, double y2, bool* resultatGlobal)
{

    QMutex mutex;

    bool result = true;
    cout << x1 << " " << x2 << endl;
    QVector3D vectNabs(1,0,0);
    QVector3D vectNord(0,1,0);
    QVector3D vectOblique(1,-1,0);

    droite d(pt1, pt2);//on construit la droite passant par les deux points

    //PARCOURS DES DROITES OBLIQUES
    //cout << "limites du plan: " << x1 << " " << x2 << " " << y1 << " " << y2 << endl;

    for (int i(y1); i<=y2; i+=25)
    {

        if (*resultatGlobal == false)
            break;

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
                //cout << "pas de visibilité sur le parcours des droites obliques!" << endl;
                result = false;
                mutex.lock();
                *resultatGlobal = false;
                mutex.unlock();
                //return false;
            }
        }
    }
}


bool MNT::verifPreliminaire(QVector3D pt1, QVector3D pt2)
{
    bool result = true;
    if (computeSousTerre(pt1))
    {
        //cout << "le premier point n'est pas sous terre" << endl;
    }
    else
    {
        cout << "le premier point est sous terre" << endl;
        result = false;
        //return false;
    }

    if (computeSousTerre(pt2))
    {
        //cout << "le deuxieme point n'est pas sous terre" << endl;
    }
    else
    {
        cout << "le deuxieme point est sous terre" << endl;
        result = false;
    }

    return result;
}
