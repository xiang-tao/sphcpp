#pragma once
#include "head.h"
void getdata(str* vari)
{
    vari->two_h = 2.0 * vari->hsml;
    vari->four_h = 4.0 * vari->hsml;
    vari->six_h = 6.0 * vari->hsml;
    vari->h_over_100 = 0.01 * vari->hsml;
    vari->h_over_1000 = 0.001 * vari->hsml;
    vari->h2 = vari->hsml * vari->hsml;
    vari->fourh2 = 4.0 * vari->h2;

    vari->nstep_DBC = 0;

    //Wendland Quiintic kernel function系数
    vari->Awen = 0.557 / vari->h2;
    vari->Bwen = -2.7852 / (vari->h2 * vari->hsml);
    vari->adh = vari->Awen;

    vari->eta = 0.1 * vari->hsml;
    vari->eta2 = vari->eta * vari->eta;
    vari->xmin = vari->x[0][vari->ntotal];
    vari->xmax = vari->x[0][vari->ntotal];
    vari->ymin = vari->x[1][vari->ntotal];
    vari->ymax = vari->x[1][vari->ntotal];

    //找出横坐标纵坐标中虚粒子的最大最小值，便于生成列表,后续用于控制整体粒子的范围，比如由于飞溅.
    for (int i = vari->ntotal; i < vari->ntotal + vari->nvirt; i++) {
        if (vari->x[0][i] > vari->xmax) {
            vari->xmax = vari->x[0][i];
        }
        if (vari->x[0][i] < vari->xmin) {
            vari->xmin = vari->x[0][i];
        }
        if (vari->x[1][i] > vari->ymax) {
            vari->ymax = vari->x[1][i];
        }
        if (vari->x[1][i] < vari->ymin) {
            vari->ymin = vari->x[1][i];
        }
    }

    //原始域的范围控制，即初始流动和虚粒子的范围，因为后续怕粒子的飞溅超出y轴方向的虚粒子高度，就要生成新的列表
    vari->xmax_container = vari->xmax;
    vari->xmin_container = vari->xmin;
    vari->ymin_container = vari->ymin;
    //前面比较了虚粒子，现在比较流动粒子的范围最值，相当于是初始时候所有粒子的范围情况，便于生成列表
    for (int i = 0; i < vari->ntotal; i++) {
        if (vari->x[0][i] > vari->xmax) {
            vari->xmax = vari->x[0][i];
        }
        if (vari->x[0][i] < vari->xmin) {
            vari->xmin = vari->x[0][i];
        }
        if (vari->x[1][i] > vari->ymax) {
            vari->ymax = vari->x[1][i];
        }
        if (vari->x[1][i] < vari->ymin) {
            vari->ymin = vari->x[1][i];
        }
    }
    //给列表添加小边框区域，防止计算错误，提高程序的健壮性.
    vari->xmax += 0.1 * vari->hsml;
    vari->xmin -= 0.1 * vari->hsml;
    vari->ymax += 0.1 * vari->hsml;
    vari->ymin -= 0.1 * vari->hsml;
    //判断移动障碍物在初始边界内，如飞溅粒子，以及越界粒子的位置设置
    vari->ymax_ini = vari->ymax;
    vari->xtrash = 2.0 * vari->xmax;
    vari->ytrash = 0.0;
    //确定细胞（列表）初始数量
    vari->one_over_h = 1.0 / vari->hsml;
    vari->one_over_2h = 1.0 / (2.0 * vari->hsml);
    vari->ncx = int((vari->xmax - vari->xmin) * vari->one_over_2h) + 1;
    vari->ncy = int((vari->ymax - vari->ymin) * vari->one_over_2h) + 1;
    //用于列表检查限制，这里是包含了初始小边框的y轴最高位置
    vari->ycontrol = vari->ymin + vari->ncy * 2.0 * vari->hsml;

    //初始总的列表数量
    vari->nct = vari->ncx * vari->ncy;
    //记录初始时候总列表数量，因为后续由于粒子的飞溅ncx与ncy可能发生变化
    vari->ncy_ini = vari->ncy;
    vari->nct_ini = vari->nct;
}
