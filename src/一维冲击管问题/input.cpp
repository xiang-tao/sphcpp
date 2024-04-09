#pragma once
#include "head.h"
#include <string>
using namespace std;

void input(double* time, int* timestep, str* vari)

{
    void output_x(str * vari, const string& name, int cc = 0);
    *timestep = 0;
    *time = 0;
    vari->ntotal = 400;
    double space_x = 0.6 / 80;

    for (int i = 0; i < vari->ntotal; i++) {
        vari->mass[i] = 0.75 / 400;
        vari->hsml[i] = 0.015;
        vari->itype[i] = 1;
        for (int d = 0; d < dim; d++) {
            vari->x[d][i] = 0.0;
            vari->v[d][i] = 0.0;
        }
    }
    for (int i = 0; i < 320; i++) {
        vari->x[0][i] = -0.6 + space_x / 4 * i;
    }
    for (int i = 320; i < vari->ntotal; i++) {
        vari->x[0][i] = 0.0 + space_x * (i - 320 + 1);
    }
    for (int i = 0; i < vari->ntotal; i++) {
        if (vari->x[0][i] <= 1.0e-8) {
            vari->e[i] = 2.5;
            vari->rho[i] = 1.0;
            vari->p[i] = 1.0;
        }
        if (vari->x[0][i] > 1.0e-8) {
            vari->e[i] = 1.795;
            vari->rho[i] = 0.25;
            vari->p[i] = 0.1795;
        }
    }
    output_x(vari, "coor.txt");
}
