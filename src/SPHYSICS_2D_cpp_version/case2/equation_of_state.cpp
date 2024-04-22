#pragma once
#include "head.h"
void equation_of_state(str* vari, int& n)
{
    double B = vari->B;
    double rho0 = 1000.0;
    double gamma = 7.0;
    vari->p[n] = B * (pow(vari->rho[n] / rho0, gamma) - 1.0);
    vari->cs[n] = vari->cs0 * pow(vari->rho[n] / rho0, 3);
}
