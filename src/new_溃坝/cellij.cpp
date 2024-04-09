#pragma once
#include "head.h"
void cellij(str* vari, int j1, int j2, int kind_p1, int ini_kind_p2, int lx2)
{
    void kernel(str * vari, double drx, double dry, int i, int k, int j1, int j2, double rr2);
    void kernel_correction(str * vari, int i, int k);
    double drx = 0.0;
    double dry = 0.0;
    double dux = 0.0;
    double duy = 0.0;
    double rr2 = 0.0;
    for (int kind_p2 = ini_kind_p2; kind_p2 <= 1; kind_p2++) {
        if (vari->nc[j2][kind_p2] != 0) {
            for (int ii = 0; ii < vari->nc[j1][kind_p1]; ii++) {
                int i = vari->ibox[j1][kind_p1][ii];

                for (int kk = 0; kk < vari->nc[j2][kind_p2]; kk++) {
                    int k = vari->ibox[j2][kind_p2][kk];
                    drx = vari->x[0][i] - vari->x[0][k];
                    dry = vari->x[1][i] - vari->x[1][k];
                    rr2 = drx * drx + dry * dry;
                    if (rr2 < vari->fourh2 and rr2 > 0.0) {
                        dux = vari->v[0][i] - vari->v[0][k];
                        duy = vari->v[1][i] - vari->v[1][k];
                        kernel(vari, drx, dry, i, k, j1, j2, rr2);
                        kernel_correction(vari, i, k);
                    }
                }
            }
        }
    }
}
