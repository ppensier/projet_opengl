#ifndef MNT_H
#define MNT_H

#include <QMouseEvent>
#include <QVector>
#include <QVector2D>
#include <QVector3D>
#include <QThread>
#include <QGLViewer/qglviewer.h>

#include "plan.h"
#include "droite.h"


class MNT
{
public:
    //MNT();
    MNT(QVector<QVector3D>& vector, QVector<QVector3D>& vector_interp, double& distMax, int vertices_by_x);

    //Fonctions pour l'affichage du mnt
    void computeLineLength();
    void computeExtremes();
    void trierPoints();
    void computeColorTable();

    //Fonctions de calcul d'intervisibilité
    bool computeSousTerre(QVector3D pt1);
    float compareAlti(QVector3D intersect, int code);
    bool intervisibility(QVector3D pt1, QVector3D pt2);
    void computeIntervisility(const QVector<QVector3D> &m_vec);
    bool verifHorizontal(QVector3D pt1, QVector3D pt2, double x1, double x2, double y1, double y2, bool *resultatGlobal);
    bool verifVertical(QVector3D pt1, QVector3D pt2, double x1, double x2, double y1, double y2, bool *resultatGlobal);
    bool verifOblique(QVector3D pt1, QVector3D pt2, double x1, double x2, double y1, double y2, bool *resultatGlobal);

    bool verifPreliminaire(QVector3D pt1, QVector3D pt2);

    //minimum et maximum pour le dessin
    qglviewer::Vec minCoord;
    qglviewer::Vec maxCoord;

    qglviewer::Vec pointMin;
    qglviewer::Vec pointMax;

//protected:
    QVector<QVector3D>& m_vector;//vecteur récupéré de la lecture du fichier
    int vertices_by_x;//nombre de ligne sur une ligne du MNT
    int m_nbLines;//nombre de lignes dans le MNT
    QVector<QVector3D> m_vertexSort;//tableau trié des sommets à tracer
    QVector<QVector3D>& m_coordInterp;//vecteur de coordonnées à interpoler
    QVector<QVector3D> m_tabColor;//tableau des couleurs
    QVector<QVector3D> m_vect1;
    double& distanceTir;//distance de tir maximale
    int pasX;
    int pasY;

};



#endif // MNT_H
