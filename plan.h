#ifndef PLAN_H
#define PLAN_H

#include <QVector3D>

class plan
{
public:
    plan(QVector3D pt1, QVector3D vectN);
    plan(QVector3D pt1, QVector3D pt2, QVector3D pt3);
    void afficherPlan();

//protected:
    double a;
    double b;
    double c;
    double d;

};

#endif // PLAN_H
