#pragma once
#include "head.h"

void viscous_force(str* vari)
{
    int i, j, k, d;

    double dvx[dim];
    double hxx;
    double hyy;
    double hxy;

    for (i = 0; i < vari->ntotal; i++) {
        vari->txx[i] = 0.0;
        vari->tyy[i] = 0.0;
        vari->txy[i] = 0.0;
    }

    for (k = 0; k < vari->niac; k++) {
        i = vari->pair_i[k];
        j = vari->pair_j[k];

        for (d = 0; d < dim; d++) {
            dvx[d] = vari->v[d][j] - vari->v[d][i];
        }

        hxx = 2.0 * dvx[0] * vari->dwdx[0][k] - dvx[1] * vari->dwdx[1][k];
        hxy = dvx[0] * vari->dwdx[1][k] + dvx[1] * vari->dwdx[0][k];
        hyy = 2.0 * dvx[1] * vari->dwdx[1][k] - dvx[0] * vari->dwdx[0][k];
        hxx = 2.0 / 3.0 * hxx;
        hyy = 2.0 / 3.0 * hyy;

        ////////////////////////////////////////Õ³ÐÔÓ¦Á¦
        vari->txx[i] = vari->txx[i] + vari->mass[j] * hxx / vari->rho[j];
        vari->txx[j] = vari->txx[j] + vari->mass[i] * hxx / vari->rho[i];

        vari->txy[i] = vari->txy[i] + vari->mass[j] * hxy / vari->rho[j];
        vari->txy[j] = vari->txy[j] + vari->mass[i] * hxy / vari->rho[i];

        vari->tyy[i] = vari->tyy[i] + vari->mass[j] * hyy / vari->rho[j];
        vari->tyy[j] = vari->tyy[j] + vari->mass[i] * hyy / vari->rho[i];
    }
}
