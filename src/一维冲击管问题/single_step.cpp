#pragma once
#include "head.h"
void single_step(str* vari)
{
    void direct_find(str * vari);
    void density_sum(str * vari);
    void int_force(str * vari);
    void art_visc(str * vari);

    for (int i = 0; i < vari->ntotal; i++) //是否要循环到ntotal+nvirt?
    {
        vari->dvxdt[0][i] = 0.0;
        vari->dedt[i] = 0.0;
    }
    direct_find(vari);
    density_sum(vari);
    int_force(vari);
    art_visc(vari);
}
