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

    //ui->verticalLayout_3->addStretch(100);
    ui->zonePTE->setFixedHeight(80);
    //ui->horizontalLayout_3->setSizeConstraint(QLayout::SetFixedSize);

    //Initialisation du paramètre m_vect
    //m_vect();
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

    // On nettoie les autres objets
    //QObject::connect(ui->razB,SIGNAL(released()),this,SLOT(raz()));

    // On navigue dans l'arborescence des fichiers
    //QObject::connect(ui->openFileB,SIGNAL(released()),this,SLOT(changeNom()));

    // On lit le fichier
    //QObject::connect(ui->choiceB,SIGNAL(released()),this,SLOT(read()));

    // On écrit dans le fichier
    //QObject::connect(ui->computationB,SIGNAL(released()),this,SLOT(write()));

    // On détecte si le texte a changé
    QObject::connect(ui->zonePTE,SIGNAL(textChanged()),this,SLOT(changed()));

    QObject::connect(ui->envoyerCoord, SIGNAL(clicked()), this, SLOT(chargerCoordonneesInterp()));

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

        cout << "on rentre dans la condition!" << endl;
        cout << ui->x1->value() << " " << m_viewer->minCoord.x << endl;

        if(ui->x1->value() == m_viewer->minCoord.x || ui->x1->value() == m_viewer->maxCoord.x || ui->y1->value() == m_viewer->minCoord.y || ui->y1->value() == m_viewer->maxCoord.y || ui->x2->value() == m_viewer->minCoord.x || ui->x2->value() == m_viewer->maxCoord.x || ui->y2->value() == m_viewer->minCoord.y || ui->y2->value() == m_viewer->maxCoord.y  )
        {
            cout << "Je rentre dans la condition" << endl;
            QMessageBox::warning(this, "Titre de la fenêtre", "Attention vous n'êtes pas dans le bon interval de valeurs!");

        }
        else
        {
            QVector2D point1(ui->x1->value(), ui->y1->value());
            QVector2D point2(ui->x2->value(), ui->y2->value());

            coordAinterp.append(point1);
            coordAinterp.append(point2);

            interpolation(coordAinterp);//Interpolation des coordonnées choisies

            //cout << coordAinterp[0].x() << " " << coordAinterp[0].y() << " " << coordAinterp[1].x() << " " << coordAinterp[1].y() << endl;

        }

        //cout << ui->y1->value() << endl;
        //cout << "abscisse du point 1: " << coordAinterp1.x() << " ordonnée du point 1: " << coordAinterp1.y() << endl;
    }
    else
    {
        QMessageBox::warning(this, "Titre de la fenêtre", "Attention, vous devez d'abord choisir un MNT !");
    }
}

void MainWindow::changeLimitValues()
{
    cout << "1er appel pour changer les coordonnées des limites" << endl;
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
    }
}

void MainWindow::raz() {
    //ui->nomLE->clear();
    ui->zonePTE->clear();
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

        while (!file.atEnd())
        //for (int i(0); i<100; i++)
        {

            QString line = in.readLine();
            QStringList coordonnees = line.split(' ');

            double abscisse = coordonnees[0].toDouble();
            double ordonnee = coordonnees[1].toDouble();
            double altitude = coordonnees[2].toDouble();

            //f>>abscisse>>ordonnee>>altitude;

            QVector3D point(abscisse, ordonnee, altitude);

            m_vect.push_back(point);
            //ui->widget->setterNomFile(nomF.toStdString().c_str());

        }

        file.close();
        cout << "fin de la lecture" << endl;
        m_viewer->init();
        changeLimitValues();
        m_viewer->calculateAxis(QVector3D pt1(901010, 1901110, 0), QVector3D pt2(902111, 1900120, 0));
    }
    else
    {
        ui->zonePTE->appendPlainText("impossible de lire le fichier");
    }
}

void MainWindow::interpolation(const QVector<QVector2D>& coordAinterp)
{
    double x1, x2, y1, y2;
    //cout << coordAinterp.length() << endl;

    //recherche des abscisses
    int i = 0;
    while (i != 4000)//on ne parcourt que la permiere ligne
    {
        //premier point considéré
        if (m_vect[i].x() > coordAinterp[0].x())
        {
            //cout << "Arret: " << m_vect[i].x() << " " << coordAinterp[0].x() << endl;
            x1 = m_vect[i].x();
            x2 = m_vect[i-1].x();
            cout << "les deux abscisses limites pour le 1er point sont: "  << x1 << " et " << x2 << endl;
            break;
        }
        i++;
    }

    //recherche des ordonnées, donc parcours de tout le fichier
    int j = 0;
    while(j != m_vect.length())// on parcourt une colonne du fichier
    {
        if (m_vect[j].y() < coordAinterp[0].y())
        {
                cout << "Arret sur les ordonnées!" << m_vect[j].y() << " " << coordAinterp[0].y() << endl;
                y1 = m_vect[j].y();
                y2 = m_vect[j-1].y();
                cout << "les deux ordonnees limites pour le 1er point sont: "  << y1 << " et " << y2 << endl;
                break;
        }
        j += 4000;
    }

}



void MainWindow::changed(){
    ui->sBar->showMessage("modif",2000);
}

/*
void MainWindow::write(){
        ofstream f(nomF.toStdString().c_str());
        QString texte;
        if(f)
        {
                texte = ui->zonePTE->toPlainText();
                string ligne;
                ligne = texte.toStdString();
                f << ligne << endl;
        }
        else{
                ui->sBar->showMessage("Erreur à l'ouverture !");
    }
  }
*/

MainWindow::~MainWindow()
{
    delete ui;
}


