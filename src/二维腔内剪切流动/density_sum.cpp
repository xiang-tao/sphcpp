#pragma once
#include "head.h"
void density_sum(str* vari)
{
    void kernel(double r, double hv[dim], double hsml_selfdens, double* w, double dwhv[dim]);
    int i, j, k, d;
    double r, hv[dim], hsml_selfdens, selfdens, dwhv[dim];
    for (d = 0; d < dim; d++) {
        hv[d] = 0.0;
    }
    r = 0.0;
    hsml_selfdens = vari->hsml[1];
    kernel(r, hv, hsml_selfdens, &selfdens, dwhv);
    for (i = 0; i < vari->ntotal+vari->nvirt; i++) {
        
        vari->rho[i] = selfdens * vari->mass[i];
    }
    for (k = 0; k < vari->niac; k++) {
        i = vari->pair_i[k];
        j = vari->pair_j[k];
        vari->rho[i] = vari->rho[i] + vari->mass[j] * vari->w[k];
        vari->rho[j] = vari->rho[j] + vari->mass[i] * vari->w[k];
    }
}
