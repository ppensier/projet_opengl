#ifndef DROITE_H
#define DROITE_H

#include <QVector3D>

#include "plan.h"

class droite
{
public:
    droite(QVector3D pt1, QVector3D pt2);
    void afficherDroite();
    QVector3D calculIntersection(plan p);
    int position(plan p);

//parametres d'une droite parametrique
//protected:
    double a1;//vecteur directeur a
    double a2;
    double a3;
    double b1;//la droite passe par le point de cooordonnées b1,b2,b3
    double b2;
    double b3;
};


//bool calculateAxis(QVector3D pt1, QVector3D pt2, double &x1, double &x2, double &y1, double &y2);

//bool intervisibility(QVector3D pt1, QVector3D pt2, double &x1, double &x2, double &y1, double &y2);
#endif // DROITE_H
