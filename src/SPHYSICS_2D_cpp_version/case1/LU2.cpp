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

        if (vari->i_singular < 1) {
            //源代码Fortran用的待定系数法-----该代码此处存在问题
            double LM[3][3];
            double UM[3][3];
            for (int iii = 0; iii < length; iii++) {
                LM[iii][0] = vari->A_LU[iii][0];
            }
            for (int iii = 0; iii < length; iii++) {
                UM[0][iii] = vari->A_LU[0][iii] / LM[0][0];
            }
            for (int ggg = 1; ggg < length; ggg++) {
                for (int iii = ggg; iii < length; iii++) {
                    double sum_temp = 0.0;
                    for (int kkk = 0; kkk < ggg; kkk++) {
                        sum_temp += LM[iii][kkk] * UM[kkk][ggg];
                    }
                    LM[iii][ggg] = vari->A_LU[iii][ggg] - sum_temp;
                }
                UM[ggg][ggg] = 1.0;
                for (int iii = ggg + 1; iii < length; iii++) {
                    double sum_temp1 = 0.0;
                    for (int kkk = 0; kkk < ggg; kkk++) {
                        sum_temp1 += LM[ggg][kkk] * UM[kkk][iii];
                    }
                    UM[ggg][iii] = (vari->A_LU[ggg][iii] - sum_temp1) / LM[ggg][ggg];
                }
            }

            for (int iii = 0; iii < length; iii++) {
                for (int ggg = iii + 1; ggg < length; ggg++) {
                    vari->A_LU[iii][ggg] = UM[iii][ggg];
                }
                for (int ggg = 0; ggg < iii + 1; ggg++) {
                    vari->A_LU[iii][ggg] = LM[iii][ggg];
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
        //Ux=y
        y_solution[0] = vari->b_input_vector[0];
        for (int i = 1; i < length; i++) {
            for (int k = 0; k < i; k++) {
                vari->b_input_vector[i] -= vari->A_LU[i][k] * y_solution[k];
            }
            y_solution[i] = vari->b_input_vector[i];
        }
        vari->x_solution[length - 1] = y_solution[length - 1] / vari->A_LU[length - 1][length - 1];
        for (int i = length - 2; i >= 0; i--) {
            for (int k = i; k < length - 1; k++) {
                y_solution[i] -= vari->x_solution[k + 1] * vari->A_LU[i][k + 1];
            }
            vari->x_solution[i] = y_solution[i] / vari->A_LU[i][i];
        }
        // Ly=b
    }
}
