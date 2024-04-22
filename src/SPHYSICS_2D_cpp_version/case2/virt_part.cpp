#pragma once
#include "head.h"
#include <string>
using namespace std;
void virt_part(str* vari)
{
    void writevtk(str * vari, const int number, const int cc = 0, const int gate = 1);
    void output(str * vari, const string& name);
    void equation_of_state(str * vari, int& n);

    vari->nvirt = 0;
    double dx = 0.005;
    double dy = 0.005;
    int nn = int(2.0 / dx);  //nn=400
    int kk = int(0.16 / dx); //kk=32
    int tol = vari->ntotal + vari->n_gate;
    //生成x轴y=0上的虚粒子
    for (int i = 1; i < nn; i++) {
        vari->x[0][tol + vari->nvirt] = i * dx;
        vari->x[1][tol + vari->nvirt] = 0.0;
        vari->v[0][tol + vari->nvirt] = 0.0;
        vari->v[1][tol + vari->nvirt] = 0.0;
        vari->nvirt += 1;
    }
    //生成x轴方向y=-0.5*dx的虚粒子
    for (int i = 0; i < nn; i++) {
        vari->x[0][tol + vari->nvirt] = i * dx + 0.5 * dx;
        vari->x[1][tol + vari->nvirt] = -0.5 * dy;
        vari->v[0][tol + vari->nvirt] = 0.0;
        vari->v[1][tol + vari->nvirt] = 0.0;
        vari->nvirt += 1;
    }
    //生成y轴方向x=0的虚粒子
    for (int i = 0; i < kk + 1; i++) {
        vari->x[0][tol + vari->nvirt] = 0.0;
        vari->x[1][tol + vari->nvirt] = i * dy;
        vari->v[0][tol + vari->nvirt] = 0.0;
        vari->v[1][tol + vari->nvirt] = 0.0;
        vari->nvirt += 1;
    }
    //生成y轴方向x=-0.5*dx的虚粒子
    for (int i = 0; i < kk + 1; i++) {
        vari->x[0][tol + vari->nvirt] = -0.5 * dx;
        vari->x[1][tol + vari->nvirt] = i * dy - 0.5 * dy;
        vari->v[0][tol + vari->nvirt] = 0.0;
        vari->v[1][tol + vari->nvirt] = 0.0;
        vari->nvirt += 1;
    }
    //生成y轴方向x=400*dx的虚粒子
    for (int i = 0; i < kk + 1; i++) {
        vari->x[0][tol + vari->nvirt] = int(2.0 / dx) * dx;
        vari->x[1][tol + vari->nvirt] = i * dy;
        vari->v[0][tol + vari->nvirt] = 0.0;
        vari->v[1][tol + vari->nvirt] = 0.0;
        vari->nvirt += 1;
    }
    //生成y轴方向x=400.5*dx的虚粒子
    for (int i = 0; i < kk + 1; i++) {
        vari->x[0][tol + vari->nvirt] = (int(2.0 / dx) + 0.5) * dx;
        vari->x[1][tol + vari->nvirt] = i * dy - 0.5 * dy;
        vari->v[0][tol + vari->nvirt] = 0.0;
        vari->v[1][tol + vari->nvirt] = 0.0;
        vari->nvirt += 1;
    }
    //虚粒子初始数据
    for (int i = 0; i < vari->nvirt; i++) {
        vari->rho[tol + i] = 1000.0;
        vari->rhoo[tol + i] = 0.0;
        vari->mass[tol + i] = vari->rho[tol + i] * dx * dy * 0.5;
        vari->pvol[tol + i] = vari->mass[tol + i] / vari->rho[tol + i];
        vari->p[tol + i] = 0.0;
        vari->vo[0][tol + i] = 0.0;
        vari->vo[1][tol + i] = 0.0;
        vari->itype[tol + i] = -1;
        equation_of_state(vari, i);
    }
    // vari->hsml = 0.92 * sqrt(dx * dx + dy * dy);
    // output(vari, "data.txt");
    writevtk(vari, 0, 1, 1);
}
