#include "head.h"
#include <iostream>
void art_visc(str* vari)
{
    double alpha = 1.0;
    double beta = 1.0;
    double etq = 0.1;
    double dvx[dim];
    double dedt_temp[tot_maxn];
    int i, j;
    double mhsml, hh, vr, rr, dx, muv, mrho, piv, mc;
    for (i = 0; i < vari->ntotal; i++) {
        dedt_temp[i] = 0.0;
    }
    for (int k = 0; k < vari->niac; k++) {
        i = vari->pair_i[k];
        j = vari->pair_j[k];
        mhsml = (vari->hsml[i] + vari->hsml[j]) / 2;
        vr = 0.0;
        rr = 0.0;
        for (int d = 0; d < dim; d++) {
            dvx[d] = vari->v[d][i] - vari->v[d][j];
            dx = vari->x[d][i] - vari->x[d][j];
            vr = vr + dvx[d] * dx;
            rr = rr + dx * dx;
        }
        if (vr < 0.0) {
            // std::cout << "hello vr" << std::endl;
            muv = mhsml * vr / (rr + mhsml * mhsml * etq * etq);
            mc = 0.5 * (vari->c[i] + vari->c[j]);
            mrho = 0.5 * (vari->rho[i] + vari->rho[j]);
            piv = (beta * muv - alpha * mc) * muv / mrho;
            for (int d = 0; d < dim; d++) {
                hh = -piv * vari->dwdx[d][k];
                vari->dvxdt[d][i] += vari->mass[j] * hh;
                vari->dvxdt[d][j] -= vari->mass[i] * hh;
                dedt_temp[i] -= vari->mass[j] * dvx[d] * hh;
                dedt_temp[j] -= vari->mass[i] * dvx[d] * hh;
            }
        }
    }
    for (i = 0; i < vari->ntotal; i++) {
        vari->dedt[i] += 0.5 * dedt_temp[i];
    }
}
