#include "threadoblique.h"
#include "qvector3d.h"

using namespace std;

threadOblique::threadOblique(QVector3D point1, QVector3D point2, MNT *mnt)
{
    m_point1.setX(point1.x());
    m_point1.setY(point1.y());
    m_point1.setZ(point1.z());
    m_point2.setX(point2.x());
    m_point2.setY(point2.y());
    m_point2.setZ(point2.z());
    monMNT=mnt;
}

void threadOblique::run()
{
   //cout << "TEST: " << *resulatGlobal << endl;
   monMNT->verifOblique(m_point1,m_point2, x1, x2, y1, y2, resulatGlobal);
}

