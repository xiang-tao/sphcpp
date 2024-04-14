#pragma once
#include "head.h"
#include <algorithm> //提供min,max等函数
#include <iostream>
void variable_time_step(str* vari)
{
    double Fa_max = -1000.0;
    double Fa = 0.0;
    double cs_max = -1000.0;
    int i_fa = -1000;
    int nstart_VTS = 0;
    //计算每单位质量力和声速的最大值
    for (int i = nstart_VTS; i < vari->ntotal; i++) {
        Fa = sqrt(vari->av[0][i] * vari->av[0][i] + vari->av[1][i] * vari->av[1][i]);
        if (Fa >= Fa_max) {
            i_fa = i;
            Fa_max = Fa;
        }
        if (vari->cs[i] >= cs_max) {
            cs_max = vari->cs[i];
        }
    }
    //计算使用手册公式p25页
    double fa_sqrt, dt_1, dt_2;
    if (i_fa >= 0) {
        fa_sqrt = pow((vari->av[0][i_fa] + grx) * (vari->av[0][i_fa] + grx) + (vari->av[1][i_fa] + gry) * (vari->av[1][i_fa] + gry), 0.25);
        dt_1 = sqrt(vari->hsml) / fa_sqrt;
    } else {
        fa_sqrt = pow(grx * grx + gry * gry, 0.25);
        dt_1 = sqrt(vari->hsml) / fa_sqrt;
    }
    if (cs_max > 0.0) {
        dt_2 = vari->hsml / (cs_max + vari->hsml * vari->visc_dt);

    } else {
        dt_2 = dt_1;
    }
    vari->min_dt = CFL_number * std::min(dt_1, dt_2);
    // std::cout << "dt_1=" << dt_1 << "  "
    //           << "dt_2" << dt_2 << std::endl;
}
