#pragma once
#include "head.h"
#include <iostream>
using namespace std;

void direct_find(str* vari)
{
    void kernel(double r, double dx[dim], double mhsml, double* aw, double adwdx[dim]);

    int i, j, d;
    double mhsml;      //i,j粒子平均后的光滑粒子长度
    double driac[dim]; //扮演了空间中各个方向轴粒子的距离
    double r;          //粒子间欧式距离
    double aw;         //核函数值
    double adwdx[dim]; //x,y方向核函数的偏导数
    double dria;       //两粒子之间的欧式距离平方

    vari->niac = 0;

    for (i = 0; i < vari->ntotal + vari->nvirt; i++) //流体粒子与所有粒子的相互作用对
    {
        for (j = i + 1; j < vari->ntotal + vari->nvirt; j++) {
            mhsml = (vari->hsml[i] + vari->hsml[j]) / 2;
       

        dria = 0.0;

        for (d = 0; d < dim; d++) {
            driac[d] = vari->x[d][i] - vari->x[d][j];
            dria = dria + driac[d] * driac[d];
        }

        if (sqrt(dria) <= kapa * mhsml) {
            if (vari->niac < maxiac) {
                vari->niac = vari->niac + 1;
                vari->pair_i[vari->niac] = i; //第niac个作用对的i粒子
                vari->pair_j[vari->niac] = j; //第niac个作用对的j粒子
                r = sqrt(dria);

                kernel(r, driac, mhsml, &aw, adwdx);
                vari->w[vari->niac] = aw; //第niac个粒子对的核函数值w_ij
                for (d = 0; d < dim; d++) {
                    vari->dwdx[d][vari->niac] = adwdx[d]; //第niac个粒子对应的偏导数值partail W_ij/parital x_i
                }
            } else {
                printf("\n>>>ERROR<<<	:	Too many interactions");
            }
        }}
    }
}
