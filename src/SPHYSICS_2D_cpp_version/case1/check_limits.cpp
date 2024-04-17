#pragma once
#include "head.h"
#include <cstdlib>
#include <iomanip>
using namespace std;
#include <iostream>
void check_limits(str* vari)
{
    vari->ymax = 0.0;
    int part_ncases = 0;
    for (int i = 0; i < vari->ntotal; i++) {
        if (vari->x[1][i] > vari->ymax) {
            vari->ymax = vari->x[1][i];
        }
        if (vari->itype[i] != 0 and (vari->x[0][i] > vari->xmax_container or vari->x[0][i] < vari->xmin_container or vari->x[1][i] < vari->ymin_container)) {
            vari->itype[i] = 0;
            std::cout << "粒子" << i << "越界了" << std::endl;
            part_ncases += 1;
            vari->x[0][i] = vari->xtrash;
            vari->x[1][i] = vari->ytrash;
            vari->v[0][i] = 0.0;
            vari->v[1][i] = 0.0;
            vari->vo[0][i] = 0.0;
            vari->vo[1][i] = 0.0;
        }
    }
    double differ = vari->ymax - vari->ycontrol;

    //修复z+方向由于飞溅粒子而产生的列表
    if (differ > 0) {
        int nn = int(differ * vari->one_over_2h) + 1;
        vari->ymax = vari->ycontrol + vari->two_h * nn;
        vari->ncy = int((vari->ymax - vari->ymin) * vari->one_over_2h) + 1;
        vari->nct = vari->ncx * vari->ncy;
        for (int i = vari->nct_ini; i < vari->nct; i++) {
            vari->nc[i][0] = 0; //新增加的列表没有边界粒子
        }
    } else {
        vari->ymax = vari->ycontrol;
        vari->nct = vari->nct_ini;
        vari->ncy = vari->ncy_ini;
    }
    //每一次循环越界粒子大于100就终止程序
    if (part_ncases > 100) {
        std::cout << "单次粒子越界超过了100" << std::endl;
        exit(0);
    }
    vari->ncases += part_ncases;
}
