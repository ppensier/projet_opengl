#include "droite.h"
#include "plan.h"
#define PERMUTER(x,y) x ^= y, y ^= x, x ^= y

#include <iostream>

using namespace std;

//constructeur de la droite d (on choisit la version parametrique pour son écriture)
droite::droite(QVector3D pt1, QVector3D pt2)
{
    //vecteur directeur de la droite
    a1 = pt1.x()-pt2.x();
    a2 = pt1.y()-pt2.y();
    a3 = pt1.z()-pt2.z();

    b1 = pt1.x();//la droite passe par le point 1
    b2 = pt1.y();
    b3 = pt1.z();

    cout << pt1.x() << " " << pt2.x() << " " << a1 << endl;

}

void droite::afficherDroite()
{
    cout << "x = " << a1 << "*lambda + " << b1 << endl;
    cout << "y = " << a2 << "*lambda + " << b2 << endl;
    cout << "z = " << a3 << "*lambda + " << b3 << endl;

}

//calcule l'intersection entre une droite et un plan
//la fonction retourne un point
QVector3D droite::calculIntersection(plan p)
{
    double lambda = -(p.d + b1*p.a + p.b*b2 + p.c*b3)/(p.a*a1 + p.b*a2 + p.c*a3);

    QVector3D intersection(a1*lambda + b1, a2*lambda + b2, a3*lambda + b3);//coordonnées de l'intersection

    return intersection;
}

//determine le type d'intersection entre un point et une droite
int droite::position(plan p)
{
    //0: intersection = point
    if (p.a*a1 + p.b*a2 + p.c*a3 == 0)//si le vecteur normal au plan est orthogonal à la droite
    {
        if (p.a*b1 + p.b*b2 + p.c*b3 + p.d == 0)//le point de la droite appartient au plan p
            return 2;//apppartient au plan
        else
            return 1;//la droite est parallèle
    }
    else
    {
        return 0;
    }
}


void calculateAxis(QVector3D pt1, QVector3D pt2, double &x1, double &x2, double &y1, double &y2)
{
    QVector3D p1, p2, p3;

    //on trouve d'abord  le x de la droite du 1er point
    //double soustractionx1 = pt1.x();
    int pasX = 25;
    int pasY = 25;

    int resx1 = pt1.x()/pasX;

    int resx2 = pt2.x()/pasX;

    //calcul des y
    int resy1 = pt1.y()/pasY;
    int resy2 = pt2.y()/pasY;

    if (pt1.x() < pt2.x())
    {
        x1 = (resx1+1)*pasX;
        x2 = resx2*pasX;

    }
    else//le point
    {
        x1 = resx1*pasX;
        x2 = (resx2+1)*pasX;

    }

    if (pt1.y() < pt2.y())
    {
        y1 = (resy1+1)*pasY;
        y2 = resy2*pasY;
    }
    else
    {
        y1 = resy1*pasY;
        y2 = (resy2+1)*pasY;
    }
    if (x1 > x2)
    {
        swap(&x1, &x2);
    }
    if (y1 > y2)
    {
        swap(&y1, &y2);
    }

}

void swap(double* a, double* b)
{
  double temp;
  temp = *a;
  *a = *b;
  *b = temp;
}


