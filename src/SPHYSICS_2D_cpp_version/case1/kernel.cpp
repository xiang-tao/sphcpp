#pragma once
#include "head.h"
void kernel(str* vari, double& drx, double& dry, double& rr2)
{
    double rad, qq, wqq, wqq1, wqq2, wqq3, wqq4, fac;
    rad = sqrt(rr2);
    qq = rad / vari->hsml;
    wqq = 2.0 * qq + 1.0;
    wqq1 = 1.0 - 0.5 * qq;
    wqq2 = wqq1 * wqq1;
    wqq3 = wqq2 * wqq1;
    wqq4 = wqq3 * wqq1;
    vari->wab = vari->Awen * wqq * wqq4;
    fac = vari->Bwen * qq * wqq3 / rad;
    vari->frx = fac * drx;
    vari->fry = fac * dry;
}
