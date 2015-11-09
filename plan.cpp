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

void plan::afficherPlan()
{

     cout << "l'equation du plan: " << a << "*x + " << b << "*y + " << c << "*z + " << d << " = 0" << endl;

}

