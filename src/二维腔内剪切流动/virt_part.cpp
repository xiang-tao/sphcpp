#include "head.h"
#include <string>
using namespace std;
void virt_part(str* vari)
{
    void output(str * vari, const string& name, int cc = 0);

    vari->nvirt = 0;
    double v_inf = 1.0e-3;
    double dx = xl / mp;
    double dy = yl / np;
    //生成矩阵上边的虚粒子
    for (int i = 0; i < 2 * mp + 1; i++) {
        vari->x[0][vari->ntotal + vari->nvirt] = i * dx / 2.0;
        vari->x[1][vari->ntotal + vari->nvirt] = yl;
        vari->v[0][vari->ntotal + vari->nvirt] = v_inf;
        vari->v[1][vari->ntotal + vari->nvirt] = 0.0;
        vari->nvirt += 1;
    }
    //生成矩阵下边的虚粒子
    for (int i = 0; i < 2 * mp + 1; i++) {
        vari->x[0][vari->ntotal + vari->nvirt] = i * dx / 2.0;
        vari->x[1][vari->ntotal + vari->nvirt] = 0.0;
        vari->v[0][vari->ntotal + vari->nvirt] = 0.0;
        vari->v[1][vari->ntotal + vari->nvirt] = 0.0;
        vari->nvirt += 1;
    }
    //生成矩阵左边的虚粒子
    for (int i = 0; i < 2 * mp - 1; i++) {
        vari->x[0][vari->ntotal + vari->nvirt] = 0.0;
        vari->x[1][vari->ntotal + vari->nvirt] = (i + 1) * dy / 2.0;
        vari->v[0][vari->ntotal + vari->nvirt] = 0.0;
        vari->v[1][vari->ntotal + vari->nvirt] = 0.0;
        vari->nvirt += 1;
    }
    //生成矩阵右边的虚粒子
    for (int i = 0; i < 2 * mp - 1; i++) {
        vari->x[0][vari->ntotal + vari->nvirt] = xl;
        vari->x[1][vari->ntotal + vari->nvirt] = (i + 1) * dy / 2.0;
        vari->v[0][vari->ntotal + vari->nvirt] = 0.0;
        vari->v[1][vari->ntotal + vari->nvirt] = 0.0;
        vari->nvirt += 1;
    }
    //虚粒子初始数据
    for (int i = 0; i < vari->nvirt; i++) {
        vari->rho[vari->ntotal + i] = 1000.0;
        vari->mass[vari->ntotal + i] = vari->rho[vari->ntotal + i] * dx * dy;
        vari->p[vari->ntotal + i] = 0.0;
        vari->e[vari->ntotal + i] = 0.0;
        vari->itype[vari->ntotal + i] = -2;
        vari->hsml[vari->ntotal + i] = dx;
    }
    // output(vari, "virtual_coor.txt", 1);
}
