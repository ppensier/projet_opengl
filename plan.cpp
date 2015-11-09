#include "plan.h"

#include <iostream>


using namespace std;


plan::plan(QVector3D pt1, QVector3D vectN)
{
    a = vectN.x();
    b = vectN.y();
    c = vectN.z();
    d = -vectN.x()*pt1.x() - (vectN.y()*pt1.y()) - (vectN.z()*pt1.z());
}

void plan::afficherPlan()
{

     cout << "l'equation du plan: " << a << "*x + " << b << "*y + " << c << "*z + " << d << " = 0" << endl;

}
