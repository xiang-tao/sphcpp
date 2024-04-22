#pragma once
#include "head.h"
#include <string>
using namespace std;

void particle(str* vari)

{
    void output(str * vari, const string& name, int cc = 0);

    vari->ntotal = 0;
    double dx = 0.005;
    double dy = 0.005;
    int mp1 = int(0.376 / dx);          //mp1=75  //int取整为去除小数部分，如int(4.1)=4,int(4.9)=4
    int np1 = int(0.15 / dy);           //np1=30
    int mp2 = int((1.995 - 0.40) / dx); //mp2=319
    int np2 = int((0.018) / dy);        //np2=3
    for (int i = 1; i < mp1 + 1; i++) {
        for (int j = 1; j < np1 + 1; j++) {
            vari->x[0][vari->ntotal] = i * dx;
            vari->x[1][vari->ntotal] = j * dy;
            vari->ntotal = vari->ntotal + 1;
            vari->itype[vari->ntotal] = 1; //1表示流动粒子
        }
    }
    for (int i = 1; i < mp1; i++) {
        for (int j = 1; j < np1 + 1; j++) {
            vari->x[0][vari->ntotal] = i * dx + 0.5 * dx;
            vari->x[1][vari->ntotal] = j * dy - 0.5 * dy;
            vari->ntotal = vari->ntotal + 1;
            vari->itype[vari->ntotal] = 1;
        }
    }
    vari->part_ntotal = vari->ntotal; //记录门左边粒子数
    for (int i = 0; i < mp2 + 1; i++) {
        for (int j = 1; j < np2 + 2; j++) {
            vari->x[0][vari->ntotal] = i * dx + 0.40;
            vari->x[1][vari->ntotal] = j * dy;
            vari->ntotal = vari->ntotal + 1;
            vari->itype[vari->ntotal] = 1; //1表示流动粒子
        }
    }
    for (int i = 0; i < mp2; i++) {
        for (int j = 1; j < np2 + 2; j++) {
            vari->x[0][vari->ntotal] = i * dx + 0.5 * dx + 0.40;
            vari->x[1][vari->ntotal] = j * dy - 0.5 * dy;
            vari->ntotal = vari->ntotal + 1;
            vari->itype[vari->ntotal] = 1;
        }
    }
    // output(vari, "vtk_coor.vtu");
}
