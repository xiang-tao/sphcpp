#pragma once
#include "head.h"

void single_fluid(str *vari)
{
	int i, j, k, d;
	double dvx[dim];
	double temp_dvx[dim];
	double temp_dedt;
	double dedti,dedtj;
	double con_dedti;
	double con_dedtj;
	double dx[dim];
	double rr;
	double dT;
	

	for (k = 0; k < vari->niac; k++) 
	{
		i = vari->pair_i[k];
		j = vari->pair_j[k];

		rr = 0.0;    // ？？？？？？？？？？？？1
		for (d = 0; d < dim; d++)
		{
			dvx[d] = vari->v[d][j] - vari->v[d][i];
			dx[d] = vari->x[d][j] - vari->x[d][i];
			rr = rr + dx[d] * dx[d];
			
		}

		dT = vari->T[j] - vari->T[i];

		/////粘性应力项

		temp_dvx[0] = (vari->txx[i] / pow(vari->rho[i], 2) + vari->txx[j] / pow(vari->rho[j], 2))* vari->dwdx[0][k]
					+ (vari->txy[i] / pow(vari->rho[i], 2) + vari->txy[j] / pow(vari->rho[j], 2))* vari->dwdx[1][k];


		temp_dvx[1] = (vari->txy[i] / pow(vari->rho[i], 2) + vari->txy[j] / pow(vari->rho[j], 2))* vari->dwdx[0][k]
					+ (vari->tyy[i] / pow(vari->rho[i], 2) + vari->tyy[j] / pow(vari->rho[j], 2))* vari->dwdx[1][k];

		for (d = 0; d < dim; d++)
		{
			vari->dvxdt[d][i] = vari->dvxdt[d][i] + vari->mass[j] * temp_dvx[d];
			vari->dvxdt[d][j] = vari->dvxdt[d][j] - vari->mass[i] * temp_dvx[d];
		}

				
		temp_dedt = temp_dvx[0] * dvx[0] + temp_dvx[1] * dvx[1];
		
		
		dedti = 0.5*vari->mass[j] * temp_dedt;
		dedtj = 0.5*vari->mass[i] * temp_dedt;

		con_dedti = 2 * thermal * vari->mass[j] * (dx[0] * vari->dwdx[0][k] + dx[1] * vari->dwdx[1][k])*dT
			/ (vari->rho[i] * vari->rho[j] * (rr + 0.01*vari->hsml[i] * vari->hsml[i]));

		con_dedtj = -2 * thermal * vari->mass[i] * (dx[0] * vari->dwdx[0][k] + dx[1] * vari->dwdx[1][k])*dT
			/ (vari->rho[i] * vari->rho[j] * (rr + 0.01*vari->hsml[j] * vari->hsml[j]));

		vari->dedt[i] = vari->dedt[i] + dedti + con_dedti;
		vari->dedt[j] = vari->dedt[j] + dedtj + con_dedtj;

	}
}
