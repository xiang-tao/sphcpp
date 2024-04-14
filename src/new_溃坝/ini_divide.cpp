#pragma once
#include "head.h"
void ini_divide(str* vari, int kind_p)
{
    for (int i = 0; i < vari->nct; i++) {
        vari->nc[i][kind_p] = 0;
        for (int k = 0; k < nplink_max; k++) {
            vari->ibox[i][kind_p][k] = 0;
        }
    }
}
