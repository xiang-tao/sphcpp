#pragma once
#include "head.h"
void av_vel(str* vari)
{
    double epsilon = 0.3;
    double dvx[dim];
    for (int i = 0; i < vari->ntotal; i++) {
        for (int d = 0; d < dim; d++) {
            vari->av[d][i] = 0.0;
        }
    }
    for (int k = 0; k < vari->niac; k++) {
        int i = vari->pair_i[k];
        int j = vari->pair_j[k];
        for (int d = 0; d < dim; d++) {
            dvx[d] = vari->v[d][i] - vari->v[d][j];
            vari->av[d][i] = vari->av[d][i] - 2 * vari->mass[j] * dvx[d] / (vari->rho[i] + vari->rho[j]) * vari->w[k];
            vari->av[d][j] = vari->av[d][j] + 2 * vari->mass[i] * dvx[d] / (vari->rho[i] + vari->rho[j]) * vari->w[k];
        }
    }
    for (int i = 0; i < vari->ntotal; i++) {
        for (int d = 0; d < dim; d++) {
            vari->av[d][i] = epsilon * vari->av[d][i];
        }
    }
}
