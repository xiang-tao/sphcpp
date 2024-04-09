#include "NS_pressure.cpp"
#include "av_vel.cpp"
#include "density_sum.cpp"
#include "direct_find.cpp"
#include "external_force.cpp"
#include "input.cpp"
#include "internal_force.cpp"
#include "kernel.cpp"
#include "output.cpp"
#include "output_v.cpp"
#include "particle.cpp"
#include "single_fluid.cpp"
#include "single_step.cpp"
#include "time_integration.cpp"
#include "virt_part.cpp"
#include "viscous_force.cpp"

#include <iostream>

int main()
{
    void particle(str * vari);
    void virt_part(str * vari);
    void input(double* time, int* timestep, str* vari);

    //void leap_frog(double* time, int* timestep, str* vari);
    void time_integration(double* time, int* timestep, str* vari);
    void virt_part(str * vari);

    int timestep;
    double time;

    str* vari = new str;

    if (!input_data) {
        particle(vari);
    }
    input(&time, &timestep, vari);
    
    if (virtual_part) {
        virt_part(vari);
    }
    time_integration(&time, &timestep, vari);
    // virt_part(vari);
    std::cout << vari->ntotal << " " << vari->nvirt << std::endl;

    return 0;
}
