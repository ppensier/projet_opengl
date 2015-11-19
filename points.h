#ifndef POINTS_H
#define POINTS_H

class Points
{
public:
    Points();
    Points(double abscisse, double ordonnee, double altitude);
    virtual ~Points();
    double getterAbscisse() const;
    double setterAbscisse(double autreAbscisse);
    double getterOrdonnee() const;
    double setterOrdonnee(double autreOrdonnee);
    double getterAltitude() const;
    double setterAltitude(double autreAltitude);

private:
    double m_abscisse;
    double m_ordonnee;
    double m_altitude;
};

double distan(Points p1, Points p2);

#endif // POINTS_H
