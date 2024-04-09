#pragma once
#include "head.h"
void single_step(str* vari)
{
    void direct_find(str * vari);
    void density_sum(str * vari);
    void viscous_force(str * vari);
    void external_force(str * vari);
    void single_fluid(str * vari);
    void virt_part(str * vari);
    void NS_pressure(str * vari);
    void av_vel(str * vari);
    void int_force(str * vari);

    //if (virtual_part) {
     //   virt_part(vari);
   // }
    for (int i = 0; i < vari->ntotal + vari->nvirt; i++) //�Ƿ�Ҫѭ����ntotal+nvirt?
    {
        vari->dvxdt[0][i] = 0.0;
        vari->dvxdt[1][i] = 0.0;
        vari->dedt[i] = 0.0;
    }
    direct_find(vari);
    density_sum(vari);
    int_force(vari);

    // NS_pressure(vari);
    // viscous_force(vari);
    // single_fluid(vari);
    external_force(vari);
    av_vel(vari);
}
