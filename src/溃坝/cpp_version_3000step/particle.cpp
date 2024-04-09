#pragma once
#include "head.h"
#include <string>
using namespace std;

void particle(str* vari)

{
    void output(str * vari, const string& name, int cc = 0);

    vari->ntotal = 0;
    double dx = 0.03;
    double dy = 0.03;
    int mp = int(xl / dx); //int取整为去除小数部分，如int(4.1)=4,int(4.9)=4
    int np = int(yl / dy);
    for (int i = 2; i < mp + 2; i++) {
        for (int j = 2; j < np + 2; j++) {
            vari->x[0][vari->ntotal] = i * dx;
            vari->x[1][vari->ntotal] = j * dy;
            vari->ntotal = vari->ntotal + 1;
            vari->itype[vari->ntotal] = 2;
        }
    }
    // output(vari, "vtk_coor.vtu");
}
