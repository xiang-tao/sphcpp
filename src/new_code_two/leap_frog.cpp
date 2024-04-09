#pragma once
#include "head.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

void leap_frog(double* time, int* timestep, str* vari)
{
    void single_step(str * vari);
    void density_sum(str * vari);
    //void output(int timestep, double time, str* vari);

    void direct_find(str * vari, int m);
    
	

    int i, d, n;

    //single_step(vari);

    for (n = 0; n < nmaxstep; n++) {
        //printf("%d\n", n);

        //////////////////////////////////////////////////////////////////////////

        single_step(vari);

        for (i = 0; i < vari->ntotal; i++) {
            for (d = 0; d < dim; d++) {
                vari->v[d][i] = vari->v[d][i] + vari->dvxdt[d][i] * dt; //更新速度
                vari->x[d][i] = vari->x[d][i] + vari->v[d][i] * dt;         //更新坐标位置
            }
            vari->e[i] = vari->e[i] + dt * vari->dedt[i];

            // vari->T[i] = (vari->e[i] + a* vari->rho[i]) / kc;
            ////////////////粒子的位置更新后，需不需要重新计算密度
        }

        *timestep = *timestep + 1;
        *time = *time + dt;

        if (*timestep % save_step == 0) {
	        ofstream dataFile;
	dataFile.open("coor5000.txt", ofstream::app);
	fstream file("coor5000.txt", ios::out);
            //output(*timestep, *time, vari);
            for (int i = 0; i < vari->ntotal; i++) {
                dataFile << vari->x[0][i] << " " << vari->x[1][i] << endl;
            }
            dataFile.close();
        }
    }
}
