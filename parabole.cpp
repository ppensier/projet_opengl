#include "parabole.h"

#include "math.h"

#include <iostream>

using namespace std;

parabole::parabole(float coeff, QVector3D& pt1, QVector3D& pt2) :
m_point1(pt1), m_point2(pt2)
{
    a=coeff;
    b=(pt1.y()-pt2.x()-(coeff*(pow(pt1.x(),2)-pow(pt2.x(),2))))/(pt1.x()-pt2.x());
    c=pt1.y()-(coeff*pow(pt1.x(),2))-(b*pt1.x());

}

void parabole::afficherParabole()
{
    cout << "l'équation de la parabole est: " << "y=" << a << "*x² + " << b << "*x + " << c << endl;
}

/*
QVector3D parabole::calculIntersection(plan p)
{
    droite d(m_point1,m_point2);
    QVector3D intersection = d.calculIntersection(plan p);
    //intersection.setZ();

    return intersection;
}
*/

