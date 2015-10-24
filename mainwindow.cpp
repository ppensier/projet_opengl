#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "simpleViewer.h"

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

//count the number of lines in the file;

//QVector tab[taille_fichier];
//Points* tab2 = new Points[taille_fichier];//allocation dynamique de tableaux

//Essai Qttor
QVector<QVector3D> vectorT(taille_fichier);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //Initialisation du paramètre m_vect
    //m_vect(0);

    ui->setupUi(this);

    ui->sBar->showMessage("...Bonjour...(5s)",5000);

    QWidget *m_viewer = new Viewer(m_vect, this);
    ui->verticalLayout_3->addWidget(m_viewer);

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

    QIcon image("../Preview.jpg");
    ui->openFileB->setIcon(image);
    ui->openFileB->show();
}

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
    ifstream f (nomF.toStdString().c_str());
    if ( !f )
           ui->zonePTE->QPlainTextEdit::appendPlainText("fichier inexistant");
       else
       {

        //while(getline(f,texte)){
            //    ui->zonePTE->appendPlainText(QString(texte.c_str()));

            for(int i(0); i<taille_fichier; i++)
            //while(getline(f,texte))
            {
                double abscisse;
                double ordonnee;
                double altitude;

                f>>abscisse>>ordonnee>>altitude;

                QVector3D point(abscisse, ordonnee, altitude);
/*
                tab[i].setX(abscisse);
                tab[i].setY(ordonnee);
                tab[i].setZ(altitude);
*/
                vectorT.push_back(point);

                //ui->widget->setterNomFile(nomF.toStdString().c_str());

                ui->zonePTE->appendPlainText(nomF.toStdString().c_str());
                //ui->zonePTE->appendPlainText( QString::number(tab[i].x()));
//                ui->zonePTE->appendPlainText( QString::number(tab[i].x()));
            }
            //ui->widget->setterTableau(vectorT);
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

void readMNT()
{
    std::cout << "toto" << endl;
}

