#pragma once
#include "head.h"

void kernel(double r, double dx[dim], double mhsml, double* aw, double adwdx[dim])
{
    int d;
    double q;
    double factor; //相当于p61中核函数前面的alpha_d
    /////////////////////////////////////////
    q = r / mhsml;
    *aw = 0.0;
    for (d = 0; d < dim; d++) {
        adwdx[d] = 0.0; //中間變量
    }
    //////////////////////////////////////////
    //cubic spline kernel function

    if (skf == 1) {
        if (dim == 1) {
            factor = 1.0 / mhsml;
        } else if (dim == 2) {
            factor = 15.0 / (7.0 * pi * mhsml * mhsml);
        } else if (dim == 3) {
            factor = 3.0 / (2.0 * pi * mhsml * mhsml * mhsml);
        }
        if (q >= 0 && q <= 1.0) {
            *aw = factor * (2.0 / 3.0 - q * q + pow(q, 3) / 2.0);
            for (d = 0; d < dim; d++) {
                adwdx[d] = factor * (-2.0 + 3.0 / 2.0 * q) / pow(mhsml, 2) * dx[d];
            }
        } else if (q > 1.0 && q <= 2) {

            *aw = factor * 1.0 / 6.0 * pow((2.0 - q), 3);
            for (d = 0; d < dim; d++) {
                adwdx[d] = -factor * 1.0 / 6.0 * 3.0 * pow((2.0 - q), 2) / mhsml * (dx[d] / r);
            }
        } else {
            *aw = 0;
            for (d = 0; d < dim; d++) {
                adwdx[d] = 0;
            }
        }
    }
    /////////////////////////////////////////////
    //hyperbolic-shaped kernel function

    else if (skf == 2) {
        if (dim == 1) {
            factor = 1.0 / (7.0 * mhsml);
        } else if (dim == 2) {
            factor = 1.0 / (3.0 * pi * mhsml * mhsml);
        } else if (dim == 3) {
            factor = 15.0 / (62.0 * pi * mhsml * mhsml * mhsml);
        }
        if (q >= 0 && q <= 1.0) {
            *aw = factor * (6.0 - 6 * q + pow(q, 3));
            for (d = 0; d < dim; d++) {
                adwdx[d] = factor * (3.0 * q * q - 6.0) / mhsml * (dx[d] / r);
            }
        } else if (q > 1.0 && q <= 2) {

            *aw = factor * pow((2.0 - q), 3);
            for (d = 0; d < dim; d++) {
                adwdx[d] = -factor * 3.0 * pow((2.0 - q), 2) / mhsml * (dx[d] / r);
            }
        } else {
            aw = 0;
            for (d = 0; d < dim; d++) {
                adwdx[d] = 0;
            }
        }
    }

    else if (skf == 3) {
        if (dim == 1) {
            factor = 1.0 / (7.0 * mhsml);
        } else if (dim == 2) {
            factor = 1.0 / (3.0 * pi * mhsml * mhsml);
        } else if (dim == 3) {
            factor = 15.0 / (62.0 * pi * mhsml * mhsml * mhsml);
        }
        if (q >= 0 && q <= 1.0) {
            *aw = factor * (6.0 - 6 * q + pow(q, 3));
            for (d = 0; d < dim; d++) {
                adwdx[d] = factor * (3.0 * q * q - 6.0) / mhsml * (dx[d] / r);
            }
        } else if (q > 1.0 && q <= 2) {

            *aw = factor * pow((2.0 - q), 3);
            for (d = 0; d < dim; d++) {
                adwdx[d] = -factor * 3.0 * pow((2.0 - q), 2) / mhsml * (dx[d] / r);
            }
        } else {
            aw = 0;
            for (d = 0; d < dim; d++) {
                adwdx[d] = 0;
            }
        }
    }

    else if (skf == 4) {
        if (dim == 1) {
            factor = 1.0 / mhsml;
        } else if (dim == 2) {
            factor = 15.0 / (7.0 * pi * mhsml * mhsml);
        } else if (dim == 3) {
            factor = 3.0 / (2.0 * pi * mhsml * mhsml * mhsml);
        }
        if (q >= 0 && q <= 1.0) {
            *aw = factor * (2.0 / 3.0 - q * q + q * q * q / 2.0);
            for (d = 0; d < dim; d++) {
                adwdx[d] = factor * (-2 + 3.0 / 2.0 * q) / (mhsml * mhsml) * dx[d];
            }
        } else if (q > 1.0 && q <= 2) {

            *aw = factor * (1.0 / 6.0 * pow((2.0 - q), 3));
            for (d = 0; d < dim; d++) {
                adwdx[d] = -factor * 1.0 / 2.0 * pow((2.0 - q), 2) / mhsml * (dx[d] / r);
            }
        } else {
            aw = 0;
            for (d = 0; d < dim; d++) {
                adwdx[d] = 0;
            }
        }
    } else if (skf == 5) { //skf=5该核函数还不确定怎么写，后面改
        if (dim == 1) {

        } else if (dim == 2) {
            factor = 7.0 / (4.0 * pi * mhsml * mhsml);
        } else if (dim == 3) {
        }
        if (q >= 0 && q <= 1.0) {
            *aw = factor * pow(1 - 0.5 * q, 4) * (2 * q + 1);
            for (d = 0; d < dim; d++) {
                adwdx[d] = factor * (-2 + 3.0 / 2.0 * q) / (mhsml * mhsml) * dx[d];
            }
        } else {
            aw = 0;
            for (d = 0; d < dim; d++) {
                adwdx[d] = 0;
            }
        }
    }
}
