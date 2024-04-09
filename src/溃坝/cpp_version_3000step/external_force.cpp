#pragma once
#include "head.h"
#include <iostream>
void external_force(str* vari)
{
    double g = -9.8;
    for (int i = 0; i < vari->ntotal + vari->nvirt; i++) {
        vari->dvxdt[1][i] += g;
    }
}
