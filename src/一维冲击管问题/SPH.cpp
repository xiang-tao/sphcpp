#include "art_visc.cpp"
#include "density_sum.cpp"
#include "direct_find.cpp"
#include "input.cpp"
#include "internal_force.cpp"
#include "kernel.cpp"
#include "output_e.cpp"
#include "output_p.cpp"
#include "output_rho.cpp"
#include "output_v.cpp"
#include "output_x.cpp"
#include "single_step.cpp"
#include "time_integration.cpp"

#include <iostream>

int main()
{
    void input(double* time, int* timestep, str* vari);

    //void leap_frog(double* time, int* timestep, str* vari);
    void time_integration(double* time, int* timestep, str* vari);

    int timestep;
    double time;

    str* vari = new str;

    input(&time, &timestep, vari);
    time_integration(&time, &timestep, vari);

    return 0;
}
