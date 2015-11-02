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


    //Initialisation du paramètre m_vect
    //m_vect();
    m_viewer = new Viewer(m_vect, this);
    ui->verticalLayout_3->addWidget(m_viewer);

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
    QObject::connect(ui->razB,SIGNAL(released()),this,SLOT(raz()));

    // On navigue dans l'arborescence des fichiers
    QObject::connect(ui->openFileB,SIGNAL(released()),this,SLOT(changeNom()));

    // On lit le fichier
    QObject::connect(ui->choiceB,SIGNAL(released()),this,SLOT(read()));

    // On écrit dans le fichier
    QObject::connect(ui->computationB,SIGNAL(released()),this,SLOT(write()));

    // On détecte si le texte a changé
    QObject::connect(ui->zonePTE,SIGNAL(textChanged()),this,SLOT(changed()));

    /*
    QIcon image("../Preview.jpg");
    ui->openFileB->setIcon(image);
    ui->openFileB->show();
    */
}

/*
QVector<QVector3D>& MainWindow::vect(int taille) {

    return m_vect;

}
*/

void MainWindow::raz() {
    ui->nomLE->clear();
    ui->zonePTE->clear();
    ui->sBar->showMessage("...Nettoyage...",2000);
}

void MainWindow::changeNom(){
   nomF = QFileDialog::getOpenFileName(this);
   ui->nomLE->setText(nomF);
   read();
}

void MainWindow::read(){
    QFile file(nomF.toStdString().c_str());
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);

        while (!file.atEnd())
        //for (int i(0); i<10; i++)
        {

            QString line = in.readLine();
            QStringList coordonnees = line.split(' ');

            double abscisse = coordonnees[0].toDouble();
            double ordonnee = coordonnees[1].toDouble();
            double altitude = coordonnees[2].toDouble();

            //f>>abscisse>>ordonnee>>altitude;

            QVector3D point(abscisse, ordonnee, altitude);

            m_vect.push_back(point);
            //vectorT.push_back(point);
            //ui->widget->setterNomFile(nomF.toStdString().c_str());

        }

        file.close();
        m_viewer->init();
    }
    else
    {
        ui->zonePTE->appendPlainText("impossible de lire le fichier");
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


//ifstream f (nomF.toStdString().c_str());
//if ( !f )
//       ui->zonePTE->QPlainTextEdit::appendPlainText("le fichier choisi n'existe pas");
//   else
//   {
