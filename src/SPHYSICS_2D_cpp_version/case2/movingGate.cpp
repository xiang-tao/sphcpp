#pragma once
#include "head.h"
#include <algorithm> //提供min,max等函数
using namespace std;
void movingGate(str* vari)
{
    double VXgate = 0.0, VYgate = 1.5, tgate = 0.0; //来自gate文件
    for (int i = vari->ntotal; i < vari->ntotal + vari->n_gate; i++) {
        if (vari->time >= tgate) {
            vari->x[0][i] += VXgate * vari->new_dt;
            vari->x[1][i] = std::min(vari->x[1][i] + VYgate * vari->new_dt, vari->ymax_ini);
            vari->v[0][i] = VXgate;
            vari->v[1][i] = VYgate;
        }
    }
}
