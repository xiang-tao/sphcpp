#pragma once
#include "head.h"

void int_force(str* vari)
{
    int i, j, k, d;
    double temp_dvx[dim];
    double temp_dedt;
    double dvx[dim];
    double hxx;
    double hyy;
    double hxy;
    double hh = 0.0;
    double he = 0.0;
    double rhoij = 0.0;

    for (i = 0; i < vari->ntotal + vari->nvirt; i++) {
        vari->txx[i] = 0.0;
        vari->tyy[i] = 0.0;
        vari->txy[i] = 0.0;
    }
    for (k = 0; k < vari->niac; k++) {
        i = vari->pair_i[k];
        j = vari->pair_j[k];

        for (d = 0; d < dim; d++) {
            dvx[d] = vari->v[d][j] - vari->v[d][i];
            //     if(dvx[d]!=0.0){
            //     std::cout<<dvx[d]<<std::endl;
            // }
        }

        hxx = 2.0 * dvx[0] * vari->dwdx[0][k] - dvx[1] * vari->dwdx[1][k];
        hxy = dvx[0] * vari->dwdx[1][k] + dvx[1] * vari->dwdx[0][k];
        hyy = 2.0 * dvx[1] * vari->dwdx[1][k] - dvx[0] * vari->dwdx[0][k];
        hxx = 2.0 / 3.0 * hxx;
        hyy = 2.0 / 3.0 * hyy;
        // if(hxx!=0.0){
        //     std::cout<<hxx<<std::endl;
        // }

        vari->txx[i] = vari->txx[i] + vari->mass[j] * hxx / vari->rho[j];
        vari->txx[j] = vari->txx[j] + vari->mass[i] * hxx / vari->rho[i];

        vari->txy[i] = vari->txy[i] + vari->mass[j] * hxy / vari->rho[j];
        vari->txy[j] = vari->txy[j] + vari->mass[i] * hxy / vari->rho[i];

        vari->tyy[i] = vari->tyy[i] + vari->mass[j] * hyy / vari->rho[j];
        vari->tyy[j] = vari->tyy[j] + vari->mass[i] * hyy / vari->rho[i];
    }
    for (i = 0; i < vari->ntotal + vari->nvirt; i++) {
        vari->p[i] = 1.0e-4 * vari->rho[i];
        // vari->p[i] = 0.1;
    }

    for (k = 0; k < vari->niac; k++) {
        i = vari->pair_i[k];
        j = vari->pair_j[k];
        he = 0.0;
        //rhoij = 1.0 / (vari->rho[i] * vari->rho[j]);
        for (d = 0; d < dim; d++) {
            hh = -(vari->p[i] / pow(vari->rho[i], 2) + vari->p[j] / pow(vari->rho[j], 2)) * vari->dwdx[d][k];
            he = he + (vari->v[d][j] - vari->v[d][i]) * hh;
            if (d == 0) {
                hh = hh + (eta * vari->txx[i] / pow(vari->rho[i], 2) + eta * vari->txx[j] / pow(vari->rho[j], 2)) * vari->dwdx[0][k];
                if (dim >= 2) {
                    hh = hh + (eta * vari->txy[i] / pow(vari->rho[i], 2) + eta * vari->txy[j] / pow(vari->rho[j], 2)) * vari->dwdx[1][k];
                }
            } else if (d == 1) {
                hh = hh + (eta * vari->txy[i] / pow(vari->rho[i], 2) + eta * vari->txy[j] / pow(vari->rho[j], 2)) * vari->dwdx[0][k]
                    + (eta * vari->tyy[i] / pow(vari->rho[i], 2) + eta * vari->tyy[j] / pow(vari->rho[j], 2)) * vari->dwdx[1][k];
            }

            vari->dvxdt[d][i] += vari->mass[j] * hh;
            vari->dvxdt[d][j] -= vari->mass[i] * hh;
        }
        vari->dedt[i] += vari->mass[j] * he;
        vari->dedt[j] += vari->mass[i] * he;
    }
    // for (k = 0; k < 100; k++) {
    //     std::cout << vari->dvxdt[0][k] << " " << vari->dvxdt[1][k] << std::endl;
    // }
}
