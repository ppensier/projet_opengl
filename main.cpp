#include "mainwindow.h"
//#include "myglwidget.h"
#include "points.h"
#include "triangle.h"
#include <QApplication>

#include <cstdlib>
#include <iostream>

#include "droite.h"
#include "plan.h"

using namespace std;

int main(int argc, char *argv[])
{

    QVector3D pt1(1,0,0);
    QVector3D pt2(1,1,0);
    QVector3D pt3(1,1,1);
    QVector3D vectN(1,1,0);

    plan p(pt1, vectN);
    p.afficherPlan();

    droite d(pt2, pt3);
    cout << d.a1 << endl;
    d.afficherDroite();

    //QVector3D resultat = d.calculIntersection(p);

    //cout << resultat.x() << resultat.y() << resultat.z() << endl;

    int res = d.position(p);
    cout << res << endl;

    QApplication a(argc, argv);

//    QSharedMemory sharedMemory("{69B55631-A712-4d8c-8852-A8ED297EF439}");

//    if(!sharedMemory.create(sizeof(int))) {
//        QMessageBox msgBox;
//        msgBox.setIcon(QMessageBox::Information);
//        msgBox.setWindowTitle("");
//        msgBox.setText("L'application est déjà lancée");
//        msgBox.exec();
//        return 1;
//    }

    MainWindow w;
    w.show();
    return a.exec();

}

