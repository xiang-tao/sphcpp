#pragma once
#include "head.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
void read(str* vari)
{
    void writevtk(str * vari, const int number, const int cc = 0);
    void output(str * vari, const string& name);
    void equation_of_state(str * vari, int& n);

    vari->ntotal = 4322;
    vari->nvirt = 801;
    int tot = vari->ntotal + vari->nvirt;
    double array[tot][7];
    int i, k;
    //读取文件
    ifstream infile;
    infile.open("IPART", ios::in);
    //判断是否读取成功
    if (!infile.is_open()) {
        cout << "error" << endl;
        exit(0);
    }
    //输入数组
    for (i = 0; i < tot; i++) {
        for (k = 0; k < 7; k++) {
            infile >> array[i][k];
        }
    }
    infile.close();

    double dx = 0.03;
    double dy = 0.03;
    double rho0 = 1000.0;
    double g = 9.81;
    double gamma = 7.0;
    double c0 = 10.0;
    double h_SML = 2.0;

    vari->B = c0 * c0 * rho0 * g * h_SML / gamma;
    vari->cs0 = sqrt(vari->B * gamma / rho0);
    // std::cout << "cs0=" << vari->cs0 << std::endl;
    double expont = 1.0 / gamma;
    vari->hsml = 0.92 * sqrt(dx * dx + dy * dy); //光滑长度由于不变故不用数组形式

    //输出数组
    for (i = 0; i < tot; i++) {
        vari->x[0][i] = array[i][0];
        vari->x[1][i] = array[i][1];
        vari->v[0][i] = array[i][2];
        vari->v[1][i] = array[i][3];
        vari->rho[i] = array[i][4];
        vari->p[i] = array[i][5];
        vari->mass[i] = array[i][6];
    }
    for (i = 0; i < tot; i++) {
        if (i < vari->ntotal) {
            vari->rhoo[i] = 0.0;
            vari->pvol[i] = vari->mass[i] / vari->rho[i];
            vari->vo[0][i] = 0.0;
            vari->vo[1][i] = 0.0;
            vari->itype[i] = 1; //1表示流动粒子
            equation_of_state(vari, i);
        } else {
            vari->rhoo[i] = 0.0;
            vari->pvol[i] = vari->mass[i] / vari->rho[i];
            vari->vo[0][i] = 0.0;
            vari->vo[1][i] = 0.0;
            vari->itype[i] = -1;
            equation_of_state(vari, i);
        }
    }
}
