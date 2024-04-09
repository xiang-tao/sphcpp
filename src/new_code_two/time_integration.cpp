#pragma once
#include "head.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

void time_integration(double* time, int* timestep, str* vari)
{
    void single_step(str * vari);
    void density_sum(str * vari);
    //void output(int timestep, double time, str* vari);

    void direct_find(str * vari, int m);

    // int i, n;

    for (int n = 0; n < nmaxstep; n++) {
        if (n != 0) {
            for (int i = 0; i < vari->ntotal; i++) {
                vari->e0[i] = vari->e[i];
                vari->e[i] = vari->e[i] + dt * vari->dedt[i] / 2.0;
                for (int d = 0; d < dim; d++) {
                    vari->v0[d][i] = vari->v[d][i];                               //存储半时刻的速度
                    vari->v[d][i] = vari->v[d][i] + vari->dvxdt[d][i] * dt / 2.0; //更新速度到整时刻以便用于加速度整时刻的计算
                }
            }
        }
        single_step(vari);
        if (n == 0) {
            for (int i = 0; i < vari->ntotal; i++) {
                vari->e[i] = vari->e[i] + dt * vari->dedt[i] / 2.0;
                for (int d = 0; d < dim; d++) {
                    vari->v[d][i] = vari->v[d][i] + vari->dvxdt[d][i] * dt / 2.0; //更新速度到半时刻以便更新位移
                    vari->x[d][i] = vari->x[d][i] + vari->v[d][i] * dt;           //更新坐标位置
                }
            }
        } else {
            for (int i = 0; i < vari->ntotal; i++) {
                vari->e[i] = vari->e0[i] + dt * vari->dedt[i];
                for (int d = 0; d < dim; d++) {
                    vari->v[d][i] = vari->v0[d][i] + vari->dvxdt[d][i] * dt; //更新速度到半时刻以便更新位移
                    vari->x[d][i] = vari->x[d][i] + vari->v[d][i] * dt;      //更新坐标位置
                }
            }
        }
         *timestep = *timestep + 1;
        *time = *time + dt;

        if (*timestep % save_step == 0) {
	        ofstream dataFile;
	dataFile.open("coor.txt", ofstream::app);
	fstream file("coor.txt", ios::out);
            //output(*timestep, *time, vari);
            for (int i = 0; i < vari->ntotal; i++) {
                dataFile << vari->x[0][i] << " " << vari->x[1][i] << endl;
            }
            dataFile.close();
        }
    }
}
