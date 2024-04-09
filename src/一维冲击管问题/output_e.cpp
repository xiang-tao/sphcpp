#pragma once
#include "head.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;
void output_e(str* vari, const string& name, int cc = 0)
{
    ofstream dataFile;
    dataFile.open(name, ofstream::app);
    fstream file(name, ios::out);
    //output(*timestep, *time, vari);
    if (cc == 1) {
        for (int i = 0; i < vari->ntotal + vari->nvirt; i++) {
            dataFile << vari->e[i] << endl;
        }
    } else {
        for (int i = 0; i < vari->ntotal; i++) {
            dataFile << vari->e[i] << endl;
        }
    }
    dataFile.close();
}
