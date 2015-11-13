#include "plan.h"

#include <iostream>


using namespace std;

//constructeur d'un plan p à partir d'un vecteur normal au plan et d'un point
plan::plan(QVector3D pt1, QVector3D vectN)
{
    a = vectN.x();//les coefficients a,b,c sont les
    b = vectN.y();
    c = vectN.z();
    d = -vectN.x()*pt1.x() - (vectN.y()*pt1.y()) - (vectN.z()*pt1.z());//pour trouver d, on se sert des coordonnées du point en question
}

plan::plan(QVector3D pt1, QVector3D pt2, QVector3D pt3)
{

    QVector3D ab(pt2.x()-pt1.x(),pt2.y()-pt1.y(),pt2.z()-pt1.z());
    QVector3D ac(pt3.x()-pt1.x(),pt3.y()-pt1.y(),pt3.z()-pt1.z());

    //QVector3D vectN((pt1.y()*pt2.z())-(pt1.z()*pt2.y()), (pt1.z()*pt2.x())-(pt1.x()*pt2.z()), (pt1.x()*pt2.y())-(pt1.y()*pt2.x()));//calcul du produit vectoriel entre ab et ac
    QVector3D vectN = QVector3D::crossProduct (ab, ac);

    a = vectN.x();
    b = vectN.y();
    c = vectN.z();
    d = -vectN.x()*pt1.x() - (vectN.y()*pt1.y()) - (vectN.z()*pt1.z());//pour trouver d, on se sert des coordonnées du point en question

}

void plan::afficherPlan()
{

     cout << "l'equation du plan: " << a << "*x + " << b << "*y + " << c << "*z + " << d << " = 0" << endl;

}

