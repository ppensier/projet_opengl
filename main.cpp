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

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

}




