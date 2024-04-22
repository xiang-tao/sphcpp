#pragma once
#include "head.h"
#include <string>
using namespace std;
void gate(str* vari)
{
    void equation_of_state(str * vari, int& n);
    void writevtk(str * vari, const int number, const int cc = 0, const int gate = 1);
    void output(str * vari, const string& name);

    vari->n_gate = 0;
    double dx = 0.005;
    double dy = 0.005;
    double Xgate = 0.388;
    int kk = int(0.16 / dx); //kk=32
    for (int i = 0; i < kk + 1; i++) {
        vari->x[0][vari->ntotal + vari->n_gate] = Xgate;
        vari->x[1][vari->ntotal + vari->n_gate] = i * dx;
        vari->v[0][vari->ntotal + vari->n_gate] = 0.0;
        vari->v[1][vari->ntotal + vari->n_gate] = 0.0;
        vari->n_gate += 1;
    }
    for (int i = 0; i < kk; i++) {
        vari->x[0][vari->ntotal + vari->n_gate] = Xgate + 0.5 * dx;
        vari->x[1][vari->ntotal + vari->n_gate] = (i + 0.5) * dy;
        vari->v[0][vari->ntotal + vari->n_gate] = 0.0;
        vari->v[1][vari->ntotal + vari->n_gate] = 0.0;
        vari->n_gate += 1;
    }
    //生成门的粒子初始数据,注意这里vari->nvrit=0
    for (int i = 0; i < vari->n_gate; i++) {
        vari->rho[vari->ntotal + i] = 1000.0;
        vari->rhoo[vari->ntotal + i] = 0.0;
        vari->mass[vari->ntotal + i] = vari->rho[vari->ntotal + i] * dx * dy;
        vari->pvol[vari->ntotal + i] = vari->mass[vari->ntotal + i] / vari->rho[vari->ntotal + i];
        vari->p[vari->ntotal + i] = 0.0;
        vari->vo[0][vari->ntotal + i] = 0.0;
        vari->vo[1][vari->ntotal + i] = 0.0;
        vari->itype[vari->ntotal + i] = -2; //gate 类型为
        equation_of_state(vari, i);
    }
    // writevtk(vari, 0, 1, 1);
}
