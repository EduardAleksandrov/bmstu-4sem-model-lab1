#include "funcs.h"

Funcs::Funcs(QObject *parent, double nn, double mm) : QObject(parent), n{nn}, m{mm}
{

}
Funcs::~Funcs()
{

}

double Funcs::getN()
{
    return n;
}
double Funcs::getM()
{
    return m;
}

void Funcs::setN(double nn)
{
    n = nn;
}
void Funcs::setM(double mm)
{
    m = mm;
}
