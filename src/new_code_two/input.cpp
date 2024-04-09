#pragma once
#include "head.h"

void input(double* time, int* timestep, str* vari)

{
    void direct_find(str * vari, int m);
    void density_sum(str * vari);
    /////////////////////////////////////////////////////////////////////////////////////////
    int i;

    if (input_data) {
        ///////////////////////////////////²Î¿¼×¤²¨³ÌÐò

    } else {
        *timestep = 0;
        *time = 0;

        for (i = 0; i < vari->ntotal; i++) {
            vari->mass[i] = 1.0;
            vari->hsml[i] = h * eta;
            vari->hsml2[i] = 2 * h * eta;
        }

        direct_find(vari, 1);
        density_sum(vari);

        for (i = 0; i < vari->ntotal; i++) {

            vari->T[i] = 0.2;

            vari->p[i] = (vari->rho[i] * kc * vari->T[i]) / (1 - vari->rho[i] * b);
            //vari->p[i] = vari->rho[i] * kc*vari->T[i] / (1 - vari->rho[i] * b) - a*vari->rho[i] * vari->rho[i];
            vari->e[i] = kc * vari->T[i] - a * vari->rho[i];
            vari->v[0][i] = 0.0;
            vari->v[1][i] = 0.0;
        }
    }
}
