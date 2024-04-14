#pragma once
#include "head.h"
#include <algorithm> //提供min,max等函数
void single_step(str* vari)
{
    void check_limits(str * vari);
    void ini_divide(str * vari, int kind_p);
    void divide(str * vari, int n_start, int n_end, int kind_p);
    void ac(str * vari);
    void correct(str * vari);
    void variable_time_step(str * vari);
    void equation_of_state(str * vari, int n);

    double dt2 = 0.5 * vari->new_dt;
    double rho0 = 1000.0;
    int iDBC;

    //计算n时刻相关信息
    check_limits(vari);
    ini_divide(vari, 1);
    divide(vari, 0, vari->ntotal, 1);
    ac(vari);
    correct(vari);
    variable_time_step(vari);
    vari->ddt_p = vari->min_dt;

    int tot = vari->ntotal + vari->nvirt;
    for (int i = 0; i < tot; i++) {
        vari->xo[0][i] = vari->x[0][i];
        vari->xo[1][i] = vari->x[1][i];
        vari->vo[0][i] = vari->v[0][i];
        vari->vo[1][i] = vari->v[1][i];
        vari->po[i] = vari->p[i];
        vari->rhoo[i] = vari->rho[i];
    }
    for (int i = 0; i < vari->ntotal; i++) {
        vari->rho[i] = vari->rhoo[i] + dt2 * vari->rdot[i];
        vari->pvol[i] = vari->mass[i] / vari->rho[i];
        equation_of_state(vari, i);
    }
    if (IBC == 2) {
        vari->nstep_DBC += 1;
        iDBC = 0;
        if (vari->nstep_DBC % 15 == 0) {
            for (int i = vari->ntotal; i < tot; i++) {
                vari->rho[i] = vari->rhoo[i] + dt2 * vari->rdot[i];
                if (vari->rho[i] < rho0) {
                    vari->rho[i] = rho0;
                }
                vari->pvol[i] = vari->mass[i] / vari->rho[i];
                equation_of_state(vari, i);
            }
            iDBC = 1;
            vari->nstep_DBC = 0;
        }
    }
    for (int i = 0; i < vari->ntotal; i++) {
        vari->x[0][i] = vari->xo[0][i] + dt2 * vari->xdot[0][i];
        vari->x[1][i] = vari->xo[1][i] + dt2 * vari->xdot[1][i];
        vari->v[0][i] = vari->vo[0][i] + dt2 * vari->vdot[0][i];
        vari->v[1][i] = vari->vo[1][i] + dt2 * vari->vdot[1][i];
    }

    //计算n+1/2时刻相关信息
    check_limits(vari);
    ini_divide(vari, 1);
    divide(vari, 0, vari->ntotal, 1);
    ac(vari);
    correct(vari);

    variable_time_step(vari);
    vari->ddt_c = vari->min_dt;

    vari->new_dt = std::min(vari->ddt_c, vari->ddt_p);

    for (int i = 0; i < vari->ntotal; i++) {
        vari->rho[i] = vari->rhoo[i] + dt2 * vari->rdot[i];
    }
    if (iDBC == 1) {
        for (int i = vari->ntotal; i < tot; i++) {
            vari->rho[i] = vari->rhoo[i] + dt2 * vari->rdot[i];
            if (vari->rho[i] < rho0) {
                vari->rho[i] = rho0;
            }
        }
    }
    for (int i = 0; i < vari->ntotal; i++) {
        vari->x[0][i] = vari->xo[0][i] + dt2 * vari->xdot[0][i];
        vari->x[1][i] = vari->xo[1][i] + dt2 * vari->xdot[1][i];
        vari->v[0][i] = vari->vo[0][i] + dt2 * vari->vdot[0][i];
        vari->v[1][i] = vari->vo[1][i] + dt2 * vari->vdot[1][i];
    }
    for (int i = 0; i < vari->ntotal; i++) {
        vari->rho[i] = 2 * vari->rho[i] - vari->rhoo[i];
        vari->pvol[i] = vari->mass[i] / vari->rho[i];
        equation_of_state(vari, i);
    }
    if (iDBC == 1) {
        for (int i = vari->ntotal; i < tot; i++) {
            vari->rho[i] = 2 * vari->rho[i] - vari->rhoo[i];
            if (vari->rho[i] < rho0) {
                vari->rho[i] = rho0;
            }
            vari->pvol[i] = vari->mass[i] / vari->rho[i];
            equation_of_state(vari, i);
        }
    }
    for (int i = 0; i < vari->ntotal; i++) {
        vari->x[0][i] = 2 * vari->x[0][i] - vari->xo[0][i];
        vari->x[1][i] = 2 * vari->x[1][i] - vari->xo[1][i];
        vari->v[0][i] = 2 * vari->v[0][i] - vari->vo[0][i];
        vari->v[1][i] = 2 * vari->v[1][i] - vari->vo[1][i];
    }
}
