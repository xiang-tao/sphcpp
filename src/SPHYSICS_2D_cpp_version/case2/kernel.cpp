#pragma once
#include "head.h"
void kernel(str* vari, double& drx, double& dry, double& rr2)
{
    double rad, qq, tmq, tm2, tm3, q2, q3, fac;

    vari->index_tensile = 1;
    rad = sqrt(rr2);
    qq = rad / vari->hsml;
    if (rr2 > vari->h2) {
        tmq = 2.0 - qq;
        tm2 = tmq * tmq;
        tm3 = tm2 * tmq;
        vari->wab = vari->aa24 * tm3;

        fac = vari->cc2 * tm2 / rad;
        vari->frx = fac * drx;
        vari->fry = fac * dry;
    } else {
        q2 = qq * qq;
        q3 = q2 * qq;
        vari->wab = vari->aa2 * (1.0 - 1.5 * q2 + 0.75 * q3);
        fac = (vari->cc1 * qq + vari->dd1 * q2) / rad;
        vari->frx = fac * drx;
        vari->fry = fac * dry;
    }
}
