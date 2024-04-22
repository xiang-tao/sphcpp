#pragma once
#include "head.h"
void recover_list(str* vari)
{
    for (int i = 0; i < vari->nct; i++) {
        // vari->keep_nc[i] = vari->nc[i][0];
        vari->nc[i][0] = vari->keep_nc[i];
    }
}
