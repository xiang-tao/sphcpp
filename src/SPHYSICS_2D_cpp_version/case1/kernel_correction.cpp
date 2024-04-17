#pragma once
#include "head.h"
void kernel_correction(str* vari)
{
    vari->frxi = vari->frx;
    vari->fryi = vari->fry;
    vari->frxj = vari->frx;
    vari->fryj = vari->fry;
}
