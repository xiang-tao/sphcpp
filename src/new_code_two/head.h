#pragma once
#include <math.h>
#include <stdio.h>
//粒子间距dx和粒子数量怎么写到头文件?
#define tot_maxn 30000
#define sub_maxn 1000 //每个网格内的粒子数目
#define cell_xmaxn 100
#define cell_ymaxn 100
#define dim 2
#define maxiac 300000 //大于 作用粒子数量的最大值
#define pi 3.14159265358979323846
#define skf 2
#define kapa 2  //?????
#define eta 2.0 //4.0/3.0
#define g 9.8

#define a 2.0
#define b 0.5
#define kc 1.0      //Boltzmann’s constant
#define thermal 5.0 //conduction
#define miu 1.0     //第一粘性系数
#define miu2 0.1    //第二粘性系数

#define h 0.75 // 0.375
#define dt 0.005

#define nmaxstep 1001 //150000
#define save_step 1000

#define nx 30
#define ny 30
#define xmin -10.875
#define ymin -10.875

#define input_data false

#define cell_scale 1.5

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
    double rhoij[tot_maxn];
    double mass[tot_maxn];
    double hsml[tot_maxn];
    double hsml2[tot_maxn];
    int itype[tot_maxn];

    double txx[tot_maxn];
    double tyy[tot_maxn];
    double txy[tot_maxn];

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

    double bb[3][sub_maxn];
    double cc[3][sub_maxn];

    int ngrid[dim];
    int grid[cell_xmaxn][cell_ymaxn];
    int cell_mark[cell_xmaxn][cell_ymaxn][sub_maxn];
};
