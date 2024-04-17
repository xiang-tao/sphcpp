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
    for (int i = 1; i < mp + 1; i++) {
        for (int j = 1; j < np + 1; j++) {
            vari->x[0][vari->ntotal] = i * dx;
            vari->x[1][vari->ntotal] = j * dy;
            vari->ntotal = vari->ntotal + 1;
            vari->itype[vari->ntotal] = 1; //1表示流动粒子
        }
    }
    for (int i = 1; i < mp; i++) {
        for (int j = 1; j < np + 2; j++) {
            vari->x[0][vari->ntotal] = i * dx + 0.5 * dx;
            vari->x[1][vari->ntotal] = j * dy - 0.5 * dy;
            vari->ntotal = vari->ntotal + 1;
            vari->itype[vari->ntotal] = 1;
        }
    }
    // output(vari, "vtk_coor.vtu");
}
