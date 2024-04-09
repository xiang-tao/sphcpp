#pragma once
#include "head.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;
void output_v(str* vari, const string& name, int cc = 0)
{
    ofstream dataFile;
    dataFile.open(name, ofstream::app);
    fstream file(name, ios::out);
    //output(*timestep, *time, vari);
    if (cc == 1) {
        if (dim == 1) {
            for (int i = 0; i < vari->ntotal + vari->nvirt; i++) {
                dataFile << vari->v[0][i] << endl;
            }
        }
        if (dim == 2) {
            for (int i = 0; i < vari->ntotal + vari->nvirt; i++) {
                dataFile << vari->v[0][i] << " " << vari->v[1][i] << endl;
            }
        }
        if (dim == 3) {
            for (int i = 0; i < vari->ntotal + vari->nvirt; i++) {
                dataFile << vari->v[0][i] << " " << vari->v[1][i] << " " << vari->v[2][i] << endl;
            }
        }
    } else {
        if (dim == 1) {
            for (int i = 0; i < vari->ntotal; i++) {
                dataFile << vari->v[0][i] << endl;
            }
        }
        if (dim == 2) {
            for (int i = 0; i < vari->ntotal; i++) {
                dataFile << vari->v[0][i] << " " << vari->v[1][i] << endl;
            }
        }
        if (dim == 3) {
            for (int i = 0; i < vari->ntotal; i++) {
                dataFile << vari->v[0][i] << " " << vari->v[1][i] << " " << vari->v[2][i] << endl;
            }
        }
    }
    dataFile.close();
}
