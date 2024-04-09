#pragma once
#include "head.h"

void input(double* time, int* timestep, str* vari)

{
    *timestep = 0;
    *time = 0;
    double dx = xl / mp;
    double dy = yl / np;

    for (int i = 0; i < vari->ntotal; i++) {

        vari->rho[i] = 1000.0;
        vari->mass[i] = vari->rho[i] * dx * dy;

        vari->p[i] = 0.0;
        vari->e[i] = 357.1;
        vari->v[0][i] = 0.0;
        vari->v[1][i] = 0.0;
        vari->hsml[i] = dx;
    }
}
