#pragma once
#include "head.h"
void viscosity(str* vari, double& dot, double& rr2, double& cbar, double& robar, int& i, int& k)
{
    double amubar = 0.0;
    double pi_visc = 0.0;
    if (dot < 0) {
        amubar = vari->hsml * dot / (rr2 + vari->eta2);
        pi_visc = -viscos_val * cbar * amubar / robar;
    } else {
        pi_visc = 0.0;
    }
    vari->av[0][i] = vari->av[0][i] - vari->mass[k] * pi_visc * vari->frxi;
    vari->av[1][i] = vari->av[1][i] - vari->mass[k] * pi_visc * vari->fryi;
    vari->av[0][k] = vari->av[0][k] + vari->mass[i] * pi_visc * vari->frxj;
    vari->av[1][k] = vari->av[1][k] + vari->mass[i] * pi_visc * vari->fryj;
}
