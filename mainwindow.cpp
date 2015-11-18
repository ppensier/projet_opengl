#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTextStream>
#include <QVector3D>
#include <QVector>
#include <QFileDialog>
#include <fstream>
#include <iostream>
#include <string>
#include <QIcon>
#include <limits>
#include <typeinfo>

using namespace std;

const int taille_fichier = 100;

//Points* tab2 = new Points[taille_fichier];//allocation dynamique de tableaux

//QVector<QVector3D> vectorT(taille_fichier);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{  

    ui->setupUi(this);

    ui->sBar->showMessage("...Bonjour...(5s)",5000);

    ui->zonePTE->setFixedHeight(80);
    //ui->horizontalLayout_3->setSizeConstraint(QLayout::SetFixedSize);

    //Initialisation du paramètre m_vect

    ui->nb2->setChecked(true);
    m_viewer = new Viewer(m_vect, coordAinterp, this);
    ui->verticalLayout_3->addWidget(m_viewer);

    //Ajout d'information aux spinbox
    ui->point1->setToolTip("Entrer les coordonnées x,y de votre point en Lambert II étendu");
    ui->point1->setCursor(Qt::WhatsThisCursor);
    ui->point2->setToolTip("Entrer les coordonnées x,y de votre point en Lambert II étendu");
    ui->point2->setCursor(Qt::WhatsThisCursor);

    //bouton quitter
    QObject::connect(ui->actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    ui->actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));

    //ouvrir un fichier
    QObject::connect(ui->actionMNT, SIGNAL(triggered()), this, SLOT(changeNom()));

    //méthode raz de la zone de texte
    QObject::connect(ui->actionRAZ, SIGNAL(triggered()), this, SLOT(raz()));

    //Anciens boutons
    // On ferme l'application
    QObject::connect(ui->quitB,SIGNAL(released()),this,SLOT(close()));

    // On lit le fichier
    //QObject::connect(ui->choiceB,SIGNAL(released()),this,SLOT(read()));

    // On écrit dans le fichier
    //QObject::connect(ui->computationB,SIGNAL(released()),this,SLOT(write()));

    // On détecte si le texte a changé
    QObject::connect(ui->zonePTE,SIGNAL(textChanged()),this,SLOT(changed()));

    QObject::connect(ui->envoyerCoord, SIGNAL(clicked()), this, SLOT(chargerCoordonneesInterp()));

    QObject::connect(ui->actionLancer_le_calcul, SIGNAL(triggered()), qApp, SLOT(chargerCoordonneesInterp()));

    QObject::connect(ui->x1, SIGNAL(valueChanged(int)),this, SLOT(setValue(int)));

    /*
    QIcon image("../Preview.jpg");
    ui->openFileB->setIcon(image);
    ui->openFileB->show();
    */
}

void MainWindow::chargerCoordonneesInterp()
{
    if (m_vect.length() != 0)
    {

        if (ui->nb2->isChecked() && !(ui->nb1->isChecked()))
        {

            if(ui->x1->value() == m_viewer->minCoord.x || ui->x1->value() == m_viewer->maxCoord.x || ui->y1->value() == m_viewer->minCoord.y || ui->y1->value() == m_viewer->maxCoord.y || ui->x2->value() == m_viewer->minCoord.x || ui->x2->value() == m_viewer->maxCoord.x || ui->y2->value() == m_viewer->minCoord.y || ui->y2->value() == m_viewer->maxCoord.y  )
            {
                //cout << "Je rentre dans la condition" << endl;
                QMessageBox::warning(this, "Titre de la fenêtre", "Attention vous n'êtes pas dans le bon interval de valeurs!");

            }
            else
            {
                QVector3D point1(ui->x1->value(), ui->y1->value(), ui->z1->value());
                QVector3D point2(ui->x2->value(), ui->y2->value(), ui->z2->value());

                coordAinterp.append(point1);
                coordAinterp.append(point2);

                //interpolation(coordAinterp);//Interpolation des coordonnées choisies
                QString distance = QString::number(point1.distanceToPoint(point2));

                ui->zonePTE->clear();
                ui->zonePTE->appendPlainText("la distance entre les deux points interpolés est de: " + distance + " m");
                //ui->zonePTE->appendPlainText(QString::number(point1.distanceToPoint(point2)));
                //cout << "les points à interpoler sont: " << endl;
                //cout << coordAinterp[0].x() << " " << coordAinterp[0].y() << " " << coordAinterp[1].x() << " " << coordAinterp[1].y() << endl;
                m_viewer->draw();

                if (m_viewer->intervisibility(point1, point2))
                {
                    //cout << "Intervisibilité OK" << endl;
                    ui->zonePTE->appendPlainText("Les deux points sélectionnés sont visibles");
                }
                else
                {
                    ui->zonePTE->appendPlainText("Les deux points sélectionnés ne sont pas visibles");
                    //cout << "Pas d'intervisibilité" << endl;
                    QMessageBox msgBox;
                    msgBox.setIcon(QMessageBox::Information);
                    msgBox.setWindowTitle("");
                    msgBox.setText("Pas d'intervisibilité entre les deux points!");
                    msgBox.exec();
                }
            }
        }
        else if (!(ui->nb1->isChecked()) && !(ui->nb2->isChecked()))
        {
            QMessageBox::warning(this, "Titre de la fenêtre", "Choisissez le nombre de points pour réaliser le calcul d'intervisibilité!");
        }
        else if (ui->nb1->isChecked() && ui->nb2->isChecked())
        {
            QMessageBox::warning(this, "Titre de la fenêtre", "Cochez une seule case!");
        }
        else
        {
            QVector3D point1(ui->x1->value(), ui->y1->value(), ui->z1->value());
            coordAinterp.append(point1);
            ui->zonePTE->clear();
            m_viewer->draw();
/*
            if (m_viewer->intervisibility(point1, m_vect[0]))
            {
                ui->zonePTE->appendPlainText("Les deux points sélectionnés sont visibles");
            }
            else
            {
                ui->zonePTE->appendœPlainText("Les deux points sélectionnés ne sont pas visibles");
                cout << "Pas d'intervisibilité" << endl;
                QMessageBox msgBox;
                msgBox.setIcon(QMessageBox::Information);
                msgBox.setWindowTitle("");
                msgBox.setText("Pas d'intervisibilité entre les deux points!");
                msgBox.exec();
            }
*/

        }

    }
    else
    {
        QMessageBox::warning(this, "Titre de la fenêtre", "Attention, vous devez d'abord choisir un MNT !");
    }
}

void MainWindow::changeLimitValues()
{
    //cout << "1er appel pour changer les coordonnées des limites" << endl;
    //si le MNT est chargé on change les valeurs limites des spinbox
    if (m_vect.length() != 0)
    {
        ui->x1->setMinimum(int(m_viewer->minCoord.x));
        ui->x1->setMaximum(int(m_viewer->maxCoord.x));
        ui->x2->setMinimum(int(m_viewer->minCoord.x));
        ui->x2->setMaximum(int(m_viewer->maxCoord.x));
        ui->y1->setMinimum(int(m_viewer->minCoord.y));
        ui->y1->setMaximum(int(m_viewer->maxCoord.y));
        ui->y2->setMinimum(int(m_viewer->minCoord.y));
        ui->y2->setMaximum(int(m_viewer->maxCoord.y));
        ui->z1->setMinimum(int(m_viewer->minCoord.z));
        ui->z1->setMaximum(int(m_viewer->maxCoord.z));
        ui->z2->setMinimum(int(m_viewer->minCoord.z));
        ui->z2->setMaximum(int(m_viewer->maxCoord.z));

    }
}

void MainWindow::raz() {
    //ui->nomLE->clear();
    ui->zonePTE->clear();
    ui->x1->setValue(0);
    ui->y1->setValue(0);
    ui->z1->setValue(m_viewer->minCoord.z);
    ui->x2->setValue(0);
    ui->y2->setValue(0);
    ui->z2->setValue(m_viewer->minCoord.z);
    m_viewer->init();
    ui->sBar->showMessage("...Nettoyage...",2000);
}

void MainWindow::changeNom(){
   nomF = QFileDialog::getOpenFileName(this);
   //ui->nomLE->setText(nomF);
   read();
}

void MainWindow::read(){
    QFile file(nomF.toStdString().c_str());
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);

        while (!in.atEnd())
        {

            QString line = in.readLine();
            QStringList coordonnees = line.split(' ');

            double abscisse = coordonnees[0].toDouble();
            double ordonnee = coordonnees[1].toDouble();
            double altitude = coordonnees[2].toDouble();


            QVector3D point(abscisse, ordonnee, altitude);

            m_vect.push_back(point);

        }

        file.close();
        //cout << "fin de la lecture" << endl;
        m_viewer->init();
        changeLimitValues();
//        if (m_viewer->intervisibility(p1, p2))
//            cout << "Intervisibilité OK" << endl;
//        else
//            cout << "Pas d'intervisibilité" << endl;
    }
    else
    {
        ui->zonePTE->appendPlainText("impossible de lire le fichier");
    }
}


void MainWindow::changed(){
    ui->sBar->showMessage("modif",2000);
}

MainWindow::~MainWindow()
{
    delete ui;
}


