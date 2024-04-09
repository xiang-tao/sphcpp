#pragma once
#include "head.h"

void single_fluid(str* vari)
{
    int i, j, k, d;
    double temp_dvx[dim];
    double dx[dim];
    double rr;
    double dT;

    for (k = 0; k < vari->niac; k++) {
        i = vari->pair_i[k];
        j = vari->pair_j[k];

        /////粘性应力项

        temp_dvx[0] = eta * (vari->txx[i] / pow(vari->rho[i], 2) + vari->txx[j] / pow(vari->rho[j], 2)) * vari->dwdx[0][k]
            + eta * (vari->txy[i] / pow(vari->rho[i], 2) + vari->txy[j] / pow(vari->rho[j], 2)) * vari->dwdx[1][k];

        temp_dvx[1] = eta * (vari->txy[i] / pow(vari->rho[i], 2) + vari->txy[j] / pow(vari->rho[j], 2)) * vari->dwdx[0][k]
            + eta * (vari->tyy[i] / pow(vari->rho[i], 2) + vari->tyy[j] / pow(vari->rho[j], 2)) * vari->dwdx[1][k];

        for (d = 0; d < dim; d++) {
            vari->dvxdt[d][i] = vari->dvxdt[d][i] + vari->mass[j] * temp_dvx[d];
            vari->dvxdt[d][j] = vari->dvxdt[d][j] - vari->mass[i] * temp_dvx[d];
        }
    }
}
