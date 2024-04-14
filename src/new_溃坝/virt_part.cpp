#pragma once
#include "head.h"
#include <string>
using namespace std;
void virt_part(str* vari)
{
    void writevtk(str * vari, const int number, const int cc = 0);

    vari->nvirt = 0;
    double dx = 0.03;
    double dy = 0.03;
    int nn = int(4.0 / dx);
    //生成x轴y=0上的虚粒子
    for (int i = 1; i < nn; i++) {
        vari->x[0][vari->ntotal + vari->nvirt] = i * dx;
        vari->x[1][vari->ntotal + vari->nvirt] = 0.0;
        vari->v[0][vari->ntotal + vari->nvirt] = 0.0;
        vari->v[1][vari->ntotal + vari->nvirt] = 0.0;
        vari->nvirt += 1;
    }
    //生成x轴方向y=-0.5*dx的虚粒子
    for (int i = 0; i < nn; i++) {
        vari->x[0][vari->ntotal + vari->nvirt] = i * dx + 0.5 * dx;
        vari->x[1][vari->ntotal + vari->nvirt] = -0.5 * dy;
        vari->v[0][vari->ntotal + vari->nvirt] = 0.0;
        vari->v[1][vari->ntotal + vari->nvirt] = 0.0;
        vari->nvirt += 1;
    }
    //生成y轴方向x=0的虚粒子
    for (int i = 0; i < nn + 1; i++) {
        vari->x[0][vari->ntotal + vari->nvirt] = 0.0;
        vari->x[1][vari->ntotal + vari->nvirt] = i * dy;
        vari->v[0][vari->ntotal + vari->nvirt] = 0.0;
        vari->v[1][vari->ntotal + vari->nvirt] = 0.0;
        vari->nvirt += 1;
    }
    //生成y轴方向x=-0.5*dx的虚粒子
    for (int i = 0; i < nn + 1; i++) {
        vari->x[0][vari->ntotal + vari->nvirt] = -0.5 * dx;
        vari->x[1][vari->ntotal + vari->nvirt] = i * dy - 0.5 * dy;
        vari->v[0][vari->ntotal + vari->nvirt] = 0.0;
        vari->v[1][vari->ntotal + vari->nvirt] = 0.0;
        vari->nvirt += 1;
    }
    //生成y轴方向x=133*dx的虚粒子
    for (int i = 0; i < nn + 1; i++) {
        vari->x[0][vari->ntotal + vari->nvirt] = int(4 / dx) * dx;
        vari->x[1][vari->ntotal + vari->nvirt] = i * dy;
        vari->v[0][vari->ntotal + vari->nvirt] = 0.0;
        vari->v[1][vari->ntotal + vari->nvirt] = 0.0;
        vari->nvirt += 1;
    }
    //生成y轴方向x=133.5*dx的虚粒子
    for (int i = 0; i < nn + 1; i++) {
        vari->x[0][vari->ntotal + vari->nvirt] = (int(4 / dx) + 0.5) * dx;
        vari->x[1][vari->ntotal + vari->nvirt] = i * dy - 0.5 * dy;
        vari->v[0][vari->ntotal + vari->nvirt] = 0.0;
        vari->v[1][vari->ntotal + vari->nvirt] = 0.0;
        vari->nvirt += 1;
    }
    //虚粒子初始数据
    for (int i = 0; i < vari->nvirt; i++) {
        vari->rho[vari->ntotal + i] = 1000.0;
        vari->rhoo[vari->ntotal + i] = 0.0;
        vari->mass[vari->ntotal + i] = vari->rho[vari->ntotal + i] * dx * dy * 0.5;
        vari->pvol[vari->ntotal + i] = vari->mass[vari->ntotal + i] / vari->rho[vari->ntotal + i];
        vari->p[vari->ntotal + i] = 0.0;
        vari->vo[0][vari->ntotal + vari->nvirt] = 0.0;
        vari->vo[1][vari->ntotal + vari->nvirt] = 0.0;
        vari->itype[vari->ntotal + i] = -1;
    }
    // vari->hsml = 0.92 * sqrt(dx * dx + dy * dy);
    writevtk(vari, 0, 1);
}
