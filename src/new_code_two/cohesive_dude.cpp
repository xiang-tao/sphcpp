#pragma once
#include "head.h"

void cohesive_dude(str *vari, double (&ducp)[dim][tot_maxn], double (&decp)[tot_maxn])
{
	void direct_find(str *vari, int m);

	int i, j, k,d;
	double dvx[dim];

	direct_find(vari, 0);//重新计算了光滑长度，niac,pair_i,pair_j，wij(w),dwdx，见公式17下面一段英文描述

	for (i = 0; i < vari->ntotal; i++)
	{
		ducp[0][i] = 0.0;
		ducp[1][i] = 0.0;
		decp[i] = 0.0;
	}

	for (k = 0; k < vari->niac; k++)
	{
		i = vari->pair_i[k];
		j = vari->pair_j[k];


		for (d = 0; d < dim; d++)
		{
			ducp[d][i] = ducp[d][i] + 2 * a*vari->mass[j] * vari->dwdx[d][k];//eq16
			ducp[d][j] = ducp[d][j] - 2 * a*vari->mass[i] * vari->dwdx[d][k];
		}

		for (d = 0; d < dim; d++)
		{
			dvx[d] = vari->v[d][j] - vari->v[d][i];
		}

		decp[i] = decp[i] + a * vari->mass[j] * (dvx[0] * vari->dwdx[0][k] + dvx[1] * vari->dwdx[1][k]);//eq17
		decp[j] = decp[j] + a * vari->mass[i] * (dvx[0] * vari->dwdx[0][k] + dvx[1] * vari->dwdx[1][k]);

	}

	for (i = 0; i < vari->ntotal; i++)
	{
		for (d = 0; d < dim; d++)
		{
			vari->dvxdt[d][i] = vari->dvxdt[d][i] + ducp[d][i];
		}
		vari->dedt[i] = vari->dedt[i] + decp[i];
	}


}
