#pragma once
#include <math.h>
#include <stdio.h>
//粒子间距dx和粒子数量怎么写到头文件?
#define tot_maxn 30000
#define dim 1
#define maxiac 300000 //大于 作用粒子数量的最大值
#define pi 3.14159265358979323846
#define skf 4
#define kapa 2 //?????

#define dt 0.005

#define nmaxstep 41 //150000
#define save_step 40

#define input_data false

struct str {
    int ntotal;
    int nvirt;
    int niac;

    double x[dim][tot_maxn];
    double v[dim][tot_maxn];
    double ds[dim][tot_maxn];
    double f[tot_maxn];
    double s[tot_maxn];
    double p[tot_maxn];
    double T[tot_maxn];
    double e[tot_maxn];
    double rho[tot_maxn];
    double mass[tot_maxn];
    double hsml[tot_maxn];
    int itype[tot_maxn];
    double c[tot_maxn];

    double x0[dim][tot_maxn];
    double v0[dim][tot_maxn];
    double e0[tot_maxn];
    double vtemp[dim][tot_maxn];

    double dvxdt[dim][tot_maxn];
    double dedt[tot_maxn];

    int pair_i[maxiac];
    int pair_j[maxiac];
    double w[maxiac];
    double dwdx[dim][maxiac];
};
