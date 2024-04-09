#include "sph/sphobject.h"
#include <iostream>
using namespace std;
const int dim = 10;
const double kk = 5.0, span = 0.01;
double aa[dim];
double bbx[dim][dim], bby[dim][dim];
double ccx[dim][dim][dim], ccy[dim][dim][dim], ccz[dim][dim][dim];
const double rho = 0.1, ma = rho * span, mb = rho * span * span, mc = rho * span * span * span;
void CreatParticle()
{
    for (int i = 0; i < dim; i++) {
        aa[i] = kk + i * span;
        for (int j = 0; j < dim; j++) {
            bbx[i][j] = aa[i];
            bby[i][j] = kk + j * span;
            for (int k = 0; k < dim; k++) {
                ccx[i][j][k] = bbx[i][j];
                ccy[i][j][k] = bby[i][j];
                ccz[i][j][k] = kk + k * span;
            }
        }
    }
}
//验证核函数归一性（gy）
double onegy()
{
    CreatParticle();
    double fx = 0.0, xx = kk + 5 * span;
    for (int i = 0; i < dim; i++) {
        fx += (ma / rho) * LucyQuartickernel(xx, aa[i], 3 * span);
    }
    return fx;
}
double twogy()
{
    CreatParticle();
    double fx = 0.0, xx = kk + 5 * span;
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            fx += (mb / rho) * LucyQuartickernel(xx, xx, bbx[i][j], bby[i][j], 3 * span);
        }
    }
    return fx;
}
double threegy()
{
    CreatParticle();
    double fx = 0.0, xx = kk + 5 * span;
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            for (int k = 0; k < dim; k++) {
                fx += (mc / rho) * LucyQuartickernel(xx, xx, xx, ccx[i][j][k], ccy[i][j][k], ccz[i][j][k], 3 * span);
            }
        }
    }
    return fx;
}
//验证筛选性(ss)
double oness()
{
    CreatParticle();
    double fx = 0.0, xx = kk + 5 * span;
    for (int i = 0; i < dim; i++) {
        fx += aa[i] * aa[i] * (ma / rho) * LucyQuartickernel(xx, aa[i], 3 * span);
    }
    return fx;
}
//验证导数.....

int main()
{
    double xx = kk + 5 * span;
    double f1 = onegy();
    double f2 = twogy();
    double f3 = threegy();
    double ss1 = oness();
    cout << f1 << endl;
    cout << f2 << endl;
    cout << f3 << endl;
    cout << ss1 << endl;
    cout << xx * xx << endl;
    return 0;
}
