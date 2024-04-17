#pragma once
#include "head.h"
#include <iostream>
void ac(str* vari)
{
    void cellij(str * vari, int& j1, int& j2, int& kind_p1, int& ini_kind_p2);
    void self(str * vari, int& j1, int& kind_p1, int& ini_kind_p2);
    int ntotal = vari->ntotal;
    int nvirt = vari->nvirt;
    int tot = ntotal + nvirt;

    //初始化相关数据信息
    for (int i = 0; i < tot; i++) {
        vari->pr[i] = vari->p[i] / (vari->rho[i] * vari->rho[i]);
        vari->one_over_rho[i] = 1.0 / vari->rho[i];
        vari->av[0][i] = 0.0; //加速度
        vari->av[1][i] = 0.0;
        vari->vx[0][i] = 0.0; //XSPH
        vari->vx[1][i] = 0.0;
        vari->ar[i] = 0.0; //密度变化
    }
    for (int kind_p1 = 0; kind_p1 <= 1; kind_p1++) {
        int ini_kind_p2 = (kind_p1 + 1) % 2;
        for (int ly = 0; ly < vari->ncy; ly++) {
            for (int lx = 0; lx < vari->ncx; lx++) {
                int j1 = lx + ly * vari->ncx;
                if (vari->nc[j1][kind_p1] > 0) {
                    int lx2 = lx + 1;
                    if (lx2 < vari->ncx) {
                        int j2 = j1 + 1;
                        cellij(vari, j1, j2, kind_p1, ini_kind_p2);
                    }
                    int ly2 = ly + 1;
                    if (ly2 < vari->ncy) {
                        int j2 = j1 + vari->ncx;
                        cellij(vari, j1, j2, kind_p1, ini_kind_p2);
                        lx2 = lx + 1;
                        if (lx2 > 1) {
                            int j2 = j1 + vari->ncx - 1;
                            cellij(vari, j1, j2, kind_p1, ini_kind_p2);
                        }
                        lx2 = lx + 1;
                        if (lx2 < vari->ncx) {
                            int j2 = j1 + vari->ncx + 1;
                            cellij(vari, j1, j2, kind_p1, ini_kind_p2);
                        }
                    }
                }
            }
        }
        for (int j1 = 0; j1 < vari->nct; j1++) {
            if (vari->nc[j1][kind_p1] > 0) {
                self(vari, j1, kind_p1, ini_kind_p2);
            }
        }
    }
    for (int i = 0; i < tot; i++) {
        vari->vdot[0][i] = vari->av[0][i];
        vari->vdot[1][i] = vari->av[1][i];
        vari->rdot[i] = vari->ar[i];
        vari->xcor[0][i] = eps * vari->vx[0][i];
        vari->xcor[1][i] = eps * vari->vx[1][i];
    }
}
