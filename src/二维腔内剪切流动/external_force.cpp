#pragma once
#include "head.h"
#include <iostream>
void external_force(str* vari)
{
    double rr0 = 1.25e-5;
    double dd = 1.0e-2;
    double f = 0.0;
    double dx[dim];
    int p1 = 12;
    int p2 = 4;
    for (int k = 0; k < vari->niac; k++) {
        int i = vari->pair_i[k];
        int j = vari->pair_j[k];
        if (vari->itype[i] > 0 and vari->itype[j] < 0) {
            double rr = 0.0;
            for (int d = 0; d < dim; d++) {
                dx[d] = vari->x[d][i] - vari->x[d][j];
                rr = rr + dx[d] * dx[d];
            }
            rr = sqrt(rr);
            if (rr < rr0) {
                f = (pow(rr0 / rr, p1) - pow(rr0 / rr, p2)) / pow(rr, 2);
                // std::cout << "hello f" << std::endl;
                for (int d = 0; d < dim; d++) {
                    vari->dvxdt[d][i] = vari->dvxdt[d][i] + dd * dx[d] * f;
                }
            }
        }
    }
}
