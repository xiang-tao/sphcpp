#pragma once
#include "head.h"
#include <algorithm> //提供min,max等函数
void self(str* vari, int& j1, int& kind_p1, int& ini_kind_p2)
{
    void kernel(str * vari, double& drx, double& dry, double& rr2);
    void kernel_correction(str * vari);
    void viscosity(str * vari, double& dot, double& rr2, double& cbar, double& robar, int& i, int& k);
    double drx = 0.0;
    double dry = 0.0;
    double dux = 0.0;
    double duy = 0.0;
    double rr2 = 0.0;
    double robar, one_over_robar, cbar;
    double fab, Ra, Rb, RR;
    double dot, p_v;
    double dot2i, dot2k;
    double pmk_wab_over_rhobar;
    double pmi_wab_over_rhobar;
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
                drx = vari->x[0][i] - vari->x[0][k];
                dry = vari->x[1][i] - vari->x[1][k];
                rr2 = drx * drx + dry * dry;
                if (rr2 < vari->fourh2 and rr2 > 1.0e-18) {
                    dux = vari->v[0][i] - vari->v[0][k];
                    duy = vari->v[1][i] - vari->v[1][k];
                    kernel(vari, drx, dry, rr2);
                    kernel_correction(vari);
                    robar = 0.5 * (vari->rho[i] + vari->rho[k]);
                    one_over_robar = 2.0 / (vari->rho[i] + vari->rho[k]);
                    cbar = 0.5 * (vari->cs[i] + vari->cs[k]);
                    dot = drx * dux + dry * duy;
                    vari->visc_dt = std::max(dot / (rr2 + vari->eta2), vari->visc_dt);
                    p_v = vari->pr[i] + vari->pr[k];
                    if (vari->index_tensile == 1) {
                        fab = vari->wab * vari->od_wdeltap;
                        fab = fab * fab;
                        fab = fab * fab;
                        if (vari->p[i] > 0.0) {
                            Ra = 0.01 * vari->pr[i];
                        } else {
                            Ra = 0.2 * std::abs(vari->pr[i]);
                        }
                        if (vari->p[k] > 0.0) {
                            Rb = 0.01 * vari->pr[k];
                        } else {
                            Rb = 0.2 * std::abs(vari->pr[k]);
                        }
                        RR = Ra + Rb;
                        p_v += RR * fab;
                    }
                    //加速度
                    vari->av[0][i] = vari->av[0][i] - vari->mass[k] * p_v * vari->frxi;
                    vari->av[1][i] = vari->av[1][i] - vari->mass[k] * p_v * vari->fryi;
                    vari->av[0][k] = vari->av[0][k] + vari->mass[i] * p_v * vari->frxj;
                    vari->av[1][k] = vari->av[1][k] + vari->mass[i] * p_v * vari->fryj;
                    viscosity(vari, dot, rr2, cbar, robar, i, k);
                    //计算密度变化
                    dot2i = dux * vari->frxi + duy * vari->fryi;
                    dot2k = dux * vari->frxj + duy * vari->fryj;
                    vari->ar[i] = vari->ar[i] + vari->mass[k] * dot2i;
                    vari->ar[k] = vari->ar[k] + vari->mass[i] * dot2k;
                    //XSPH校正
                    pmk_wab_over_rhobar = vari->mass[k] * vari->wab * one_over_robar;
                    vari->vx[0][i] -= dux * pmk_wab_over_rhobar;
                    vari->vx[1][i] -= duy * pmk_wab_over_rhobar;
                    pmi_wab_over_rhobar = vari->mass[i] * vari->wab * one_over_robar;
                    vari->vx[0][k] += dux * pmi_wab_over_rhobar;
                    vari->vx[1][k] += duy * pmi_wab_over_rhobar;
                }
            }
        }
    }
}
