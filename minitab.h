#ifndef MINITAB_H
#define MINITAB_H

#include "simpleViewer.h"

class Viewer;

class MiniTab : public Viewer
{
    Q_OBJECT
public:
    MiniTab();
    MiniTab(QVector<QVector3D>& vector);
public slots:
    void computeIntervisility();
};


#endif // MINITAB_H
