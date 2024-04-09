#pragma once
#include "head.h"

void viscous_force(str *vari)
{
	int i, j, k, d;

	double dvx[dim];
	double hxx;
	double hyy;
	double hxy;
	double rhoij;

	for (i = 0; i < vari->ntotal; i++)
	{
		vari->txx[i] = 0.0;
		vari->tyy[i] = 0.0;
		vari->txy[i] = 0.0;
	}

	for (k = 0; k < vari->niac; k++)
	{
		i = vari->pair_i[k];
		j = vari->pair_j[k];

		for (d = 0; d < dim; d++)
		{
			dvx[d] = vari->v[d][j] - vari->v[d][i];
		}
		rhoij = (vari->rho[i] + vari->rho[j]) / 2.0;

		hxx = 2.0 * miu*dvx[0] * vari->dwdx[0][k] + (miu2 - miu)*(dvx[0] * vari->dwdx[0][k] + dvx[1] * vari->dwdx[1][k]);
		hxy = miu*(dvx[0] * vari->dwdx[1][k] + dvx[1] * vari->dwdx[0][k]);
		hyy = 2.0 * miu*dvx[1] * vari->dwdx[1][k] + (miu2 - miu)*(dvx[0] * vari->dwdx[0][k] + dvx[1] * vari->dwdx[1][k]);

		////////////////////////////////////////Õ³ÐÔÓ¦Á¦
		vari->txx[i] = vari->txx[i] + vari->mass[j] * hxx / rhoij;
		vari->txx[j] = vari->txx[j] + vari->mass[i] * hxx / rhoij;

		vari->txy[i] = vari->txy[i] + vari->mass[j] * hxy / rhoij;
		vari->txy[j] = vari->txy[j] + vari->mass[i] * hxy / rhoij;

		vari->tyy[i] = vari->tyy[i] + vari->mass[j] * hyy / rhoij;
		vari->tyy[j] = vari->tyy[j] + vari->mass[i] * hyy / rhoij;

	}

}
