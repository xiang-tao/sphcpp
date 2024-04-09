#pragma once
#include "head.h"
//连续密度法
void density_con(str* vari)
{
    int i, j, k, d;
    double r, dvx[dim], vcc;
    for (d = 0; d < vari->ntotal + vari->nvirt; d++) {
        vari->drho[d] = 0.0;
    }
    for (k = 0; k < vari->niac; k++) {
        i = vari->pair_i[k];
        j = vari->pair_j[k];
        for (d = 0; d < dim; d++) {
            dvx[d] = vari->v[d][i] - vari->v[d][j];
        }
        vcc = 0.0;
        for (d = 0; d < dim; d++) {
            vcc += dvx[d] * vari->dwdx[d][k];
        }
        vari->drho[i] = vari->drho[i] + vari->mass[j] * vcc;
        vari->drho[j] = vari->drho[j] + vari->mass[i] * vcc;
    }
    for (d = 0; d < vari->ntotal + vari->nvirt; d++) {
        vari->rho[d] = vari->rho[d] + dt * vari->drho[d];
    }
}
