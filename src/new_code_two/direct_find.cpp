#pragma once
#include "head.h"
#include <iostream>
using namespace std;

void direct_find(str* vari, int m)
{
    void kernel(double r, double dx[dim], double mhsml, double* aw, double adwdx[dim]);

    int i, j, d;
    double mhsml;      //i,j����ƽ����Ĺ⻬���ӳ���
    double driac[dim]; //�����˿ռ��и������������ӵľ���
    double r;          //���Ӽ�ŷʽ����
    double aw;         //�˺���ֵ
    double adwdx[dim]; //x,y����˺�����ƫ����
    double dria;       //������֮���ŷʽ����ƽ��

    vari->niac = 0;

    for (i = 0; i < vari->ntotal; i++) //�����������������ӵ��໥���ö�
    {
        for (j = i + 1; j < vari->ntotal; j++) {
            if (m == 1) {
                mhsml = (vari->hsml[i] + vari->hsml[j]) / 2;
            }
            if (m == 0) {
                mhsml = (vari->hsml2[i] + vari->hsml2[j]) / 2;
            }

            // driac[0] = vari->x[0][i] - vari->x[0][j];
            // dria = driac[0] * driac[0];
            // driac[0] = 0.0;
            dria = 0.0;

            for (d = 0; d < dim; d++) {
                driac[d] = vari->x[d][i] - vari->x[d][j];
                dria = dria + driac[d] * driac[d];
            }

            if (sqrt(dria) <= kapa * mhsml) {
                if (vari->niac < maxiac) {
                    vari->niac = vari->niac + 1;
                    vari->pair_i[vari->niac] = i; //��niac�����öԵ�i����
                    vari->pair_j[vari->niac] = j; //��niac�����öԵ�j����
                    r = sqrt(dria);

                    kernel(r, driac, mhsml, &aw, adwdx);
                    vari->w[vari->niac] = aw; //��niac�����ӶԵĺ˺���ֵw_ij
                    for (d = 0; d < dim; d++) {
                        vari->dwdx[d][vari->niac] = adwdx[d]; //��niac�����Ӷ�Ӧ��ƫ����ֵpartail W_ij/parital x_i
                    }
                } else {
                    printf("\n>>>ERROR<<<	:	Too many interactions");
                }
            }
        }
    }
}
