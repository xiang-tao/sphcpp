#pragma once
#include "head.h"
#include <algorithm> //提供min,max等函数
#include <iostream>
using namespace std;
void densityFilter_MLS(str* vari)
{
    void ac_MLS(str * vari);
    void LU(str * vari);
    void equation_of_state(str * vari, int& n);
    int nstart_MLS = 0;
    for (int i = nstart_MLS; i < vari->ntotal; i++) {
        vari->pvol[i] = vari->mass[i] / vari->rho[i];
        vari->rho_sum_MLS[i] = 0.0;
        vari->A_MLS[i][0][0] = 0.0;
        vari->A_MLS[i][0][1] = 0.0;
        vari->A_MLS[i][0][2] = 0.0;
        vari->A_MLS[i][1][0] = 0.0;
        vari->A_MLS[i][1][1] = 0.0;
        vari->A_MLS[i][1][2] = 0.0;
        vari->A_MLS[i][2][0] = 0.0;
        vari->A_MLS[i][2][1] = 0.0;
        vari->A_MLS[i][2][2] = 0.0;
    }
    vari->i_MLS_part = 1; //1为组装矩阵A
    ac_MLS(vari);
    if (vari->test_step < 100 and vari->test_step > 1) {
        std::cout << "A_MLS[0]00=" << vari->A_MLS[0][0][0] << std::endl;
        std::cout << "A_MLS[0]11=" << vari->A_MLS[0][1][1] << std::endl;
    }

    int i_singularMatrix_count = 0;
    const int length = 3;
    double A_MLS_11;
    for (int i = nstart_MLS; i < vari->ntotal; i++) {
        vari->A_MLS[i][0][0] += vari->adh * vari->mass[i] / vari->rho[i]; //考虑自身
        A_MLS_11 = vari->A_MLS[i][0][0];
        //对称性赋值
        vari->A_MLS[i][1][0] = vari->A_MLS[i][0][1];
        vari->A_MLS[i][2][0] = vari->A_MLS[i][0][2];
        vari->A_MLS[i][2][1] = vari->A_MLS[i][1][2];
        for (int ii = 0; ii < 3; ii++) {
            for (int kk = 0; kk < 3; kk++) {
                vari->A_LU[ii][kk] = vari->A_MLS[i][ii][kk];
            }
        }
        vari->i_MLS_step = 1;
        LU(vari);
        if (vari->i_singular > 0) {
            if (A_MLS_11 == 0) {
                cout << "A_MLS_11=" << 0 << endl;
                cout << "矩阵是病态(奇异)的，程序终止" << endl;
                exit(0);
            }
            if (vari->test_step < 100 and vari->test_step > 1) {
                std::cout << "hello:i_singular" << std::endl;
            }
            i_singularMatrix_count += 1;
            vari->beta0_MLS[i] = 1 / A_MLS_11;
            vari->beta1x_MLS[i] = 0.0;
            vari->beta1y_MLS[i] = 0.0;
        } else {
            vari->i_MLS_step = 2;
            for (int kk = 0; kk < 1; kk++) { //kk<3，可以把A的逆阵算出来，但是我们只要逆阵的第一列
                for (int ii = 0; ii < 3; ii++) {
                    vari->b_input_vector[ii] = 0.0;
                }
                vari->b_input_vector[kk] = 1.0;
                LU(vari);
                for (int ii = 0; ii < 3; ii++) {
                    vari->A_MLS_inverse[ii][kk] = vari->x_solution[ii];
                }
            }
            vari->beta0_MLS[i] = vari->A_MLS_inverse[0][0];
            vari->beta1x_MLS[i] = vari->A_MLS_inverse[1][0];
            vari->beta1y_MLS[i] = vari->A_MLS_inverse[2][0];
        }
    }
    vari->i_MLS_part = 2;
    ac_MLS(vari);
    for (int i = nstart_MLS; i < vari->ntotal; i++) {
        vari->rho_sum_MLS[i] += vari->beta0_MLS[i] * vari->adh * vari->mass[i]; //考虑自身
        vari->rho[i] = vari->rho_sum_MLS[i];
        equation_of_state(vari, i);
    }
}
