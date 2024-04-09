#pragma once
#include "head.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

void particle(str *vari)

{
	int i, j;

	vari->ntotal = 0;

	for (i = 1; i <= nx; i++)   
	{
		for (j = 1; j <= ny; j++) 
		{
			
			vari->x[0][vari->ntotal] =xmin+ h*(i - 1);
			vari->x[1][vari->ntotal] = ymin+h*(j - 1);
			vari->ntotal = vari->ntotal + 1;
			vari->itype[vari->ntotal] = 1;
		}
	}
		        ofstream dataFile;
	dataFile.open("ordcoor.txt", ofstream::app);
	fstream file("ordcoor.txt", ios::out);
            //output(*timestep, *time, vari);
            for (int i = 0; i < vari->ntotal; i++) {
                dataFile << vari->x[0][i] << " " << vari->x[1][i] << endl;
            }
            dataFile.close();

}
