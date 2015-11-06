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

