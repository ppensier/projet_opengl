#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextStream>
#include <QVector3D>
#include <QVector2D>
#include <QVector>
#include <QFileDialog>
#include <fstream>
#include <iostream>
#include <string>
#include <QIcon>
#include <limits>
#include <typeinfo>
#include <QtWidgets>

#include "simpleViewer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void read();
    void changeLimitValues();
    void interpolation(const QVector<QVector2D>& coordAinterp);
    //QVector<QVector3D>& vect(int taille);

public slots:
    void raz();
    void changeNom();
    void changed();
    void chargerCoordonneesInterp();

private:
    Ui::MainWindow *ui;

protected:
    QVector<QVector3D> m_vect;
    QString nomF;
    Viewer* m_viewer;
    QVector<QVector3D> coordAinterp;//vecteurs de coordonnées où l'on désire interpoler l'altitude.

};

#endif // MAINWINDOW_H
