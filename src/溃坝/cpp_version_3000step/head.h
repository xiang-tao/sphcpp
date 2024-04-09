#pragma once
#include <math.h>
#include <stdio.h>
//粒子间距dx和粒子数量怎么写到头文件?
#define tot_maxn 30000
#define dim 2
#define maxiac 300000 //大于 作用粒子数量的最大值
#define pi 3.14159265358979323846
#define skf 4
#define kapa 2     //?????
#define eta 1.0e-3 //4.0/3.0

// #define h 0.75 // 0.375
#define dt 0.001

#define nmaxstep 3001 //150000
#define save_step 100

// #define mp 40
// #define np 40
#define xl 1.0
#define yl 2.0

#define input_data false
#define virtual_part true

struct str {
    int ntotal;
    int nvirt;
    int niac;

    double x[dim][tot_maxn];
    double v[dim][tot_maxn];
    double av[dim][tot_maxn];
    double ds[dim][tot_maxn];
    double f[tot_maxn];
    double s[tot_maxn];
    double p[tot_maxn];
    double T[tot_maxn];
    double e[tot_maxn];
    double rho[tot_maxn];
    double drho[tot_maxn];
    // double rhoij[tot_maxn];
    double mass[tot_maxn];
    double hsml[tot_maxn];
    int itype[tot_maxn];
    double c[tot_maxn]; //声速

    double txx[tot_maxn];
    double tyy[tot_maxn];
    double txy[tot_maxn];

    double x0[dim][tot_maxn];
    double v0[dim][tot_maxn];
    double drho0[tot_maxn];
    double vtemp[dim][tot_maxn];

    double dvxdt[dim][tot_maxn];
    double dedt[tot_maxn];

    int pair_i[maxiac];
    int pair_j[maxiac];
    double w[maxiac];
    double dwdx[dim][maxiac];
};
