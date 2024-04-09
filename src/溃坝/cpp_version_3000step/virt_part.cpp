#pragma once
#include "head.h"
#include <string>
using namespace std;
void virt_part(str* vari)
{
    void output(str * vari, const string& name, int cc = 0);

    vari->nvirt = 0;
    double v_inf = 1.0e-3;
    double dx = 0.03;
    double dy = 0.03;
    int n1 = int(4.0 / dx) + 2;
    int n2 = int(4.0 / dx) + 3;
    int n3 = int(4.0 / dy) + 1;
    // int n4 = int(4.0 / dy) + 1;
    // int n5 = int(4.0 / dy) + 1;
    // int n6 = int(4.0 / dy) + 1;
    //生成x轴y=0上的虚粒子
    for (int i = 0; i < n1; i++) {
        vari->x[0][vari->ntotal + vari->nvirt] = i * dx;
        vari->x[1][vari->ntotal + vari->nvirt] = 0.0;
        vari->v[0][vari->ntotal + vari->nvirt] = 0.0;
        vari->v[1][vari->ntotal + vari->nvirt] = 0.0;
        vari->nvirt += 1;
    }
    //生成x轴方向y=dx的虚粒子
    for (int i = 0; i < n2; i++) {
        vari->x[0][vari->ntotal + vari->nvirt] = i * dx - 0.5 * dx;
        vari->x[1][vari->ntotal + vari->nvirt] = dx;
        vari->v[0][vari->ntotal + vari->nvirt] = 0.0;
        vari->v[1][vari->ntotal + vari->nvirt] = 0.0;
        vari->nvirt += 1;
    }
    //生成y轴方向x=0的虚粒子
    for (int i = 0; i < n3; i++) {
        vari->x[0][vari->ntotal + vari->nvirt] = 0.0;
        vari->x[1][vari->ntotal + vari->nvirt] = (i + 1) * dy;
        vari->v[0][vari->ntotal + vari->nvirt] = 0.0;
        vari->v[1][vari->ntotal + vari->nvirt] = 0.0;
        vari->nvirt += 1;
    }
    //生成y轴方向x=dy的虚粒子
    for (int i = 0; i < n3; i++) {
        vari->x[0][vari->ntotal + vari->nvirt] = dy;
        vari->x[1][vari->ntotal + vari->nvirt] = (i + 1) * dy + 0.5 * dy;
        vari->v[0][vari->ntotal + vari->nvirt] = 0.0;
        vari->v[1][vari->ntotal + vari->nvirt] = 0.0;
        vari->nvirt += 1;
    }
    //生成y轴方向x=4.0的虚粒子
    for (int i = 0; i < n3; i++) {
        vari->x[0][vari->ntotal + vari->nvirt] = 4.0;
        vari->x[1][vari->ntotal + vari->nvirt] = (i + 1) * dy;
        vari->v[0][vari->ntotal + vari->nvirt] = 0.0;
        vari->v[1][vari->ntotal + vari->nvirt] = 0.0;
        vari->nvirt += 1;
    }
    //生成y轴方向x=4.0-dy的虚粒子
    for (int i = 0; i < n3; i++) {
        vari->x[0][vari->ntotal + vari->nvirt] = 4.0 - dy;
        vari->x[1][vari->ntotal + vari->nvirt] = (i + 1) * dy + 0.5 * dy;
        vari->v[0][vari->ntotal + vari->nvirt] = 0.0;
        vari->v[1][vari->ntotal + vari->nvirt] = 0.0;
        vari->nvirt += 1;
    }
    //虚粒子初始数据
    for (int i = 0; i < vari->nvirt; i++) {
        vari->rho[vari->ntotal + i] = 1000.0;
        vari->mass[vari->ntotal + i] = vari->rho[vari->ntotal + i] * dx * dy;
        vari->p[vari->ntotal + i] = 0.0;
        // vari->e[vari->ntotal + i] = 0.0;
        vari->itype[vari->ntotal + i] = -2;
        vari->hsml[vari->ntotal + i] = 0.92 * sqrt(dx * dx + dy * dy);
    }
    output(vari, "vtk_virtual.vtu", 1);
}
