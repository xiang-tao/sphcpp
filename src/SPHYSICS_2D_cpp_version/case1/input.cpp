#pragma once
#include "head.h"
#include <iostream>

void input(str* vari)

{
    void equation_of_state(str * vari, int& n);

    double dx = 0.03;
    double dy = 0.03;
    double rho0 = 1000.0;
    double g = 9.81;
    double gamma = 7.0;
    double c0 = 10.0;
    double h_SML = 2.0;

    vari->B = c0 * c0 * rho0 * g * h_SML / gamma;
    vari->cs0 = sqrt(vari->B * gamma / rho0);
    // std::cout << "cs0=" << vari->cs0 << std::endl;
    double expont = 1.0 / gamma;
    vari->hsml = 0.92 * sqrt(dx * dx + dy * dy); //光滑长度由于不变故不用数组形式
    for (int i = 0; i < vari->ntotal; i++) {

        vari->rho[i] = rho0 * pow((1.0 + rho0 * g * (2.0 - vari->x[1][i]) / vari->B), expont);
        vari->rhoo[i] = 0.0;
        vari->mass[i] = vari->rho[i] * dx * dy * 0.5;
        vari->pvol[i] = vari->mass[i] / vari->rho[i];

        vari->p[i] = vari->B * (pow((vari->rho[i] / rho0), gamma) - 1.0);
        // vari->e[i] = 357.1;
        vari->v[0][i] = 0.0;
        vari->v[1][i] = 0.0;
        vari->vo[0][i] = 0.0;
        vari->vo[1][i] = 0.0;
        equation_of_state(vari, i);
    }
}
