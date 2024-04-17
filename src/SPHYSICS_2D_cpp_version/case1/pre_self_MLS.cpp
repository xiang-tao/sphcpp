#pragma once
#include "head.h"
#include <algorithm> //提供min,max等函数
void pre_self_MLS(str* vari, int& j1, int& kind_p1, int& ini_kind_p2)
{
    void kernel(str * vari, double& drx, double& dry, double& rr2);
    double drx = 0.0;
    double dry = 0.0;
    double rr2 = 0.0;
    double v_k, v_i;
    double wab_MLSi, wab_MLSk;
    for (int kind_p2 = ini_kind_p2; kind_p2 <= 1; kind_p2++) {
        int kk_start = 0;
        if (kind_p1 > kind_p2) {
            kk_start = nplink_max;
        }
        for (int ii = 0; ii < vari->nc[j1][kind_p1]; ii++) {
            int i = vari->ibox[j1][kind_p1][ii];
            if (kind_p1 == kind_p2) {
                kk_start += 1;
            }
            for (int kk = kk_start; kk < vari->nc[j1][kind_p2]; kk++) {
                int k = vari->ibox[j1][kind_p2][kk];

                if (i < vari->ntotal and k < vari->ntotal) {
                    drx = vari->x[0][i] - vari->x[0][k];
                    dry = vari->x[1][i] - vari->x[1][k];
                    rr2 = drx * drx + dry * dry;
                    if (rr2 < vari->fourh2 and rr2 > 1.0e-18) {
                        kernel(vari, drx, dry, rr2);
                        v_k = vari->pvol[k];
                        v_i = vari->pvol[i];
                        if (vari->i_MLS_part == 1) {
                            //i-matrix
                            vari->A_MLS[i][0][0] += vari->wab * v_k;
                            vari->A_MLS[i][0][1] += drx * vari->wab * v_k;
                            vari->A_MLS[i][0][2] += dry * vari->wab * v_k;

                            vari->A_MLS[i][1][1] += drx * drx * vari->wab * v_k;
                            vari->A_MLS[i][1][2] += drx * dry * vari->wab * v_k;

                            vari->A_MLS[i][2][2] += dry * dry * vari->wab * v_k;

                            //k-matrix
                            vari->A_MLS[k][0][0] += vari->wab * v_i;
                            vari->A_MLS[k][0][1] -= drx * vari->wab * v_i; //注意是-=
                            vari->A_MLS[k][0][2] -= dry * vari->wab * v_i;

                            vari->A_MLS[k][1][1] += drx * drx * vari->wab * v_i;
                            vari->A_MLS[k][1][2] += drx * dry * vari->wab * v_i;

                            vari->A_MLS[k][2][2] += dry * dry * vari->wab * v_i;
                        } else {
                            wab_MLSi = (vari->beta0_MLS[i] + vari->beta1x_MLS[i] * drx + vari->beta1y_MLS[i] * dry) * vari->wab;
                            wab_MLSk = (vari->beta0_MLS[k] - vari->beta1x_MLS[k] * drx - vari->beta1y_MLS[k] * dry) * vari->wab;
                            vari->rho_sum_MLS[i] += vari->mass[k] * wab_MLSi;
                            vari->rho_sum_MLS[k] += vari->mass[i] * wab_MLSk;
                        }
                    }
                }
            }
        }
    }
}
