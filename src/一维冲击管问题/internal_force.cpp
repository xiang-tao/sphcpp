#pragma once
#include "head.h"

void int_force(str* vari)
{
    int i, j, k, d;
    double temp_dvx[dim];
    double temp_dedt[tot_maxn];
    double dvx[dim];
    double hxx;
    double hh = 0.0;
    double he = 0.0;
    double gamma = 1.4;

    for (i = 0; i < vari->ntotal; i++) {
        temp_dedt[i] = 0.0;
        vari->p[i] = (gamma - 1) * vari->rho[i] * vari->e[i];
        vari->c[i] = sqrt((gamma - 1) * vari->e[i]);
    }

    for (k = 0; k < vari->niac; k++) {
        i = vari->pair_i[k];
        j = vari->pair_j[k];
        he = 0.0;
        //rhoij = 1.0 / (vari->rho[i] * vari->rho[j]);
        for (d = 0; d < dim; d++) {
            hh = -(vari->p[i] / pow(vari->rho[i], 2) + vari->p[j] / pow(vari->rho[j], 2)) * vari->dwdx[d][k];
            he = he + (vari->v[d][j] - vari->v[d][i]) * hh;

            vari->dvxdt[d][i] += vari->mass[j] * hh;
            vari->dvxdt[d][j] -= vari->mass[i] * hh;
        }
        temp_dedt[i] += vari->mass[j] * he;
        temp_dedt[j] += vari->mass[i] * he;
    }
    for (i = 0; i < vari->ntotal; i++) {
        vari->dedt[i] += 0.5 * temp_dedt[i];
    }
}
