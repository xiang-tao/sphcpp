#include "LU.cpp"
#include "ac.cpp"
#include "ac_MLS.cpp"
#include "cellij.cpp"
#include "check_limits.cpp"
#include "correct.cpp"
#include "densityFilter_MLS.cpp"
#include "divide.cpp"
#include "equation_of_state.cpp"
#include "getdata.cpp"
#include "ini_divide.cpp"
#include "input.cpp"
#include "keep_list.cpp"
#include "kernel.cpp"
#include "kernel_correction.cpp"
#include "output.cpp"
#include "particle.cpp"
#include "pre_cellij_MLS.cpp"
#include "pre_self_MLS.cpp"
#include "read.cpp"
#include "self.cpp"
#include "single_step.cpp"
#include "variable_time_step.cpp"
#include "virt_part.cpp"
#include "viscosity.cpp"
#include "writevtk.cpp"
#include <iostream>

int main()
{
    void particle(str * vari);
    void read(str * vari);
    void getdata(str * vari);
    void keep_list(str * vari);
    void ini_divide(str * vari, int kind_p);
    void divide(str * vari, int n_start, int n_end, int kind_p);
    void virt_part(str * vari);
    void input(str * vari);
    void single_step(str * vari);
    void densityFilter_MLS(str * vari);
    void writevtk(str * vari, const int number, const int cc = 0);

    int timestep = 0;
    double time = 0.0;
    int ngrab = 0;
    int output = 0;

    str* vari = new str;

    //自己生成的粒子数据
    if (!input_data) {
        particle(vari); //获取流动位置信息
    }
    input(vari);     //获取计算流动粒子的一些初始数据
    virt_part(vari); //获取虚粒子的位置及虚粒子的初始数据

    //sphyscis生成的初始数据
    // read(vari);

    getdata(vari);
    ini_divide(vari, 0);
    divide(vari, vari->ntotal, vari->ntotal + vari->nvirt, 0);
    keep_list(vari);

    //主循环
    while (time < tmax) {
        vari->visc_dt = 0.0;
        //设置每0.02s输出粒子属性相关信息到文件，用于可视化out=0.02,ngrab表示输出文件数量
        if (time - outt * ngrab >= outt) {
            output = 1;
            ngrab += 1;
        } else {
            output = 0;
        }
        single_step(vari);
        time += vari->new_dt;
        timestep += 1;
        if (timestep % 30 == 0) {
            densityFilter_MLS(vari);
        }
        if (vari->new_dt < 1e-8) {
            std::cout << "时间步长太短：" << std::endl;
            std::cout << "dt=" << vari->new_dt << std::endl;
            std::cout << "step=" << timestep << std::endl;
            exit(0);
        }
        if (output == 1) {
            writevtk(vari, ngrab, 1); //ngrab用于文件的编号,1表示输出虚粒子一起,0表示不含虚粒子输出
            std::cout << "time=" << time << "  "
                      << "dt=" << vari->new_dt << "  "
                      << "step=" << timestep << std::endl;
        }
    }
    std::cout << "撞击出计算域的粒子有" << vari->ncases << "个." << std::endl;

    return 0;
}
