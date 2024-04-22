#pragma once
#include "head.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;
void output(str* vari, const string& name)
{
    ofstream dataFile;
    dataFile.open(name, ofstream::app);
    fstream file(name, ios::out);
    //output(*timestep, *time, vari);
    int tot = vari->ntotal + vari->nvirt;
    for (int i = 0; i < tot; i++) {
        dataFile << vari->x[0][i] << "  " << vari->x[1][i] << "  "
                 << vari->v[0][i] << "  " << vari->v[1][i] << "  "
                 << vari->rho[i] << "  " << vari->p[i] << "  "
                 << vari->mass[i] << endl;
    }
    dataFile.close();
}
