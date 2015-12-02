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

#include "droite.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    //ui->sBar->showMessage("...Bonjour...(5s)",5000);

    ui->zonePTE->setFixedHeight(80);
    //ui->horizontalLayout_3->setSizeConstraint(QLayout::SetFixedSize);

    //Initialisation du paramètre m_vect

    ui->nb2->setChecked(true);
    distMax= 0;
    m_mnt = new MNT(m_vect, coordAinterp, distMax, 0);

    //ouvrir le fichier du MNT
    QObject::connect(ui->actionMNT, SIGNAL(triggered()), this, SLOT(changeNom()));

    cout << "TAILLE: " << m_mnt->m_vertexSort.size() << endl;
    //initialisation du viewer
    //m_viewer = new Viewer(m_mnt->m_vertexSort, this);
    m_viewer = new Viewer(m_mnt->m_vertexSort, m_mnt->m_tabColor, coordAinterp, m_mnt->minCoord, m_mnt->maxCoord, m_mnt->m_vect1, this);
    ui->verticalLayout_3->addWidget(m_viewer);

    connect(m_viewer,SIGNAL(coordAinterpModif(QVector3D)),this, SLOT(appendCoordAinterp(QVector3D)));

    //Ajout d'information aux spinbox
    ui->point1->setToolTip("Entrer les coordonnées x,y de votre point en Lambert II étendu");
    ui->point1->setCursor(Qt::WhatsThisCursor);
    ui->point2->setToolTip("Entrer les coordonnées x,y de votre point en Lambert II étendu");
    ui->point2->setCursor(Qt::WhatsThisCursor);

    //bouton quitter
    QObject::connect(ui->actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    ui->actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));

    //méthode raz de la zone de texte
    QObject::connect(ui->actionRAZ, SIGNAL(triggered()), this, SLOT(reset()));

    //Anciens boutons
    // On ferme l'application
    QObject::connect(ui->quitB,SIGNAL(released()),this,SLOT(close()));

    // On détecte si le texte a changé
    QObject::connect(ui->zonePTE,SIGNAL(textChanged()),this,SLOT(changed()));

    QObject::connect(ui->envoyerCoord, SIGNAL(clicked()), this, SLOT(chargerCoordonneesInterp()));

    QObject::connect(ui->x1, SIGNAL(valueChanged(int)),this, SLOT(setValue(int)));

    QObject::connect(ui->pointMNT, SIGNAL(clicked()), m_viewer, SLOT(activateSelection()));
    //connect(this, SIGNAL(beginThread()), m_vect1, SLOT(computeIntervisility()));

}


void MainWindow::chargerCoordonneesInterp()
{
    cout << "premier affichage: " << m_vect.length() << endl;

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

                //APPEL de la fonction de calcul de l'intervisibilité sur le mnt
                m_viewer->init();
                m_viewer->draw();
/*
                if (m_mnt->verifPreliminaire(point1, point2))
                {
                    cout << "pas sous terre" << endl;
                }
                //cration thread
                double x1;
                double x2;
                double y1;
                double y2;

                bool* globalResult;
                globalResult = new bool();
                *globalResult = true;
                cout << "resultat gobal: " << *globalResult << endl;

                calculateAxis(point1, point2, x1, x2, y1, y2);
                threadHorizontal monThreadH(point1, point2, m_mnt);
                monThreadH.x1=x1;
                monThreadH.x2=x2;
                monThreadH.y1=y1;
                monThreadH.y2=y2;
                monThreadH.d=5;

                monThreadH.resulatGlobal = globalResult;

                threadVertical monThreadV(point1, point2, m_mnt);
                monThreadV.x1=x1;
                monThreadV.x2=x2;
                monThreadV.y1=y1;
                monThreadV.y2=y2;
                monThreadV.d=5;

                threadOblique monThreadO(point1, point2, m_mnt);
                monThreadO.x1=x1;
                monThreadO.x2=x2;
                monThreadO.y1=y1;
                monThreadO.y2=y2;
                monThreadO.d=5;

                //monTh= new threadHorizontal(point1, point2, m_mnt);

                monThreadH.start();
                monThreadV.start();
                monThreadO.start();

                cout << "thread lancé" << endl;
                monThreadV.wait();
                cout << "resultat:" << monThreadV.resultat << endl;

                cout << "thread lancé" << endl;
                monThreadH.wait();
                cout << "global result: " << *globalResult << endl;
                cout << "resultat:" << monThreadH.resultat << endl;

                cout << "resultat:" << monThreadO.resultat << endl;
                monThreadO.wait();

                if (*globalResult)
*/
                if (m_mnt->intervisibility(point1, point2))
                {
                    //cout << "Intervisibilité OK" << endl;
                    ui->zonePTE->appendPlainText("Les deux points sélectionnés sont visibles");
                }
                else
                {
                    cout << "test" << endl;
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
        else//i.e l'utilisateur a seulement choisi un point
        {
            distMax = ui->dist_max->value();
            QVector3D point1(ui->x1->value(), ui->y1->value(), ui->z1->value());
            coordAinterp.append(point1);
            ui->zonePTE->clear();

            cout << "test appel un seul point: " << coordAinterp.length() << endl;
            //Appel de la fonction du mnt responsable du calcul
            m_mnt->computeIntervisility(m_vect);

            m_viewer->init();
            m_viewer->draw();

        }
    }
    else
    {
        QMessageBox::warning(this, "Titre de la fenêtre", "Attention, vous devez d'abord choisir un MNT !");
    }
}

//fonction pour changer les coordonnées limites pour les spinbox
void MainWindow::changeLimitValues()
{
    //si le MNT est chargé on change les valeurs limites des spinbox
    if (m_vect.length() != 0)
    {
        cout << "on rentre ici " << m_mnt->minCoord.z << endl;
        ui->x1->setMinimum(int(m_mnt->minCoord.x));
        ui->x1->setMaximum(int(m_mnt->maxCoord.x));
        ui->x2->setMinimum(int(m_mnt->minCoord.x));
        ui->x2->setMaximum(int(m_mnt->maxCoord.x));
        ui->y1->setMinimum(int(m_mnt->minCoord.y));
        ui->y1->setMaximum(int(m_mnt->maxCoord.y));
        ui->y2->setMinimum(int(m_mnt->minCoord.y));
        ui->y2->setMaximum(int(m_mnt->maxCoord.y));
        ui->z1->setMinimum(int(m_mnt->minCoord.z));
        ui->z1->setMaximum(int(m_mnt->maxCoord.z));
        ui->z2->setMinimum(int(m_mnt->minCoord.z));
        ui->z2->setMaximum(int(m_mnt->maxCoord.z));
    }
}


void MainWindow::reset() {
    ui->zonePTE->clear();
    ui->x1->setValue(0);
    ui->y1->setValue(0);
    ui->z1->setValue(m_viewer->minCoord.z);
    ui->x2->setValue(0);
    ui->y2->setValue(0);
    ui->z2->setValue(m_viewer->minCoord.z);
    ui->dist_max->setValue(0);
    int i=0;
    while (coordAinterp.length() != 0)
    {
        coordAinterp.removeLast();
        i++;
    }

    int j=0;
    while (m_viewer->m_vect1.length() != 0)
    {
        m_viewer->m_vect1.removeLast();
        j++;
    }

    m_viewer->init();
    m_viewer->draw();
    ui->sBar->showMessage("...Nettoyage...",1000);
}


void MainWindow::changeNom(){
   nomF = QFileDialog::getOpenFileName(this);
   //ui->nomLE->setText(nomF);
   read();
   m_mnt->computeLineLength();
   m_mnt->computeExtremes();
   m_mnt->trierPoints();
   m_mnt->computeColorTable();
   changeLimitValues();
   m_viewer->init();
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
    }
    else
    {
        ui->zonePTE->appendPlainText("impossible de lire le fichier");
    }
}


void MainWindow::changed(){
    ui->sBar->showMessage("modif",2000);
}

void MainWindow::appendCoordAinterp(QVector3D ap)
{
    if (coordAinterp.length() == 0)
    {
        cout << "test rentre une fois!" << endl;
        coordAinterp.append(ap);
        ui->x1->setValue((ap.x()));
        ui->y1->setValue((ap.y()));
        ui->z1->setValue((ap.z()));
        return;
    }

    if (coordAinterp.length() == 1)
    {
             cout << "test rentre deux fois!" << endl;
             coordAinterp.append(ap);
             ui->x2->setValue(float(ap.x()));
             ui->y2->setValue(float(ap.y()));
             ui->z2->setValue(float(ap.z()));
             return;
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}


