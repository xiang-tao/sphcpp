#pragma once
#include "head.h"
void single_step(str *vari)
{
	void direct_find(str *vari,int m);
	void density_sum(str *vari);
	void viscous_force(str *vari);
	void single_fluid(str *vari);
	void cohesive_dude(str *vari, double (&ducp)[dim][tot_maxn], double (&decp)[tot_maxn]);
	void NS_pressure(str *vari);


	int i;
	double ducp[dim][tot_maxn];
	double decp[tot_maxn];
	
	for (i = 0; i < vari->ntotal; i++)
	{
		vari->dvxdt[0][i] = 0.0;
		vari->dvxdt[1][i] = 0.0;  //体力项
		vari->dedt[i] = 0.0;
	}

	cohesive_dude(vari, ducp, decp);//计算内聚力，公式16,17


	direct_find(vari, 1);
	density_sum(vari);


	for (i = 0; i < vari->ntotal; i++)
	{
		vari->T[i] = (vari->e[i] + a* vari->rho[i]) / kc;//eq8
		//vari->p[i] = vari->rho[i] * kc*vari->T[i] / (1 - vari->rho[i] * b) - a*vari->rho[i] * vari->rho[i];
		vari->p[i] = (vari->rho[i] * kc*vari->T[i]) / (1 - vari->rho[i] * b);//eq7
		
	}

	

	///////////////////////////////////////////////////////////////////////////
	NS_pressure(vari);

	viscous_force(vari);


	single_fluid(vari);



	
}
