#pragma once
#include "head.h"

void int_force(str* vari)
{
    int i, j, k, d;
    double hh = 0.0;
    double rhoij = 0.0;
    double gamma = 7.0;
    double rho0 = 1000.0;
    double B = 0.0;
    double c0 = 10.0;

    for (i = 0; i < vari->ntotal + vari->nvirt; i++) {
        B = c0 * c0 * rho0 / gamma;
        vari->p[i] = B * (pow((vari->rho[i] / rho0), gamma) - 1);
        vari->c[i] = B * gamma / rho0 * sqrt(pow((vari->rho[i] / rho0), gamma - 1));
    }

    for (k = 0; k < vari->niac; k++) {
        i = vari->pair_i[k];
        j = vari->pair_j[k];
        for (d = 0; d < dim; d++) {
            hh = -(vari->p[i] / pow(vari->rho[i], 2) + vari->p[j] / pow(vari->rho[j], 2)) * vari->dwdx[d][k];

            vari->dvxdt[d][i] += vari->mass[j] * hh;
            vari->dvxdt[d][j] -= vari->mass[i] * hh;
        }
    }
}
