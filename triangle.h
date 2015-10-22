#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "points.h"

class triangle
{
public:
    triangle();
    triangle(Points A, Points B, Points C);
    virtual ~triangle();
    float perimetre();
private:
    Points m_A;
    Points m_B;
    Points m_C;

};

#endif // TRIANGLE_H
