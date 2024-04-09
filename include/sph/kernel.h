#pragma once
#include "Constants.h"
#include <math.h>
/*
notes:
计算核函数W(R,h)及其导函数的值，其中h称为光滑长度（核宽度），
R=(xi-xj)/h,输入已知参数（如xi,xj,h），计算W的值
 */
namespace SPHCPP {
namespace SphKernel {
    //Lucy在1977年提出的四次核函数
    //input:R
    //output:W/alpha
    double LucyQuartickernel(const double R)
    {
        if (R > 1) {
            return 0.0;
        } else {
            double RR = R * R;
            return 1.0 - (6.0 - 8.0 * R + 3.0 * RR) * RR;
        }
    }

    double LucyQuartickernel(const double r, const double h)
    {
        if (r > h) {
            return 0.0;
        } else {
            double R = r / h;
            double RR = R * R;
            return 1.0 - (6.0 - 8.0 * R + 3.0 * RR) * RR;
        }
    }

    //一维
    double LucyQuartickernel(const double x1, const double x2, const double h)
    {
        double r = abs(x1 - x2);
        double alpha = 5.0 / (4.0 * h);
        return alpha * LucyQuartickernel(r, h);
    }

    //二维
    double LucyQuartickernel(const double x1, const double y1, const double x2, const double y2, const double h)
    {
        double r = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
        double alpha = 5.0 / (Constant::pi * h * h);
        return alpha * LucyQuartickernel(r, h);
    }
    //三维
    double LucyQuartickernel(const double x1, const double y1, const double z1,
        const double x2, const double y2, const double z2, const double h)
    {
        double r = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) + (z2 - z1) * (z2 - z1));
        double alpha = 105.0 / (16.0 * Constant::pi * h * h * h);
        return alpha * LucyQuartickernel(r, h);
    }
    //下面计算导数
    //计算导数公共部分，称为核心。理论见b站
    double LucyQuarticDerivativeCore(double R)
    {
        if (R > 1.0) {
            return 0.0;
        } else {
            return 12.0 * (-1.0 + 2.0 * R - R * R);
        }
    }
    double LucyQuarticDerivative(const double r, const double h)
    {
        if (r > h) {
            return 0.0;
        } else {
            double R = r / h;
            return 12.0 * (-1.0 + 2.0 * R - R * R) / (h * h);
        }
    }
    double LucyQuarticDerivative(const double x1, const double x2, const double h)
    {
        double r = abs(x2 - x1);
        double alpha = 5.0 / (4.0 * h);
        return alpha * LucyQuarticDerivative(r, h);
    }
    double LucyQuarticDerivative(const double x1, const double y1, const double x2, const double y2, const double h)
    {
        double r = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
        double alpha = 5.0 / (Constant::pi * h * h);
        return alpha * LucyQuarticDerivative(r, h);
    }
    double LucyQuarticDerivative(const double x1, const double y1, const double z1,
        const double x2, const double y2, const double z2, const double h)
    {
        double r = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) + (z2 - z1) * (z2 - z1));
        double alpha = 105.0 / (16 * Constant::pi * h * h * h);
        return alpha * LucyQuarticDerivative(r, h);
    }
}
}
