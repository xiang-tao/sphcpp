#pragma once
#include "head.h"
#include <algorithm> //提供min,max等函数
#include <iostream>
void LU(str* vari)
{
    const int length = 3;
    double TOL_REAL = 1.0e-8;
    double TOL_DBLE = 1.0e-16;
    double y_solution[length];
    double al_min;
    double al_max;

    if (vari->i_MLS_step == 1) {
        double amax_Aik = 0.0;
        double row_sum_min = 10.0e8;
        double row_sum;
        double A_temp_ik_abs;
        vari->i_singular = 0;
        //检查奇点
        for (int iii = 0; iii < length; iii++) {
            row_sum = 0.0;
            for (int kkk = 0; kkk < length; kkk++) {
                A_temp_ik_abs = std::abs(vari->A_LU[iii][kkk]);
                row_sum += A_temp_ik_abs;
                if (A_temp_ik_abs > amax_Aik) {
                    amax_Aik = A_temp_ik_abs;
                }
            }
            if (row_sum < row_sum_min) {
                row_sum_min = row_sum;
            }
        }
        if (amax_Aik < TOL_REAL) {
            vari->i_singular = 1;
            if (vari->test_step < 100 and vari->test_step > 1) {
                std::cout << "hello:REAL" << std::endl;
            }
        }
        if (row_sum_min < TOL_DBLE) {
            vari->i_singular = 1;
            if (vari->test_step < 100 and vari->test_step > 1) {
                std::cout << "hello:DBLE" << std::endl;
            }
        }
        //ikj LU分解，见潘建瑜矩阵讲义p42,适合c++，源代码Fortran用的待定系数法
        if (vari->i_singular < 1) {
            for (int i = 1; i < length; i++) {
                for (int k = 0; k < i; k++) {
                    vari->A_LU[i][k] = vari->A_LU[i][k] / vari->A_LU[k][k];
                    for (int j = k + 1; j < length; j++) {
                        vari->A_LU[i][j] = vari->A_LU[i][j] - vari->A_LU[i][k] * vari->A_LU[k][j];
                    }
                }
            }
            //对奇异（病态）矩阵处理建议
            al_min = 1.0e8;
            al_max = -1.0e8;
            for (int iii = 0; iii < length; iii++) {
                if (vari->A_LU[iii][iii] > al_max) {
                    al_max = vari->A_LU[iii][iii];
                }
                if (vari->A_LU[iii][iii] < al_min) {
                    al_min = vari->A_LU[iii][iii];
                }
            }
            if (std::abs(al_min) < 1.0e-14 * std::abs(al_max)) {
                vari->i_singular = 1;
            }
        }

    } else {
        for (int i = 0; i < length; i++) {
            vari->x_solution[i] = 0.0;
            y_solution[i] = 0.0;
        }
        // 三角方程回带求解，矩阵讲义p45
        // Ly=b
        y_solution[0] = vari->b_input_vector[0];
        for (int i = 1; i < length; i++) {
            for (int k = 0; k < i; k++) {
                vari->b_input_vector[i] -= vari->A_LU[i][k] * y_solution[k];
            }
            y_solution[i] = vari->b_input_vector[i];
        }
        //Ux=y
        vari->x_solution[length - 1] = y_solution[length - 1] / vari->A_LU[length - 1][length - 1];
        for (int i = length - 2; i >= 0; i--) {
            for (int k = i; k < length - 1; k++) {
                y_solution[i] -= vari->x_solution[k + 1] * vari->A_LU[i][k + 1];
            }
            vari->x_solution[i] = y_solution[i] / vari->A_LU[i][i];
        }
    }
}
