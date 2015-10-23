#include "mainwindow.h"
//#include "myglwidget.h"
#include "points.h"
#include "triangle.h"
#include <QApplication>

#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
/*
    Points p1(1.0, 0.0, 0.0);
    Points p2(3.0, 0.0, 0.0);
    Points p3(1.0, 0.0, 0.0);

    //test on instansie un triangle
    triangle t(p1, p2, p3);
    float peri = t.perimetre();
    double res = distan( p1, p2);

    cout << "distance: " << res << endl;
    cout << "Le perimetre du triangle est le suivant: " << peri << endl;
    double abs = p1.getterAbscisse();
    cout << abs << endl;
*/

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

}




