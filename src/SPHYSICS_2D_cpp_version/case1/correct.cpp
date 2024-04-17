#pragma once
#include "head.h"
void correct(str* vari)
{
    //考虑重力
    for (int i = 0; i < vari->ntotal; i++) {
        vari->vdot[0][i] += grx * vari->itype[i];
        vari->vdot[1][i] += gry * vari->itype[i];
    }

    //XSPH校正
    for (int i = 0; i < vari->ntotal; i++) {
        vari->xdot[0][i] = vari->v[0][i] + vari->xcor[0][i];
        vari->xdot[1][i] = vari->v[1][i] + vari->xcor[1][i];
    }
}
