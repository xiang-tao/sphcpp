#include "NS_pressure.cpp"
#include "cohesive_dude.cpp"
#include "direct_find.cpp"
#include "head.h"
#include "input.cpp"
#include "kernel.cpp"
//#include "leap_frog.cpp"
#include "particle.cpp"
#include "single_fluid.cpp"
#include "single_step.cpp"
#include "viscous_force.cpp"
//#include "output.cpp"
#include "time_integration.cpp"
#include "density_sum.cpp"
#include <iostream>

int main()
{
    void particle(str * vari);

    void input(double* time, int* timestep, str* vari);

    //void leap_frog(double* time, int* timestep, str* vari);
    void time_integration(double *time, int *timestep, str *vari);

    void output(int timestep, double time, str* vari);

    ////////////////////////////////////////////////////////

    int timestep;
    double time;

    str* vari = new str;

    if (!input_data) {
        particle(vari);
    }
    input(&time, &timestep, vari);

    time_integration(&time, &timestep, vari);

    //output(timestep, time, vari);
    std::cout << vari->ntotal << std::endl;
    return 0;
}
