#ifndef THREADHORIZONTAL_H
#define THREADHORIZONTAL_H

#include "mnt.h"

#include "qvector3d.h"
#include "qthread.h"

class threadHorizontal : public QThread
{
public:
    threadHorizontal(QVector3D point1, QVector3D point2, MNT* mnt);
    //threadHorizontal();
    void run();

    MNT* monMNT;
    QVector3D m_point1;
    QVector3D m_point2;
    int d;
    bool resultat;
    bool* resulatGlobal;

    double x1;
    double y1;
    double x2;
    double y2;

};

#endif // THREADHORIZONTAL_H
