#pragma once
#include "head.h"
#include <iostream>
void divide(str* vari, int n_start, int n_end, int kind_p)
{
    double dx, dy;
    int icell = 0, kcell = 0, ii = 0;
    for (int k = n_start; k < n_end; k++) {
        if (vari->itype[k] != 0) {
            dx = vari->x[0][k] - vari->xmin;
            dy = vari->x[1][k] - vari->ymin;
            icell = int(dx * vari->one_over_2h) + 1;
            kcell = int(dy * vari->one_over_2h) + 1;
            ii = icell - 1 + (kcell - 1) * vari->ncx;
            vari->nc[ii][kind_p] += 1;
            if (vari->nc[ii][kind_p] > nplink_max) {
                std::cout << "列表粒子超过了120" << std::endl;
                exit(0);
            }
            vari->ibox[ii][kind_p][vari->nc[ii][kind_p] - 1] = k;
        }
    }
}
