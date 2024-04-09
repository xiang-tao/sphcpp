#pragma once
#include "head.h"
#include <string>
using namespace std;

void particle(str* vari)

{
    void output(str * vari, const string& name, int cc = 0);

    vari->ntotal = 0;
    double dx = xl / mp;
    double dy = yl / np;
    for (int i = 0; i < mp; i++) {
        for (int j = 0; j < np; j++) {
            vari->x[0][vari->ntotal] = i * dx + dx / 2;
            vari->x[1][vari->ntotal] = j * dy + dy / 2;
            vari->ntotal = vari->ntotal + 1;
            vari->itype[vari->ntotal] = 2;
        }
    }
    output(vari, "coor.txt");
}
