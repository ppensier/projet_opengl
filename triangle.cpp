#include "triangle.h"

triangle::triangle()
{

}

triangle::~triangle()
{
    //dtor
}

triangle::triangle(Points A, Points B, Points C)
{
    m_A = A;
    m_B = B;
    m_C = C;
}

//fonction perimetre du triangle
float triangle::perimetre() {
    float resultat = 0;
    resultat += distan(m_A, m_B) + distan(m_B, m_C) + distan(m_C, m_A);
    return resultat;
}

