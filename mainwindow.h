#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QVector3D>

namespace Ui {
class MainWindow;
}

void readMNT();

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QString nomF;
    ~MainWindow();

public slots:
    void raz();
    void changeNom();
    void read();
    //void write();
    void changed();
    //void readMNT(); Fonction à rajouter pour lire le fichier texte du MNT!

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
