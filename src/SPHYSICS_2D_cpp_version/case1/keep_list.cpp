#pragma once
#include "head.h"
void keep_list(str* vari)
{
    for (int i = 0; i < vari->nct; i++) {
        vari->keep_nc[i] = vari->nc[i][0];
    }
}
