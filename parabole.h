#ifndef PARABOLE_H
#define PARABOLE_H

#include "qvector3d.h"

#include "droite.h"
#include "plan.h"

class parabole
{
public:
    parabole(float coeff, QVector3D &pt1, QVector3D &pt2);
    void afficherParabole();
    //QVector3D calculIntersection(plan p);

protected:
    double a;
    double b;
    double c;
    QVector3D& m_point1;
    QVector3D& m_point2;

};

#endif // PARABOLE_H
