#pragma once
#include <math.h>
#include <stdio.h>
#define tot_maxn 100000 //粒子最大数量
#define nct_max 30000   //列表最大数量
#define nplink_max 120  //单个列表中粒子最大数量
#define dim 2
#define num_FB_max 21
#define np_max 12000 //大于 作用粒子数量的最大值
#define pi 3.14159265358979323846
#define twopi 2 * 3.14159265358979323846

// #define dt 0.0001
#define tmax 3.0
#define outt 0.02
#define eps 0.5
#define grx 0.0
#define gry -9.81
#define IBC 2
#define CFL_number 0.2
#define viscos_val 0.3 //粘度系数

// #define mp 40
// #define np 40
#define xl 1.0
#define yl 2.0

#define input_data false
#define virtual_part true

struct str {
    int ntotal;
    int nvirt;
    int ncases;                                   //记录越界粒子数量
    double wab, frx, fry, frxi, frxj, fryi, fryj; //核函数相关值
    double Awen, Bwen, adh;
    double new_dt;
    double B;
    int nstep_DBC;
    double ddt_p, ddt_c, min_dt;
    double visc_dt; //=max abs(v_ab*r_ab/abs(r_ab),方便用于varialbe_time_step中计算)
    double eta, eta2;
    double two_h, four_h, six_h, h_over_100, h_over_1000, h2, fourh2;
    double xmin, xmax, ymin, ymax;
    double xmax_container, xmin_container, ymin_container, ycontrol;
    double ymax_ini, xtrash, ytrash;
    double one_over_h, one_over_2h;
    double ncx, ncy, nct, ncy_ini, nct_ini;
    double hsml;

    double x[dim][tot_maxn];
    double xo[dim][tot_maxn];
    double xdot[dim][tot_maxn];
    double xcor[dim][tot_maxn];
    double v[dim][tot_maxn];
    double vx[dim][tot_maxn]; //XSPH
    double vo[dim][tot_maxn];
    double vdot[dim][tot_maxn];
    double av[dim][tot_maxn];
    double p[tot_maxn];
    double po[tot_maxn];
    double pr[tot_maxn];
    double rho[tot_maxn];
    double rdot[tot_maxn];
    double one_over_rho[tot_maxn];
    double rhoo[tot_maxn];
    double ar[tot_maxn];
    // double rhoij[tot_maxn];
    double mass[tot_maxn];
    double pvol[tot_maxn];
    int itype[tot_maxn];
    double cs[tot_maxn]; //声速
    int nc[nct_max][2];  //记录每个列表中粒子数量
    int keep_nc[nct_max];
    int ibox[nct_max][2][nplink_max];
};
