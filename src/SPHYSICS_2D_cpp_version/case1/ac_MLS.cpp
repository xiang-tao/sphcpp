#pragma once
#include "head.h"
#include <iostream>
void ac_MLS(str* vari)
{
    void pre_cellij_MLS(str * vari, int& j1, int& j2, int& kind_p1, int& ini_kind_p2);
    void pre_self_MLS(str * vari, int& j1, int& kind_p1, int& ini_kind_p2);

    for (int kind_p1 = 0; kind_p1 <= 1; kind_p1++) {
        int ini_kind_p2 = (kind_p1 + 1) % 2;
        for (int ly = 0; ly < vari->ncy; ly++) {
            for (int lx = 0; lx < vari->ncx; lx++) {
                int j1 = lx + ly * vari->ncx;
                if (vari->nc[j1][kind_p1] > 0) {
                    int lx2 = lx + 1;
                    if (lx2 < vari->ncx) {
                        int j2 = j1 + 1;
                        pre_cellij_MLS(vari, j1, j2, kind_p1, ini_kind_p2);
                    }
                    int ly2 = ly + 1;
                    if (ly2 < vari->ncy) {
                        int j2 = j1 + vari->ncx;
                        pre_cellij_MLS(vari, j1, j2, kind_p1, ini_kind_p2);
                        lx2 = lx + 1;
                        if (lx2 > 1) {
                            int j2 = j1 + vari->ncx - 1;
                            pre_cellij_MLS(vari, j1, j2, kind_p1, ini_kind_p2);
                        }
                        lx2 = lx + 1;
                        if (lx2 < vari->ncx) {
                            int j2 = j1 + vari->ncx + 1;
                            pre_cellij_MLS(vari, j1, j2, kind_p1, ini_kind_p2);
                        }
                    }
                }
            }
        }
        for (int j1 = 0; j1 < vari->nct; j1++) {
            if (vari->nc[j1][kind_p1] > 0) {
                pre_self_MLS(vari, j1, kind_p1, ini_kind_p2);
            }
        }
    }
}
