#pragma once
#include "head.h"

void NS_pressure(str* vari)
{
    int i, j, k, d;
    double temp_dvx[dim];
    double temp_dedt;
    for (i = 0; i < vari->ntotal + vari->nvirt; i++) {
        if (abs(vari->itype[i]) == 2) {
            vari->p[i] = 0.1;
        }
    }
    for (k = 0; k < vari->niac; k++) {
        i = vari->pair_i[k];
        j = vari->pair_j[k];
        temp_dvx[0] = -(vari->p[i] / pow(vari->rho[i], 2) + vari->p[j] / pow(vari->rho[j], 2)) * vari->dwdx[0][k];
        temp_dvx[1] = -(vari->p[i] / pow(vari->rho[i], 2) + vari->p[j] / pow(vari->rho[j], 2)) * vari->dwdx[1][k];
        for (d = 0; d < dim; d++) {
            vari->dvxdt[d][i] = vari->dvxdt[d][i] + vari->mass[j] * temp_dvx[d];
            vari->dvxdt[d][j] = vari->dvxdt[d][j] - vari->mass[i] * temp_dvx[d];
        }
        temp_dedt = temp_dvx[0] * (vari->v[0][j] - vari->v[0][i]) + temp_dvx[1] * (vari->v[1][j] - vari->v[1][i]);
        vari->dedt[i] = vari->dedt[i] + vari->mass[j] * temp_dedt;
        vari->dedt[j] = vari->dedt[j] + vari->mass[i] * temp_dedt;
    }
}
