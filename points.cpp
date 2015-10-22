#include "points.h"
#include <cmath>

#include <iostream>

//constructeur par defaut de la classe points
Points::Points()
{
}

//constructeur surchargé de la classe points
Points::Points(double abscisse, double ordonnee, double altitude)
{
    m_abscisse = abscisse;
    m_ordonnee = ordonnee;
    m_altitude = altitude;
}

//destructeur de la classe points
Points::~Points()
{
    //dtor
}

//acsesseurs et mutateurs de la classe points
double Points::getterAbscisse() const
{
    return this->m_abscisse;
}

double Points::setterAbscisse(double autreAbscisse)
{
    m_abscisse = autreAbscisse;
}

double Points::getterOrdonnee() const
{
    return this->m_ordonnee;
}

double Points::setterOrdonnee(double autreOrdonnee)
{
    m_ordonnee = autreOrdonnee;
}

double Points::getterAltitude() const
{
    return this->m_altitude;
}

double Points::setterAltitude(double autreAltitude)
{
    m_altitude = autreAltitude;
}

double distan(Points p1, Points p2)
{
    double abs1 = p1.getterAbscisse();
    double ord1 = p1.getterOrdonnee();
    double alt1 = p1.getterAltitude();
    double abs2 = p2.getterAbscisse();
    double ord2 = p2.getterOrdonnee();
    double alt2 = p2.getterAltitude();

    //std::cout << "toto" << abs2 << std::endl;
    double dist = sqrt(pow(abs1-abs2,2)+pow(ord1-ord2,2)+pow(alt1-alt2,2));

    return dist;

}

