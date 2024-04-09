#pragma once
#include "head.h"
void single_step(str* vari)
{
    void direct_find(str * vari);
    void density_sum(str * vari);
    void density_con(str * vari);
    void int_force(str * vari);
    void external_force(str * vari);
    void av_vel(str * vari);

    for (int i = 0; i < vari->ntotal + vari->nvirt; i++) //是否要循环到ntotal+nvirt?
    {
        vari->dvxdt[0][i] = 0.0;
        vari->dvxdt[1][i] = 0.0;
        vari->dedt[i] = 0.0;
    }
    direct_find(vari);
    density_con(vari);
    int_force(vari);

    external_force(vari);
    av_vel(vari);
}
